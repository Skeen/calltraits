#ifndef __STD_IS_MEMBER_FUNCTION_HPP
#define __STD_IS_MEMBER_FUNCTION_HPP

#include "std_call_helper.hpp"

namespace std
{
    template<typename Callable, typename... Args>
    struct is_member_function : std::integral_constant<bool, internal_worker::call_helper<Callable, Args...>::member_function>
    {
    };
}

#endif //__STD_HAS_VARYING_ARGUMENTS_HPP

