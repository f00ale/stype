#pragma once

#include <utility>
#include <type_traits>
#include <iosfwd>
namespace stype {
struct self;

template<typename T, typename Tag, typename ... Mods>
class type : public Mods::template mod<type<T, Tag, Mods...>> ... {
    T val;
public:

    constexpr explicit type(T && t) noexcept(noexcept(T{std::move(t)})) : val(std::move(t)) {}

    constexpr const T & get() const noexcept { return val; }
    constexpr T & get() noexcept { return val; }
};

namespace detail {

template<typename T, typename Tag, typename ... Mods>
constexpr const T & getValue(const type<T,Tag,Mods...> & t) noexcept(noexcept(t.get())) { return t.get(); }

template<typename T, typename Tag, typename ... Mods>
constexpr T & getValue(type<T,Tag,Mods...> & t) noexcept(noexcept(t.get())) { return t.get(); }

template<typename T>
constexpr const T & getValue(const T & t) noexcept { return t; }

}

template<typename T = self>
struct equality_compareable {
    template<typename S>
    struct mod {
        using A1 = std::conditional_t<std::is_same_v<T, self>, S, T>;
        using A2 = S;

        friend constexpr
        bool
        operator==(const A1 & lhs, const A2 & rhs)
        noexcept(noexcept(bool(detail::getValue(lhs)==detail::getValue(rhs))))
        {
            return bool(detail::getValue(lhs)==detail::getValue(rhs));
        }

        friend constexpr
        bool
        operator!=(const A1 & lhs, const A2 & rhs)
        noexcept(noexcept(bool(detail::getValue(lhs)!=detail::getValue(rhs))))
        {
            return bool(detail::getValue(lhs)!=detail::getValue(rhs));
        }

        template<bool cond = std::is_same_v<A1, A2>>
        friend constexpr
        std::enable_if_t<!cond, bool>
        operator==(const A2 & lhs, const A1 & rhs)
        noexcept(noexcept(bool(detail::getValue(lhs)==detail::getValue(rhs))))
        {
            return bool(detail::getValue(lhs)==detail::getValue(rhs));
        }

        template<bool cond = std::is_same_v<A1, A2>>
        friend constexpr
        std::enable_if_t<!cond, bool>
        operator!=(const A2 & lhs, const A1 & rhs)
        noexcept(noexcept(bool(detail::getValue(lhs)!=detail::getValue(rhs))))
        {
            return bool(detail::getValue(lhs)!=detail::getValue(rhs));
        }
    };
};

template<typename R = self, typename A1 = self, typename A2 = self>
struct add {
    template<typename S>
    struct mod {
        using Ret = std::conditional_t<std::is_same<R, self>::value, S, R>;
        using Arg1 = std::conditional_t<std::is_same<A1, self>::value, S, A1>;
        using Arg2 = std::conditional_t<std::is_same<A2, self>::value, S, A2>;

        friend
        constexpr
        Ret
        operator+(const Arg1 & t1, const Arg2 & t2)
        noexcept(noexcept(Ret{detail::getValue(t1)+detail::getValue(t2)}))
        { return Ret{detail::getValue(t1)+detail::getValue(t2)}; }

        template<bool cond = std::is_same_v<Arg1, Arg2>>
        friend
        constexpr
        std::enable_if_t<!cond, Ret>
        operator+(const Arg2 & t1, const Arg1 & t2)
        noexcept(noexcept(Ret{detail::getValue(t1)+detail::getValue(t2)}))
        { return Ret{detail::getValue(t1)+detail::getValue(t2)}; }
    };
};

template<typename R = self, typename A1 = self, typename A2 = self>
struct sub {
    template<typename S>
    struct mod {
        using Ret = std::conditional_t<std::is_same<R, self>::value, S, R>;
        using Arg1 = std::conditional_t<std::is_same<A1, self>::value, S, A1>;
        using Arg2 = std::conditional_t<std::is_same<A2, self>::value, S, A2>;

        friend
        constexpr
        Ret operator-(const Arg1 & t1, const Arg2 & t2)
        noexcept(noexcept(Ret{detail::getValue(t1)-detail::getValue(t2)}))
        { return Ret{detail::getValue(t1)-detail::getValue(t2)}; }
    };
};

template<typename R = self, typename A1 = self, typename A2 = self>
struct multiply {
    template<typename S>
    struct mod {
        using Ret = std::conditional_t<std::is_same<R, self>::value, S, R>;
        using Arg1 = std::conditional_t<std::is_same<A1, self>::value, S, A1>;
        using Arg2 = std::conditional_t<std::is_same<A2, self>::value, S, A2>;

        friend
        constexpr
        Ret
        operator*(const Arg1 & t1, const Arg2 & t2)
        noexcept(noexcept(Ret{detail::getValue(t1)*detail::getValue(t2)}))
        { return Ret{detail::getValue(t1)*detail::getValue(t2)}; }

        template<bool cond = std::is_same_v<Arg1, Arg2>>
        friend
        constexpr
        std::enable_if_t<!cond, Ret>
        operator*(const Arg2 & t1, const Arg1 & t2)
        noexcept(noexcept(Ret{detail::getValue(t1)*detail::getValue(t2)}))
        { return Ret{detail::getValue(t1)*detail::getValue(t2)}; }
    };
};

template<typename R = self, typename A1 = self, typename A2 = self>
struct divide {
    template<typename S>
    struct mod {
        using Ret = std::conditional_t<std::is_same<R, self>::value, S, R>;
        using Arg1 = std::conditional_t<std::is_same<A1, self>::value, S, A1>;
        using Arg2 = std::conditional_t<std::is_same<A2, self>::value, S, A2>;

        friend
        constexpr
        Ret
        operator/(const Arg1 & t1, const Arg2 & t2)
        noexcept(noexcept(Ret{detail::getValue(t1)/detail::getValue(t2)}))
        { return Ret{detail::getValue(t1)/detail::getValue(t2)}; }
    };
};

template<typename R = self, typename A1 = self, typename A2 = self>
struct modulus {
    template<typename S>
    struct mod {
        using Ret = std::conditional_t<std::is_same<R, self>::value, S, R>;
        using Arg1 = std::conditional_t<std::is_same<A1, self>::value, S, A1>;
        using Arg2 = std::conditional_t<std::is_same<A2, self>::value, S, A2>;

        friend
        constexpr
        Ret
        operator%(const Arg1 & t1, const Arg2 & t2)
        noexcept(noexcept(Ret{detail::getValue(t1)%detail::getValue(t2)}))
        { return Ret{detail::getValue(t1)%detail::getValue(t2)}; }
    };
};

template<typename O = self>
struct add_assign {
    template<typename S>
    struct mod {
        using Arg = std::conditional_t<std::is_same<O, self>::value, S, O>;

        friend
        constexpr
        const S & operator+=(S & t1, const Arg & t2)
        noexcept(noexcept(detail::getValue(t1)+=detail::getValue(t2)))
        { detail::getValue(t1)+=detail::getValue(t2); return t1; }
    };
};

struct outputable {
    template<typename S>
    struct mod {
        friend
        std::ostream & operator<<(std::ostream & os, const S & s){
            os << detail::getValue(s);
            return os;
        }
    };
};

template<typename T = self>
struct compareable {
    template<typename S>
    struct mod {
        using A1 = std::conditional_t<std::is_same_v<T, self>, S, T>;
        using A2 = S;

        friend constexpr
        bool
        operator<(const A1 & lhs, const A2 & rhs)
        noexcept(noexcept(bool(detail::getValue(lhs)<detail::getValue(rhs))))
        {
            return bool(detail::getValue(lhs)<detail::getValue(rhs));
        }
        template<bool cond = std::is_same_v<A1, A2>>
        friend constexpr
        std::enable_if_t<!cond, bool>
        operator<(const A2 & lhs, const A1 & rhs)
        noexcept(noexcept(bool(detail::getValue(lhs)<detail::getValue(rhs))))
        {
            return bool(detail::getValue(lhs)<detail::getValue(rhs));
        }

        friend constexpr
        bool
        operator>(const A1 & lhs, const A2 & rhs)
        noexcept(noexcept(bool(detail::getValue(lhs)>detail::getValue(rhs))))
        {
            return bool(detail::getValue(lhs)>detail::getValue(rhs));
        }
        template<bool cond = std::is_same_v<A1, A2>>
        friend constexpr
        std::enable_if_t<!cond, bool>
        operator>(const A2 & lhs, const A1 & rhs)
        noexcept(noexcept(bool(detail::getValue(lhs)>detail::getValue(rhs))))
        {
            return bool(detail::getValue(lhs)>detail::getValue(rhs));
        }

        friend constexpr
        bool
        operator<=(const A1 & lhs, const A2 & rhs)
        noexcept(noexcept(bool(detail::getValue(lhs)<=detail::getValue(rhs))))
        {
            return bool(detail::getValue(lhs)<=detail::getValue(rhs));
        }
        template<bool cond = std::is_same_v<A1, A2>>
        friend constexpr
        std::enable_if_t<!cond, bool>
        operator<=(const A2 & lhs, const A1 & rhs)
        noexcept(noexcept(bool(detail::getValue(lhs)<=detail::getValue(rhs))))
        {
            return bool(detail::getValue(lhs)<=detail::getValue(rhs));
        }

        friend constexpr
        bool
        operator>=(const A1 & lhs, const A2 & rhs)
        noexcept(noexcept(bool(detail::getValue(lhs)>=detail::getValue(rhs))))
        {
            return bool(detail::getValue(lhs)>=detail::getValue(rhs));
        }
        template<bool cond = std::is_same_v<A1, A2>>
        friend constexpr
        std::enable_if_t<!cond, bool>
        operator>=(const A2 & lhs, const A1 & rhs)
        noexcept(noexcept(bool(detail::getValue(lhs)>=detail::getValue(rhs))))
        {
            return bool(detail::getValue(lhs)>=detail::getValue(rhs));
        }

    };
};


}
