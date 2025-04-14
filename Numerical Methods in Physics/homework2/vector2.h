#include <cmath>

template <typename T>
class Vector2
{
public:
    T x, y;

    // Constructor
    Vector2(T x, T y) : x(x), y(y) {}

    // Vector addition - modifying the vector
    Vector2<T> operator+=(const Vector2<T> &other)
    {
        return Vector2<T>(x += other.x, y += other.y);
    }

    // Vector subtraction - modifying the vector
    Vector2<T> operator-=(const Vector2<T> &other)
    {
        return Vector2<T>(x -= other.x, y -= other.y);
    }

    // Vector multiplication with scalar - modifying the vector
    Vector2<T> operator*=(T scalar)
    {
        return Vector2<T>(x *= scalar, y *= scalar);
    }

    // Vector division by scalar
    Vector2<T> operator/=(T scalar)
    {
        return Vector2<T>(x /= scalar, y /= scalar);
    }
};

// Vector magnitude (length)
template <typename T>
double length(const Vector2<T> &v)
{
    double val = sqrt(v.x * v.x + v.y * v.y);
    return val;
}

// Square of the vector's magnitude
template <typename T>
double sqlength(const Vector2<T> &v)
{
    double val = (v.x * v.x + v.y * v.y);
    return val;
}

// Normalize the vector
template <typename T>
Vector2<double> normalized(const Vector2<T> &v)
{
    double len = length(v);
    if (len != 0)
    {
        return Vector2<double>(v.x / len, v.y / len);
    }
    return Vector2<double>(0, 0);
}

// Dot product
template <typename T, typename K>
T dot(const Vector2<T> &v1, const Vector2<K> &v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

// Vector addition
template <typename T>
Vector2<T> operator+(Vector2<T> const &a, Vector2<T> const &b)
{
    return Vector2<T>(a.x + b.x, a.y + b.y);
}

// Vector subtraction
template <typename T>
Vector2<T> operator-(Vector2<T> const &a, Vector2<T> const &b)
{
    return Vector2<T>(a.x - b.x, a.y - b.y);
}

// Scalar multiplication - from the right
template <typename T>
Vector2<T> operator*(Vector2<T> const &v, T const &scalar)
{
    return Vector2<T>(v.x * scalar, v.y * scalar);
}

// Scalar multiplication - from the left
template <typename T>
Vector2<T> operator*(T const &scalar, Vector2<T> const &v)
{
    return Vector2<T>(v.x * scalar, v.y * scalar);
}

// Scalar division
template <typename T>
Vector2<T> operator/(Vector2<T> const &v, T const &scalar)
{
    return Vector2<T>(v.x / scalar, v.y / scalar);
}
