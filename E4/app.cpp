#include <iostream>
#include <tuple>
#include <vector>
#include <list>
#include <string>


template<bool condition, typename THEN, typename ELSE>
struct if_ {};

template<typename THEN, typename ELSE>
struct if_<true, THEN, ELSE> {
    using type = THEN;
};

template<typename THEN, typename ELSE>
struct if_<false, THEN, ELSE> {
    using type = ELSE;
};

bool contains(const std::string& str, std::list<std::string> list) {

    if(list.empty()) return false;
    else {
        if(list.front() == str) return true;
        else {
            list.pop_front();
            return contains(str, list);
        }
    }
}

template<typename... T>
struct type_list
{};

template<typename LIST>
struct empty: std::false_type
{};

template<>
struct empty<type_list<>>: std::true_type
{};

template<typename LIST>
struct front
{};

template<typename T_THIS, typename... T_REST> // T_REST can be empty
struct front<type_list<T_THIS, T_REST...>>
{
    using type = T_THIS;
};

template<typename LIST>
struct pop_front
{};

template<typename T_THIS, typename... T_REST>
struct pop_front<type_list<T_THIS, T_REST...>>
{
    using type = type_list<T_REST...>;
};

template<typename LIST>
using front_t = typename front<LIST>::type;

template<typename LIST>
using pop_front_t = typename pop_front<LIST>::type;

template<typename LIST>
static constexpr bool empty_v = empty<LIST>::value;

// template<typename SEARCH, typename LIST>
// struct contains_type;

// template<typename SEARCH, typename LIST>
// struct non_empty_contains_type :
// if_<
//     (std::is_same_v<SEARCH, front_t<LIST>>), 
//     // THEN
//     std::true_type, 
//     // ELSE
//     contains_type<SEARCH, pop_front_t<LIST>>
// >::type
// {};

// template<typename SEARCH, typename LIST>
// struct contains_type :
// if_<
//     empty_v<LIST>, 
//     // THEN
//     std::false_type, 
//     // ELSE
//     non_empty_contains_type<SEARCH, LIST>
//     >::type
// {};

template<typename SEARCH, typename LIST>
struct contains_type :
if_<
    (std::is_same_v<SEARCH, front_t<LIST>>), 
    // THEN
    std::true_type, 
    // ELSE
    contains_type<SEARCH, pop_front_t<LIST>>
>::type
{};

template<typename SEARCH>
struct contains_type<SEARCH, type_list<>> : std::false_type
{};

template<typename SEARCH, typename LIST>
static constexpr bool contains_type_v = contains_type<SEARCH, LIST>::value;

int main() {

    const std::list<std::string> list{"int", "bool", "string"};

    std::cout << std::boolalpha << contains("int", list) << "\n";
    std::cout << std::boolalpha << contains("double", list) << "\n";

    type_list<int, bool, std::string> types;
    std::cout << std::boolalpha << contains_type_v<int, decltype(types)> << "\n";
    std::cout << std::boolalpha << contains_type_v<bool, decltype(types)> << "\n";
    std::cout << std::boolalpha << contains_type_v<double, decltype(types)> << "\n";
    std::cout << std::boolalpha << contains_type_v<double, type_list<>> << "\n";

    return 0;
}