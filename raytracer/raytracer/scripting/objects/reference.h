#pragma once

#include "scripting/objects/object.h"

namespace scripting
{
	class Reference : public Object
	{
	public:
		Reference(unsigned);
		void write(std::ostream&) const override;
		bool operator ==(const Object&) const override;

		std::shared_ptr<Object> evaluate(std::shared_ptr<Environment>, std::shared_ptr<scripting::Heap>) override;

		unsigned id() const { return m_id; }

	private:
		unsigned m_id;
	};
}