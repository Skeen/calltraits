#include <type_traits>
#include <functional>

#include "library/call_traits.hpp"

namespace std 
{
    template<typename T, T... I>
    struct integer_sequence 
    {
        typedef T value_type;

        static constexpr size_t size() noexcept { return sizeof...(I); }
    };
    
    template<typename T, int N, int... S>
    struct gen_integer_sequence : gen_integer_sequence<T, N-1, N-1, S...>
    {
    };

    template<typename T, int... S>
    struct gen_integer_sequence<T, 0, S...> 
    {
        typedef integer_sequence<T, S...> type;
    };

    template<typename T, T N>
    using make_integer_sequence = typename gen_integer_sequence<T, N>::type;

}  // namespace std

template <typename Callable, typename... Args>
struct converted_std_function_type_worker
{
    template <typename, typename>
    struct internal_struct;

    template <typename T, T... S>
    struct internal_struct<T, std::integer_sequence<T, S...>>
    {
        using std_function =
            std::function<typename std::return_type<Callable, Args...>(
                typename std::parameter_type<S, Callable, Args...>...)>;
    };
};

template <typename Callable, typename... Args>
using converted_std_function_type =
    typename converted_std_function_type_worker<Callable, Args...>::
        template internal_struct<
            size_t, std::make_integer_sequence<
                        size_t, std::arity<
                                    Callable, Args...>::value>>::std_function;

template <typename Callable, typename... Args>
auto make_stdfunction(Callable c, Args... args)
    -> converted_std_function_type<Callable, Args...>
{ return c; }

int function(int)
{
    return 2;
}

int main()
{
    auto func = make_stdfunction(&function);
    static_assert(std::is_same<decltype(func), std::function<int(int)>>::value, "");

    auto lambda =  make_stdfunction([](int){ return 'C'; });
    static_assert(std::is_same<decltype(lambda), std::function<char(int)>>::value, "");
}
