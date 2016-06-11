#pragma once

#include "scripting/values/object.h"
#include "scripting/values/native-value-adapter.h"

namespace scripting
{
	class String : public NativeValueAdapter<std::string>
	{
	public:
		String(const std::string&);

		std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>) override;
	};
}
