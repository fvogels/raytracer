#pragma once

#include "scripting/objects/object.h"
#include "scripting/environment.h"

namespace scripting
{
	std::shared_ptr<Object> evaluate(std::shared_ptr<Object> object, std::shared_ptr<Environment> environment, std::shared_ptr<scripting::Heap> heap);
}