#pragma once

struct Vector2 {
    float x, y;

    Vector2();
    Vector2(float x, float y);

    Vector2 operator+(const Vector2& other);
    Vector2 operator-(const Vector2& other);

    Vector2 operator+=(const Vector2& other);
    Vector2 operator-=(const Vector2& other);

    Vector2 operator+(const float& other);
    Vector2 operator-(const float& other);
    Vector2 operator*(const float& other);
    Vector2 operator/(const float& other);

    Vector2 operator+=(const float& other);
    Vector2 operator-=(const float& other);
    Vector2 operator*=(const float& other);
    Vector2 operator/=(const float& other);

    float length();

    Vector2 normalized();

    float dot(const Vector2& other);
};

struct Vector3 {
    float x, y, z;

    Vector3();
    Vector3(float x, float y, float z);

    Vector3 operator+(const Vector3& other);
    Vector3 operator-(const Vector3& other);

    Vector3 operator+=(const Vector3& other);
    Vector3 operator-=(const Vector3& other);

    Vector3 operator+(const float& other);
    Vector3 operator-(const float& other);
    Vector3 operator*(const float& other);
    Vector3 operator/(const float& other);

    Vector3 operator+=(const float& other);
    Vector3 operator-=(const float& other);
    Vector3 operator*=(const float& other);
    Vector3 operator/=(const float& other);

    float length();

    Vector3 normalized();

    float dot(const Vector3& other);
    Vector3 cross(const Vector3& other);
};
