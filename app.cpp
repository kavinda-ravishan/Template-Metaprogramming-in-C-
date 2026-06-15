#include <iostream>
#include <tuple>
#include <vector>
#include <list>
#include <string>
#include "type_list.hpp"

template<typename T>
void func(T arg) {

    std::cout << arg << "\n";
}

template<typename T_THIS, typename... T_REST>
void func(T_THIS arg, T_REST... args_rest) {

    std::cout << arg << ", ";

    func(args_rest...);
}

int main() {

    func(1.23f, false, "HELLO");

    std::vector<std::vector<int>> vec;
    std::vector<int> vec2{1, 2, 3};

    for(const auto val : vec2) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    vec.push_back(vec2);
    vec.push_back(std::move(vec2));

    for(const auto val : vec2) {
        std::cout << val << " ";
    }
    std::cout << "\n";


    return 0;
}