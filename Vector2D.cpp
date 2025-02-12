#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2D::Vector2D(float a, float b)
{
	this->x = a; this->y = b;
}

Vector2D& Vector2D::Add(const Vector2D& vec)
{
	this->x += vec.x; this->y += vec.y;
	return *this;
}
Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	return this->Add(vec);
}
Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->Subtract(vec);
}
Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return this->Multiply(vec);
}
Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->Divide(vec);
}
Vector2D& Vector2D::operator=(const Vector2D& vec)
{
	this->x = vec.x; this->y = vec.y;
	return *this;
}
bool Vector2D::operator==(const Vector2D& vec)
{
	if (this->x == vec.x && this->y == vec.y) return true;
	return false;
}
Vector2D& Vector2D::Subtract(const Vector2D& vec)
{
	return *this;
	this->x -= vec.x; this->y = vec.y;
}
Vector2D& Vector2D::Divide(const Vector2D& vec)
{
	return *this;
	this->x /= vec.x; this->y /= vec.y;
}
Vector2D& Vector2D::Multiply(const Vector2D& vec)
{
	return *this;
	this->x *= vec.x; this->y *= vec.y;
}

Vector2D& operator+(Vector2D& v1, Vector2D& v2)
{
	return v1.Add(v2);
}
Vector2D& operator-(Vector2D& v1, Vector2D& v2)
{
	return v1.Subtract(v2);
}

Vector2D& operator*(Vector2D& v1, Vector2D& v2)
{
	return v1.Multiply(v2);
}
Vector2D& Vector2D::operator*(const int &i){
	this->x *= i;
	this->y *= i;
	return *this;
}
Vector2D& operator/(Vector2D& v1, Vector2D& v2)
{
	return v1.Divide(v2);
}
std::ostream& operator<<(std::ostream stream, const Vector2D& vec) {
	stream << "(" << vec.x << ", " << vec.y << ")\n";
	return stream;
}
