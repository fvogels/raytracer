#pragma once

#include "scripting/environment.h"
#include "math/point3d.h"
#include "math/vector3d.h"

namespace scripting
{
	template<typename T>
	class NativeValueAdapter : public scripting::Object
	{
	public:
		NativeValueAdapter(T value)
			: m_value(value) { }

		void write(std::ostream& out) const override { out << m_value; }

		bool operator ==(const Object& object) const override
		{
			return m_value == value_cast<NativeValueAdapter<T>>(object).m_value;
		}

		std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>) override
		{
			return std::make_shared<NativeValueAdapter<T>>(this->m_value);
		}

		T value() const { return m_value; }

	protected:
		T m_value;
	};

	typedef NativeValueAdapter<std::string> String;
	typedef NativeValueAdapter<double> Number;
	typedef NativeValueAdapter<bool> Boolean;
	typedef NativeValueAdapter<math::Point3D> Point;
	typedef NativeValueAdapter<math::Vector3D> Vector;
}