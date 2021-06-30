#pragma once

namespace math
{

	template<typename T>
	class Vec2
	{
	public:
		T x, y;


		Vec2(const T& _x, const T& _y) : x(_x), y(_y) {}
		Vec2(const Vec2<T>&& other) { operator=(other); }
		Vec2(Vec2<T>&& other) { operator=(other); }



		bool operator==(const Vec2<T>& other) const
		{
			return isZero(x - other.x) && isZero(y - other.y);
		}
		bool operator!=(const Vec2<T>& other) const
		{
			return !isZero(x - other.x) || !isZero(y - other.y);
		}
		Vec2<T>& operator=(const Vec2<T>& other)
		{
			x = other.x;
			y = other.y;
			return *this;
		}

		Vec2<T> operator+(const T& t) const
		{
			return { x + t, y + t };
		}
		Vec2<T> operator+(const Vec2<T>& other) const
		{
			return { x + other.x, y + other.y };
		}
		Vec2<T>& operator+=(const T& t)
		{
			x += t;
			y += t;
			return *this;
		}
		Vec2<T>& operator+=(const Vec2<T>& other) const
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		Vec2<T> operator-(const T& t) const
		{
			return { x - t, y - t };
		}
		Vec2<T> operator-(const Vec2<T>& other) const
		{
			return { x - other.x, y - other.y };
		}
		Vec2<T>& operator-=(const T& t)
		{
			x -= t;
			y -= t;
			return *this;
		}
		Vec2<T>& operator-=(const Vec2<T>& other) const
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		Vec2<T> operator*(const T& t) const
		{
			return { x * t, y * t };
		}
		Vec2<T> operator*(const Vec2<T>& other) const
		{
			return { x * other.x, y * other.y };
		}
		Vec2<T>& operator*=(const T& t)
		{
			x *= t;
			y *= t;
			return *this;
		}
		Vec2<T>& operator*=(const Vec2<T>& other) const
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		Vec2<T> operator/(const T& t) const
		{
			return { x / t, y / t };
		}
		Vec2<T> operator/(const Vec2<T>& other) const
		{
			return { x / other.x, y / other.y };
		}
		Vec2<T>& operator/=(const T& t)
		{
			x /= t;
			y /= t;
			return *this;
		}
		Vec2<T>& operator/=(const Vec2<T>& other) const
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}

		T Magnitude() const
		{
			return dist(0.f, 0.f, x, y);
		}
		Vec2<T> Normalized() const
		{
			return operator/(Magnitude());
		}
		Vec2<T>& Normalize()
		{
			return operator/= (Magnitude());
		}
		T Dot(const Vec2<T>& other) const
		{
			return x * other.x + y * other.y;
		}
		T Angle() const
		{
			return atan(x, y);
		}
		T AngleBetween(const Vec2<T>& other) const
		{
			return acos(Dot(other) / (Magnitude() * other.Magnitude()));
		}

	};
}