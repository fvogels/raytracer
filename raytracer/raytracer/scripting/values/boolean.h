#pragma once

#include "scripting/values/object.h"
#include "scripting/values/native-value-adapter.h"


namespace scripting
{
	class Boolean : public scripting::NativeValueAdapter<bool>
	{
	public:
		Boolean(bool);

		std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>) override;
	};
}