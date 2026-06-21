#pragma once

#include "my_mpl.hpp"

namespace my {

    template<typename... T>
    class Tuple {
    public:
        constexpr Tuple() = default;
    };

    template<typename T_THIS, typename... T_REST>
    class Tuple<T_THIS, T_REST...> : public Tuple<T_REST...> {
    public:
        explicit constexpr Tuple(T_THIS el, T_REST... rest)
        : Tuple<T_REST...>(rest...), data(el) {}

        T_THIS data;
    };

    // deduction guide (C++17)
    // my::Tuple<float, bool, int> t2{1.2, false, 23}; -> my::Tuple t2{1.2, false, 23};
    template<typename T_THIS, typename... T_REST>
    Tuple(T_THIS, T_REST...) -> Tuple<std::unwrap_ref_decay_t<T_THIS>, std::unwrap_ref_decay_t<T_REST>...>;

    template<typename... T>
    auto make_tuple(T... elems) {
        return Tuple<std::unwrap_ref_decay_t<T>...>{elems...};
    }

    // ======================================== GET ========================================
    namespace detail {
        template<size_t i, typename TUPLE>
        struct get_impl : get_impl<i-1, my_mpl::pop_front_t<TUPLE>> {};

        template<typename TUPLE>
        struct get_impl<0, TUPLE> {
            template<typename T>
            constexpr static decltype(auto) get(T&& t) {
                constexpr bool is_lvalue = std::is_lvalue_reference_v<T>;
                constexpr bool is_const = std::is_const_v<std::remove_reference_t<T>>;

                using data_t = my_mpl::front_t<TUPLE>;

                if constexpr (is_const && is_lvalue) {
                    return static_cast<const data_t&>(static_cast<const TUPLE&>(t).data);
                } else if constexpr (!is_const && is_lvalue) {
                    return static_cast<data_t&>(static_cast<TUPLE&>(t).data);
                } else if constexpr (!is_const && !is_lvalue) {
                    return static_cast<data_t&&>(static_cast<TUPLE&&>(t).data);
                } else if constexpr (is_const && !is_lvalue) {
                    return static_cast<const data_t&&>(static_cast<const TUPLE&&>(t).data);
                }
            }
        };
    } // namespace detail

    template<size_t i, typename TUPLE>
    constexpr decltype(auto) get(TUPLE&& tuple) {
        return detail::get_impl<i, std::remove_cvref_t<TUPLE>>::get(std::forward<TUPLE>(tuple));
    }

} // namespace my
