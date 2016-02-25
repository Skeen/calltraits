#include <type_traits>

#include "library/call_traits.hpp"

void function(int, double);
// void(int)
static_assert(std::is_same<std::return_type<decltype(function)>, void>::value == true, "");
static_assert(std::is_same<std::parameter_type<0, decltype(function)>, int>::value == true, "");
static_assert(std::is_same<std::parameter_type<1, decltype(function)>, double>::value == true, "");
static_assert(std::arity<decltype(function)>::value == 2, "");
static_assert(std::has_varying_arguments<decltype(function)>::value == false, "");
static_assert(std::is_member_function<decltype(function)>::value == false, "");
static_assert(std::is_static_member_or_free_function<decltype(function)>::value == true, "");

// void(int,double)
static_assert(std::is_same<std::return_type<void(int,double)>, void>::value == true, "");
static_assert(std::is_same<std::parameter_type<0, void(int,double)>, int>::value == true, "");
static_assert(std::is_same<std::parameter_type<1, void(int,double)>, double>::value == true, "");
static_assert(std::arity<void(int,double)>::value == 2, "");
static_assert(std::has_varying_arguments<void(int,double)>::value == false, "");
static_assert(std::is_member_function<void(int,double)>::value == false, "");
static_assert(std::is_static_member_or_free_function<void(int, double)>::value == true, "");

// void(...)
static_assert(std::arity<void(...)>::value == 0, "");
static_assert(std::has_varying_arguments<void(...)>::value == true, "");

// void(int, double, ...)
static_assert(std::arity<void(int, double, ...)>::value == 2, "");
static_assert(std::has_varying_arguments<void(int, double, ...)>::value == true, "");

template <typename T>
T template_function1(int, T);
// int(int, int)
static_assert(std::is_same<std::return_type<decltype(template_function1<int>)>, int>::value == true, "");
static_assert(std::is_same<std::parameter_type<1, decltype(template_function1<int>)>, int>::value == true, "");
static_assert(std::arity<decltype(template_function1<int>)>::value == 2, "");
static_assert(std::has_varying_arguments<decltype(template_function1<int>)>::value == false, "");

template <typename T>
void template_function2(int, T, ...);
// void(int, int, ...)
static_assert(std::arity<decltype(template_function2<int>)>::value == 2, "");
static_assert(std::has_varying_arguments<decltype(template_function2<int>)>::value == true, "");

template <typename... Ts>
void template_function3(Ts...);
// void()
static_assert(std::arity<decltype(template_function3<>)>::value == 0, "");
// void(int)
static_assert(std::arity<decltype(template_function3<int>)>::value == 1, "");
// void(int, double)
static_assert(std::arity<decltype(template_function3<int, double>)>::value == 2, "");
static_assert(std::is_same<std::parameter_type<1, decltype(template_function3<int,double>)>, double>::value == true, "");
static_assert(std::has_varying_arguments<decltype(template_function3<int, double>)>::value == false, "");

template <typename... Ts>
void template_function4(Ts..., ...);
// void(int, double, ...)
static_assert(std::has_varying_arguments<decltype(template_function4<int, double>)>::value == true, "");

struct functor
{
    void operator()(int);
};
// void (functor::*) operator(int)
static_assert(std::is_same<std::return_type<functor>, void>::value == true, "");
static_assert(std::is_same<std::parameter_type<0, functor>, int>::value == true, "");
static_assert(std::arity<functor>::value == 1, "");
static_assert(std::has_varying_arguments<functor>::value == false, "");
static_assert(std::is_same<std::implicit_object_type<functor>, functor>::value == true, "");

struct template_functor
{
    template <typename T>
    void operator()(T);
};
// void (template_functor::*) operator(T)<int>
static_assert(std::is_same<std::return_type<template_functor, int>, void>::value == true, "");
static_assert(std::is_same<std::parameter_type<0, template_functor, int>, int>::value == true, "");
static_assert(std::arity<template_functor, int>::value == 1, "");
static_assert(std::has_varying_arguments<template_functor, int>::value == false, "");
static_assert(std::is_same<std::implicit_object_type<template_functor, int>, template_functor>::value == true, "");

struct variadic_template_functor
{
    template <typename... Ts>
    void operator()(Ts..., ...);
};
// void (variadic_template_functor::*) operator(Ts..., ...)<int, double>
static_assert(std::is_same<std::return_type<variadic_template_functor, int, double>, void>::value == true, "");
static_assert(std::is_same<std::parameter_type<1, variadic_template_functor, int, double>, double>::value == true, "");
static_assert(std::arity<variadic_template_functor, int, double>::value == 2, "");
static_assert(std::has_varying_arguments<variadic_template_functor, int, double>::value == true, "");
static_assert(std::is_same<std::implicit_object_type<variadic_template_functor, int, double>, variadic_template_functor>::value == true, "");

struct klass
{
    void function(int);
    void const_function(int) const;
    static void static_function(int);
};
// void (klass::*)(void)
static_assert(std::is_member_function<decltype(&klass::function)>::value == true, "");
static_assert(std::is_static_member_or_free_function<decltype(&klass::function)>::value == false, "");
static_assert(std::is_same<std::return_type<decltype(&klass::function)>, void>::value == true, "");
static_assert(std::is_same<std::parameter_type<0, decltype(&klass::function)>, int>::value == true, "");
static_assert(std::is_same<std::implicit_object_type<decltype(&klass::function)>, klass>::value == true, "");
static_assert(std::is_const_function<decltype(&klass::function)>::value == false, "");
// void (klass::*)(void) const
static_assert(std::is_const_function<decltype(&klass::const_function)>::value == true, "");
// static void (*)(void)
// TODO: Static functions are not considered member_functions
// static_assert(std::is_member_function<decltype(klass::static_function)> == true, "");
static_assert(std::is_static_member_or_free_function<decltype(&klass::static_function)>::value == true, "");
static_assert(std::is_same<std::return_type<decltype(klass::static_function)>, void>::value == true, "");
static_assert(std::is_same<std::parameter_type<0, decltype(klass::static_function)>, int>::value == true, "");
// Note: The below yields an error, as the static_function isn't bound to the type
//static_assert(std::is_same<std::implicit_object_type<decltype(&klass::function)>, functor>::value == true, "");

const auto lambda = [](int i){ return i; };
using lambda_type = decltype(lambda);
// int (lambdaID::*)(int)
static_assert(std::is_member_function<lambda_type>::value == true, "");
static_assert(std::is_static_member_or_free_function<lambda_type>::value == false, "");
static_assert(std::is_same<std::return_type<lambda_type>, int>::value == true, "");
static_assert(std::is_same<std::parameter_type<0, lambda_type>, int>::value == true, "");
static_assert(std::is_const_function<lambda_type>::value == true, "");

#include <functional>
// std::function<int(int)>
static_assert(std::is_member_function<std::function<int(int)>>::value == true, "");
static_assert(std::is_static_member_or_free_function<std::function<int(int)>>::value == false, "");
static_assert(std::is_same<std::return_type<std::function<int(int)>>, int>::value == true, "");
static_assert(std::is_same<std::parameter_type<0, std::function<int(int)>>, int>::value == true, "");
static_assert(std::is_const_function<std::function<int(int)>>::value == true, "");
