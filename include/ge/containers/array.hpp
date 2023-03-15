#pragma once

#include <cassert>
#include <cstddef>
#include <cstring>
#include <functional>
#include <memory>
#include <optional>
#include <type_traits>

namespace ge::containers
{

/**
 * @brief Fized size type erasured array
 *
 * Allocated memory is freed when destructed
 */
class Array
{
    //! data array
    void* array_;

    //! Current count of data
    size_t count_;

    //! Max capacity
    size_t size_;

    //! Size of each element
    size_t element_size_;

    //! Deallocate function
    std::function<void(void* array, size_t size)> deallocator_{};

  public:
    ~Array();
    Array(const Array& other) = delete;
    Array(Array&& other) noexcept = delete;
    Array& operator=(const Array& other) = delete;
    Array& operator=(Array&& other) noexcept = delete;

    /**
     * @brief Return a pointer to the specified element
     *
     * @tparam T Element type
     * @param[in] index Index of the element to return
     * @return const T* A pointer to the specified element
     */
    template<typename T>
    const T* at(size_t index) const noexcept;

    /**
     * @brief Return a pointer to the specified element
     *
     * @tparam T Element type
     * @param[in] index Index of the element to return
     * @return const T* A pointer to the specified element
     */
    template<typename T>
    T* at(size_t index) noexcept;

    /**
     * @brief Append the given data to the end of array
     *
     * @note if data count reached capacity, this function does nothing and returns nullptr
     *
     * @tparam T Data type
     * @param[in] t The data to append
     * @return const T* A pointer to the point where the given data is appended
     */
    template<typename T>
    const T* push_back(const T& t) noexcept;

    /**
     * @brief Insert the given data at the specified location
     *
     * @note If the specified location is out of range, this function does nothing and returns nullptr
     *
     * @tparam T Data type
     * @param[in] index Index of the element to insert
     * @param[in] t The data to insert
     * @return const T* A pointer to the point where the given data is inserted
     */
    template<typename T>
    const T* insert(size_t index, const T& t);

    /**
     * @brief Return current data count
     */
    [[nodiscard]] size_t count() const noexcept;

    /**
     * @brief Return max capacity
     */
    [[nodiscard]] size_t size() const noexcept;

    /**
     * @brief Return size of each element
     */
    [[nodiscard]] size_t element_size() const noexcept;

    /**
     * @brief Create new instance
     *
     * @tparam T Type of element
     * @tparam Allocator Custom allocator type
     *
     * @param[in] size Max capacity
     * @return Array Created instance
     */
    template<typename T, typename Allocator = std::allocator<T>>
    static Array create(size_t size);

  private:
    explicit Array(size_t size) noexcept;
    Array(
        void* array,
        size_t size,
        size_t element_size,
        std::function<void(void* array, size_t size)> deallocator) noexcept;
};

template<typename T>
const T* Array::at(size_t index) const noexcept
{
    if (index >= count_)
    {
        return nullptr;
    }

    return static_cast<const T*>(array_) + (sizeof(T) * index);
}

template<typename T>
T* Array::at(size_t index) noexcept
{
    if (index >= count_)
    {
        return nullptr;
    }

    return static_cast<T*>(array_) + (sizeof(T) * index);
}

template<typename T>
const T* Array::push_back(const T& t) noexcept
{
    static_assert(std::is_trivially_copyable_v<T>, "T must be memcpy-able");
    constexpr size_t elem_size = sizeof(T);
    assert(count_ < size_);
    assert(elem_size == element_size_);
    if (count_ >= size_)
    {
        return nullptr;
    }

    return static_cast<const T*>(std::memcpy(static_cast<T*>(array_) + count_++, &t, elem_size));
}

template<typename T>
const T* Array::insert(size_t index, const T& t)
{
    static_assert(std::is_trivially_copyable_v<T>, "T must be memcpy-able");
    constexpr size_t elem_size = sizeof(T);
    assert(elem_size == element_size_);
    if (index >= size_)
    {
        return nullptr;
    }

    return static_cast<const T*>(std::memcpy(static_cast<T*>(array_) + index, &t, elem_size));
}

template<typename T, typename Allocator>
Array Array::create(size_t size)
{
    constexpr size_t element_size = sizeof(T);
    if constexpr (element_size == 0)
    {
        return Array{ size };
    }
    else
    {
        auto alloc = Allocator();
        T* array = alloc.allocate(size);
        return Array{ static_cast<void*>(array), size, element_size, [alloc](void* array, size_t size) mutable {
                         alloc.deallocate(static_cast<T*>(array), size);
                     } };
    }
}

}  // namespace ge::containers
