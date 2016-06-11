#pragma once

#include "scripting/values/object.h"


namespace scripting
{
	class Boolean : public scripting::Object
	{
	public:
		Boolean(bool value);

		void write(std::ostream&) const override;
		bool operator ==(const Object&) const override;

		std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>) override;

		bool value() const;

	private:
		bool m_value;
	};
}