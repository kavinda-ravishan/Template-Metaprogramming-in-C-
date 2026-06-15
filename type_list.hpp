#pragma once

#include <type_traits>

// ======================================== HAS TYPE ========================================

template<typename T>
struct has_type {
    using type = T;
};

// ======================================== IF ========================================

template<bool condition, typename THEN, typename ELSE>
struct if_;

template<bool condition, typename THEN, typename ELSE>
using if_t = typename if_<condition, THEN, ELSE>::type;

template<typename THEN, typename ELSE>
struct if_<true, THEN, ELSE> : has_type<THEN> {};

template<typename THEN, typename ELSE>
struct if_<false, THEN, ELSE> : has_type<ELSE> {};

// ======================================== TYPE LIST ========================================

template<typename... T>
struct type_list {};

// ======================================== EMPTY ========================================

template<typename LIST>
struct empty: std::false_type {};

template<template<typename...> class LIST>
struct empty<LIST<>>: std::true_type {};

template<typename LIST>
static constexpr bool empty_v = empty<LIST>::value;

// ======================================== FRONT ========================================

template<typename LIST>
struct front;

template<typename LIST>
using front_t = typename front<LIST>::type;

template<template<typename...> class LIST, typename T_THIS, typename... T_REST> // T_REST can be empty
struct front<LIST<T_THIS, T_REST...>> : has_type<T_THIS> {};

// ======================================== POP FRONT ========================================

template<typename LIST>
struct pop_front;

template<typename LIST>
using pop_front_t = typename pop_front<LIST>::type;

template<template<typename...> class LIST, typename T_THIS, typename... T_REST>
struct pop_front<LIST<T_THIS, T_REST...>> : has_type<type_list<T_REST...>> {};

// ======================================== ANY ========================================

template<template<typename> class PREDICATE, typename LIST>
struct any;

template<template<typename> class PREDICATE, template<typename...> class LIST>
struct any<PREDICATE, LIST<>> : std::false_type {};

template<template<typename> class PREDICATE, typename LIST>
struct any :
if_t<
    PREDICATE<front_t<LIST>>::value, 
    std::true_type, 
    typename any<PREDICATE, pop_front_t<LIST>>
>
{};

template<template<typename> class PREDICATE, typename LIST>
static constexpr bool any_v = any<PREDICATE, LIST>::value;

// ======================================== CONTAINS TYPE ========================================

// ==================== contains type 1 ====================

template<typename T>
struct same_as_pred {
    template<typename U>
    struct predicate : std::is_same<T, U> {};
    
};

template<typename SEARCH, typename LIST>
static constexpr bool contains_type_v = any_v<same_as_pred<SEARCH>::template predicate, LIST>;

// ==================== contains type 2 ====================

// template<typename SEARCH, typename LIST>
// struct contains_type :
// if_t<
//     (std::is_same_v<SEARCH, front_t<LIST>>), 
//     // THEN
//     std::true_type, 
//     // ELSE
//     contains_type<SEARCH, pop_front_t<LIST>>
// >
// {};

// template<template<typename...> class LIST, typename SEARCH>
// struct contains_type<SEARCH, LIST<>> : std::false_type {};

// template<typename SEARCH, typename LIST>
// static constexpr bool contains_type_v = contains_type<SEARCH, LIST>::value;

// ======================================== AT ========================================
template<typename LIST, size_t index>
struct at : has_type<typename at<pop_front_t<LIST>, index-1>::type> {};

template<typename LIST>
struct at<LIST, 0> : has_type<front_t<LIST>> {};

template<typename LIST, size_t index>
using at_t = typename at<LIST, index>::type;

// ======================================== BACK ========================================

// ==================== back 1 ====================
template<typename LIST>
struct back;

template<template<typename...> class LIST, typename T0, typename... T_REST>
struct back<LIST<T0, T_REST...>> : has_type<typename back<LIST<T_REST...>>::type> {};

template<template<typename...> class LIST, typename T>
struct back<LIST<T>> : has_type<front_t<LIST<T>>> {};

template<typename LIST>
using back_t = typename back<LIST>::type;

// ==================== back 2 ====================
// template<typename LIST>
// struct back : has_type<typename back<pop_front_t<LIST>>::type> {};

// template<typename T>
// struct back<type_list<T>> : has_type<T> {};

// template<typename LIST>
// using back_t = typename back<LIST>::type;

// ======================================== PUSH BACK ========================================

template<typename LIST, typename T>
struct push_back;

template<template<typename...> class LIST, typename T, typename... TYPES>
struct push_back<LIST<TYPES...>, T> : has_type<LIST<TYPES..., T>> {};

template<typename LIST, typename T>
using push_back_t = typename push_back<LIST, T>::type;

// ======================================== MAKE EMPTY LIST ========================================

template<typename LIST>
struct make_empty_list;

template<template<typename...> class LIST, typename... Ts>
struct make_empty_list<LIST<Ts...>> : has_type<LIST<>> {};

template<typename LIST>
using make_empty_list_t = typename make_empty_list<LIST>::type;

// ======================================== POP BACK ========================================

template<typename LIST, typename RET_LIST = typename make_empty_list_t<LIST>>
struct pop_back;

template<template<typename...> class LIST, typename T, typename RET_LIST>
struct pop_back<LIST<T>, RET_LIST> : has_type<RET_LIST> {};

template<template<typename...> class LIST, typename T0, typename T1, typename... T_REST, typename RET_LIST>
struct pop_back<LIST<T0, T1, T_REST...>, RET_LIST> : pop_back<LIST<T1, T_REST...>, push_back_t<RET_LIST, T0>> {};

template<typename LIST>
using pop_back_t = typename pop_back<LIST>::type;

// ======================================== CAT ========================================

template<typename LIST_1, typename LIST_2, typename RET_LIST = typename make_empty_list_t<LIST_1>>
struct cat;

template<template<typename...> class LIST_1, template<typename...> class LIST_2, typename RET_LIST>
struct cat<LIST_1<>, LIST_2<>, RET_LIST> : has_type<RET_LIST> {};

template<template<typename...> class LIST_1, template<typename...> class LIST_2, typename T, typename RET_LIST>
struct cat<LIST_1<>, LIST_2<T>, RET_LIST> : cat<LIST_1<>, LIST_2<>, push_back_t<RET_LIST, T>> {};

template<template<typename...> class LIST_1, template<typename...> class LIST_2, typename T0, typename T1, typename... T_REST, typename RET_LIST>
struct cat<LIST_1<>, LIST_2<T0, T1, T_REST...>, RET_LIST> : cat<LIST_1<>, LIST_2<T1, T_REST...>, push_back_t<RET_LIST, T0>> {};

template<template<typename...> class LIST_1 , typename T, typename LIST_2, typename RET_LIST>
struct cat<LIST_1<T>, LIST_2, RET_LIST> : cat<LIST_1<>, LIST_2, push_back_t<RET_LIST, T>> {};

template<template<typename...> class LIST_1, typename T0, typename T1, typename... T_REST, typename LIST_2, typename RET_LIST>
struct cat<LIST_1<T0, T1, T_REST...>, LIST_2, RET_LIST> : cat<LIST_1<T1, T_REST...>, LIST_2, push_back_t<RET_LIST, T0>> {};

template<typename LIST_1, typename LIST_2>
using cat_t = typename cat<LIST_1, LIST_2>::type;
