#pragma once
namespace arrow {
namespace internal {

/// A type erased callable object which may only be invoked once.
/// It can be constructed from any lambda which matches the provided call signature.
/// Invoking it results in destruction of the lambda, freeing any state/references
/// immediately. Invoking a default constructed FnOnce or one which has already been
/// invoked will segfault.
template <typename Signature>
class FnOnce;

template <typename R, typename... A>
class FnOnce<R(A...)> {
 public:
  FnOnce() = default;

  template <typename Fn,
            typename = typename std::enable_if<std::is_convertible<
                decltype(std::declval<Fn&&>()(std::declval<A>()...)), R>::value>::type>
  FnOnce(Fn fn) : impl_(new FnImpl<Fn>(std::move(fn))) {  // NOLINT runtime/explicit
  }

  explicit operator bool() const { return impl_ != nullptr; }

  R operator()(A... a) && {
    auto bye = std::move(impl_);
    return bye->invoke(std::forward<A&&>(a)...);
  }

 private:
  struct Impl {
    virtual ~Impl() = default;
    virtual R invoke(A&&... a) = 0;
  };

  template <typename Fn>
  struct FnImpl : Impl {
    explicit FnImpl(Fn fn) : fn_(std::move(fn)) {}
    R invoke(A&&... a) override { return std::move(fn_)(std::forward<A&&>(a)...); }
    Fn fn_;
  };

  std::unique_ptr<Impl> impl_;
};

}  // namespace internal
}  // namespace arrow
