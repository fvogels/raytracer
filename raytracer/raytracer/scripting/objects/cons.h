#pragma once

#include "scripting/objects/object.h"
#include <vector>

namespace scripting
{
	class Cons : public Object
	{
	public:
		Cons(std::shared_ptr<Object>, std::shared_ptr<Object>);

		void write(std::ostream&) const override;
		bool operator ==(const Object&) const override;

		std::shared_ptr<Object> evaluate(std::shared_ptr<Environment>, std::shared_ptr<scripting::Heap>) override;

		std::shared_ptr<Object> car();
		std::shared_ptr<Object> cdr();

		bool is_list() const;
		std::vector<std::shared_ptr<scripting::Object>> elements();

	private:
		std::shared_ptr<scripting::Object> m_car;
		std::shared_ptr<scripting::Object> m_cdr;
	};

	std::shared_ptr<Object> construct_list(std::vector<std::shared_ptr<Object>>);
}
