#include <iostream>
#include <tuple>
#include <vector>
#include <string>

template<typename... T>
struct MyContainer
{
    std::tuple<T...> data;    
};

bool contain(const std::string& search, const std::vector<std::string> v, size_t start_from = 0) {

    if(v[start_from] == search) return true;
    else {
        if(v.size() - 1 == start_from) return false;
        else return contain(search, v, start_from + 1);
    }
}

template<bool condition, typename THEN, typename ELSE>
struct if_;

template<typename THEN, typename ELSE>
struct if_<true, THEN, ELSE> {
    using type  = THEN;
};

template<typename THEN, typename ELSE>
struct if_<false, THEN, ELSE> {
    using type  = ELSE;
};

template<typename SEARCH, typename TUPLE, size_t start_from = 0>
struct contain_type : 
if_<// IF
    std::is_same<std::tuple_element_t<start_from, TUPLE>, SEARCH>::value, 
    // THEN
    std::true_type, 
    // ELSE
    typename if_<
        // IF
        (std::tuple_size<TUPLE>::value - 1 == start_from), 
        // THEN
        std::false_type, 
        // ELSE
        contain_type<SEARCH, TUPLE, start_from + 1>
    >::type
>::type {};

int main() {

    std::tuple<float, int, std::string> point_2d(1.0f, 2, "hello");
    std::cout << std::get<0>(point_2d) << "\n";

    const std::vector<std::string> vec{"int", "bool", "float"};
    std::cout << std::boolalpha << contain("bool", vec) << "\n";
    std::cout << std::boolalpha << contain("string", vec) << "\n";
    
    std::cout << std::boolalpha << std::is_same<int, if_<(1<2), int, float>::type>::value << "\n";
    std::cout << std::boolalpha << std::is_same<int, if_<(1>2), int, float>::type>::value << "\n";

    std::cout << std::boolalpha << std::true_type::value << "\n";
    std::cout << std::boolalpha << std::false_type::value << "\n";

    std::cout << std::boolalpha << contain_type<int, decltype(point_2d)>::value << "\n";
    std::cout << std::boolalpha << contain_type<double, decltype(point_2d)>::value << "\n";


    return 0;
}