#include "scripting/standard-library.h"
#include "scripting/values/native-functions.h"
#include "scripting/values/special-form.h"

using namespace scripting;


void scripting::add_standard_library_bindings(Environment* environment)
{
	environment->bind(Symbol("let"), std::make_shared<scripting::Let>());

#ifdef BIND
#error BIND macro already defined
#else
#define BIND(SYMBOL_NAME, CLASS) environment->bind(Symbol(SYMBOL_NAME), std::make_shared<scripting::library::CLASS>());
	
	BIND("+", Addition);
	BIND("-", Subtraction);
	BIND("*", Multiplication);

#undef BIND
#endif
}