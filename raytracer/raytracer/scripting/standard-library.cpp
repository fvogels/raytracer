#include "scripting/standard-library.h"
#include "scripting/objects/native-functions.h"
#include "scripting/objects/special-form.h"
#include "scripting/values.h"

using namespace scripting;


void scripting::add_standard_library_bindings(Environment* environment)
{
	environment->bind(Symbol("true"), std::make_shared<scripting::Boolean>(true));
	environment->bind(Symbol("false"), std::make_shared<scripting::Boolean>(false));
	environment->bind(Symbol("nil"), std::make_shared<scripting::Nil>());

#ifdef BIND
#error BIND macro already defined
#else
#define BIND(SYMBOL_NAME, CLASS) environment->bind(Symbol(SYMBOL_NAME), std::make_shared<scripting::library::CLASS>());
	
	BIND("let", Let);
	BIND("if", If);
	BIND("+", Addition);
	BIND("-", Subtraction);
	BIND("*", Multiplication);
	BIND("=", Equality);
	BIND("<", LessThan);
	BIND(">", GreaterThan);
	BIND("<=", NotGreaterThan);
	BIND(">=", NotLessThan);
	BIND("not", Negation);
	BIND("@", CreatePoint);
	BIND("->", CreateVector);
	BIND("x", GetX);
	BIND("y", GetY);
	BIND("z", GetZ);

#undef BIND
#endif
}