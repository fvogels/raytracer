#pragma once

#include "scripting/reader.h"
#include <memory>
#include <assert.h>

namespace scripting
{
	template<typename R1, typename R2, typename LOC>
	class CombinedReader : public Reader<typename R2::datum_t, LOC>
	{
	public:
		CombinedReader(typename R1::source_t& in)
		{
			r1 = std::make_unique<R1>(in);

			if (!r1->end_reached())
			{
				r2 = std::make_unique<R2>(r1->current());
			}
		}

		typename R2::datum_t current() const override
		{
			return r2->current();
		}

		LOC location() const override
		{
			return LOC(r1->location(), r2->location());
		}

		bool end_reached() const override
		{
			return r1->end_reached();
		}

		void next() override
		{
			assert(!end_reached());

			if (r2->end_reached())
			{
				r1->next();

				if (!r1->end_reached())
				{
					r2 = std::make_unique<R2>(r1->current());
				}
			}
		}

	private:
		std::unique_ptr<R1> r1;
		std::unique_ptr<R2> r2;
	};
}