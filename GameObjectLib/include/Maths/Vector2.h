#pragma once
#include <iostream>

template <typename T>
class Vector2 {
public:
    T x;
    T y;

    // Constructors
    Vector2() : x(0), y(0) {}
    Vector2(T x, T y) : x(x), y(y) {}

    // Static Properties
    static Vector2<T> zero;
    static Vector2<T> one;
    static Vector2<T> up;
    static Vector2<T> down;
    static Vector2<T> left;
    static Vector2<T> right;
    static Vector2<T> positiveInfinity;
    static Vector2<T> negativeInfinity;

    // Properties
    T magnitude() const;

    Vector2<T> normalized() const;

    T sqrMagnitude() const;

    T operator[](int index) const;

    // Public Methods
    bool Equals(const Vector2<T>& other) const;

    void Normalize();

    void Set(T x, T y);

    std::string ToString() const;

    // Static Methods
    static T Angle(const Vector2<T>& from, const Vector2<T>& to);

    static Vector2<T> ClampMagnitude(const Vector2<T>& vector, T maxLength);

    static T Distance(const Vector2<T>& a, const Vector2<T>& b);

    static T Dot(const Vector2<T>& a, const Vector2<T>& b);

    static Vector2<T> Lerp(const Vector2<T>& a, const Vector2<T>& b, T t);

    static Vector2<T> LerpUnclamped(const Vector2<T>& a, const Vector2<T>& b, T t);

    static Vector2<T> Max(const Vector2<T>& a, const Vector2<T>& b);

    static Vector2<T> Min(const Vector2<T>& a, const Vector2<T>& b);

    static Vector2<T> MoveTowards(const Vector2<T>& current, const Vector2<T>& target, T maxDistanceDelta);

    static Vector2<T> Perpendicular(const Vector2<T>& vector);

    static Vector2<T> Reflect(const Vector2<T>& inDirection, const Vector2<T>& inNormal);

    static Vector2<T> Scale(const Vector2<T>& a, const Vector2<T>& b);

    static T SignedAngle(const Vector2<T>& from, const Vector2<T>& to);

    // Operators
    Vector2<T> operator-() const;

    Vector2<T> operator+(const Vector2<T>& other) const;

    Vector2<T> operator-(const Vector2<T>& other) const;

    Vector2<T> operator*(T scalar) const;

    Vector2<T> operator/(T scalar) const;

    bool operator==(const Vector2<T>& other) const;
};

#include "Vector2.inl"