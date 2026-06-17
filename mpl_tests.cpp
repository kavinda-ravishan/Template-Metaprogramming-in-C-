#include <cassert>
#include <tuple>

#include "gtest/gtest.h"
#include "my_mpl.hpp"
#include "type_list.hpp"

using namespace my_mpl;

TEST(MetaProTestSuite, IfTest) {
    static_assert(std::is_same_v<if_t<true, int, bool>, int>);
    static_assert(std::is_same_v<if_t<false, int, bool>, bool>);
}

TEST(MetaProTestSuite, EmptyTest) {
    static_assert(empty_v<type_list<>>);
    static_assert(!empty_v<type_list<bool>>);
    static_assert(!empty_v<type_list<int, bool>>);

    static_assert(empty_v<std::tuple<>>);
    static_assert(!empty_v<std::tuple<bool>>);
    static_assert(!empty_v<std::tuple<int, bool>>);
}

TEST(MetaProTestSuite, FrontTest) {
    static_assert(std::is_same_v<front_t<type_list<int, bool, double>>, int>);
    static_assert(!std::is_same_v<front_t<type_list<int, bool, double>>, bool>);

    static_assert(std::is_same_v<front_t<std::tuple<int, bool, double>>, int>);
    static_assert(!std::is_same_v<front_t<std::tuple<int, bool, double>>, bool>);
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

    static_assert(
        std::is_same_v<
            pop_front_t<std::tuple<int, double, bool>>, 
            std::tuple<double, bool>
        >);
    
    static_assert(
        !std::is_same_v<
            pop_front_t<std::tuple<int, double, bool>>, 
            std::tuple<int, double, bool>
        >);
}

TEST(MetaProTestSuite, ContainsTypeTest) {
    static_assert(contains_type_v<int, type_list<int, bool, double>> == true);
    static_assert(contains_type_v<float, type_list<int, bool, double>> == false);
    static_assert(contains_type_v<bool, type_list<>> == false);

    static_assert(contains_type_v<int, std::tuple<int, bool, double>> == true);
    static_assert(contains_type_v<float, std::tuple<int, bool, double>> == false);
    static_assert(contains_type_v<bool, std::tuple<>> == false);
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


    static_assert(
        std::is_same_v<
            at_t<std::tuple<int, bool, double>, 0>, 
            int
        >
    );

    static_assert(
        std::is_same_v<
            at_t<std::tuple<int, bool, double>, 2>, 
            double
        >
    );

    static_assert(
        !std::is_same_v<
            at_t<std::tuple<int, bool, double>, 1>, 
            int
        >
    );

    static_assert(
        !std::is_same_v<
            at_t<std::tuple<int, bool, double>, 2>, 
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
    

    static_assert(
        std::is_same_v<
            back_t<std::tuple<bool, double, int>>, 
            int
        >);

    static_assert(
        !std::is_same_v<
            back_t<std::tuple<bool, double, int>>, 
            double
        >);
    
    static_assert(
        !std::is_same_v<
            back_t<std::tuple<bool, double, int>>, 
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


    static_assert(
        std::is_same_v<
            push_back_t<std::tuple<int, bool>, double>, 
            std::tuple<int, bool, double>
        >
    );

    static_assert(
        !std::is_same_v<
            push_back_t<std::tuple<int, bool>, double>, 
            std::tuple<int, bool>
        >
    );

    static_assert(
        !std::is_same_v<
            push_back_t<std::tuple<int, bool>, double>, 
            std::tuple<int, double, bool>
        >
    );
}

TEST(MetaProTestSuite, MakeEmptyListTest) {

    static_assert(
        std::is_same_v<
            make_empty_list<std::tuple<int, bool>>::type, 
            std::tuple<>
        >
    );

    static_assert(
        std::is_same_v<
            make_empty_list<type_list<int, bool>>::type, 
            type_list<>
        >
    );

    static_assert(
        std::is_same_v<
            make_empty_list_t<type_list<int, bool>>, 
            type_list<>
        >
    );

    static_assert(
        std::is_same_v<
            make_empty_list_t<std::tuple<int, bool>>, 
            std::tuple<>
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


    static_assert(
        std::is_same_v<
            pop_back_t<std::tuple<int, bool>>, 
            std::tuple<int>
        >
    );

    static_assert(
        !std::is_same_v<
            pop_back_t<std::tuple<int, bool, double>>, 
            std::tuple<int, bool, double>
        >
    );

    static_assert(
        !std::is_same_v<
            pop_back_t<std::tuple<int, bool>>, 
            std::tuple<bool, int>
        >
    );

    std::tuple<int, bool, double> my_tuple;

    const bool val2 = std::is_same_v
        <
            pop_back_t<decltype(my_tuple)>, 
            std::tuple<int, bool>
        >;
    
    assert(val2);
}

TEST(MetaProTestSuite, AnyTest) {

    static_assert(
        any_v<std::is_integral, type_list<int, float, bool>>
    );
    static_assert(
        any_v<std::is_integral, type_list<float, int, bool>>
    );
    static_assert(
        !any_v<std::is_integral, type_list<float, double>>
    );

    static_assert(
        any_v<std::is_integral, std::tuple<int, float, bool>>
    );
    static_assert(
        any_v<std::is_integral, std::tuple<float, int, bool>>
    );
    static_assert(
        !any_v<std::is_integral, std::tuple<float, double>>
    );
}

TEST(MetaProTestSuite, CatTest) {

    static_assert(
        std::is_same_v<
            type_list<bool, double, bool, int, float>, 
            cat_t<type_list<bool, double, bool>, type_list<int, float>>
        >
    );

    static_assert(
        std::is_same_v<
            type_list<bool, int, float>, 
            cat_t<type_list<bool>, type_list<int, float>>
        >
    );

    static_assert(
        std::is_same_v<
            type_list<bool, double, bool, float>, 
            cat_t<type_list<bool, double, bool>, type_list<float>>
        >
    );

    static_assert(
        std::is_same_v<
            type_list<int, float>, 
            cat_t<type_list<>, type_list<int, float>>
        >
    );

    static_assert(
        std::is_same_v<
            type_list<bool, double, bool>, 
            cat_t<type_list<bool, double, bool>, type_list<>>
        >
    );

    
    static_assert(
        std::is_same_v<
            std::tuple<bool, double, bool, int, float>, 
            cat_t<std::tuple<bool, double, bool>, std::tuple<int, float>>
        >
    );

    static_assert(
        std::is_same_v<
            std::tuple<bool, int, float>, 
            cat_t<std::tuple<bool>, std::tuple<int, float>>
        >
    );

    static_assert(
        std::is_same_v<
            std::tuple<bool, double, bool, float>, 
            cat_t<std::tuple<bool, double, bool>, std::tuple<float>>
        >
    );

    static_assert(
        std::is_same_v<
            std::tuple<int, float>, 
            cat_t<std::tuple<>, std::tuple<int, float>>
        >
    );

    static_assert(
        std::is_same_v<
            std::tuple<bool, double, bool>, 
            cat_t<std::tuple<bool, double, bool>, std::tuple<>>
        >
    );

}
