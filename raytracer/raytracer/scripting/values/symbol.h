#pragma once

#include "scripting/values/object.h"

namespace scripting
{
	class Symbol : public Object
	{
	public:
		Symbol(const std::string&);

		void write(std::ostream&) const override;
		bool operator ==(const Object&) const override;

		std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>) override;

		std::string name() const { return m_name; }

	private:
		std::string m_name;
	};
}
