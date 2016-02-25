#ifndef __STD_TYPE_ARRAY_HPP
#define __STD_TYPE_ARRAY_HPP

namespace std
{
    // Type-Array; because the VC compiler's std::tuple library implementation,
    // does not make usage of variadic templates. Also maybe it compiles faster.
    template <typename... Ts>
    class type_array;

    template <>
    class type_array<>
    {
    };

    template <typename Head, typename... Tail>
    class type_array<Head, Tail...> : type_array<Tail...>
    {
        using car = Head;
        using cdr = type_array<Tail...>;
    };

    template <typename Tuple>
    struct type_array_size;

    template <typename... Ts>
    struct type_array_size<type_array<Ts...>>
    {
        static const int value = sizeof...(Ts);
    };

    template <int Index, typename Tuple>
    struct type_array_element;

    template <int Index, typename Head, typename... Tail>
    struct type_array_element<Index, type_array<Head, Tail...>>
    {
        using type = typename type_array_element<Index - 1, type_array<Tail...>>::type;
    };

    template <typename Head, typename... Tail>
    struct type_array_element<0, type_array<Head, Tail...>>
    {
        using type = Head;
    };
}

#endif    //__STD_TYPE_ARRAY_HPP
