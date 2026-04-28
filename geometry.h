#ifndef GEOMETRY_H
#define GEOMETRY_H

struct Vector3 {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

Vector3 operator+(const Vector3& a, const Vector3& b);
Vector3 operator-(const Vector3& a, const Vector3& b);
Vector3 operator*(double value, const Vector3& vector);
Vector3 operator/(const Vector3& vector, double value);

double squared_length(const Vector3& vector);
double distance_between(const Vector3& a, const Vector3& b);

#endif
用途： 定义三维坐标 Vector3，用于保存原子坐标、做向量加减、乘法、距离计算。