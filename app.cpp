#include <iostream>
#include "my_tuple.hpp"

int main() {

    auto t = my::make_tuple(1, true, 1.5);

    std::cout << t.data << "\n";

    my::Tuple t2{1.2, false, 23};
    // my::Tuple<float, bool, int> t2{1.2, false, 23};

    std::cout << t2.data << "\n";

    std::cout << my::get<2>(t2) << "\n";

    return 0;
}