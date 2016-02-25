#ifndef __STD_ARITY_HPP
#define __STD_ARITY_HPP

#include "std_call_helper.hpp"

namespace std
{
    template <typename Callable, typename... Args>
    struct arity
        : std::integral_constant<size_t,
            internal_worker::call_helper<Callable, Args...>::arity>
    {
    };

    template <typename Callable, typename... Args>
    struct is_nullary
        : std::integral_constant<bool, (arity<Callable, Args...>::value == 0)>
    {
    };
    template <typename Callable, typename... Args>
    struct is_unary
        : std::integral_constant<bool, (arity<Callable, Args...>::value == 1)>
    {
    };
    template <typename Callable, typename... Args>
    struct is_binary
        : std::integral_constant<bool, (arity<Callable, Args...>::value == 2)>
    {
    };
    template <typename Callable, typename... Args>
    struct is_ternary
        : std::integral_constant<bool, (arity<Callable, Args...>::value == 3)>
    {
    };
}

#endif //__STD_ARITY_HPP
