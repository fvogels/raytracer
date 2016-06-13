#pragma once

#include "scripting/objects/readable.h"
#include "scripting/objects/writeable.h"
#include "scripting/heap.h"

namespace scripting
{
	class Reference : public Readable, public Writeable
	{
	public:
	};

	class HeapReference : public Reference
	{
	public:
		HeapReference();

		void write(std::ostream&) const override;
		bool operator ==(const Object&) const override;

		std::shared_ptr<Object> evaluate(std::shared_ptr<Environment>, std::shared_ptr<scripting::Heap>) override;

		std::shared_ptr<Object> read() const override;
		void write(std::shared_ptr<Object>) override;

	private:
		std::shared_ptr<Object> m_value;
	};
}