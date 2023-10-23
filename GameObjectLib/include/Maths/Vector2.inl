#include <iostream>
#include <string>
#include "Maths/Vector2.h"

template <typename T>
Vector2<T> Vector2<T>::zero = Vector2<T>(0, 0);

template <typename T>
Vector2<T> Vector2<T>::one = Vector2<T>(1, 1);

template <typename T>
Vector2<T> Vector2<T>::up = Vector2<T>(0, 1);

template <typename T>
Vector2<T> Vector2<T>::down = Vector2<T>(0, -1);

template <typename T>
Vector2<T> Vector2<T>::left = Vector2<T>(-1, 0);

template <typename T>
Vector2<T> Vector2<T>::right = Vector2<T>(1, 0);

template <typename T>
Vector2<T> Vector2<T>::positiveInfinity = Vector2<T>(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity());

template <typename T>
Vector2<T> Vector2<T>::negativeInfinity = Vector2<T>(-std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity());

// Définition des méthodes de la classe Vector2
template <typename T>
T Vector2<T>::magnitude() const {
    return std::sqrt(x * x + y * y);
}

template <typename T>
Vector2<T> Vector2<T>::normalized() const {
    T mag = magnitude();
    if (mag != 0)
        return Vector2<T>(x / mag, y / mag);
    else
        return Vector2<T>(0, 0);
}

template <typename T>
T Vector2<T>::sqrMagnitude() const {
    return x * x + y * y;
}

template <typename T>
T Vector2<T>::operator[](int index) const {
    return (index == 0) ? x : y;
}

template <typename T>
bool Vector2<T>::Equals(const Vector2<T>& other) const {
    return x == other.x && y == other.y;
}

template <typename T>
void Vector2<T>::Normalize() {
    T mag = magnitude();
    if (mag != 0) {
        x /= mag;
        y /= mag;
    }
}

template <typename T>
void Vector2<T>::Set(T x, T y) {
    this->x = x;
    this->y = y;
}

template <typename T>
std::string Vector2<T>::ToString() const {
    return "Vector2(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

template <typename T>
T Vector2<T>::Angle(const Vector2<T>& from, const Vector2<T>& to) {
    T dot = from.x * to.x + from.y * to.y;
    T magFrom = from.magnitude();
    T magTo = to.magnitude();
    return std::acos(dot / (magFrom * magTo)) * (180.0 / 3.14);
}

template <typename T>
Vector2<T> Vector2<T>::ClampMagnitude(const Vector2<T>& vector, T maxLength) {
    T mag = vector.magnitude();
    if (mag > maxLength) {
        return vector.normalized() * maxLength;
    }
    else {
        return vector;
    }
}

template <typename T>
T Vector2<T>::Distance(const Vector2<T>& a, const Vector2<T>& b) {
    Vector2<T> delta = b - a;
    return delta.magnitude();
}

template <typename T>
T Vector2<T>::Dot(const Vector2<T>& a, const Vector2<T>& b) {
    return a.x * b.x + a.y * b.y;
}

template <typename T>
Vector2<T> Vector2<T>::Lerp(const Vector2<T>& a, const Vector2<T>& b, T t) {
    t = std::max(T(0), std::min(T(1), t));
    return a + (b - a) * t;
}

template <typename T>
Vector2<T> Vector2<T>::LerpUnclamped(const Vector2<T>& a, const Vector2<T>& b, T t) {
    return a + (b - a) * t;
}

template <typename T>
Vector2<T> Vector2<T>::Max(const Vector2<T>& a, const Vector2<T>& b) {
    return Vector2<T>(std::max(a.x, b.x), std::max(a.y, b.y));
}

template <typename T>
Vector2<T> Vector2<T>::Min(const Vector2<T>& a, const Vector2<T>& b) {
    return Vector2<T>(std::min(a.x, b.x), std::min(a.y, b.y));
}

template <typename T>
Vector2<T> Vector2<T>::MoveTowards(const Vector2<T>& current, const Vector2<T>& target, T maxDistanceDelta) {
    Vector2<T> delta = target - current;
    T distance = delta.magnitude();
    if (distance <= maxDistanceDelta || distance == 0) {
        return target;
    }
    else {
        return current + delta.normalized() * maxDistanceDelta;
    }
}

template <typename T>
Vector2<T> Vector2<T>::Perpendicular(const Vector2<T>& vector) {
    return Vector2<T>(-vector.y, vector.x);
}

template <typename T>
Vector2<T> Vector2<T>::Reflect(const Vector2<T>& inDirection, const Vector2<T>& inNormal) {
    return inDirection - 2 * Dot(inDirection, inNormal) * inNormal;
}

template <typename T>
Vector2<T> Vector2<T>::Scale(const Vector2<T>& a, const Vector2<T>& b) {
    return Vector2<T>(a.x * b.x, a.y * b.y);
}

template <typename T>
T Vector2<T>::SignedAngle(const Vector2<T>& from, const Vector2<T>& to) {
    T angle = Angle(from, to);
    T cross = from.x * to.y - from.y * to.x;
    return (cross >= 0) ? angle : -angle;
}

template <typename T>
Vector2<T> Vector2<T>::operator-() const {
    return Vector2<T>(-x, -y);
}

template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& other) const {
    return Vector2<T>(x + other.x, y + other.y);
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& other) const {
    return Vector2<T>(x - other.x, y - other.y);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(T scalar) const {
    return Vector2<T>(x * scalar, y * scalar);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(T scalar) const {
    if (scalar != 0)
        return Vector2<T>(x / scalar, y / scalar);
    else
        return Vector2<T>(0, 0);
}

template <typename T>
bool Vector2<T>::operator==(const Vector2<T>& other) const {
    return Equals(other);
}