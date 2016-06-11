#pragma once

#include "scripting/values/object.h"

namespace scripting
{
	class List : public Object
	{
	public:
		List(const std::vector<std::shared_ptr<Object>>&);

		void write(std::ostream&) const override;
		bool operator ==(const Object&) const override;

		std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>) override;

		size_t size() const;
		std::shared_ptr<const Object> nth_element(size_t index) const;

	private:
		std::vector<std::shared_ptr<Object>> m_elements;
	};
}
