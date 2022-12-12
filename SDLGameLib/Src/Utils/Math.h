#pragma once

struct Vec2
{
    Vec2() = default;
    Vec2(const float x, const float y) : x{ x }, y{ y } {}
	float x, y;

    const Vec2&& operator+(const float value) noexcept { return { this->x + value , this->y + value }; }
    const Vec2&& operator-(const float value) noexcept { return { this->x - value , this->y - value}; }
    const Vec2&& operator*(const float value) noexcept { return { this->x * value , this->y * value}; }
    const Vec2&& operator/(const float value) noexcept { return { this->x / value , this->y / value}; }
    void operator+=(const float value) { this->x += value, this->y += value; }
    void operator-=(const float value) { this->x -= value, this->y -= value; }
    void operator*=(const float value) { this->x *= value, this->y *= value; }
    void operator/=(const float value) { this->x /= value, this->y /= value; }

    const Vec2&& operator+(const Vec2& value) noexcept { return { this->x + value.x , this->y + value.y }; }
    const Vec2&& operator-(const Vec2& value) noexcept { return { this->x - value.x , this->y - value.y }; }
    const Vec2&& operator*(const Vec2& value) noexcept { return { this->x * value.x , this->y * value.y }; }
    const Vec2&& operator/(const Vec2& value) noexcept { return { this->x / value.x , this->y / value.y }; }
    void operator+=(const Vec2& value) { this->x += value.x, this->y += value.y; }
    void operator-=(const Vec2& value) { this->x -= value.x, this->y -= value.y; }
    void operator*=(const Vec2& value) { this->x *= value.x, this->y *= value.y; }
    void operator/=(const Vec2& value) { this->x /= value.x, this->y /= value.y; }
};

struct Vec3
{
    Vec3() = default;
    Vec3(const float x, const float y, const float z) : x{ x }, y{ y }, z{ z } {}
	float x, y, z;

    const Vec3&& operator+(const float value) noexcept { return { this->x + value , this->y + value, this->z + value }; }
    const Vec3&& operator-(const float value) noexcept { return { this->x - value , this->y - value, this->z - value }; }
    const Vec3&& operator*(const float value) noexcept { return { this->x * value , this->y * value, this->z * value }; }
    const Vec3&& operator/(const float value) noexcept { return { this->x / value , this->y / value, this->z / value }; }
    void operator+=(const float value) { this->x += value, this->y += value, this->z += value; }
    void operator-=(const float value) { this->x -= value, this->y -= value, this->z -= value; }
    void operator*=(const float value) { this->x *= value, this->y *= value, this->z *= value; }
    void operator/=(const float value) { this->x /= value, this->y /= value, this->z /= value; }

    const Vec3&& operator+(const Vec3& value) { return { this->x + value.x , this->y + value.y, this->z + value.z }; }
    const Vec3&& operator-(const Vec3& value) { return { this->x - value.x , this->y - value.y, this->z - value.z }; }
    const Vec3&& operator*(const Vec3& value) { return { this->x * value.x , this->y * value.y, this->z * value.z }; }
    const Vec3&& operator/(const Vec3& value) { return { this->x / value.x , this->y / value.y, this->z / value.z }; }
    void operator+=(const Vec3& value) { this->x += value.x, this->y += value.y, this->z += value.z; }
    void operator-=(const Vec3& value) { this->x -= value.x, this->y -= value.y, this->z -= value.z; }
    void operator*=(const Vec3& value) { this->x *= value.x, this->y *= value.y, this->z *= value.z; }
    void operator/=(const Vec3& value) { this->x /= value.x, this->y /= value.y, this->z /= value.z; }
};

struct Vec4
{
    Vec4() = default;
    Vec4(const float x, const float y, const float z, const float w) : x{ x }, y{ y }, z{ z }, w{ w } {}
	float x, y, z, w;

    const Vec4&& operator+(const float value) noexcept { return { this->x + value , this->y + value, this->z + value, this->w + value }; }
    const Vec4&& operator-(const float value) noexcept { return { this->x - value , this->y - value, this->z - value, this->w - value }; }
    const Vec4&& operator*(const float value) noexcept { return { this->x * value , this->y * value, this->z * value, this->w * value }; }
    const Vec4&& operator/(const float value) noexcept { return { this->x / value , this->y / value, this->z / value, this->w / value }; }
    void operator+=(const float value) { this->x += value, this->y += value, this->z += value, this->w += value; }
    void operator-=(const float value) { this->x -= value, this->y -= value, this->z -= value, this->w -= value; }
    void operator*=(const float value) { this->x *= value, this->y *= value, this->z *= value, this->w *= value; }
    void operator/=(const float value) { this->x /= value, this->y /= value, this->z /= value, this->w /= value; }

    const Vec4&& operator+(const Vec4& value) noexcept { return { this->x + value.x , this->y + value.y, this->z + value.z, this->w + value.w }; }
    const Vec4&& operator-(const Vec4& value) noexcept { return { this->x - value.x , this->y - value.y, this->z - value.z, this->w - value.w }; }
    const Vec4&& operator*(const Vec4& value) noexcept { return { this->x * value.x , this->y * value.y, this->z * value.z, this->w * value.w }; }
    const Vec4&& operator/(const Vec4& value) noexcept { return { this->x / value.x , this->y / value.y, this->z / value.z, this->w / value.w }; }
    void operator+=(const Vec4& value) { this->x += value.x, this->y += value.y, this->z += value.z, this->w += value.w; }
    void operator-=(const Vec4& value) { this->x -= value.x, this->y -= value.y, this->z -= value.z, this->w -= value.w; }
    void operator*=(const Vec4& value) { this->x *= value.x, this->y *= value.y, this->z *= value.z, this->w *= value.w; }
    void operator/=(const Vec4& value) { this->x /= value.x, this->y /= value.y, this->z /= value.z, this->w /= value.w; }
};
