#ifndef ONEFLOW_CFG_REPEATED_FIELD_H_
#define ONEFLOW_CFG_REPEATED_FIELD_H_

#include <vector>
#include <string>
#include <memory>
#include <type_traits>

namespace oneflow {
namespace cfg {

template<typename T>
class _RepeatedField_ {
 public:
  static_assert(std::is_nothrow_move_constructible<T>::value, "");
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = T*;
  using const_pointer = const T*;
  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  _RepeatedField_(): data_(std::make_shared<std::vector<T>>()) {}
  _RepeatedField_(const std::shared_ptr<std::vector<T>>& data): data_(data) {}
  _RepeatedField_(const _RepeatedField_& other): data_(std::make_shared<std::vector<T>>()) {
    CopyFrom(other);
  }
  _RepeatedField_(_RepeatedField_&&) = default;
  ~_RepeatedField_() = default;

  iterator begin() noexcept { return data_->begin(); }
  const_iterator begin() const noexcept { return data_->begin(); }
  const_iterator cbegin() const noexcept { return data_->cbegin(); }

  iterator end() noexcept { return data_->end(); }
  const_iterator end() const noexcept { return data_->end(); }
  const_iterator cend() const noexcept { return data_->end(); }

  reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
  const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

  reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
  const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

  bool empty() const { return data_->empty(); }
  size_type size() const { return data_->size(); }
  reference at(size_type pos) { return data_->at(pos); }
  const_reference at(size_type pos) const { return data_->at(pos); }
  reference operator[](size_type pos) { return data_[pos]; }
  const_reference operator[](size_type pos) const { return data_[pos]; }

  pointer Mutable(size_type pos) { return &data_->at(pos); }
  const_reference Get(size_type pos) const { return data_->at(pos); }

  void Clear() { data_->clear(); }
  void CopyFrom(const _RepeatedField_& other) {
    if (std::is_scalar<T>::value || std::is_same<std::string, T>::value) {
      *data_ = *other.data_;
    } else {
      data_->clear();
      for (const auto& elem : other) { *Add() = elem; }
    }
  }

  _RepeatedField_& operator=(const _RepeatedField_& other) {
    CopyFrom(other);
    return *this;
  }

  void Set(size_type pos, const T& elem) {
    data_->at(pos) = elem;
  }
  void Add(const T& elem) {
    data_->push_back(std::move(elem));
  }
  pointer Add() {
    data_->push_back(T());
    return &data_->at(data_->size() - 1);
  }

  const std::shared_ptr<std::vector<T>>& __SharedPtr__() const { return data_; }

  const std::shared_ptr<std::vector<T>>& __SharedPtr__() { return data_; }

 private:
  std::shared_ptr<std::vector<T>> data_;
};

}
}

#endif  // ONEFLOW_CFG_REPEATED_FIELD_H_
