from typing import Callable

from torch._dynamo.compiled_autograd import AutogradCompilerInstance

def set_autograd_compiler(
    autograd_compiler: Callable[[], AutogradCompilerInstance] | None,
) -> Callable[[], AutogradCompilerInstance] | None: ...
def clear_cache() -> None: ...
def is_cache_empty() -> bool: ...
def set_verbose_logger(fn: Callable[[str], None] | None) -> bool: ...
