#pragma once

#include "scripting/reader.h"
#include <assert.h>
#include <memory>

namespace scripting
{
	template<typename R1, typename R2, typename LOC>
	class CombinedReader : public Reader<typename R2::datum_t, typename LOC::t>
	{
	public:
		CombinedReader(typename R1::source_t& in)
		{
			r1 = std::make_unique<R1>(in);

			if (!r1->end_reached())
			{
				auto first_r1_datum = r1->current();
				r2 = std::make_unique<R2>(first_r1_datum);
				find_first_valid_position();
			}
		}

		void next() override
		{
			assert(!r1->end_reached());
			assert(!r2->end_reached());
			assert(!end_reached());

			r2->next();
			find_first_valid_position();
		}

		bool end_reached() const override
		{
			return r1->end_reached();
		}

		typename R2::datum_t current() const override
		{
			assert(!r2->end_reached());
			assert(!end_reached());

			return r2->current();
		}

		typename LOC::t location() const override
		{
			return LOC::create(r1->location(), r2->location());
		}

	private:
		std::unique_ptr<R1> r1;
		std::unique_ptr<R2> r2;

		void next_r1_datum()
		{
			assert(!r1->end_reached());
			assert(r2->end_reached());

			r1->next();

			if (!r1->end_reached())
			{
				r2 = std::make_unique<R2>(r1->current());
			}
		}

		void find_first_valid_position()
		{
			assert(!r1->end_reached());

			while (!r1->end_reached() && r2->end_reached())
			{
				next_r1_datum();
			}
		}
	};
}