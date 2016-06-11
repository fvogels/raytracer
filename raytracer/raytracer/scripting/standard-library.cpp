#include "scripting/standard-library.h"
#include "scripting/values/native-functions.h"
#include "scripting/values/special-form.h"
#include "scripting/values.h"

using namespace scripting;


void scripting::add_standard_library_bindings(Environment* environment)
{
	environment->bind(Symbol("let"), std::make_shared<scripting::Let>());
	environment->bind(Symbol("true"), std::make_shared<scripting::Boolean>(true));
	environment->bind(Symbol("false"), std::make_shared<scripting::Boolean>(false));

#ifdef BIND
#error BIND macro already defined
#else
#define BIND(SYMBOL_NAME, CLASS) environment->bind(Symbol(SYMBOL_NAME), std::make_shared<scripting::library::CLASS>());
	
	BIND("+", Addition);
	BIND("-", Subtraction);
	BIND("*", Multiplication);
	BIND("=", Equality);

#undef BIND
#endif
}