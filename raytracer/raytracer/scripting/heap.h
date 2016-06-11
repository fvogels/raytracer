#pragma once

#include "scripting/objects/object.h"
#include <map>
#include <memory>


namespace scripting
{
	class Heap
	{
	public:
		Heap() = default;

		std::shared_ptr<scripting::Object> read(unsigned);
		void write(unsigned, std::shared_ptr<scripting::Object>);

	private:
		std::map<unsigned, std::shared_ptr<scripting::Object>> m_heap;
	};
}