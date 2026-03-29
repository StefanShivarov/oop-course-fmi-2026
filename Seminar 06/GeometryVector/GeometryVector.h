#pragma once
#include <iostream>
#include <compare>

class GeometryVector {
private:
    size_t dimension;
    double* data;

    void copyFrom(const GeometryVector& other);
    void free();

    void checkIndex(size_t index) const;
    void checkSameDimension(const GeometryVector& other) const;

public:
    explicit GeometryVector(size_t n);

    GeometryVector(const GeometryVector& other);
    GeometryVector& operator=(const GeometryVector& other);
    ~GeometryVector();

    size_t getDimension() const;

    double& operator[](size_t index);
    const double& operator[](size_t index) const;

    operator bool() const;

    GeometryVector operator+() const;
    GeometryVector operator-() const;

    GeometryVector& operator+=(const GeometryVector& other);
    GeometryVector& operator-=(const GeometryVector& other);
    GeometryVector& operator*=(double scalar);
    GeometryVector& operator/=(double scalar);

    double operator%(const GeometryVector& other) const; // scalar multiplication of 2 vectors
    bool operator|=(const GeometryVector& other) const; // orthogonal check
};

bool operator==(const GeometryVector& lhs, const GeometryVector& rhs);
bool operator!=(const GeometryVector& lhs, const GeometryVector& rhs);
std::partial_ordering operator<=>(const GeometryVector& lhs, const GeometryVector& rhs);

GeometryVector operator+(const GeometryVector& lhs, const GeometryVector& rhs);
GeometryVector operator-(const GeometryVector& lhs, const GeometryVector& rhs);
GeometryVector operator*(const GeometryVector& v, double scalar);
GeometryVector operator*(double scalar, const GeometryVector& v);
GeometryVector operator/(const GeometryVector& v, double scalar);

std::ostream& operator<<(std::ostream& os, const GeometryVector& v);
std::istream& operator>>(std::istream& is, GeometryVector& v);
