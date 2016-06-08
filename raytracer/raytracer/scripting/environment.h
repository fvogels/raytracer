#pragma once

#include "scripting/s-expression.h"
#include <memory>
#include <map>

namespace scripting
{
	class Environment
	{
	public:
		bool contains(const Symbol&) const;
		std::shared_ptr<const SExpression> lookup(const Symbol&) const;
		void bind(const Symbol&, std::shared_ptr<const SExpression> value);

	private:
		std::map<std::string, std::shared_ptr<const SExpression>> m_bindings;
	};
}