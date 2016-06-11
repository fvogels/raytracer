#pragma once

#include "scripting/values/object.h"

namespace scripting
{
	namespace library
	{
		class Addition : public Function
		{
		protected:
			std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;
		};

		class Subtraction : public Function
		{
		protected:
			std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;
		};

		class Multiplication : public Function
		{
		protected:
			std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;
		};
	}
}