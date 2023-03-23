#pragma once

#include <algorithm>
#include <array>
#include <cstring>
#include <string>
#include <type_traits>
#include <vector>

namespace ge_test
{

struct Tag
{
};

struct M1
{
    int i{ 1 };
};

struct M2
{
    std::array<int, 2> arr{ 1, 2 };
    std::string str{ "abc" };
};

struct M3
{
    M1 m1{};
    M2 m2{};
    bool b{ false };
};

inline bool operator==(const ge_test::Tag& /* */, const ge_test::Tag& /* */)
{
    return true;
}

inline bool operator==(const ge_test::M1& t, const ge_test::M1& u)
{
    return t.i == u.i;
}

inline bool operator==(const ge_test::M2& t, const ge_test::M2& u)
{
    return t.arr.at(0) == u.arr.at(0) && t.arr.at(1) == u.arr.at(1) && t.str == u.str;
}

inline bool operator==(const ge_test::M3& t, const ge_test::M3& u)
{
    return t.m1 == u.m1 && t.m2 == u.m2 && t.b == u.b;
}

/**
 * @brief Test generator function no. 1
 */
template<typename T>
T create1();

template<>
inline Tag create1<Tag>()
{
    return Tag{};
}

template<>
inline M1 create1<M1>()
{
    return M1{ 2 };
}

template<>
inline M2 create1<M2>()
{
    return M2{ { 3, 4 }, "def" };
}

template<>
inline M3 create1<M3>()
{
    return M3{ create1<M1>(), create1<M2>(), true };
}

}  // namespace ge_test
