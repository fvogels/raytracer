#pragma once

#include "scripting/environment.h"
#include "math/point3d.h"
#include "math/vector3d.h"

namespace scripting
{
	template<typename T>
	class NativeObject : public scripting::Object
	{
	public:
		NativeObject(const T& object)
			: m_object(object) { }

		void write(std::ostream& out) const override { out << m_object; }

		bool operator ==(const Object& object) const override
		{
			return m_object == object_cast<NativeObject<T>>(object).m_object;
		}

		std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>) override
		{
			return std::make_shared<NativeObject<T>>(this->m_object);
		}

		T extract() const { return m_object; }

	protected:
		T m_object;
	};

	template<typename T>
	class NativeObject<std::shared_ptr<T>> : public scripting::Object
	{
	public:
		NativeObject(std::shared_ptr<T> object)
			: m_object(object) { }

		void write(std::ostream& out) const override 
		{
			// TODO
			// out << *m_object;
			throw std::runtime_error("Cannot write");
		}

		bool operator ==(const Object& object) const override
		{
			// TODO
			// return *m_object == *object_cast<NativeObject<T>>(object).m_object;
			throw std::runtime_error("Cannot compare");
		}

		std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>) override
		{
			return std::make_shared<NativeObject<std::shared_ptr<T>>>(this->m_object);
		}

		std::shared_ptr<T> extract() const { return m_object; }

	protected:
		std::shared_ptr<T> m_object;
	};

	typedef NativeObject<std::string> String;
	typedef NativeObject<double> Number;
	typedef NativeObject<bool> Boolean;
	typedef NativeObject<math::Point3D> Point;
	typedef NativeObject<math::Vector3D> Vector;
}