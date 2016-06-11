#pragma once

#include "scripting/values/object.h"
#include "scripting/values/native-value-adapter.h"

namespace scripting
{
	class String : public NativeValueAdapter<std::string>
	{
	public:
		using NativeValueAdapter<std::string>::NativeValueAdapter;

		std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>) override;
	};
}
