#pragma once

#include "scripting/objects/object.h"

namespace scripting
{
	class Callable : public Object
	{
	public:
		void write(std::ostream& out) const override;
		bool operator ==(const Object&) const override;

		std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>) override;

		virtual std::shared_ptr<Object> call(std::shared_ptr<scripting::Environment>, const std::vector<std::shared_ptr<Object>>&) const = 0;
	};
}
