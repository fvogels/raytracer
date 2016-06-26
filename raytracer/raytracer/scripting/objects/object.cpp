#include "scripting/objects/object.h"

using namespace scripting;

scripting::Object::Object()
{
    // NOP
}

bool scripting::operator !=(const Object& a, const Object& b)
{
    return !(a == b);
}

std::ostream& scripting::operator <<(std::ostream& out, const Object& object)
{
    object.write(out);

    return out;
}
