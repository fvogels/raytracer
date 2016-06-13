#pragma once

#include "scripting/objects/object.h"

namespace scripting
{
	class Nil : public Object
	{
	public:
		Nil();

		void write(std::ostream&) const override;
		bool operator ==(const Object&) const override;

		std::shared_ptr<Object> evaluate(std::shared_ptr<Environment>) override;
	};
}
