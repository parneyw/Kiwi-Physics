#pragma once

#include "vec2.hpp"

namespace ph
{

	class CircleBody
	{
	private:
		Vec2 m_pos;
		Vec2 m_oldPos;
		Vec2 m_vel;
		Vec2 m_force;
		float m_rad;
		float m_mass;
		float m_invMass;

	public:

		CircleBody() = default;

		CircleBody(const Vec2& pos, float rad, float mass) :
			m_pos(pos),
			m_oldPos(pos),
			m_vel(),
			m_force(),
			m_rad(rad),
			m_mass(mass),
			m_invMass(1.0f / mass)
		{}

		void move(float dt)
		{
			m_oldPos = m_pos;
			Vec2 acc = m_force * m_invMass;
			m_vel += acc * dt;
			m_pos += m_vel * dt;
			m_force -= m_force;
		}

		float getRadius() const
		{
			return m_rad;
		}

		Vec2 getPos() const
		{
			return m_pos;
		}

		void setPos(const Vec2& p)
		{
			m_pos = p;
		}

		void addPos(const Vec2& p)
		{
			m_pos += p;
			m_oldPos += p;
		}

		Vec2 getInterpolatedPos(float alpha) const
		{
			return Vec2(m_pos * alpha + m_oldPos * (1.0f - alpha));
		}

		Vec2 getVelocity() const
		{
			return m_vel;
		}
		
		void setVelocity(const Vec2& v)
		{
			m_vel = v;
		}

		float getMass() const
		{
			return m_mass;
		}

		void addForce(const Vec2& f)
		{
			m_force += Vec2(f.x, -f.y);
		}
	};

}