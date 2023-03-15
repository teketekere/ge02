#include <ge/containers/array.hpp>

namespace ge::containers
{

Array::~Array()
{
    if (array_ != nullptr)
    {
        deallocator_(array_, size_);
    }
}

size_t Array::count() const noexcept
{
    return count_;
}

size_t Array::size() const noexcept
{
    return size_;
}

size_t Array::element_size() const noexcept
{
    return element_size_;
}

Array::Array(size_t size) noexcept : array_(nullptr), count_(0), size_(size), element_size_(0)
{
}

Array::Array(void* array, size_t size, size_t element_size, std::function<void(void*, size_t)> deallocator) noexcept
    : array_(array),
      count_(0),
      size_(size),
      element_size_(element_size),
      deallocator_(std::move(deallocator))
{
}

}  // namespace ge::containers
