
#include <array>
#include <type_traits>

namespace ge_test
{

struct Tag
{
};

struct M1
{
    float f{ 0.0 };
};

struct M2
{
    std::array<int, 3> arr{ 1, 2, 3 };
    const char* c_str{ "c_str" };
};

struct M3
{
    M1 m1{};
    M2 m2{};
    bool b{ false };
};

static_assert(std::is_trivially_copyable_v<M1>, "<M1");
static_assert(std::is_trivially_copyable_v<M2>, "<M2");
static_assert(std::is_trivially_copyable_v<M3>, "<M3");

}  // namespace ge_test
