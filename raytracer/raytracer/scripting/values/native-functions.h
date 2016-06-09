#pragma once

#include "scripting/values/object.h"

namespace scripting
{
	namespace library
	{
		class Addition : public Function
		{
		protected:
			std::shared_ptr<const Object> perform(const std::vector<std::shared_ptr<const Object>>&) const override;
		};

		class Multiplication : public Function
		{
		protected:
			std::shared_ptr<const Object> perform(const std::vector<std::shared_ptr<const Object>>&) const override;
		};
	}
}