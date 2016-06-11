#pragma once

#include "scripting/values/native-value-adapter.h"

namespace scripting
{
	template<typename T>
	class NativeValueAdapter : public scripting::Object
	{
	public:
		void write(std::ostream& out) const override { out << m_value; }

		bool operator ==(const Object& object) const override
		{
			return m_value == value_cast<NativeValueAdapter<T>>(object).m_value;
		}

		T value() const { return m_value; }

	protected:
		NativeValueAdapter(T value)
			: m_value(value) { }

		T m_value;
	};
}