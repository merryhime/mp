/* This file is part of the mp project.
 * Copyright (c) 2020 MerryMage
 * SPDX-License-Identifier: 0BSD
 */

#pragma once

#include <tuple>

#include <mp/traits/is_instance_of_template.h>

using namespace mp;

// is_instance_of_template

template<class, class...>
class Foo {};

template<class, class>
class Pair {};

static_assert(is_instance_of_template_v<std::tuple, std::tuple<int, bool>>);
static_assert(!is_instance_of_template_v<std::tuple, bool>);
static_assert(is_instance_of_template_v<Foo, Foo<bool>>);
static_assert(is_instance_of_template_v<Pair, Pair<bool, int>>);
static_assert(!is_instance_of_template_v<Pair, Foo<bool, int>>);
