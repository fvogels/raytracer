#include "scripting/heap.h"

using namespace scripting;


std::shared_ptr<scripting::Object> scripting::Heap::read(unsigned refid)
{
	auto it = m_heap.find(refid);

	if (it == m_heap.end())
	{
		throw std::runtime_error("invalid reference");
	}
	else
	{
		return m_heap.at(refid);
	}
}

void scripting::Heap::write(unsigned refid, std::shared_ptr<scripting::Object> object)
{
	m_heap[refid] = object;
}