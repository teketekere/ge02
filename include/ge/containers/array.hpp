#pragma once

#include <cassert>
#include <cstddef>
#include <cstring>
#include <functional>
#include <memory>
#include <type_traits>

namespace ge::containers
{

/**
 * @brief Arrat iterator
 */
template<typename T>
class ArrayIterator
{
    T* ptr_;
    size_t index_;

  public:
    explicit ArrayIterator(T* ptr, size_t index) : ptr_(ptr), index_(index)
    {
    }

    T& operator*() const
    {
        return *(ptr_ + index_);
    }

    T* operator->()
    {
        return ptr_ + index;
    }

    ArrayIterator& operator++() noexcept
    {
        index_++;
        return *this;
    }

    bool operator==(const ArrayIterator& other) const noexcept
    {
        return index_ == other.index_;
    }

    bool operator!=(const ArrayIterator& other) const noexcept
    {
        return index_ != other.index_;
    }
};

/**
 * @brief (Typed) View of array.
 */
template<typename T>
class ArrayView
{
    T* array_;
    size_t size_;

  public:
    explicit ArrayView(T* array, size_t size) : array_(array), size_(size)
    {
    }

    ~ArrayView() = default;
    ArrayView(const ArrayView& other) = default;
    ArrayView(ArrayView&& other) noexcept = default;
    ArrayView& operator=(const ArrayView& other) = default;
    ArrayView& operator=(ArrayView&& other) noexcept = default;

    [[nodiscard]] ArrayIterator<T> begin() noexcept
    {
        return ArrayIterator<T>{ array_, 0 };
    }

    [[nodiscard]] ArrayIterator<T> end() noexcept
    {
        return ArrayIterator<T>{ array_, size_ };
    }
};

/**
 * @brief Array with the following features.
 *
 * + Fixed size.
 * + Type is erassured.
 *
 * Must call deallocate to free memory before calling destructor.
 */
class Array
{
    //! Data array.
    void* array_;

    //! Capacity.
    size_t size_;

    //! Size of each element.
    //! This member can be removed if element size assertion is not needed
    size_t element_size_;

  public:
    ~Array();
    Array(const Array& other) = delete;
    Array(Array&& other) noexcept = delete;
    Array& operator=(const Array& other) = delete;
    Array& operator=(Array&& other) noexcept = delete;

    /**
     * @brief Return a pointer to the specified element.
     *
     * @tparam T Type of element.
     * @param[in] index Index of the element to return.
     * @return const T* A pointer to the specified element.
     */
    template<typename T>
    const T* at(size_t index) const noexcept;

    /**
     * @brief Return a pointer to the specified element.
     *
     * @tparam T Type of element.
     * @param[in] index Index of the element to return.
     * @return T* A pointer to the specified element.
     */
    template<typename T>
    T* at(size_t index) noexcept;

    /**
     * @brief Returns an iterator to the beginning.
     *
     * @tparam T Element type.
     * @return ArrayIterator<T> Iterator.
     */
    template<typename T>
    ArrayIterator<T> begin() noexcept;

    /**
     * @brief Returns an iterator to the end.
     *
     * @tparam T Element type.
     * @return ArrayIterator<T> Iterator.
     */
    template<typename T>
    ArrayIterator<T> end() noexcept;

    /**
     * @brief Returns view instance of this array.
     *
     * @tparam T Type of element.
     * @return ArrayView<T> View.
     */
    template<typename T>
    ArrayView<T> view() noexcept;

    /**
     * @brief Return capacity.
     */
    [[nodiscard]] size_t size() const noexcept;

    /**
     * @brief Return size of element.
     */
    [[nodiscard]] size_t element_size() const noexcept;

    /**
     * @brief Deallocate memory.
     *
     * @tparam T Type of element.
     * @tparam Allocator Custome allocator type.
     */
    template<typename T, typename Allocator = std::allocator<T>>
    void deallocate();

    /**
     * @brief Create new instance.
     *
     * @tparam T Type of element.
     * @tparam Allocator Custom allocator type.
     *
     * @param[in] size Capacity.
     * @return Array Created instance.
     */
    template<typename T, typename Allocator = std::allocator<T>>
    static Array create(size_t size);

  private:
    Array(void* array, size_t size, size_t element_size) noexcept;
};

template<typename T>
const T* Array::at(size_t index) const noexcept
{
    constexpr size_t elem_size = sizeof(T);
    assert(elem_size == element_size_);
    if (index >= size_)
    {
        return nullptr;
    }

    const T* ptr = static_cast<const T*>(array_) + index;
    return ptr;
}

template<typename T>
T* Array::at(size_t index) noexcept
{
    constexpr size_t elem_size = sizeof(T);
    assert(elem_size == element_size_);
    if (index >= size_)
    {
        return nullptr;
    }

    T* ptr = static_cast<T*>(array_) + index;
    return ptr;
}

template<typename T>
ArrayIterator<T> Array::begin() noexcept
{
    return ArrayIterator<T>{ static_cast<T*>(array_), 0 };
}

template<typename T>
ArrayIterator<T> Array::end() noexcept
{
    return ArrayIterator<T>{ static_cast<T*>(array_), size_ };
}

template<typename T>
ArrayView<T> Array::view() noexcept
{
    return ArrayView<T>{ static_cast<T*>(array_), size_ };
}

template<typename T, typename Allocator>
void Array::deallocate()
{
    auto alloc = Allocator();
    alloc.deallocate(static_cast<T*>(array_), size_);
}

template<typename T, typename Allocator>
Array Array::create(size_t size)
{
    constexpr size_t element_size = sizeof(T);
    auto alloc = Allocator();
    T* array = alloc.allocate(size);
    return Array{ static_cast<void*>(array), size, element_size };
}

}  // namespace ge::containers
