#include <iostream>
#include <vector>
#include "my_tuple.hpp"

template<typename T>
class MyContainer {
public:
    MyContainer(std::initializer_list<T> ini_lst) {

        _size = ini_lst.size();
        _start_ptr = new int[_size];

        for(size_t i=0; i<_size; i++) {
            _start_ptr[i] = *(ini_lst.begin() + i);
        }
    }

    ~MyContainer() {
        delete[] _start_ptr;
    }

    T& operator[](size_t index) { return _start_ptr[index]; }

    void print() {
        std::cout << "Arr: ";
        for(size_t i=0; i<_size; i++) {
            std::cout << _start_ptr[i] << " ";
        }
        std::cout << "\n";
    }

    T* begin() {
        return _start_ptr;
    }

    T* end() {
        return _start_ptr + _size;
    }
private:
    T* _start_ptr{nullptr};
    size_t _size{0};
};

int main() {

    MyContainer arr{1, 2, 3, 4, 5};
    arr.print();

    std::cout << arr[3] << "\n";

    for(const auto& item : arr) {
        std::cout << item << "\n";
    }

    // auto t = my::make_tuple(1, true, 1.5);

    // std::cout << t.data << "\n";

    // // my::Tuple<float, bool, int> t2{1.2, false, 23};
    // my::Tuple t2{1.2, false, 23};

    // std::cout << t2.data << "\n";

    // std::cout << my::get<2>(t2) << "\n";

    return 0;
}