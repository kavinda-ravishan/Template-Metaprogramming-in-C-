#pragma once

#include <type_traits>

// ======================================== HAS TYPE ========================================

template<typename T>
struct has_type {
    using type = T;
};

// ======================================== IF ========================================

template<bool condition, typename THEN, typename ELSE>
struct if_ {};

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

template<>
struct empty<type_list<>>: std::true_type {};

template<typename LIST>
static constexpr bool empty_v = empty<LIST>::value;

// ======================================== FRONT ========================================

template<typename LIST>
struct front {};

template<typename LIST>
using front_t = typename front<LIST>::type;

template<typename T_THIS, typename... T_REST> // T_REST can be empty
struct front<type_list<T_THIS, T_REST...>> : has_type<T_THIS> {};

// ======================================== POP FRONT ========================================

template<typename LIST>
struct pop_front {};

template<typename LIST>
using pop_front_t = typename pop_front<LIST>::type;

template<typename T_THIS, typename... T_REST>
struct pop_front<type_list<T_THIS, T_REST...>> : has_type<type_list<T_REST...>> {};

// ======================================== CONTAINS TYPE ========================================

template<typename SEARCH, typename LIST>
struct contains_type :
if_t<
    (std::is_same_v<SEARCH, front_t<LIST>>), 
    // THEN
    std::true_type, 
    // ELSE
    contains_type<SEARCH, pop_front_t<LIST>>
>
{};

template<typename SEARCH>
struct contains_type<SEARCH, type_list<>> : std::false_type {};

template<typename SEARCH, typename LIST>
static constexpr bool contains_type_v = contains_type<SEARCH, LIST>::value;

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
struct back {};

template<typename T0, typename... T_REST>
struct back<type_list<T0, T_REST...>> : has_type<typename back<type_list<T_REST...>>::type> {};

template<typename T>
struct back<type_list<T>> : has_type<front_t<type_list<T>>> {};

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
struct push_back {};

template<typename T, typename... TYPES>
struct push_back<type_list<TYPES...>, T> : has_type<type_list<TYPES..., T>> {};

template<typename LIST, typename T>
using push_back_t = typename push_back<LIST, T>::type;

// ======================================== POP BACK ========================================

template<typename LIST, typename RET_LIST = type_list<>>
struct pop_back {};

template<typename T, typename RET_LIST>
struct pop_back<type_list<T>, RET_LIST> : has_type<RET_LIST> {};

template<typename T0, typename T1, typename... T_REST, typename RET_LIST>
struct pop_back<type_list<T0, T1, T_REST...>, RET_LIST> : pop_back<type_list<T1, T_REST...>, push_back_t<RET_LIST, T0>> {};

template<typename LIST>
using pop_back_t = typename pop_back<LIST>::type;
