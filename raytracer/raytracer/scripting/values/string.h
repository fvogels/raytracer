#pragma once

#include "scripting/values/object.h"

namespace scripting
{
	class String : public Object
	{
	public:
		String(const std::string&);

		void write(std::ostream&) const override;
		bool operator ==(const Object&) const override;

		std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>) override;

		std::string value() const;

	private:
		std::string m_value;
	};
}
