#ifndef __STD_CALL_HELPER_HPP
#define __STD_CALL_HELPER_HPP

#include "std_is_function_pointer.hpp"
#include "std_type_array.hpp"

namespace std
{
    namespace internal_worker
    {
        template<typename Signature>
        struct call_helper_data;

        // Ordinary functions; T(Args...)
        template<typename ReturnType, typename... Args>
        struct call_helper_data<ReturnType(Args...)>
        {
            // The arity (i.e. the number of arguments this function takes)
            static constexpr size_t arity = sizeof...(Args);
            // Is the number of arguments variable (eg. ellipsis (...))
            static constexpr bool varying = false;
            // Is this a member function (defined on a class)
            static constexpr bool member_function = false;
            // Is this a const function (i.e. T(Args...) const)
            static constexpr bool const_function = false;
            // Capture the return type
            using return_type = ReturnType;
            // Capture the argument types
            template<size_t i>
            using arg = typename std::type_array_element<i, std::type_array<Args...>>::type;
        };
    
        // Variadic functions; T(Args..., ...)
        template<typename ReturnType, typename... Args>
        struct call_helper_data<ReturnType(Args..., ...)>
            : call_helper_data<ReturnType(Args...)>
        {
            // Shadow the previos definition; we're now varying in arguments
            static constexpr bool varying = true;
        };

        // Function pointers; T(*)(Args...)
        template<typename ReturnType, typename... Args>
        struct call_helper_data<ReturnType(*)(Args...)>
            : call_helper_data<ReturnType(Args...)>
        {
        };
        
        // Function pointers to variadic functions; T(*)(Args..., ...)
        template<typename ReturnType, typename... Args>
        struct call_helper_data<ReturnType(*)(Args..., ...)>
            : call_helper_data<ReturnType(Args..., ...)>
        {
        };

        // Class methods; T(Class::*)(Args...)
        template<typename ReturnType, typename Class, typename... Args>
        struct call_helper_data<ReturnType(Class::*)(Args...)>
            : call_helper_data<ReturnType(Args...)>
        {
            // Shadow the previos definition; we're now a class method
            static constexpr bool member_function = true;
            using object_type = Class;
        };
    
        // Variadic class methods; T(Class::*)(Args..., ...)
        template<typename ReturnType, typename Class, typename... Args>
        struct call_helper_data<ReturnType(Class::*)(Args..., ...)>
            : call_helper_data<ReturnType(Class::*)(Args...)>
        {
            // Shadow the previos definition; we're now varying in arguments
            static constexpr bool varying = true;
        };

        // const class methods; T(Class::*)(Args...) const
        template<typename ReturnType, typename Class, typename... Args>
        struct call_helper_data<ReturnType(Class::*)(Args...) const>
            : call_helper_data<ReturnType(Class::*)(Args...)>
        {
            // Shadow the previous definition; we're now const
            static constexpr bool const_function = true;
        };
        
        // const variadic class methods; T(Class::*)(Args..., ...) const
        template<typename ReturnType, typename Class, typename... Args>
        struct call_helper_data<ReturnType(Class::*)(Args..., ...) const>
            : call_helper_data<ReturnType(Class::*)(Args..., ...)>
        {
            // Shadow the previous definition; we're now const
            static constexpr bool const_function = true;
        };

        // call_helper_unfold
        // Figure out whether to call operator(), operator()<Args...>
        // or pass directly to call_helper_data.
        //
        // This makes use of std::enable_if to ensure, that only a single
        // specialization is valid, whenever an instantation is attempted.
        template<typename Callable, typename Args = std::type_array<>, typename Enable = void>
        struct call_helper_unfold;

        // The type is not directly callable, and the type array is empty.
        // (i.e. we need to call operator())
        template<typename Callable>
        struct call_helper_unfold<Callable,
            std::type_array<>,
            typename std::enable_if<!internal_worker::is_function_pointer<Callable>::callable>::type>
            : assert_is_function_pointer<decltype(&Callable::operator())>
        {
            using type = call_helper_data<decltype(&Callable::operator())>;
        };

        // The type is not directly callable, and the type array is not empty.
        // (i.e. we need to call operator()<Args...>)
        template<typename Callable, typename... Args>
        struct call_helper_unfold<Callable,
            std::type_array<Args...>,
            typename std::enable_if<!internal_worker::is_function_pointer<Callable>::callable>::type>
            : assert_is_function_pointer<decltype(&Callable::template operator()<Args...>)>
        {
            using type = call_helper_data<decltype(&Callable::template operator()<Args...>)>;
        };

        // The type is directly callable, and the type array may or may not be empty.
        // (i.e. we pass it directly)
        template<typename Callable, typename... Args>
        struct call_helper_unfold<Callable,
            std::type_array<Args...>,
            typename std::enable_if< internal_worker::is_function_pointer<Callable>::callable>::type>
            : assert_is_function_pointer<Callable>
        {
            using type = call_helper_data<Callable>;
        };

        // Entry point for everything in the call traits
        template <typename Callable, typename... Args>
        using call_helper = typename call_helper_unfold<Callable, std::type_array<Args...>>::type;
    }
}

#endif //__STD_CALL_HELPER_HPP
