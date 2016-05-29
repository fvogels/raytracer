#pragma once

namespace scripting
{
	template<typename T, typename LOC>
	class Reader
	{
	public:
		virtual bool end_reached() const = 0;
		virtual const T& current() const = 0;
		virtual const LOC& location() const = 0;
		virtual void next() = 0;
	};
}