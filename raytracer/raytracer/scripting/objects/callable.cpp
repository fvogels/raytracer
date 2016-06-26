#include "scripting/objects/callable.h"

using namespace scripting;


std::shared_ptr<Object> scripting::Callable::evaluate(std::shared_ptr<scripting::Environment>)
{
    throw std::runtime_error("Cannot evaluate callable object");
}

void scripting::Callable::write(std::ostream& out) const 
{
    out << "<Callable>"; 
}

bool scripting::Callable::operator ==(const Object&) const 
{
    return false; 
}