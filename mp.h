#pragma once

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

namespace mp {

/// Contains a list of types
template<class... T>
struct list {};

/// Identity metafunction
template<class T>
using id = T;

/// Bool metatype
template<bool V>
using bool_mv = std::integral_constant<bool, V>;

/// True metavalue
using true_ = bool_mv<true>;

/// False metavalue
using false_ = bool_mv<false>;

/// Size metatype
template<std::size_t V>
using size_mv = std::integral_constant<std::size_t, V>;

/// Lifts a function to be a metafunction
template <auto F>
struct lift {
    template <class... T>
    static constexpr auto value = F(T::value...);

    template <class... T>
    using type = std::integral_constant<decltype(value<T...>), value<T...>>;
};

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

template<class S>
struct sequence_to_list_impl;

template<template<class T, T...> class ST, class IT, IT... I>
struct sequence_to_list_impl<ST<IT, I...>> {
    using type = list<std::integral_constant<IT, I>...>;
};

} // namespace detail

/// Convert a value sequence to a metavalue sequence
template<class S>
using sequence_to_list = typename detail::sequence_to_list_impl<S>::type;

namespace detail {

template<class L>
struct list_to_sequence_impl;

template<template<class...> class LT, class T1, class... T>
struct list_to_sequence_impl<LT<T1, T...>> {
    using element_type = typename T1::value_type;
    static_assert((true && ... && std::is_same_v<typename T::value_type, element_type>));
    using type = std::integer_sequence<element_type, T1::value, T::value...>;
};

template<template<class...> class LT>
struct list_to_sequence_impl<LT<>> {
    using type = std::integer_sequence<size_t>;
};

} // namespace detail

/// Convert a metavalue sequence to a value sequence
template<class L>
using list_to_sequence = typename detail::list_to_sequence_impl<L>::type;

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
using arg_count = size_mv<sizeof...(T)>;

/// Metafunction that returns the size of list L
template<class L> 
using length = invoke<arg_count, L>;

/// Metafunction that returns the size of list L as a value
template<class L> 
constexpr size_t length_v = length<L>::value;

namespace detail {

template<class... L>
struct concat_impl;

template<>
struct concat_impl<> {
    using type = list<>;
};

template<class L>
struct concat_impl<L> {
    using type = L;
};

template<template<class...> class LT, class... T1, class... T2, class... Ls>
struct concat_impl<LT<T1...>, LT<T2...>, Ls...> {
    using type = typename concat_impl<LT<T1..., T2...>, Ls...>::type;
};

template<template<class...> class LT, class... T1, class... T2, class... T3, class... T4, class... T5, class... Ls>
struct concat_impl<LT<T1...>, LT<T2...>, LT<T3...>, LT<T4...>, LT<T5...>, Ls...> {
    using type = typename concat_impl<LT<T1..., T2..., T3..., T4..., T5...>, Ls...>::type;
};

} // namespace detail

/// Concatenate lists together
template<class... L>
using concat = typename detail::concat_impl<L...>::type;

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
