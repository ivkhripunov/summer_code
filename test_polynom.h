#include "test_vector.h"

template<typename Type, int N>
class Polynom : public Vector<Type, N> {

    static_assert(N >= 0);

    friend class Polynom<Type, N - 1>;

    friend class Polynom<Type, N + 1>;

private:

    using Vector<Type, N>::data_; //номер элемента соответствует степени

public:

    constexpr Polynom() = default;

    constexpr Polynom(const Polynom<Type, N> &other) {
        data_ = other.data_;
    }

    constexpr Polynom(const Vector<Type, N> &other) {
        data_ = other.get_data();
    }

    constexpr Polynom(std::initializer_list<Type> initializer) {
        for (auto i = 0; i < initializer.size(); ++i) data_[i] = *(initializer.begin() + i);
    }

    [[nodiscard]] unsigned int get_degree() const {
        return N - 1 - (std::find_if(std::rbegin(data_), std::rend(data_) - 1, [](auto &element) {
            return std::fabs(element - 0) > std::numeric_limits<double>::epsilon();
        }) - data_.rbegin());
    }

    Polynom<Type, N> &operator=(const Polynom<Type, N> &polynom) {
        data_ = polynom.get_data();

        return *this;
    }

    [[nodiscard]] Polynom<Type, N - 1> get_derivative() const {
        Polynom<Type, N - 1> derivative;

        for (auto i = 1; i < N; ++i) {
            derivative[i - 1] = data_[i] * i;
        }

        return derivative;
    }

    [[nodiscard]] Polynom<Type, N + 1> get_antiderivative(Type constant) const {
        Polynom<Type, N + 1> antiderivative;

        for (auto i = 0; i < N; ++i) {
            antiderivative[i + 1] = data_[i] / (i + 1);
        }

        antiderivative[0] = constant;

        return antiderivative;
    }

    [[nodiscard]] Polynom<Type, N> get_increased_degree_polynom(unsigned degree) const {
        if (this->get_degree() + degree <= data_.size()) {
            Polynom<Type, N> result;
            for (auto i = 0; i < this->get_degree() + 1; ++i) result[i + degree] = data_[i];

            return result;
        }
        return *this;
    }

    friend
    Polynom<Type, N> polynomial_long_division(Polynom<Type, N> numerator, const Polynom<Type, N> &denominator,
                                              Polynom<Type, N> &remainder) {

        Polynom<Type, N> result;
        const size_t denominator_degree = denominator.get_degree();

        if (numerator.get_degree() < denominator.get_degree()) {
            return numerator;
        }

        while (numerator.get_degree() >= denominator_degree) {

            result[numerator.get_degree() - denominator_degree] =
                    numerator[numerator.get_degree()] / denominator[denominator_degree];

            numerator -= denominator.get_increased_degree_polynom(numerator.get_degree() - denominator.get_degree())
                         * (numerator[numerator.get_degree()] / denominator[denominator.get_degree()]);
        }

        remainder = numerator;

        return result;
    }

};

constexpr int Modified = -1;

template<typename Type>
class Polynom<Type, Modified> {

private:

    std::map<unsigned, Type> data_; //пары степень - коэффициент

public:

    constexpr Polynom() = default;

    constexpr Polynom(const Polynom<Type, Modified> &other) {
        data_ = other.data_;
    }

    constexpr Polynom(std::initializer_list<std::pair<unsigned, Type>> initializer) {
        for (const auto &pair: initializer) data_.insert(pair);
    }

    const Type &operator[](unsigned int i) const {
        if (data_.contains(i)) return data_[i];
        const Type &tmp = 0;
        return tmp;
    }

    Type &operator[](unsigned int i) {
        if (data_.contains(i)) return data_[i];
        Type tmp = 0;
        return tmp;
    }

    Polynom<Type, Modified> operator*=(Type num) {
        for (auto &pair: data_) pair.second *= num;
        return *this;
    }

    Polynom<Type, Modified> operator/=(Type num) {
        for (auto &pair: data_) pair.second /= num;
        return *this;
    }

    Polynom<Type, Modified> operator+=(const Polynom<Type, Modified> &other) {
        for (const auto &pair: other.data_) {
            if (data_.contains(pair.first)) data_[pair.first] += pair.second;
            else data_.insert(pair);
        }
        return *this;
    }

    Polynom<Type, Modified> operator-=(const Polynom<Type, Modified> &other) {
        for (const auto &pair: other.data_) {
            if (data_.contains(pair.first)) data_[pair.first] -= pair.second;
            else data_.insert(pair);
        }

        return *this;
    }

    Polynom<Type, Modified> operator*(Type num) const {
        Polynom<Type, Modified> result(*this);
        result *= num;

        return result;
    }

    Polynom<Type, Modified> operator/(Type num) const {
        Polynom<Type, Modified> result(*this);
        result /= num;

        return result;
    }

    Polynom<Type, Modified> operator+(const Polynom<Type, Modified> &other) const {
        Polynom<Type, Modified> result(*this);
        result += other;

        return result;
    }

    Polynom<Type, Modified> operator-(const Polynom<Type, Modified> &other) const {
        Polynom<Type, Modified> result(*this);
        result -= other;

        return result;
    }

    friend Polynom<Type, Modified> operator*(Type num, const Polynom<Type, Modified> &polynom) {
        return polynom * num;
    }

    bool operator==(const Polynom<Type, Modified> &other) const {
        return data_ == other.data_;
    }

    bool operator!=(const Polynom<Type, Modified> &other) const {
        return data_ != other.data_;
    }

    Polynom<Type, Modified> &operator=(const Polynom<Type, Modified> &other) {
        data_ = other.data_;

        return *this;
    }

    [[nodiscard]] Polynom<Type, Modified> get_derivative() const {
        Polynom<Type, Modified> result;

        for (const auto &pair: data_) if (pair.first != 0) result[pair.first - 1] = pair.second * pair.first;

        return result;
    }

    [[nodiscard]] Polynom<Type, Modified> get_antiderivative(Type constant) const {
        Polynom<Type, Modified> result;

        for (const auto &pair: data_) result[pair.first + 1] = pair.second / (pair.first + 1);
        result[0] = constant;

        return result;
    }

    [[nodiscard]] unsigned get_degree() const {
        return (*std::find_if(std::rbegin(data_), std::rend(data_), [](auto &element) {
            return std::fabs(element.second - 0) > std::numeric_limits<double>::epsilon();
        })).first;
    }

    [[nodiscard]] Polynom<Type, Modified> get_increased_degree_polynom(unsigned degree) const {

        Polynom<Type, Modified> result;
        for (const auto &pair: data_) result.data_.insert({pair.first + degree, pair.second});

        return result;

    }

    Polynom<Type, Modified> clean_zero_values() {
        std::erase_if(data_, [](auto &element) {
            return std::fabs(element.second - 0) < std::numeric_limits<double>::epsilon();
        });

        return *this;
    }

    friend
    Polynom<Type, Modified>
    polynomial_long_division(Polynom<Type, Modified> numerator, Polynom<Type, Modified> &denominator,
                             Polynom<Type, Modified> &remainder) {

        Polynom<Type, Modified> result;
        const size_t denominator_degree = denominator.get_degree();

        if (numerator.get_degree() < denominator_degree) {
            return numerator;
        }

        while (numerator.get_degree() >= denominator_degree) {
            result.data_.insert({numerator.get_degree() - denominator_degree,
                                 numerator[numerator.get_degree()] /
                                 denominator[denominator_degree]});

            numerator -= denominator.get_increased_degree_polynom(numerator.get_degree() - denominator.get_degree())
                         * (numerator.data_[numerator.get_degree()] / denominator.data_[denominator_degree]);
        }

        remainder = numerator.clean_zero_values();

        return result;
    }


    friend std::ostream &operator<<(std::ostream &out, const Polynom<Type, Modified> &polynom) {
        for (const auto &pair: polynom.data_) std::cout << "[" << pair.first << ", " << pair.second << "]";
        std::cout << std::endl;

        return out;
    }

};