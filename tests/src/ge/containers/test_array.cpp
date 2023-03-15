#include <gtest/gtest.h>

#include <ge/containers/array.hpp>
#include <ge_test/structs.hpp>

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

TYPED_TEST(ArrayTestFixture, ShouldInitializeArrayWithGivenSizeWhenCreated)
{
    // Arrange
    constexpr size_t array_size = 1000;
    Array array = Array::create<typename TestFixture::Type>(array_size);

    // Act, Assert
    EXPECT_EQ(array.count(), 0);
    EXPECT_EQ(array.size(), array_size);
    EXPECT_EQ(array.element_size(), sizeof(typename TestFixture::Type));
}

TYPED_TEST(ArrayTestFixture, ShouldPushbackDataWhenDataCountDoesNotExcessSize)
{
    // Arrange
    constexpr size_t array_size = 10;
    Array array = Array::create<typename TestFixture::Type>(array_size);

    // Act
    for (size_t i = 0; i < array_size; ++i)
    {
        EXPECT_TRUE(array.push_back(typename TestFixture::Type{}) != nullptr);
    }

    // Assert
    for (size_t i = 0; i < array_size; ++i)
    {
        EXPECT_TRUE(array.at<typename TestFixture::Type>(i) != nullptr);
    }
}

TYPED_TEST(ArrayTestFixture, ShouldReturnNullptrWhenDataIsNotStored)
{
    // Arrange
    constexpr size_t array_size = 10;
    Array array = Array::create<typename TestFixture::Type>(array_size);

    // Act
    for (size_t i = 0; i < array_size; i += 2)
    {
        typename TestFixture::Type data{};
        EXPECT_TRUE(array.insert(i, data) != nullptr);
    }

    // Assert
    for (size_t i = 0; i < array_size; ++i)
    {
        if (i % 2 == 0)
        {
            EXPECT_TRUE(array.at<typename TestFixture::Type>(i) != nullptr);
        }
        else
        {
            EXPECT_TRUE(array.at<typename TestFixture::Type>(i) == nullptr);
        }
    }
}

}  // namespace ge::containers
