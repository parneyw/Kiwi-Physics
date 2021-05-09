#pragma once

#include <utility>
#include <math.h>
#include <iostream>

class Vec2
{
private:
	// First = value
	// Second = needs recalculating?
	std::pair<float, bool> m_mag;
	std::pair<float, bool> m_invMag;
	std::pair<float, bool> m_magSq;
	std::pair<float, bool> m_invMagSq;

public:
	float x;
	float y;

	Vec2() :
		x(0.0f), y(0.0f),
		m_mag({ 0.0f, true }),
		m_invMag({ 0.0f, true }),
		m_magSq({ 0.0f, true }),
		m_invMagSq({ 0.0f, true })
	{}

	Vec2(float pX, float pY) :
		x(pX), y(pY),
		m_mag({ 0.0f, true }),
		m_invMag({ 0.0f, true }),
		m_magSq({ 0.0f, true }),
		m_invMagSq({ 0.0f, true })
	{}

	float getMag()
	{
		if (m_mag.second)
		{
			m_mag.first = sqrtf(x * x + y * y);
			m_mag.second = false;
		}
		return m_mag.first;
	}

	float getInvMag()
	{
		// If magnitude already calculated ...
		if (!m_mag.second)
		{
			m_invMag.first = 1.0f / m_mag.first;
			m_invMag.second = false;
		}
		else if (m_invMag.second)
		{
			m_invMag.first = 1.0f / sqrtf(x * x + y * y);
			m_invMag.second = false;
		}
		return m_invMag.first;
	}

	float getMagSq()
	{
		if (m_magSq.second)
		{
			m_magSq.first = x * x + y * y;
			m_magSq.second = false;
		}
		return m_magSq.first;
	}

	float getInvMagSq()
	{
		// If magnitude squared already calculated ...
		if (!m_magSq.second)
		{
			m_invMagSq.first = 1.0f / m_magSq.first;
			m_invMagSq.second = false;
		}
		else if (m_invMagSq.second)
		{
			m_invMagSq.first = 1.0f / (x * x + y * y);
			m_invMagSq.second = false;
		}
		return m_invMagSq.first;
	}

	void normalise()
	{
		float mag = getInvMag();
		x /= mag;
		y /= mag;

		m_mag = { 1.0f, false };
		m_invMag = { 1.0f, false };
		m_magSq = { 1.0f, false };
		m_invMagSq = { 1.0f, false };
	}

	Vec2 getNormal(bool ccw=true) const
	{
		if (ccw)
			return Vec2(y, x);
		else
			return Vec2(-y, x);
	}

	void operator+=(const Vec2& v)
	{
		x += v.x;
		y += v.y;
	}

	void operator-=(const Vec2& v)
	{
		x -= v.x;
		y -= v.y;
	}

	void operator*=(float s)
	{
		x *= s;
		y *= s;
	}

	void operator/=(float s)
	{
		x /= s;
		y /= s;
	}

	float dot(const Vec2& v)
	{
		return (x * v.x + y * v.y);
	}
};

inline Vec2 operator+(const Vec2& v1, const Vec2& v2)
{
	return Vec2(v1.x + v2.x, v1.y + v2.y);
}

inline Vec2 operator-(const Vec2& v1, const Vec2& v2)
{
	return Vec2(v1.x - v2.x, v1.y - v2.y);
}

inline Vec2 operator-(const Vec2& v)
{
	return Vec2(-v.x, -v.y);
}

inline Vec2 operator*(const Vec2& v, float s)
{
	return Vec2(v.x * s, v.y * s);
}

inline Vec2 operator*(float s, const Vec2& v)
{
	return Vec2(v.x * s, v.y * s);
}

inline Vec2 getMidpoint(const Vec2& v1, const Vec2& v2)
{
	return (v1 + v2) * 0.5f;
}