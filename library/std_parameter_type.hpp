#ifndef __STD_PARAMETER_TYPE_HPP
#define __STD_PARAMETER_TYPE_HPP

#include "std_call_helper.hpp"

namespace std
{
    namespace internal_worker
    {
        template <int N, typename Callable, typename... Args>
        struct parameter_type_worker
        {
            // Assert that the requested index
            static_assert(N >= 0 && N < std::arity<Callable, Args...>::value, "Parameter index, out-of-range");

            using type = typename internal_worker::call_helper<Callable, Args...>::template arg<N>;
        };
    }

    template<int I, typename Callable, typename... Args>
    using parameter_type = typename internal_worker::parameter_type_worker<I, Callable, Args...>::type;
}

#endif //__STD_PARAMETER_TYPE_HPP
