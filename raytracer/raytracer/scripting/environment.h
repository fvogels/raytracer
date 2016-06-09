#pragma once

#include "scripting/values/object.h"
#include <memory>
#include <map>

namespace scripting
{
	class Environment
	{
	public:
		bool contains(const Symbol&) const;
		std::shared_ptr<const Object> lookup(const Symbol&) const;
		void bind(const Symbol&, std::shared_ptr<const Object> value);

	private:
		std::map<std::string, std::shared_ptr<const Object>> m_bindings;
	};
}