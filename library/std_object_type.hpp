#ifndef __STD_OBJECT_TYPE_HPP
#define __STD_OBJECT_TYPE_HPP

#include "std_call_helper.hpp"
#include "std_is_member_function.hpp"

namespace std
{
    namespace internal_worker
    {
        template<typename Callable, typename... Args>
        struct implicit_object_type_worker
        {
            // Assert that the requested index
            static_assert(is_member_function<Callable, Args...>::value == true, "Unable to get implicit_object_type on a non member function");

            using object_type = typename internal_worker::call_helper<Callable, Args...>::object_type;
        };
    }


    template<typename Callable, typename... Args>
    using implicit_object_type = typename internal_worker::implicit_object_type_worker<Callable, Args...>::object_type;
}

#endif //__STD_OBJECT_TYPE_HPP
