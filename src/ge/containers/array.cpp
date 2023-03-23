#include <ge/containers/array.hpp>

namespace ge::containers
{

Array::~Array()
{
}

size_t Array::size() const noexcept
{
    return size_;
}

size_t Array::element_size() const noexcept
{
    return element_size_;
}

Array::Array(void* array, size_t size, size_t element_size) noexcept
    : array_(array),
      size_(size),
      element_size_(element_size)
{
}

}  // namespace ge::containers
