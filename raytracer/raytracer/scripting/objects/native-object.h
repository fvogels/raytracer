#pragma once

#include "scripting/environment.h"
#include "math/point3d.h"
#include "math/vector3d.h"

namespace scripting
{
	template<typename T>
	class NativeObject : public scripting::Object
	{
	public:
		NativeObject(T value)
			: m_value(value) { }

		void write(std::ostream& out) const override { out << m_value; }

		bool operator ==(const Object& object) const override
		{
			return m_value == object_cast<NativeObject<T>>(object).m_value;
		}

		std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>) override
		{
			return std::make_shared<NativeObject<T>>(this->m_value);
		}

		T value() const { return m_value; }

	protected:
		T m_value;
	};

	typedef NativeObject<std::string> String;
	typedef NativeObject<double> Number;
	typedef NativeObject<bool> Boolean;
	typedef NativeObject<math::Point3D> Point;
	typedef NativeObject<math::Vector3D> Vector;
}