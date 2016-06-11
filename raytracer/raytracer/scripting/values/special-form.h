#pragma once

#include "scripting/values/callable.h"

namespace scripting
{
	class SpecialForm : public Callable
	{

	};

	namespace library
	{
		class Let : public SpecialForm
		{
		public:
			std::shared_ptr<Object> call(std::shared_ptr<scripting::Environment>, const std::vector<std::shared_ptr<Object>>&) const override;
		};

		class If : public SpecialForm
		{
		public:
			std::shared_ptr<Object> call(std::shared_ptr<scripting::Environment>, const std::vector<std::shared_ptr<Object>>&) const override;
		};
	}
}