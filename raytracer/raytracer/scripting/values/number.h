#pragma once

#include "scripting/values/object.h"
#include "scripting/values/native-value-adapter.h"

namespace scripting
{
	class Number : public scripting::NativeValueAdapter<double>
	{
	public:
		using NativeValueAdapter<double>::NativeValueAdapter;

		std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>) override;
	};
}