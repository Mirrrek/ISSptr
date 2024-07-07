#include "vector.hpp"
#include <cmath>

Vector2::Vector2() {
    x = 0;
    y = 0;
}

Vector2::Vector2(float _x, float _y) {
    x = _x;
    y = _y;
}

Vector2 Vector2::operator+(const Vector2& other) {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2 Vector2::operator-=(const Vector2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2 Vector2::operator+(const float& other) {
    return Vector2(x + other, y + other);
}

Vector2 Vector2::operator-(const float& other) {
    return Vector2(x - other, y - other);
}

Vector2 Vector2::operator*(const float& other) {
    return Vector2(x * other, y * other);
}

Vector2 Vector2::operator/(const float& other) {
    return Vector2(x / other, y / other);
}

Vector2 Vector2::operator+=(const float& other) {
    x += other;
    y += other;
    return *this;
}

Vector2 Vector2::operator-=(const float& other) {
    x -= other;
    y -= other;
    return *this;
}

Vector2 Vector2::operator*=(const float& other) {
    x *= other;
    y *= other;
    return *this;
}

Vector2 Vector2::operator/=(const float& other) {
    x /= other;
    y /= other;
    return *this;
}

float Vector2::length() {
    return sqrt(x * x + y * y);
}

Vector2 Vector2::normalized() {
    float l = length();
    return Vector2(x / l, y / l);
}

float Vector2::dot(const Vector2& other) {
    return x * other.x + y * other.y;
}

Vector3::Vector3() {
    x = 0;
    y = 0;
    z = 0;
}

Vector3::Vector3(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
}

Vector3 Vector3::operator+(const Vector3& other) {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator+=(const Vector3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3 Vector3::operator-=(const Vector3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3 Vector3::operator+(const float& other) {
    return Vector3(x + other, y + other, z + other);
}

Vector3 Vector3::operator-(const float& other) {
    return Vector3(x - other, y - other, z - other);
}

Vector3 Vector3::operator*(const float& other) {
    return Vector3(x * other, y * other, z * other);
}

Vector3 Vector3::operator/(const float& other) {
    return Vector3(x / other, y / other, z / other);
}

Vector3 Vector3::operator+=(const float& other) {
    x += other;
    y += other;
    z += other;
    return *this;
}

Vector3 Vector3::operator-=(const float& other) {
    x -= other;
    y -= other;
    z -= other;
    return *this;
}

Vector3 Vector3::operator*=(const float& other) {
    x *= other;
    y *= other;
    z *= other;
    return *this;
}

Vector3 Vector3::operator/=(const float& other) {
    x /= other;
    y /= other;
    z /= other;
    return *this;
}

float Vector3::length() {
    return sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::normalized() {
    float l = length();
    return Vector3(x / l, y / l, z / l);
}

float Vector3::dot(const Vector3& other) {
    return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::cross(const Vector3& other) {
    return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}
