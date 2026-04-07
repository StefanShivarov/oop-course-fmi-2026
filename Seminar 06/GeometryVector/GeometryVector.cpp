#include "GeometryVector.h"

void GeometryVector::copyFrom(const GeometryVector& other) {
    data = new double[other.dimension];
    for (size_t i = 0; i < other.dimension; i++) {
        data[i] = other.data[i];
    }
}

void GeometryVector::free() {
    delete[] data;
    data = nullptr;
    dimension = 0;
}

void GeometryVector::checkIndex(size_t index) const {
    if (index >= dimension) {
        throw std::out_of_range("Index out of range");
    }
}

void GeometryVector::checkSameDimension(const GeometryVector& other) const {
    if (dimension != other.dimension) {
        throw std::invalid_argument("Vectors must have the same dimension");
    }
}

GeometryVector::GeometryVector(size_t n)
    : dimension(n), data(new double[n]{}) {}

GeometryVector::GeometryVector(const GeometryVector& other) : dimension(other.dimension) {
    copyFrom(other);
}

GeometryVector& GeometryVector::operator=(const GeometryVector& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

GeometryVector::~GeometryVector() {
    free();
}

size_t GeometryVector::getDimension() const {
    return dimension;
}

double& GeometryVector::operator[](size_t index) {
    checkIndex(index);
    return data[index];
}

const double& GeometryVector::operator[](size_t index) const {
    checkIndex(index);
    return data[index];
}

GeometryVector::operator bool() const {
    for (size_t i = 0; i < dimension; i++) {
        if (data[i] != 0.0) {
            return true;
        }
    }
    return false;
}

GeometryVector GeometryVector::operator+() const {
    return *this;
}

GeometryVector GeometryVector::operator-() const {
    GeometryVector result(*this);
    result *= -1;
    return result;
}

GeometryVector& GeometryVector::operator+=(const GeometryVector& other) {
    checkSameDimension(other);

    for (size_t i = 0; i < dimension; i++) {
        data[i] += other.data[i];
    }

    return *this;
}

GeometryVector& GeometryVector::operator-=(const GeometryVector& other) {
    checkSameDimension(other);

    for (size_t i = 0; i < dimension; i++) {
        data[i] -= other.data[i];
    }

    return *this;
}

GeometryVector& GeometryVector::operator*=(double scalar) {
    for (size_t i = 0; i < dimension; i++) {
        data[i] *= scalar;
    }

    return *this;
}

GeometryVector& GeometryVector::operator/=(double scalar) {
    if (scalar == 0.0) {
        throw std::invalid_argument("Division by zero");
    }

    for (size_t i = 0; i < dimension; i++) {
        data[i] /= scalar;
    }

    return *this;
}

double GeometryVector::operator%(const GeometryVector& other) const {
    checkSameDimension(other);

    double result = 0.0;
    for (size_t i = 0; i < dimension; i++) {
        result += data[i] * other.data[i];
    }

    return result;
}

bool GeometryVector::operator|=(const GeometryVector& other) const {
    return *this % other == 0.0;
}

bool operator==(const GeometryVector& lhs, const GeometryVector& rhs) {
    if (lhs.getDimension() != rhs.getDimension()) {
        return false;
    }

    for (size_t i = 0; i < lhs.getDimension(); i++) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }

    return true;
}

bool operator!=(const GeometryVector& lhs, const GeometryVector& rhs) {
    return !(lhs == rhs);
}

// ! spaceship operator<=> !
std::partial_ordering operator<=>(const GeometryVector& lhs, const GeometryVector& rhs) {
    if (lhs.getDimension() < rhs.getDimension()) {
        return std::partial_ordering::less;
    }

    if (lhs.getDimension() > rhs.getDimension()) {
        return std::partial_ordering::greater;
    }

    for (size_t i = 0; i < lhs.getDimension(); i++) {
        // partial_ordering, because comparison of doubles also returns partial_ordering
        // due to NaN being a possible double value...
        if (auto cmp = lhs[i] <=> rhs[i]; cmp != 0) {
            return cmp;
        }
    }

    return std::partial_ordering::equivalent;
}

GeometryVector operator+(const GeometryVector& lhs, const GeometryVector& rhs) {
    GeometryVector result(lhs);
    result += rhs;
    return result;
}

GeometryVector operator-(const GeometryVector& lhs, const GeometryVector& rhs) {
    GeometryVector result(lhs);
    result -= rhs;
    return result;
}

GeometryVector operator*(const GeometryVector& v, double scalar) {
    GeometryVector result(v);
    result *= scalar;
    return result;
}

GeometryVector operator*(double scalar, const GeometryVector& v) {
    return v * scalar;
}

GeometryVector operator/(const GeometryVector& v, double scalar) {
    GeometryVector result(v);
    result /= scalar;
    return result;
}

std::ostream& operator<<(std::ostream& os, const GeometryVector& v) {
    os << '(';

    for (size_t i = 0; i < v.getDimension(); i++) {
        os << v[i];
        if (i + 1 < v.getDimension()) {
            os << ", ";
        }
    }

    os << ')';
    return os;
}

std::istream& operator>>(std::istream& is, GeometryVector& v) {
    for (size_t i = 0; i < v.getDimension(); i++) {
        is >> v[i];
    }

    return is;
}
