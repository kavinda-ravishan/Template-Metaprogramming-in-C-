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

    return 0;
}