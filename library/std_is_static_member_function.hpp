#ifndef __STD_IS_STATIC_MEMBER_FUNCTION_HPP
#define __STD_IS_STATIC_MEMBER_FUNCTION_HPP

#include "std_call_helper.hpp"

namespace std
{
    template<typename Callable, typename... Args>
    struct is_static_member_or_free_function : std::integral_constant<bool, not internal_worker::call_helper<Callable, Args...>::member_function>
    {
    };
}

#endif //__STD_IS_STATIC_MEMBER_FUNCTION_HPP

