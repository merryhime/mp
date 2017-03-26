#pragma once

#include <cstddef>
#include <tuple>
#include <type_traits>

namespace mp {

/// Contains a list of types
template<class... T>
struct list {};

/// Identity metafunction
template<class T>
using id = T;

/// True metavalue
using true_ = std::integral_constant<bool, true>;

/// False metavalue
using false_ = std::integral_constant<bool, false>;

/// Constant metavalue metafunction
template<class V>
struct constant_fn {
    template<class...>
    using type = V;
};

/// True metafunction
template<class...>
using true_fn = true_;

/// False metafunction
template<class...>
using false_fn = false_;

namespace detail {

template<template<class...> class F, class L>
struct invoke_impl;

template<template<class...> class F, template<class...> class LT, class... T>
struct invoke_impl<F, LT<T...>> {
    using type = F<T...>;
};

} // namespace detail

/// Invokes metafunction F where the arguments are the members of list L
template<template<class...> class F, class L>
using invoke = typename detail::invoke_impl<F, L>::type;

template<template<class...> class F, class... A>
struct bind {
	template<class... T>
	using type = F<A..., T...>;
};

/// Metafunction that returns the number of arguments it has
template<class... T>
using arg_count = std::integral_constant<std::size_t, sizeof...(T)>;

/// Metafunction that returns the size of list L
template<class L> 
using length = invoke<arg_count, L>;

/// Metafunction that returns the size of list L as a value
template<class L> 
constexpr size_t length_v = length<L>::value;

namespace detail {

template<template<class...> class F, class L>
struct map_impl;

template<template<class...> class F, template<class...> class LT, class... T>
struct map_impl<F, LT<T...>> {
    using type = LT<F<T>...>;
};

} // namespace detail

/// Metafunction that applies each element of list L to metafunction F
template<template<class...> class F, class L>
using map = typename detail::map_impl<F, L>::type;

namespace detail {

template<class L> struct carcdr_impl;

template<template<class...> class LT, class T1, class... T> 
struct carcdr_impl<LT<T1, T...>> {
    using car = T1;
    using cdr = LT<T...>;
};

} // namespace detail

/// Metafunction that returns the first type of list L
template<class L>
using car = typename detail::carcdr_impl<L>::car;

/// Metafunction that returns all of L except the first type
template<class L>
using cdr = typename detail::carcdr_impl<L>::cdr;

/// Metafunction that returns the I-th type of L
template<std::size_t I, class L>
using get = typename std::tuple_element<I, invoke<std::tuple, L>>;

} // namespace mp
