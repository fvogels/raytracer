#include "scripting/standard-library.h"
#include "scripting/objects/native-functions.h"
#include "scripting/objects/special-form.h"
#include "scripting/objects.h"
#include "math/point3d.h"
#include "math/vector3d.h"
#include "primitives/primitives.h"
#include "materials/materials.h"
#include "easylogging++.h"
#include <sstream>
#include <typeinfo>

namespace scripting
{
	namespace library
	{
		template<unsigned I, typename T>
		struct Indexed
		{
			static constexpr unsigned index = I;
			typedef T type;
		};

		template<unsigned... Ns>
		struct Indices { };

		template<unsigned I, unsigned... Ns>
		struct BuildIndex : public BuildIndex<I - 1, I - 1, Ns...> { };

		template<unsigned... Ns>
		struct BuildIndex<0, Ns...> : public Indices<Ns...> { };

		template<typename... Ts>
		using CreateIndex = BuildIndex<sizeof...(Ts)>;

		template<typename... Ts>
		struct Indexate
		{
			template<unsigned... Ns>
			struct with
			{
				typedef std::tuple<Indexed<Ns, Ts>...> pairs;
			};
		};

		template<typename... Ts, unsigned... Ns>
		std::tuple<Indexed<Ns, Ts>...> Indexation(Indices<Ns...>)
		{
			return std::tuple<Indexed<Ns, Ts>...>();
		}

		template<typename Pair>
		typename Pair::type convert(const std::vector<std::shared_ptr<scripting::Object>>& objects)
		{
			CLOG(DEBUG, "stdlib") << "Converting argument #" << Pair::index << " of type " << typeid(*objects[Pair::index]).name() << " to " << typeid(scripting::NativeObject<typename Pair::type>).name();

			return scripting::object_cast<scripting::NativeObject<typename Pair::type>>(objects[Pair::index])->extract();
		}

		template<typename R, typename... Ps>
		std::shared_ptr<scripting::NativeObject<R>> create_by_value(const std::vector<std::shared_ptr<scripting::Object>>& objects, std::tuple<Ps...> pairs)
		{
			return std::make_shared<scripting::NativeObject<R>>(R(convert<Ps>(objects)...));
		}

		template<typename R, typename... Ts>
		class CreateNativeByValue : public scripting::Function
		{
		protected:
			std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>& objects) const override
			{
				CreateIndex<Ts...> indices;
				auto indexation = Indexation<Ts...>(indices);

				return create_by_value<R>(objects, indexation);
			}
		};

		template<typename R, typename T, typename... Ps>
		std::shared_ptr<scripting::NativeObject<std::shared_ptr<T>>> create_by_pointer(const std::vector<std::shared_ptr<scripting::Object>>& objects, std::tuple<Ps...> pairs)
		{
			return std::make_shared<scripting::NativeObject<std::shared_ptr<T>>>(std::make_shared<R>(convert<Ps>(objects)...));
		}

		template<typename R, typename T, typename... Ts>
		class CreateNativeByPointer : public scripting::Function
		{
		protected:
			std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>& objects) const override
			{
				CreateIndex<Ts...> indices;
				auto indexation = Indexation<Ts...>(indices);

				return create_by_pointer<R, T>(objects, indexation);
			}
		};
	}
}

using namespace scripting;


void scripting::add_standard_library_bindings(Environment* environment)
{
#define BIND_CREATE_BY_VALUE(SYMBOL, TYPE, ...) environment->bind(Symbol(SYMBOL), std::make_shared<scripting::library::CreateNativeByValue<TYPE, __VA_ARGS__>>())
#define BIND_CREATE_BY_POINTER(SYMBOL, TYPE, SUPERTYPE, ...) environment->bind(Symbol(SYMBOL), std::make_shared<scripting::library::CreateNativeByPointer<TYPE, SUPERTYPE, __VA_ARGS__>>())
#define BIND_LIBRARY_FUNCTION(SYMBOL_NAME, CLASS) environment->bind(Symbol(SYMBOL_NAME), std::make_shared<scripting::library::CLASS>())

	environment->bind(Symbol("true"), std::make_shared<scripting::Boolean>(true));
	environment->bind(Symbol("false"), std::make_shared<scripting::Boolean>(false));
	environment->bind(Symbol("nil"), std::make_shared<scripting::Nil>());

	BIND_CREATE_BY_VALUE("@", math::Point3D, double, double, double);
	BIND_CREATE_BY_VALUE("->", math::Vector3D, double, double, double);
	BIND_CREATE_BY_VALUE("rgb", color, double, double, double);

	BIND_CREATE_BY_POINTER("plane", Raytracer::Plane, Raytracer::Primitive, math::Point3D, math::Vector3D);
	BIND_CREATE_BY_POINTER("decorate", Raytracer::Decorator, Raytracer::Primitive, std::shared_ptr<Raytracer::Material3D>, std::shared_ptr<Raytracer::Primitive>);
	BIND_CREATE_BY_POINTER("uniform-material", Raytracer::UniformMaterial, Raytracer::Material3D, color);

	BIND_LIBRARY_FUNCTION("let", Let);
	BIND_LIBRARY_FUNCTION("if", If);
	BIND_LIBRARY_FUNCTION("+", Addition);
	BIND_LIBRARY_FUNCTION("-", Subtraction);
	BIND_LIBRARY_FUNCTION("*", Multiplication);
	BIND_LIBRARY_FUNCTION("=", Equality);
	BIND_LIBRARY_FUNCTION("<", LessThan);
	BIND_LIBRARY_FUNCTION(">", GreaterThan);
	BIND_LIBRARY_FUNCTION("<=", NotGreaterThan);
	BIND_LIBRARY_FUNCTION(">=", NotLessThan);
	BIND_LIBRARY_FUNCTION("not", Negation);
	BIND_LIBRARY_FUNCTION("x", GetX);
	BIND_LIBRARY_FUNCTION("y", GetY);
	BIND_LIBRARY_FUNCTION("z", GetZ);
	BIND_LIBRARY_FUNCTION("alloc", Allocate);
	BIND_LIBRARY_FUNCTION("get", ReadHeap);
	BIND_LIBRARY_FUNCTION("set", WriteHeap);

#undef BIND_CREATE_BY_POINTER
#undef BIND_CREATE_BY_VALUE
#undef BIND
}