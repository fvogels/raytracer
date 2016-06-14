#include "scripting/standard-library.h"
#include "scripting/objects/native-functions.h"
#include "scripting/objects/special-form.h"
#include "scripting/objects.h"
#include "math/point3d.h"
#include "math/vector3d.h"
#include "primitives/plane.h"

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
			return scripting::object_cast<scripting::NativeObject<typename Pair::type>>(objects[Pair::index])->extract();
		}

		template<typename R, typename... Ps>
		std::shared_ptr<scripting::NativeObject<R>> create(const std::vector<std::shared_ptr<scripting::Object>>& objects, std::tuple<Ps...> pairs)
		{
			return std::make_shared<scripting::NativeObject<R>>(R(convert<Ps>(objects)...));
		}

		template<typename R, typename... Ps>
		std::shared_ptr<scripting::NativeObject<std::shared_ptr<R>>> create_shared_pointer(const std::vector<std::shared_ptr<scripting::Object>>& objects, std::tuple<Ps...> pairs)
		{
			return std::make_shared<scripting::NativeObject<std::shared_ptr<R>>>(std::make_shared<R>(convert<Ps>(objects)...));
		}

		template<typename R, typename... Ts>
		class CreateNativeObject : public scripting::Function
		{
		protected:
			std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>& objects) const override
			{
				CreateIndex<Ts...> indices;
				auto indexation = Indexation<Ts...>(indices);

				return create<R>(objects, indexation);
			}
		};

		template<typename R, typename... Ts>
		class CreateNativeObject<std::shared_ptr<R>, Ts...> : public scripting::Function
		{
		protected:
			std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>& objects) const override
			{
				if (objects.size() != sizeof...(Ts))
				{
					throw std::runtime_error("Wrong number of arguments");
				}
				else
				{
					CreateIndex<Ts...> indices;
					auto indexation = Indexation<Ts...>(indices);

					return create_shared_pointer<R>(objects, indexation);
				}
			}
		};
	}
}

using namespace scripting;


void scripting::add_standard_library_bindings(Environment* environment)
{
	environment->bind(Symbol("true"), std::make_shared<scripting::Boolean>(true));
	environment->bind(Symbol("false"), std::make_shared<scripting::Boolean>(false));
	environment->bind(Symbol("nil"), std::make_shared<scripting::Nil>());

#ifdef BIND_NATIVE_OBJECT_FACTORY
#error BIND_NATIVE_OBJECT_FACTORY already defined (how improbable that may be)
#else
#define BIND_NATIVE_OBJECT_FACTORY(SYMBOL, TYPE, ...) environment->bind(Symbol(SYMBOL), std::make_shared<scripting::library::CreateNativeObject<TYPE, __VA_ARGS__>>())

	BIND_NATIVE_OBJECT_FACTORY("@", math::Point3D, double, double, double);
	BIND_NATIVE_OBJECT_FACTORY("->", math::Vector3D, double, double, double);
	BIND_NATIVE_OBJECT_FACTORY("plane", std::shared_ptr<Raytracer::Plane>, math::Point3D, math::Vector3D);	

#undef BIND_NATIVE_OBJECT_FACTORY
#endif

#ifdef BIND
#error BIND macro already defined
#else
#define BIND(SYMBOL_NAME, CLASS) environment->bind(Symbol(SYMBOL_NAME), std::make_shared<scripting::library::CLASS>())

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
	BIND("x", GetX);
	BIND("y", GetY);
	BIND("z", GetZ);
	BIND("alloc", Allocate);
	BIND("get", ReadHeap);
	BIND("set", WriteHeap);

#undef BIND
#endif
}