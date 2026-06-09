#include "gtest/gtest.h"
#include "type_list.hpp"

TEST(MetaProTestSuite, IfTest) {
    static_assert(std::is_same_v<if_t<true, int, bool>, int>);
    static_assert(std::is_same_v<if_t<false, int, bool>, bool>);
}

TEST(MetaProTestSuite, EmptyTest) {
    static_assert(empty_v<type_list<>> == true);
    static_assert(empty_v<type_list<int>> == false);
}

TEST(MetaProTestSuite, FrontTest) {
    static_assert(std::is_same_v<front_t<type_list<int, bool, double>>, int>);
    static_assert(!std::is_same_v<front_t<type_list<int, bool, double>>, bool>);
}

TEST(MetaProTestSuite, PopFrontTest) {
    static_assert(
        std::is_same_v<
            pop_front_t<type_list<int, double, bool>>, 
            type_list<double, bool>
        >);
    
    static_assert(
        !std::is_same_v<
            pop_front_t<type_list<int, double, bool>>, 
            type_list<int, double, bool>
        >);
}

TEST(MetaProTestSuite, ContainsTypeTest) {
    static_assert(contains_type_v<int, type_list<int, bool, double>> == true);
    static_assert(contains_type_v<float, type_list<int, bool, double>> == false);
    static_assert(contains_type_v<bool, type_list<>> == false);
}

TEST(MetaProTestSuite, AtTest) {
    static_assert(
        std::is_same_v<
            at_t<type_list<int, bool, double>, 0>, 
            int
        >
    );

    static_assert(
        std::is_same_v<
            at_t<type_list<int, bool, double>, 2>, 
            double
        >
    );

    static_assert(
        !std::is_same_v<
            at_t<type_list<int, bool, double>, 1>, 
            int
        >
    );

    static_assert(
        !std::is_same_v<
            at_t<type_list<int, bool, double>, 2>, 
            float
        >
    );
}

TEST(MetaProTestSuite, BackTest) {
    static_assert(
        std::is_same_v<
            back_t<type_list<bool, double, int>>, 
            int
        >);

    static_assert(
        !std::is_same_v<
            back_t<type_list<bool, double, int>>, 
            double
        >);
    
    static_assert(
        !std::is_same_v<
            back_t<type_list<bool, double, int>>, 
            float
        >);
}

TEST(MetaProTestSuite, PushBackTest) {
    static_assert(
        std::is_same_v<
            push_back_t<type_list<int, bool>, double>, 
            type_list<int, bool, double>
        >
    );

    static_assert(
        !std::is_same_v<
            push_back_t<type_list<int, bool>, double>, 
            type_list<int, bool>
        >
    );

    static_assert(
        !std::is_same_v<
            push_back_t<type_list<int, bool>, double>, 
            type_list<int, double, bool>
        >
    );
}

TEST(MetaProTestSuite, PopBackTest) {
    static_assert(
        std::is_same_v<
            pop_back_t<type_list<int, bool>>, 
            type_list<int>
        >
    );

    static_assert(
        !std::is_same_v<
            pop_back_t<type_list<int, bool, double>>, 
            type_list<int, bool, double>
        >
    );

    static_assert(
        !std::is_same_v<
            pop_back_t<type_list<int, bool>>, 
            type_list<bool, int>
        >
    );

    type_list<int, bool, double> my_type_list;

    const bool val = std::is_same_v
        <
            pop_back_t<decltype(my_type_list)>, 
            type_list<int, bool>
        >;
    
    assert(val);
}
