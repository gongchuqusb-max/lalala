#include "geometry.h"

#include <cmath>

Vector3 operator+(const Vector3& a, const Vector3& b)
{
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

Vector3 operator-(const Vector3& a, const Vector3& b)
{
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

Vector3 operator*(double value, const Vector3& vector)
{
    return {value * vector.x, value * vector.y, value * vector.z};
}

Vector3 operator/(const Vector3& vector, double value)
{
    return {vector.x / value, vector.y / value, vector.z / value};
}

double squared_length(const Vector3& vector)
{
    return vector.x * vector.x
         + vector.y * vector.y
         + vector.z * vector.z;
}

double distance_between(const Vector3& a, const Vector3& b)
{
    return std::sqrt(squared_length(b - a));
}
用途： 实现三维向量的基本运算和两个原子之间的距离计算。