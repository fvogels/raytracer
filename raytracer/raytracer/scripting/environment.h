#pragma once

#include "scripting/values/object.h"
#include <memory>
//#include <map>

namespace scripting
{
	class Environment
	{
	public:
		Environment();
		Environment(std::shared_ptr<Environment>);
		~Environment();

		bool is_bound(const Symbol&) const;
		std::shared_ptr<const Object> lookup(const Symbol&) const;
		void bind(const Symbol&, std::shared_ptr<const Object> value);

	private:
		struct Impl;
		std::unique_ptr<Impl> m_pimpl;
		//std::map<std::string, std::shared_ptr<const Object>> m_bindings;
		//std::shared_ptr<Environment> m_parent;
	};
}