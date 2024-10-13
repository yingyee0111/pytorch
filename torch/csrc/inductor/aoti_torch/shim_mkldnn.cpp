
#include <torch/csrc/inductor/aoti_torch/c/shim_mkldnn.h>
#include <torch/csrc/inductor/aoti_torch/utils.h>

#ifndef AT_PER_OPERATOR_HEADERS
#include <ATen/CPUFunctions.h>
#else
#include <ATen/ops/mkldnn_rnn_layer_cpu_dispatch.h>
#endif
#include <ATen/native/mkldnn/Conv.h>
#include <ATen/native/mkldnn/Linear.h>

using namespace torch::aot_inductor;

#if AT_MKLDNN_ENABLED()

AOTITorchError aoti_torch_cpu_mkldnn__convolution_pointwise_binary(
    AtenTensorHandle X,
    AtenTensorHandle other,
    AtenTensorHandle W,
    AtenTensorHandle* B,
    const int64_t* padding,
    int64_t padding_len_,
    const int64_t* stride,
    int64_t stride_len_,
    const int64_t* dilation,
    int64_t dilation_len_,
    int64_t groups,
    const char* binary_attr,
    double* alpha,
    const char** unary_attr,
    const double** unary_scalars,
    int64_t unary_scalars_len_,
    const char** unary_algorithm,
    AtenTensorHandle* ret0) {
  AOTI_TORCH_CONVERT_EXCEPTION_TO_ERROR_CODE({
    c10::List<std::optional<c10::Scalar>> unary_scalars_list;
    unary_scalars_list.reserve(unary_scalars_len_);
    for (int64_t i = 0; i < unary_scalars_len_; i++) {
      unary_scalars_list.emplace_back(pointer_to_optional(unary_scalars[i]));
    }
    auto tmp_result = at::native::mkldnn_convolution_pointwise_binary(
        *tensor_handle_to_tensor_pointer(X),
        *tensor_handle_to_tensor_pointer(other),
        *tensor_handle_to_tensor_pointer(W),
        pointer_to_optional<at::Tensor>(B),
        pointer_to_list<int64_t>(padding, padding_len_),
        pointer_to_list<int64_t>(stride, stride_len_),
        pointer_to_list<int64_t>(dilation, dilation_len_),
        groups,
        binary_attr,
        pointer_to_optional<c10::Scalar>(alpha),
        pointer_to_optional<c10::string_view>(unary_attr),
        unary_scalars_list,
        pointer_to_optional<c10::string_view>(unary_algorithm));
    *ret0 = new_tensor_handle(std::move(tmp_result));
  });
}

AOTITorchError aoti_torch_cpu_mkldnn__convolution_pointwise_binary_(
    AtenTensorHandle other,
    AtenTensorHandle X,
    AtenTensorHandle W,
    AtenTensorHandle* B,
    const int64_t* padding,
    int64_t padding_len_,
    const int64_t* stride,
    int64_t stride_len_,
    const int64_t* dilation,
    int64_t dilation_len_,
    int64_t groups,
    const char* binary_attr,
    double* alpha,
    const char** unary_attr,
    const double** unary_scalars,
    int64_t unary_scalars_len_,
    const char** unary_algorithm,
    AtenTensorHandle* ret0) {
  AOTI_TORCH_CONVERT_EXCEPTION_TO_ERROR_CODE({
    c10::List<std::optional<c10::Scalar>> unary_scalars_list;
    unary_scalars_list.reserve(unary_scalars_len_);
    for (int64_t i = 0; i < unary_scalars_len_; i++) {
      unary_scalars_list.emplace_back(pointer_to_optional(unary_scalars[i]));
    }
    auto tmp_result = at::native::mkldnn_convolution_pointwise_binary_(
        *tensor_handle_to_tensor_pointer(other),
        *tensor_handle_to_tensor_pointer(X),
        *tensor_handle_to_tensor_pointer(W),
        pointer_to_optional<at::Tensor>(B),
        pointer_to_list<int64_t>(padding, padding_len_),
        pointer_to_list<int64_t>(stride, stride_len_),
        pointer_to_list<int64_t>(dilation, dilation_len_),
        groups,
        binary_attr,
        pointer_to_optional<c10::Scalar>(alpha),
        pointer_to_optional<c10::string_view>(unary_attr),
        unary_scalars_list,
        pointer_to_optional<c10::string_view>(unary_algorithm));
    *ret0 = new_tensor_handle(std::move(tmp_result));
  });
}

AOTITorchError aoti_torch_cpu_mkldnn__convolution_pointwise(
    AtenTensorHandle X,
    AtenTensorHandle W,
    AtenTensorHandle* B,
    const int64_t* padding,
    int64_t padding_len_,
    const int64_t* stride,
    int64_t stride_len_,
    const int64_t* dilation,
    int64_t dilation_len_,
    int64_t groups,
    const char* attr,
    const double** scalars,
    int64_t scalars_len_,
    const char** algorithm,
    AtenTensorHandle* ret0) {
  AOTI_TORCH_CONVERT_EXCEPTION_TO_ERROR_CODE({
    c10::List<std::optional<c10::Scalar>> scalars_list;
    scalars_list.reserve(scalars_len_);
    for (int64_t i = 0; i < scalars_len_; i++) {
      scalars_list.emplace_back(pointer_to_optional(scalars[i]));
    }
    auto tmp_result = at::native::mkldnn_convolution_pointwise(
        *tensor_handle_to_tensor_pointer(X),
        *tensor_handle_to_tensor_pointer(W),
        pointer_to_optional<at::Tensor>(B),
        pointer_to_list<int64_t>(padding, padding_len_),
        pointer_to_list<int64_t>(stride, stride_len_),
        pointer_to_list<int64_t>(dilation, dilation_len_),
        groups,
        attr,
        scalars_list,
        pointer_to_optional<c10::string_view>(algorithm));
    *ret0 = new_tensor_handle(std::move(tmp_result));
  });
}

AOTI_TORCH_EXPORT AOTITorchError
aoti_torch_cpu_mkldnn__convolution_transpose_pointwise(
    AtenTensorHandle X,
    AtenTensorHandle W,
    AtenTensorHandle* B,
    const int64_t* padding,
    int64_t padding_len_,
    const int64_t* output_padding,
    int64_t output_padding_len_,
    const int64_t* stride,
    int64_t stride_len_,
    const int64_t* dilation,
    int64_t dilation_len_,
    int64_t groups,
    const char* attr,
    const double** scalars,
    int64_t scalars_len_,
    const char** algorithm,
    AtenTensorHandle* ret0) {
  AOTI_TORCH_CONVERT_EXCEPTION_TO_ERROR_CODE({
    c10::List<std::optional<c10::Scalar>> scalars_list;
    scalars_list.reserve(scalars_len_);
    for (int64_t i = 0; i < scalars_len_; i++) {
      scalars_list.emplace_back(pointer_to_optional(scalars[i]));
    }
    auto tmp_result = at::native::mkldnn_convolution_transpose_pointwise(
        *tensor_handle_to_tensor_pointer(X),
        *tensor_handle_to_tensor_pointer(W),
        pointer_to_optional<at::Tensor>(B),
        pointer_to_list<int64_t>(padding, padding_len_),
        pointer_to_list<int64_t>(output_padding, output_padding_len_),
        pointer_to_list<int64_t>(stride, stride_len_),
        pointer_to_list<int64_t>(dilation, dilation_len_),
        groups,
        attr,
        scalars_list,
        pointer_to_optional<c10::string_view>(algorithm));
    *ret0 = new_tensor_handle(std::move(tmp_result));
  });
}

AOTITorchError aoti_torch_cpu_mkldnn_rnn_layer(
    AtenTensorHandle input,
    AtenTensorHandle weight0,
    AtenTensorHandle weight1,
    AtenTensorHandle weight2,
    AtenTensorHandle weight3,
    AtenTensorHandle hx_,
    AtenTensorHandle cx_,
    int32_t reverse,
    const int64_t* batch_sizes,
    int64_t batch_sizes_len_,
    int64_t mode,
    int64_t hidden_size,
    int64_t num_layers,
    int32_t has_biases,
    int32_t bidirectional,
    int32_t batch_first,
    int32_t train,
    AtenTensorHandle* ret0,
    AtenTensorHandle* ret1,
    AtenTensorHandle* ret2,
    AtenTensorHandle* ret3) {
  AOTI_TORCH_CONVERT_EXCEPTION_TO_ERROR_CODE({
    auto tmp_result = at::cpu::mkldnn_rnn_layer(
        *tensor_handle_to_tensor_pointer(input),
        *tensor_handle_to_tensor_pointer(weight0),
        *tensor_handle_to_tensor_pointer(weight1),
        *tensor_handle_to_tensor_pointer(weight2),
        *tensor_handle_to_tensor_pointer(weight3),
        *tensor_handle_to_tensor_pointer(hx_),
        *tensor_handle_to_tensor_pointer(cx_),
        reverse,
        pointer_to_list<int64_t>(batch_sizes, batch_sizes_len_),
        mode,
        hidden_size,
        num_layers,
        has_biases,
        bidirectional,
        batch_first,
        train);
    *ret0 = new_tensor_handle(std::move(std::get<0>(tmp_result)));
    *ret1 = new_tensor_handle(std::move(std::get<1>(tmp_result)));
    *ret2 = new_tensor_handle(std::move(std::get<2>(tmp_result)));
    *ret3 = new_tensor_handle(std::move(std::get<3>(tmp_result)));
  });
}

AOTITorchError aoti_torch_cpu__linear_pointwise(
    AtenTensorHandle X,
    AtenTensorHandle W,
    AtenTensorHandle* B,
    const char* attr,
    const double** scalars,
    int64_t scalars_len_,
    const char** algorithm,
    AtenTensorHandle* ret0) {
  AOTI_TORCH_CONVERT_EXCEPTION_TO_ERROR_CODE({
    c10::List<std::optional<c10::Scalar>> scalars_list;
    scalars_list.reserve(scalars_len_);
    for (int64_t i = 0; i < scalars_len_; i++) {
      scalars_list.emplace_back(pointer_to_optional(scalars[i]));
    }
    auto tmp_result = at::native::mkldnn_linear_pointwise(
        *tensor_handle_to_tensor_pointer(X),
        *tensor_handle_to_tensor_pointer(W),
        pointer_to_optional<at::Tensor>(B),
        attr,
        scalars_list,
        pointer_to_optional<c10::string_view>(algorithm));
    *ret0 = new_tensor_handle(std::move(tmp_result));
  });
}

AOTITorchError aoti_torch_cpu__linear_pointwise_binary(
    AtenTensorHandle X,
    AtenTensorHandle other,
    AtenTensorHandle W,
    AtenTensorHandle* B,
    const char* attr,
    AtenTensorHandle* ret0) {
  AOTI_TORCH_CONVERT_EXCEPTION_TO_ERROR_CODE({
    auto tmp_result = at::native::mkldnn_linear_pointwise_binary(
        *tensor_handle_to_tensor_pointer(X),
        *tensor_handle_to_tensor_pointer(other),
        *tensor_handle_to_tensor_pointer(W),
        pointer_to_optional<at::Tensor>(B),
        attr);
    *ret0 = new_tensor_handle(std::move(tmp_result));
  });
}

#endif // AT_MKLDNN_ENABLED()
