#include <ATen/native/MathBitsFallback.cpp>

namespace at {

struct NegFallback : MathOpFallback {
  NegFallback() : MathOpFallback(DispatchKey::Negative, "negation") {}
  bool is_bit_set(c10::TensorImpl& tensor) override {
    return tensor.is_neg();
  }
  void set_bit(Tensor& tensor, bool value) override {
    return tensor.set_neg(value);
  }
  Tensor resolve_bit(const Tensor& tensor) override {
    return at::resolve_neg(tensor);
  }
  Tensor& math_op_(Tensor& tensor) override {
    return tensor.neg_();
  }
};

void negationFallback(const c10::OperatorHandle& op, DispatchKeySet dispatch_keys, torch::jit::Stack* stack) {
  NegFallback object;
  object.fallback_impl(op, dispatch_keys, stack);
}

TORCH_LIBRARY_IMPL(_, Negative, m) {
  m.fallback(torch::CppFunction::makeFromBoxedFunction<&negationFallback>());
}

TORCH_LIBRARY_IMPL(aten, Negative, m) {
  m.impl("copy_", torch::CppFunction::makeFallthrough());
  m.impl("conj", torch::CppFunction::makeFallthrough());
  m.impl("_conj", torch::CppFunction::makeFallthrough());
  m.impl("neg_", torch::CppFunction::makeFallthrough());
  m.impl("_resolve_conj_neg", torch::CppFunction::makeFallthrough());
  m.impl("resolve_neg", torch::CppFunction::makeFallthrough());
  m.impl("empty_like", torch::CppFunction::makeFallthrough());
  m.impl("empty.out", torch::CppFunction::makeFallthrough());
  m.impl("empty_strided", torch::CppFunction::makeFallthrough());
  m.impl("stride.int", torch::CppFunction::makeFallthrough());
  m.impl("stride.Dimname", torch::CppFunction::makeFallthrough());
  m.impl("size.int", torch::CppFunction::makeFallthrough());
  m.impl("size.Dimname", torch::CppFunction::makeFallthrough());
  m.impl("is_complex", torch::CppFunction::makeFallthrough());
  m.impl("is_floating_point", torch::CppFunction::makeFallthrough());
  m.impl("view_as_real_physical", torch::CppFunction::makeFallthrough());
  m.impl("view_as_real", torch::CppFunction::makeFallthrough());
  m.impl("imag", torch::CppFunction::makeFallthrough());
  m.impl("real", torch::CppFunction::makeFallthrough());
  m.impl("view", torch::CppFunction::makeFallthrough());
  m.impl("reshape", torch::CppFunction::makeFallthrough());
  m.impl("select", torch::CppFunction::makeFallthrough());
  // TODO: need to hit the view functions
}

} // namespace at
