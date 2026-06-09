// #include <iostream>
// #include <tuple>
// #include <vector>
// #include <list>
// #include <string>

int main() {

    // E4
    // const std::list<std::string> list{"int", "bool", "string"};

    // std::cout << std::boolalpha;

    // type_list<int, bool, std::string> types;
    // std::cout << contains_type_v<int, decltype(types)> << "\n";
    // std::cout << contains_type_v<bool, decltype(types)> << "\n";
    // std::cout << contains_type_v<double, decltype(types)> << "\n";
    // std::cout << contains_type_v<double, type_list<>> << "\n";

    // // E5
    // std::cout << std::boolalpha;

    // std::cout << std::is_same_v<at_t<decltype(types), 0>, int> << "\n";
    // std::cout << std::is_same_v<at_t<decltype(types), 1>, bool> << "\n";
    // std::cout << std::is_same_v<at_t<decltype(types), 2>, std::string> << "\n";
    
    // std::cout << std::is_same_v<at_t<decltype(types), 0>, std::string> << "\n";
    // std::cout << std::is_same_v<at_t<decltype(types), 1>, int> << "\n";
    // std::cout << std::is_same_v<at_t<decltype(types), 2>, bool> << "\n";

    // std::cout << std::is_same_v<back_t<decltype(types)>, std::string> << "\n";
    // std::cout << std::is_same_v<back_t<decltype(types)>, bool> << "\n";
    // std::cout << std::is_same_v<back_t<decltype(types)>, int> << "\n";

    // push_back_t<decltype(types), double> types2;

    // std::cout << std::is_same_v<back_t<decltype(types2)>, double> << "\n";
    // std::cout << std::is_same_v<back_t<decltype(types2)>, int> << "\n";
    // std::cout << std::is_same_v<back_t<push_back_t<type_list<>, int>>, int> << "\n";
    // std::cout << std::is_same_v<back_t<push_back_t<type_list<>, int>>, bool> << "\n";

    // std::cout << std::is_same_v<pop_back_t<type_list<int>>, type_list<>> << "\n";
    // std::cout << std::is_same_v<pop_back_t<type_list<int, bool>>, type_list<int>> << "\n";
    // std::cout << std::is_same_v<pop_back_t<type_list<int>>, type_list<bool>> << "\n";
    // std::cout << std::is_same_v<pop_back_t<type_list<int, bool>>, type_list<int, bool>> << "\n";
    return 0;
}
