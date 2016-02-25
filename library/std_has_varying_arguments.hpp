#ifndef __STD_HAS_VARYING_ARGUMENTS_HPP
#define __STD_HAS_VARYING_ARGUMENTS_HPP

#include "std_call_helper.hpp"

namespace std
{
    template <typename Callable, typename... Args>
    struct has_varying_arguments
        : std::integral_constant<
              bool, internal_worker::call_helper<Callable, Args...>::varying>
    {
    };
}

#endif //__STD_HAS_VARYING_ARGUMENTS_HPP
