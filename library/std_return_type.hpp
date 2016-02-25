#ifndef __STD_RETURN_TYPE_HPP
#define __STD_RETURN_TYPE_HPP

#include "std_call_helper.hpp"

namespace std
{
    template<typename Callable, typename... Args>
    using return_type = typename internal_worker::call_helper<Callable, Args...>::return_type;
}

#endif //__STD_RETURN_TYPE_HPP
