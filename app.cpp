#include <iostream>
#include <vector>
#include "my_tuple.hpp"
#include "test_utilities.h"


int main() {

    my_utils::CopyCounter copy_counter;
    copy_counter.reset();

    auto t = my::make_tuple(copy_counter);

    std::cout << copy_counter.stats << "\n";

    return 0;
}