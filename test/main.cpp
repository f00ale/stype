#include "stype.h"

#include <iostream>

template<typename ...>
struct is_one_of;

template<typename T>
struct is_one_of<T> : public std::false_type {};

template<typename T, typename Top, typename ... List>
struct is_one_of<T, Top, List...> {
    static const bool value = std::is_same<T, Top>::value || is_one_of<T, List...>::value;
};

template<typename T, typename ... List>
using is_one_of_v = typename is_one_of<T, List...>::value;

template<typename T> struct TAG;

template<typename T, typename S = stype::type<T, TAG<T>>>
void nothrowinfo() {
    std::cout << std::is_nothrow_constructible<S, T>::value << std::endl;
    std::cout << std::is_nothrow_constructible<S, T&>::value << std::endl;
    std::cout << std::is_nothrow_constructible<S, const T &>::value << std::endl;
    std::cout << std::is_nothrow_constructible<S, T&&>::value << std::endl;
}

int main () {
    using myint = stype::type<int, struct myinttag, stype::add<>, stype::sub<int>, stype::add<stype::self, int>, stype::equality_compareable<>>;

    myint x1{3}, x2{6};
    myint q{(int)7.9};

    auto a1 = x1 + x2;
    auto a2 = 1 + x2;

    auto b = x1 == x2;

    nothrowinfo<int>();
    nothrowinfo<std::string>();

    nothrowinfo<std::string,std::string>();
    std::cout << std::is_nothrow_constructible<std::string, const char*>::value << std::endl;
    std::cout << std::is_nothrow_constructible<std::string, void>::value << std::endl;

    auto s1 = x2 - x1;

    std::cout << (x2-x1) << std::endl;
    //std::cout << (x2+x1) << std::endl;

    static_assert(7+myint{3} == myint{10},"");

    using distance = stype::type<int, struct distag, stype::add<>, stype::sub<>>;
    using position = stype::type<int, struct postag, stype::add<stype::self, distance>, stype::sub<distance>>;

    constexpr position p1{3}, p2{8};
    constexpr auto d = p1 - p2;
    constexpr auto pd = d + p1;

    static_assert(pd.get() == -2);

    using addable = stype::type<int, struct addabletag, stype::add<>, stype::add_assign<>, stype::equality_compareable<>>;
    addable one(1), two(2);
    one += two;

    std::cout << one.get() << std::endl;

    static_assert((addable{5} + addable{7}) == addable{12}, "");
    return 0;
}
