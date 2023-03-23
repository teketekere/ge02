#include <gtest/gtest.h>

#include <ge/containers/array.hpp>
#include <ge_test/structs.hpp>
#include <memory>

#include "gtest/gtest.h"

namespace ge::containers
{

template<typename T>
class ArrayTestFixture : public ::testing::Test
{
  public:
    using Type = T;

    ArrayTestFixture() = default;
    ~ArrayTestFixture() override = default;
    ArrayTestFixture(const ArrayTestFixture& other) = delete;
    ArrayTestFixture(ArrayTestFixture&& other) noexcept = delete;
    ArrayTestFixture& operator=(const ArrayTestFixture& other) = delete;
    ArrayTestFixture& operator=(ArrayTestFixture&& other) noexcept = delete;
};

using TestTypes = ::testing::Types<ge_test::Tag, ge_test::M1, ge_test::M2, ge_test::M3>;
TYPED_TEST_SUITE(ArrayTestFixture, TestTypes, );

template<typename T>
auto create_array(size_t size)
{
    return std::shared_ptr<Array>(
        new Array{ Array::create<T>(size) },
        [](Array* a)
        {
            a->deallocate<T>();
            delete a;
        });
}

TYPED_TEST(ArrayTestFixture, ShouldInitializeArrayWithGivenSizeWhenCreated)
{
    // Arrange
    constexpr size_t array_size = 1000;
    auto array = create_array<typename TestFixture::Type>(array_size);

    // Act, Assert
    EXPECT_EQ(array->size(), array_size);
    EXPECT_EQ(array->element_size(), sizeof(typename TestFixture::Type));
}

TYPED_TEST(ArrayTestFixture, ShouldIterateEachElementWhenUseIndex)
{
    // Arrange
    constexpr size_t array_size = 2;
    auto array = create_array<typename TestFixture::Type>(array_size);

    // Act
    for (size_t i = 0; i < array_size; i++)
    {
        auto data = i % 2 == 0 ? ::ge_test::create1<typename TestFixture::Type>() : typename TestFixture::Type();
        *(array->template at<typename TestFixture::Type>(i)) = data;
    }

    // Assert
    for (size_t i = 0; i < array_size; i += 2)
    {
        EXPECT_EQ(*array->template at<typename TestFixture::Type>(i), ::ge_test::create1<typename TestFixture::Type>());
    }

    for (size_t i = 1; i < array_size; i += 2)
    {
        EXPECT_EQ(*array->template at<typename TestFixture::Type>(i), typename TestFixture::Type());
    }
}

TYPED_TEST(ArrayTestFixture, ShouldIterateEachElementWhenUseRangeBasedFor)
{
    // Arrange
    constexpr size_t array_size = 2;
    auto array = create_array<typename TestFixture::Type>(array_size);

    // Act
    size_t i = 0;
    for (auto&& elem : array->template view<typename TestFixture::Type>())
    {
        auto data = i % 2 == 0 ? ::ge_test::create1<typename TestFixture::Type>() : typename TestFixture::Type();
        elem = data;
        ++i;
    }

    // Assert
    i = 0;
    for (const auto& elem : array->template view<const typename TestFixture::Type>())
    {
        if (i % 2 == 0)
        {
            EXPECT_EQ(elem, ::ge_test::create1<typename TestFixture::Type>());
        }
        else
        {
            EXPECT_EQ(elem, typename TestFixture::Type());
        }
        ++i;
    }
}

TYPED_TEST(ArrayTestFixture, ShouldIterateEachElementWhenUseIterator)
{
    // Arrange
    constexpr size_t array_size = 2;
    auto array = create_array<typename TestFixture::Type>(array_size);

    // Act
    size_t i = 0;
    for (auto itr = array->template begin<typename TestFixture::Type>();
         itr != array->template end<typename TestFixture::Type>();
         ++itr)
    {
        auto data = i % 2 == 0 ? ::ge_test::create1<typename TestFixture::Type>() : typename TestFixture::Type();
        *itr = data;
        ++i;
    }

    // Assert
    i = 0;
    for (auto itr = array->template begin<const typename TestFixture::Type>();
         itr != array->template end<const typename TestFixture::Type>();
         ++itr)
    {
        if (i % 2 == 0)
        {
            EXPECT_EQ(*itr, ::ge_test::create1<typename TestFixture::Type>());
        }
        else
        {
            EXPECT_EQ(*itr, typename TestFixture::Type());
        }
        ++i;
    }
}

}  // namespace ge::containers
