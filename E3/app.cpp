#include <iostream>
#include <tuple>
#include <vector>
#include <string>

// void print_func() {}

// template<typename THIS>
// void print_func(THIS _this) {
//     std::cout << _this << "\n";
// }

// template<typename THIS, typename... REST>
// void print_func(THIS _this, REST... _rest) {

//     std::cout << _this << ", ";
//     print_func(_rest...); // print_func(rest1, rest2, ...)
// }

// template<typename TUPLE, size_t... index_seqence>
// void print_tuple_impl(TUPLE t, std::index_sequence<index_seqence...>) {
//     print_func(std::get<index_seqence>(t)...); // print_func(std::get<0>(t), std::get<1>(t), ...)
// }

// template<typename TUPLE>
// void print_tuple(TUPLE t) {
//     print_tuple_impl(t, std::make_index_sequence<std::tuple_size<TUPLE>::value>{});
// }

// =========================================

void print_func() {}

template<typename THIS>
void print_func(THIS&& _this) {
    std::cout << "Rred -> " << std::forward<THIS>(_this) << "\n";
}

template<typename THIS>
void print_func(THIS& _this) {
    std::cout << "Lref -> " << std::forward<THIS>(_this) << "\n";
}

template<typename THIS, typename... REST>
void print_func(THIS&& _this, REST&&... _rest) {

    std::cout << std::forward<THIS>(_this) << ", ";
    print_func(std::forward<REST>(_rest)...);
}

template<typename TUPLE, size_t... index_seqence>
void print_tuple_impl(TUPLE&& t, std::index_sequence<index_seqence...>) {
    print_func(std::get<index_seqence>(std::forward<TUPLE>(t))...);
}

template<typename TUPLE>
void print_tuple(TUPLE&& t) {
    print_tuple_impl(std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::remove_reference<TUPLE>::type>::value>{});
}

// =========================================


int main() {

    print_func("hello", 9, false);

    const std::tuple t = std::make_tuple(1, 1.23f, "world");
    print_tuple(std::move(t));

    return 0;
}