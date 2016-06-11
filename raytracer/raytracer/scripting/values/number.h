#pragma once

#include "scripting/values/object.h"

namespace scripting
{
	class Number : public scripting::Object
	{
	public:
		Number(double value);

		void write(std::ostream&) const override;
		bool operator ==(const Object&) const override;

		std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>) override;

		double value() const;

	private:
		double m_value;
	};
}