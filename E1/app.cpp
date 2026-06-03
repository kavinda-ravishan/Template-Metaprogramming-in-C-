#include <iostream>

template<typename T>
struct is_pointer {
    static constexpr bool value = false;
};

template<typename T>
struct is_pointer<T*> {
    static constexpr bool value = true;
};

template<typename T>
struct strip_pointer {
    using Type = T;
};

template<typename T>
struct strip_pointer<T*> {
    using Type = T;
};

template<typename T>
struct is_int{
    static constexpr bool value = false;
};

template<>
struct is_int<int>{
    static constexpr bool value = true;
};

template<typename T>
void print_func(T val) {

    using T_no_ptr = typename strip_pointer<T>::Type;
    if constexpr(is_int<T_no_ptr>::value) {
        std::cout << "INT\n";
    } else {
        std::cout << "NOT INT\n";
    }

    if constexpr(is_pointer<T>::value) {
        std::cout << "VAL : " << *val << "\n";
    } else {
        std::cout << "VAL : " << val << "\n";
    }
}

template<typename T1, typename T2, typename T3, typename T4>
void example(T1 val1, T2 val2, T3 val3, T4 val4) {
    print_func(val1);
    print_func(val2);
    print_func(val3);
    print_func(val4);
}

int main() {

    int x = 123;
    float y = 321.0f;
    example(x, y, &x, &y);

    return 0;
}