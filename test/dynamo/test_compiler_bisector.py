# Owner(s): ["module: dynamo"]

import unittest
from contextlib import contextmanager
from importlib import import_module

import torch
import torch._prims_common as utils
from torch._dynamo.test_case import TestCase
from torch._inductor import config
from torch._inductor.bisect_helper import BisectionManager
from torch.testing._internal.inductor_utils import HAS_CUDA


aten = torch.ops.aten

requires_cuda = unittest.skipUnless(HAS_CUDA, "requires cuda")

f32 = torch.float32
i64 = torch.int64
i32 = torch.int32


@requires_cuda
class TestCompilerBisector(TestCase):
    def test_bad_decomp(self):
        mod = import_module("torch._inductor.compile_fx")

        def bad_exp_decomp(self, rate=1, generator=None):
            assert generator is None
            torch._check(
                not utils.is_complex_dtype(self.dtype)
                and not utils.is_integer_dtype(self.dtype)
                and not utils.is_boolean_dtype(self.dtype),
                lambda: f"Exponential distribution is a continuous probability distribution. \
                dtype must be a floating point but you specified {self.dtype}",
            )
            torch._check(
                rate > 0.0,
                lambda: f"exponential_ expects lambda > 0.0, but found lambda={rate}",
            )
            return torch.rand_like(self) * float("nan")

        @contextmanager
        def patch_exp_decomp():
            from torch._inductor.compile_fx import select_decomp_table as old_decomp

            def get_decomp():
                out = old_decomp()
                out = out.copy()
                out[aten.exponential.default] = bad_exp_decomp
                return out

            torch._inductor.compile_fx.select_decomp_table = get_decomp
            try:
                yield

            finally:
                torch._inductor.compile_fx.select_decomp_table = old_decomp

        def vq(x):
            return (x + 3).exponential_() * 10.5

        def test_fn():
            torch._dynamo.reset()
            with patch_exp_decomp():
                vq_compiled = torch.compile(vq)
                x = torch.randn(4, 400, 256).cuda()
                with torch._dynamo.utils.preserve_rng_state():
                    out = vq(x)
                out_compiled = vq_compiled(x)

            return not out_compiled.isnan().any()

        out = BisectionManager.do_bisect(test_fn)
        self.assertEqual(out.backend, "aot_eager_decomp_partition")
        self.assertEqual(out.subsystem, "decomposition")
        self.assertEqual(out.bisect_number, 1)
        self.assertTrue("aten.exponential" in out.debug_info)

    def test_emulate_precision_casts(self):
        def test_fn():
            torch._dynamo.reset()

            def calculate_scale(inp):
                amax = torch.abs(torch.max(inp))
                scale = 448.0 / torch.clamp(amax, min=1e-12)
                scale = scale.to(torch.float32)
                return scale

            dtype = torch.bfloat16
            torch.manual_seed(0)
            inp = torch.randn(16, 16, 768, dtype=dtype, device="cuda")
            eager_scale = calculate_scale(inp)
            compile_scale = torch.compile(calculate_scale)(inp)

            return torch.equal(eager_scale, compile_scale)

        out = BisectionManager.do_bisect(test_fn)
        self.assertEqual(out.backend, "inductor")
        self.assertEqual(out.subsystem, "inductor_emulate_precision_casts")

    def test_bad_lowering(self):
        def test_fn():
            torch._dynamo.reset()
            with config.patch("triton.inject_relu_bug_TESTING_ONLY", "accuracy"):

                def my_func(x):
                    return ((x * -1) - 0.01).relu()

                inp = torch.rand([100], device="cuda")

                return torch.allclose(torch.compile(my_func)(inp), my_func(inp))

        out = BisectionManager.do_bisect(test_fn)
        self.assertEqual(out.backend, "inductor")
        self.assertEqual(out.subsystem, "lowerings")
        self.assertEqual(out.bisect_number, 2)
        self.assertTrue("relu" in out.debug_info)

    def test_eager_backend(self):
        # should indicate problem with first backend
        def test_fn():
            return False

        out = BisectionManager.do_bisect(test_fn)
        self.assertEqual(out.backend, "eager")
        self.assertEqual(out.subsystem, None)


if __name__ == "__main__":
    from torch._dynamo.test_case import run_tests

    run_tests()
