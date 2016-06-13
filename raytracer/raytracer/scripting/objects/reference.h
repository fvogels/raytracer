#pragma once

#include "scripting/objects/readable.h"
#include "scripting/objects/writeable.h"

namespace scripting
{
	class Reference : public Readable, public Writeable
	{
	public:
	};

	class ExternalReference : public Reference
	{
	public:
		ExternalReference(std::shared_ptr<Object>);

		void write(std::ostream&) const override;
		bool operator ==(const Object&) const override;

		std::shared_ptr<Object> evaluate(std::shared_ptr<Environment>) override;

		std::shared_ptr<Object> read() const override;
		void write(std::shared_ptr<Object>) override;

	private:
		std::shared_ptr<Object> m_value;
	};

	class HeapReference : public ExternalReference
	{
	public:
		HeapReference();
	};	
}