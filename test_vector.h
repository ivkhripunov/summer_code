#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <initializer_list>
#include <algorithm>
#include <cmath>

template<typename Type, int N>
class Vector {

    static_assert(N >= 0);

protected:
    std::array<Type, N> data_;
public:
    constexpr Vector() {
        data_.fill(0);
    }

    constexpr Vector(const Vector<Type, N> &other) {
        data_ = other.data_;
    }

    constexpr Vector(std::initializer_list<Type> initializer) {
        for (auto i = 0; i < N; ++i) data_[i] = *(initializer.begin() + i);
    }

    const Type &operator[](unsigned int i) const {
        return data_[i];
    }

    Type &operator[](unsigned int i) {
        return data_[i];
    }

    [[nodiscard]] Type norm() const {
        Type square_sum = 0;

        for (const auto &element: data_) square_sum += element * element;

        return pow(square_sum, 0.5);
    }

    Vector<Type, N> operator*=(Type num) {
        for (auto &element: data_) element *= num;
        return *this;
    }

    Vector<Type, N> operator/=(Type num) {
        for (auto &element: data_) element /= num;
        return *this;
    }

    Vector<Type, N> operator+=(const Vector<Type, N> &other) {
        for (auto i = 0; i < N; ++i) data_[i] += other[i];
        return *this;
    }

    Vector<Type, N> operator-=(const Vector<Type, N> &other) {
        for (auto i = 0; i < N; ++i) data_[i] -= other[i];
        return *this;
    }

    Vector<Type, N> operator*(Type num) const {
        Vector<Type, N> result(*this);

        result *= num;

        return result;
    }

    Vector<Type, N> operator/(Type num) const {
        Vector<Type, N> result(*this);

        result /= num;

        return result;
    }

    Vector<Type, N> operator+(const Vector<Type, N> &other) const {
        Vector<Type, N> result(*this);

        result += other;

        return result;
    }

    Vector<Type, N> operator-(const Vector<Type, N> &other) const {
        Vector<Type, N> result(*this);

        result -= other;

        return result;
    }

    friend Vector<Type, N> operator*(Type num, const Vector<Type, N> &vec) {
        return vec * num;
    }

    bool operator==(const Vector<Type, N> &other) const {
        return data_ == other.data_;
    }

    bool operator!=(const Vector<Type, N> &other) const {
        return data_ != other.data_;
    }

    Vector<Type, N> &operator=(const Vector<Type, N> &other) {
        data_ = other.data_;

        return *this;
    }


    friend std::ostream &operator<<(std::ostream &out, const Vector<Type, N> &vec) {
        for (const auto &element: vec.data_) out << element << " ";
        out << std::endl;

        return out;
    }

    std::array<Type, N> get_data() const {
        return data_;
    }
};

constexpr int Dynamic = -1;

template<typename Type>
class Vector<Type, Dynamic> {

protected:
    std::vector<Type> data_;

public:
    constexpr Vector() = default;

    constexpr Vector(const Vector<Type, Dynamic> &other) {
        data_ = other.data_;
    }

    constexpr Vector(std::initializer_list<Type> initializer) {
        data_.resize(initializer.size());
        for (auto i = 0; i < data_.size(); ++i) data_[i] = *(initializer.begin() + i);
    }

    const Type &operator[](unsigned int i) const {
        return data_[i];
    }

    Type &operator[](unsigned int i) {
        return data_[i];
    }

    [[nodiscard]] Type norm() const {
        Type square_sum = 0;

        for (const auto &element: data_) square_sum += element * element;

        return pow(square_sum, 0.5);
    }

    Vector<Type, Dynamic> operator*=(Type num) {
        for (auto &element: data_) element *= num;
        return *this;
    }

    Vector<Type, Dynamic> operator/=(Type num) {
        for (auto &element: data_) element /= num;
        return *this;
    }

    Vector<Type, Dynamic> operator+=(const Vector<Type, Dynamic> &other) {
        if (data_.size() != other.data_.size()) std::cout << "error: vectors have different sizes" << std::endl;
        else for (auto i = 0; i < data_.size(); ++i) data_[i] += other[i];
        return *this;
    }

    Vector<Type, Dynamic> operator-=(const Vector<Type, Dynamic> &other) {
        if (data_.size() != other.data_.size()) std::cout << "error: vectors have different sizes" << std::endl;
        for (auto i = 0; i < data_.size(); ++i) data_[i] -= other[i];
        return *this;
    }

    Vector<Type, Dynamic> operator*(Type num) const {
        Vector<Type, Dynamic> result(*this);

        result *= num;

        return result;
    }

    Vector<Type, Dynamic> operator/(Type num) const {
        Vector<Type, Dynamic> result(*this);

        result /= num;

        return result;
    }

    Vector<Type, Dynamic> operator+(const Vector<Type, Dynamic> &other) const {
        if (data_.size() != other.data_.size()) std::cout << "error: vectors have different sizes" << std::endl;
        else {
            Vector<Type, Dynamic> result(*this);

            result += other;

            return result;
        }
    }

    Vector<Type, Dynamic> operator-(const Vector<Type, Dynamic> &other) const {
        if (data_.size() != other.data_.size()) std::cout << "error: vectors have different sizes" << std::endl;
        else {
            Vector<Type, Dynamic> result(*this);

            result -= other;

            return result;
        }
    }

    friend Vector<Type, Dynamic> operator*(Type num, const Vector<Type, Dynamic> &vec) {
        return vec * num;
    }

    bool operator==(const Vector<Type, Dynamic> &other) const {
        return data_ == other.data_;
    }

    bool operator!=(const Vector<Type, Dynamic> &other) const {
        return data_ != other.data_;
    }

    Vector<Type, Dynamic> &operator=(const Vector<Type, Dynamic> &vec) {
        data_ = vec.get_data();

        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector<Type, Dynamic> &vec) {
        for (const auto &element: vec.data_) out << element << " ";
        out << std::endl;

        return out;
    }
};

