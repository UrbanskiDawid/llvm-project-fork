//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___TYPE_TRAITS_IS_CONVERTIBLE_H
#define _LIBCPP___TYPE_TRAITS_IS_CONVERTIBLE_H

#include <__config>
#include <__type_traits/integral_constant.h>
#include <__type_traits/is_array.h>
#include <__type_traits/is_function.h>
#include <__type_traits/is_void.h>
#include <__type_traits/remove_reference.h>
#include <__utility/declval.h>
#include <cstddef>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

#if __has_builtin(__is_convertible_to) && !defined(_LIBCPP_USE_IS_CONVERTIBLE_FALLBACK)

template <class _T1, class _T2> struct _LIBCPP_TEMPLATE_VIS is_convertible
    : public integral_constant<bool, __is_convertible_to(_T1, _T2)> {};

#else  // __has_builtin(__is_convertible_to)

namespace __is_convertible_imp
{
template <class _Tp> void  __test_convert(_Tp);

template <class _From, class _To, class = void>
struct __is_convertible_test : public false_type {};

template <class _From, class _To>
struct __is_convertible_test<_From, _To,
    decltype(__is_convertible_imp::__test_convert<_To>(declval<_From>()))> : public true_type
{};

template <class _Tp, bool _IsArray =    is_array<_Tp>::value,
                     bool _IsFunction = is_function<_Tp>::value,
                     bool _IsVoid =     is_void<_Tp>::value>
                     struct __is_array_function_or_void                          {enum {value = 0};};
template <class _Tp> struct __is_array_function_or_void<_Tp, true, false, false> {enum {value = 1};};
template <class _Tp> struct __is_array_function_or_void<_Tp, false, true, false> {enum {value = 2};};
template <class _Tp> struct __is_array_function_or_void<_Tp, false, false, true> {enum {value = 3};};
}

template <class _Tp,
    unsigned = __is_convertible_imp::__is_array_function_or_void<typename remove_reference<_Tp>::type>::value>
struct __is_convertible_check
{
    static const size_t __v = 0;
};

template <class _Tp>
struct __is_convertible_check<_Tp, 0>
{
    static const size_t __v = sizeof(_Tp);
};

template <class _T1, class _T2,
    unsigned _T1_is_array_function_or_void = __is_convertible_imp::__is_array_function_or_void<_T1>::value,
    unsigned _T2_is_array_function_or_void = __is_convertible_imp::__is_array_function_or_void<_T2>::value>
struct __is_convertible
    : public integral_constant<bool,
        __is_convertible_imp::__is_convertible_test<_T1, _T2>::value
    >
{};

template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 0, 1> : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 1, 1> : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 2, 1> : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 3, 1> : public false_type {};

template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 0, 2> : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 1, 2> : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 2, 2> : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 3, 2> : public false_type {};

template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 0, 3> : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 1, 3> : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 2, 3> : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 3, 3> : public true_type {};

template <class _T1, class _T2> struct _LIBCPP_TEMPLATE_VIS is_convertible
    : public __is_convertible<_T1, _T2>
{
    static const size_t __complete_check1 = __is_convertible_check<_T1>::__v;
    static const size_t __complete_check2 = __is_convertible_check<_T2>::__v;
};

#endif // __has_builtin(__is_convertible_to)

#if _LIBCPP_STD_VER > 14
template <class _From, class _To>
inline constexpr bool is_convertible_v = is_convertible<_From, _To>::value;
#endif

_LIBCPP_END_NAMESPACE_STD

#endif // _LIBCPP___TYPE_TRAITS_IS_CONVERTIBLE_H
