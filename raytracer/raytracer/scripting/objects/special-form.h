#pragma once

#include "scripting/objects/callable.h"

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
			std::shared_ptr<Object> call(std::shared_ptr<scripting::Environment>, std::shared_ptr<scripting::Heap>, const std::vector<std::shared_ptr<Object>>&) const override;
		};

		class If : public SpecialForm
		{
		public:
			std::shared_ptr<Object> call(std::shared_ptr<scripting::Environment>, std::shared_ptr<scripting::Heap>, const std::vector<std::shared_ptr<Object>>&) const override;
		};
	}
}