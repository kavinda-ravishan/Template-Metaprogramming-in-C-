#include <iostream>
#include <tuple>
#include <vector>
#include <list>
#include <string>

// ======================================== E4 ========================================

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

// ======================================== E5 ========================================
template<typename T>
struct has_type {
    using type = T;
};

// ======================================== at ========================================
template<typename LIST, size_t index>
struct at : has_type<typename at<pop_front_t<LIST>, index-1>::type> {};

template<typename LIST>
struct at<LIST, 0> : has_type<front_t<LIST>> {};

template<typename LIST, size_t index>
using at_t = typename at<LIST, index>::type;

// ======================================== back ========================================

// ======================================== back 1 ========================================
template<typename LIST>
struct back {};

template<typename T0, typename... T_REST>
struct back<type_list<T0, T_REST...>> : has_type<typename back<type_list<T_REST...>>::type> {};

template<typename T>
struct back<type_list<T>> : has_type<front_t<type_list<T>>> {};

template<typename LIST>
using back_t = typename back<LIST>::type;
// ======================================== back 2 ========================================
// template<typename LIST>
// struct back : has_type<typename back<pop_front_t<LIST>>::type> {};

// template<typename T>
// struct back<type_list<T>> : has_type<T> {};

// template<typename LIST>
// using back_t = typename back<LIST>::type;

// ======================================== push back ========================================

template<typename LIST, typename T>
struct push_back {};

template<typename T, typename... TYPES>
struct push_back<type_list<TYPES...>, T> : has_type<type_list<TYPES..., T>> {};

template<typename LIST, typename T>
using push_back_t = typename push_back<LIST, T>::type;

// ======================================== pop back ========================================

template<typename LIST, typename RET_LIST = type_list<>>
struct pop_back {};

template<typename T, typename RET_LIST>
struct pop_back<type_list<T>, RET_LIST> : has_type<RET_LIST> {};

template<typename T0, typename T1, typename... T_REST, typename RET_LIST>
struct pop_back<type_list<T0, T1, T_REST...>, RET_LIST> : pop_back<type_list<T1, T_REST...>, push_back_t<RET_LIST, T0>> {};

template<typename LIST>
using pop_back_t = typename pop_back<LIST>::type;

int main() {

    // E4
    const std::list<std::string> list{"int", "bool", "string"};

    std::cout << std::boolalpha;
    std::cout << contains("int", list) << "\n";
    std::cout << contains("double", list) << "\n";

    type_list<int, bool, std::string> types;
    std::cout << contains_type_v<int, decltype(types)> << "\n";
    std::cout << contains_type_v<bool, decltype(types)> << "\n";
    std::cout << contains_type_v<double, decltype(types)> << "\n";
    std::cout << contains_type_v<double, type_list<>> << "\n";

    // E5
    std::cout << std::boolalpha;

    std::cout << std::is_same_v<at_t<decltype(types), 0>, int> << "\n";
    std::cout << std::is_same_v<at_t<decltype(types), 1>, bool> << "\n";
    std::cout << std::is_same_v<at_t<decltype(types), 2>, std::string> << "\n";
    
    std::cout << std::is_same_v<at_t<decltype(types), 0>, std::string> << "\n";
    std::cout << std::is_same_v<at_t<decltype(types), 1>, int> << "\n";
    std::cout << std::is_same_v<at_t<decltype(types), 2>, bool> << "\n";

    std::cout << std::is_same_v<back_t<decltype(types)>, std::string> << "\n";
    std::cout << std::is_same_v<back_t<decltype(types)>, bool> << "\n";
    std::cout << std::is_same_v<back_t<decltype(types)>, int> << "\n";

    push_back_t<decltype(types), double> types2;

    std::cout << std::is_same_v<back_t<decltype(types2)>, double> << "\n";
    std::cout << std::is_same_v<back_t<decltype(types2)>, int> << "\n";
    std::cout << std::is_same_v<back_t<push_back_t<type_list<>, int>>, int> << "\n";
    std::cout << std::is_same_v<back_t<push_back_t<type_list<>, int>>, bool> << "\n";

    std::cout << std::is_same_v<pop_back_t<type_list<int>>, type_list<>> << "\n";
    std::cout << std::is_same_v<pop_back_t<type_list<int, bool>>, type_list<int>> << "\n";
    std::cout << std::is_same_v<pop_back_t<type_list<int>>, type_list<bool>> << "\n";
    std::cout << std::is_same_v<pop_back_t<type_list<int, bool>>, type_list<int, bool>> << "\n";
    return 0;
}
