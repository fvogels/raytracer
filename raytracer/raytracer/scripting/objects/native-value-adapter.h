#pragma once

#include "scripting/environment.h"
#include "math/point3d.h"
#include "math/vector3d.h"

namespace scripting
{
	template<typename T, typename U>
	class NativeValueAdapter : public scripting::Object
	{
	public:
		NativeValueAdapter(T value)
			: m_value(value) { }

		void write(std::ostream& out) const override { out << m_value; }

		bool operator ==(const Object& object) const override
		{
			return m_value == value_cast<NativeValueAdapter<T, U>>(object).m_value;
		}

		std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>, std::shared_ptr<scripting::Heap>) override
		{
			return std::make_shared<U>(this->m_value);
		}

		T value() const { return m_value; }

	protected:
		T m_value;
	};

#ifdef DEFINE_NATIVE_VALUE_CLASS
#error DEFINE_NATIVE_VALUE_CLASS already defined
#else
#define DEFINE_NATIVE_VALUE_CLASS(T, U)  class U : public scripting::NativeValueAdapter<T, U> { using NativeValueAdapter<T, U>::NativeValueAdapter; };

	DEFINE_NATIVE_VALUE_CLASS(double, Number)
	DEFINE_NATIVE_VALUE_CLASS(bool, Boolean)
	DEFINE_NATIVE_VALUE_CLASS(std::string, String)
	DEFINE_NATIVE_VALUE_CLASS(math::Point3D, Point)
	DEFINE_NATIVE_VALUE_CLASS(math::Vector3D, Vector)

#undef DEFINE_NATIVE_VALUE_CLASS
#endif
}