mp
===

A small, 0BSD-licensed metaprogramming library for C++17.

This is intended to be a lightweight and easy to understand implementation of a subset of useful metaprogramming utilities.

Usage
-----

Just add the `include` directory to your include path. That's it.

`typelist`
----------

A `mp::list` is a list of types. This set of headers provide metafunctions for manipulating lists of types.

### Constructor

* `mp::list`: Constructs a list.
* `mp::lift_sequence`: Lifts a value sequence into a list. Intended for use on `std::integral_sequence`.

### Element access

* `mp::get`: Gets a numbered element of a list.
* `mp::head`: Gets the first element of a list.
* `mp::tail`: Gets all-but-the-first-element as a list.

### Properties

* `mp::length`: Gets the length of a list.
* `mp::contains`: Determines if this list contains a specified element.

### Modifiers

* `mp::append`: Constructs a list with the provided elements appended to it.
* `mp::prepend`: Constructs a list with the provided elements prepended to it.

### Operations

* `mp::concat`: Concantenates multiple lists together.
* `mp::cartesian_product`: Construct a list containing the [cartesian product](https://en.wikipedia.org/wiki/Cartesian_product) of the provided lists.

### Conversions

* `mp::lower_to_tuple`: This operation only works on a list solely containing metavalues. Results in a `std::tuple` with equivalent values.


`metavalue`
-----------

A metavalue is a type of template `std::integral_constant`.

### Constants

* [`std::true_type`](https://en.cppreference.com/w/cpp/types/integral_constant)
* [`std::false_type`](https://en.cppreference.com/w/cpp/types/integral_constant)

### Constructor

* [`std::integral_constant`](https://en.cppreference.com/w/cpp/types/integral_constant)
* [`std::bool_constant`](https://en.cppreference.com/w/cpp/types/integral_constant)
* `mp::lift_value`: Lifts a value to become a metavalue

### Conversions

* `mp::value_cast`

### Operations

* `mp::value_equal`: Compares value equality, ignores type. Use `std::is_same` for strict comparison.
* [`std::negation`](https://en.cppreference.com/w/cpp/types/negation)
* [`std::conjunction`](https://en.cppreference.com/w/cpp/types/conjunction)
* [`std::disjunction`](https://en.cppreference.com/w/cpp/types/disjunction)

`metafunction`
--------------

* `std::void_t`: Always returns `void`.
* `mp::identity`: Identity metafunction. Can be used to establish a non-deduced context. See also C++20 `std::type_identity`.
* `mp::apply`: Invoke a provided metafunction with arguments specified in a list.
* `mp::map`: Apply a provided metafunction to each element of a list.
* `mp::bind`: Curry a metafunction. A macro `MM_MP_BIND` is provided to make this a little prettier.

License
-------

Please see [LICENSE-0BSD](LICENSE-0BSD).
