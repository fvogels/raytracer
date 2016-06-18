#ifdef TEST_BUILD

#include "Catch.h"
#include "scripting/interpreter.h"
#include "scripting/tokenizing/tokenizer.h"
#include "scripting/parser.h"
#include "scripting/objects.h"
#include "scripting/standard-library.h"
#include "scripting/environment.h"
#include "primitives/plane.h"
#include "materials/materials.h"
#include <sstream>

using namespace scripting;

template<typename T>
using NO = NativeObject<T>;

template<typename T>
using LNO = NativeObject<std::shared_ptr<T>>;

static std::shared_ptr<Parser> create_parser(std::istream& ss)
{
	auto tokenizer = create_tokenizer(ss);

	return std::make_shared<Parser>(tokenizer);
}

static std::shared_ptr<Object> parse(const std::string& input)
{
	std::istringstream ss(input);
	auto parser = create_parser(ss);

	return parser->current();
}

static std::shared_ptr<Environment> create_environment()
{
	auto result = std::make_shared<Environment>();

	scripting::add_standard_library_bindings(result.get());

	return result;
}

static std::shared_ptr<Object> interpret(const std::string& input)
{
	auto parsed_input = parse(input);
	
	return evaluate(parsed_input, create_environment());
}

static std::shared_ptr<Object> number(double x)
{
	return std::make_shared<Number>(x);
}

static std::shared_ptr<Object> string(const std::string& str)
{
	return std::make_shared<String>(str);
}

static std::shared_ptr<Object> symbol(const std::string& str)
{
	return std::make_shared<Symbol>(str);
}

static std::shared_ptr<Object> boolean(bool b)
{
	return std::make_shared<Boolean>(b);
}

static std::shared_ptr<Object> point(double x, double y, double z)
{
	return std::make_shared<Point>(math::Point3D(x,y,z));
}

static std::shared_ptr<Object> vector(double x, double y, double z)
{
	return std::make_shared<Vector>(math::Vector3D(x, y, z));
}

static std::shared_ptr<Object> nil()
{
	return std::make_shared<Nil>();
}

#define TEST(sexpr, expected) TEST_CASE("[interpret] Evaluating " #sexpr, "[interpreter]") { auto result = interpret(sexpr); REQUIRE(*result == *expected); }


TEST("5", number(5));
TEST("\"abc\"", string("abc"));
TEST("(+ 7)", number(7));
TEST("(+ 5 3)", number(8));
TEST("(+ 5 3 1)", number(9));
TEST("(+ (@ 1 2 3) (-> 4 5 6))", point(5, 7, 9));
TEST("(+ (-> 1 2 3) (-> 4 5 6))", vector(5, 7, 9));
TEST("(+ (-> 1 2 3) (@ 4 5 6))", point(5, 7, 9));
TEST("(*)", number(1));
TEST("(* 3)", number(3));
TEST("(* 2 7)", number(14));
TEST("(* (+ 5 2) 7)", number(49));
TEST("(-)", number(0));
TEST("(- 5)", number(-5));
TEST("(- 5 3)", number(2));
TEST("(- 5 3 1)", number(1));
TEST("(let ((x 5)) x)", number(5));
TEST("(let ((x 5) (y 3)) (+ x y))", number(8));
TEST("(let ((x (+ 3 5)) (y 3)) (+ x y))", number(11));
TEST("true", boolean(true));
TEST("false", boolean(false));
TEST("(= 5 3)", boolean(false));
TEST("(= 5 5)", boolean(true));
TEST("(= (+ 3 2) 5)", boolean(true));
TEST("(= \"abc\" \"abc\")", boolean(true));
TEST("(= \"abc\" \"xyz\")", boolean(false));
TEST("(= true true)", boolean(true));
TEST("(= true false)", boolean(false));
TEST("(<)", boolean(true));
TEST("(< 1)", boolean(true));
TEST("(< 1 2)", boolean(true));
TEST("(< 1 2 3)", boolean(true));
TEST("(< 1 1)", boolean(false));
TEST("(< 1 7 4)", boolean(false));
TEST("(<=)", boolean(true));
TEST("(<= 8)", boolean(true));
TEST("(<= 8 10)", boolean(true));
TEST("(<= 8 8)", boolean(true));
TEST("(<= 8 10 77)", boolean(true));
TEST("(<= 8 5)", boolean(false));
TEST("(<= 8 5 77)", boolean(false));
TEST("(>)", boolean(true));
TEST("(> 10)", boolean(true));
TEST("(> 10 5)", boolean(true));
TEST("(> 8 7 5)", boolean(true));
TEST("(> 8 9)", boolean(false));
TEST("(> 8 8)", boolean(false));
TEST("(> 8 5 6)", boolean(false));
TEST("(>=)", boolean(true));
TEST("(>= 7)", boolean(true));
TEST("(>= 7 6)", boolean(true));
TEST("(>= 7 7)", boolean(true));
TEST("(>= 7 9)", boolean(false));
TEST("(>= 7 9 8)", boolean(false));
TEST("(not true)", boolean(false));
TEST("(not false)", boolean(true));
TEST("(if true 1 0)", number(1));
TEST("(if true 1)", number(1));
TEST("(if false 1 2)", number(2));
TEST("(if true (+ 1 2) 4)", number(3));
TEST("(if false (+ 1 2) (* 2 2))", number(4));
TEST("(if false 0)", nil());
TEST("(if (> 5 8) (+ 1 2) (* 2 2))", number(4));
TEST("(@ 5 3 6)", point(5, 3, 6));
TEST("(-> 5 3 6)", vector(5, 3, 6));
TEST("(x (@ 1 2 3))", number(1));
TEST("(y (@ 1 2 3))", number(2));
TEST("(z (@ 1 2 3))", number(3));
TEST("(x (-> 1 2 3))", number(1));
TEST("(y (-> 1 2 3))", number(2));
TEST("(z (-> 1 2 3))", number(3));
TEST("(let ((x (alloc))) (set x 5) (get x))", number(5));
TEST("(rgb 1 1 1)", std::make_shared<NO<color>>(color(1,1,1)));

TEST_CASE("[interpret] Evaluating (plane (@ 0 0 0) (-> 0 0 1) (-> 1 0 0))", "[interpreter]")
{
	auto result = interpret("(plane (@ 0 0 0) (-> 0 0 1) (-> 1 0 0))");

	REQUIRE(has_object_type<LNO<raytracer::Primitive>>(result));

	auto primitive = object_cast<LNO<raytracer::Primitive>>(result)->extract();
	auto plane = std::dynamic_pointer_cast<raytracer::Plane>(primitive);
	
	REQUIRE(plane != nullptr);
	REQUIRE(plane->point == math::Point3D(0, 0, 0));
	REQUIRE(plane->normal == math::Vector3D(0, 0, 1));
}

TEST_CASE("[interpret] Evaluating (uniform-material (rgb 1 0 1))", "[interpreter]")
{
	auto result = interpret("(uniform-material (rgb 1 0 1))");

	REQUIRE(has_object_type<LNO<raytracer::Material>>(result));
}

TEST_CASE("[interpret] Evaluating (decorate (uniform-material (rgb 1 0 1)) (plane (@ 0 0 0) (-> 0 0 1) (-> 1 0 0)))", "[interpreter]")
{
	auto result = interpret("(decorate (uniform-material (rgb 1 0 1)) (plane (@ 0 0 0) (-> 0 0 1) (-> 1 0 0)))");

	/*REQUIRE(has_object_type<LNO<raytracer::UniformMaterial>>(result));

	auto material = object_cast<LNO<raytracer::UniformMaterial>>(result)->extract();*/
}

#endif
