#pragma once

template<class T>
class Allocator {
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;
    
    pointer allocate(size_type count) {
        return new value_type[count];
    }

    void deallocate(pointer ptr) {
        delete[] ptr;
    }
    
    size_type max_size() const noexcept {
        return std::numeric_limits<size_type>::max();
    }
};

template<class T>
class Iterator {
    using size_type = std::size_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;
protected:
    pointer current_;
public:
    Iterator(pointer cur) 
        : current_(cur) {}
    
    bool operator==(const Iterator<T>& other) const {
        return current_ == other.current_;
    }

    bool operator!=(const Iterator<T>& other) const {
        return !(*this == other);
    }

    Iterator operator++(){
        current_++;
        return *this;
    }

    Iterator operator--(){
        current_--;
        return *this;
    }

    Iterator operator++(int unused){
        Iterator<value_type> result = *this;
        current_++;
        return result;
    }

    Iterator operator--(int unused){
        Iterator<value_type> result = *this;
        current_--;
        return result;
    }

    difference_type operator-(const Iterator<T>& other) {
        return current_ - other.current_;
    }

    reference operator*() const {
        return *current_;
    }
};

namespace std {
    template<class T>
    struct iterator_traits<Iterator<T>> {
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = random_access_iterator_tag;
    };
}

template<class T, class Alloc = Allocator<T>>
class Vector {
    using size_type = size_t;
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using const_reference = const T&;
    using allocator_type = Alloc;
    using iterator = Iterator<T>;
    using reverse_iterator =  std::reverse_iterator<iterator>;
private:
    size_type size_;
    size_type capacity_;
    pointer data_;
    allocator_type alloc_;
public:
    explicit Vector(size_type count = 0)
        : size_(count)
        , capacity_(count)
        , data_(alloc_.allocate(count)) {}
    Vector(size_type count, const value_type& defaultValue)
        : size_(count)
        , capacity_(count)
        , data_(alloc_.allocate(count)) {
        std::fill(begin(), end(), defaultValue);
    }
    Vector(std::initializer_list<value_type> init)
        : size_(init.size())
        , capacity_(init.size())
        , data_(alloc_.allocate(init.size())) {
        std::copy(init.begin(), init.end(), begin());
    }
    
    iterator begin() noexcept {
        return iterator(data_);
    }
    iterator end() noexcept {
        return iterator(data_ + size_);
    }
    reverse_iterator rbegin() noexcept {
        return reverse_iterator(data_ + size_);
    }
    reverse_iterator rend() noexcept {
        return reverse_iterator(data_);
    }
    
    void reserve( size_type new_cap ) {
        if (new_cap <= capacity_) {
            return;
        }
        pointer tmp = alloc_.allocate(new_cap);
        for (size_type i = 0; i < size_; i++) {
            tmp[i] = data_[i];
        }
        alloc_.deallocate(data_);
        data_ = tmp;
        capacity_ = new_cap;
    }

    void resize( size_type count ) {
        if (count <= size_) {
            size_ = count;
            return;
        }
        reserve(count);
        while (size_ < count) {
            data_[size_++] = value_type();
        }
    }

    size_type capacity() const noexcept {
        return capacity_;
    }
    size_type size() const noexcept {
        return size_;
    }
    bool empty() const noexcept {
        return size_ == 0;
    }
    void clear() noexcept {
        size_ = 0;
    }
    
    void push_back( const value_type& value ) {
        if (size_ == capacity_){
            if (capacity_ == 0) {
                capacity_++;
            }
            reserve(2 * capacity_);
        }
        data_[size_++] = value;
    }
    void pop_back() {
        if (size_ > 0){
            size_--;
        } else {
            throw std::out_of_range("Vector is empty");
        }
    }
    
    template< class... Args >
    void emplace_back( value_type first, Args&&... args ) {
        push_back(first);
        emplace_back(std::forward<Args>(args)...);
    }

    void emplace_back( value_type first ) {
        push_back(first);
    }
    
    value_type& operator[]( size_type i ) {
        return data_[i];
    }
    const value_type& operator[]( size_type i ) const {
        return data_[i];
    }
    
    ~Vector() {
        alloc_.deallocate(data_);
    }
};
