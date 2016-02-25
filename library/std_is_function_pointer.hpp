#ifndef __STD_IS_FUNCTION_POINTER_HPP
#define __STD_IS_FUNCTION_POINTER_HPP

namespace std
{
    namespace internal_worker
    {
        template<typename Signature>
        struct is_function_pointer
        {
            static constexpr bool callable = false;
        };

        // Function
        template<typename ReturnType, typename... Args>
        struct is_function_pointer<ReturnType(Args...)>
        {
            static constexpr bool callable = true;
        };
    
        template<typename ReturnType, typename... Args>
        struct is_function_pointer<ReturnType(Args..., ...)>
        {
            static constexpr bool callable = true;
        };

        // Function ptr
        template<typename ReturnType, typename... Args>
        struct is_function_pointer<ReturnType(*)(Args...)>
        {
            static constexpr bool callable = true;
        };
    
        template<typename ReturnType, typename... Args>
        struct is_function_pointer<ReturnType(*)(Args..., ...)>
        {
            static constexpr bool callable = true;
        };
    
        // On a class
        template<typename ReturnType, typename Class, typename... Args>
        struct is_function_pointer<ReturnType(Class::*)(Args...)>
        {
            static constexpr bool callable = true;
        };
    
        template<typename ReturnType, typename Class, typename... Args>
        struct is_function_pointer<ReturnType(Class::*)(Args..., ...)>
        {
            static constexpr bool callable = true;
        };

        // On a const class
        template<typename ReturnType, typename Class, typename... Args>
        struct is_function_pointer<ReturnType(Class::*)(Args...) const>
        {
            static constexpr bool callable = true;
        };
    
        template<typename ReturnType, typename Class, typename... Args>
        struct is_function_pointer<ReturnType(Class::*)(Args..., ...) const>
        {
            static constexpr bool callable = true;
        };
    }
    
    template<typename Callable>
    struct is_function_pointer : std::integral_constant<bool, internal_worker::is_function_pointer<Callable>::callable>
    {
    };

    template<typename Callable>
    struct assert_is_function_pointer
    {
        static_assert(internal_worker::is_function_pointer<Callable>::callable == true, "non-callable type");
        // TODO: replace above with;
        // static_assert(is_function_pointer<Callable> == true, "non_callable type");
    };
}

#endif //__STD_IS_FUNCTION_POINTER_HPP
