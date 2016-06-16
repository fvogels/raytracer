#pragma once

#include "math/function.h"


namespace math
{
	namespace functions
	{
		template<typename R> class BoolMapper : public Function<R, bool>
		{
		public:
			BoolMapper(R t, R f)
				: m_true(t), m_false(f) { }


			R operator ()(bool b) const override
			{
				return b ? m_true : m_false;
			}

		private:
			R m_true;
			R m_false;
		};
	}
}