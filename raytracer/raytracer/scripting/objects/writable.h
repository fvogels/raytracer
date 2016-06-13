#pragma once

#include "scripting/objects/object.h"

namespace scripting
{
	class Writeable : public virtual Object
	{
	public:
		virtual void write(std::shared_ptr<Object>&) const = 0;
	};
}
