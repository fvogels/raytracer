#pragma once

#include "scripting/values/function.h"

namespace scripting
{
	namespace library
	{
		class Addition : public Function
		{
		protected:
			std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;
		};

		class Subtraction : public Function
		{
		protected:
			std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;
		};

		class Multiplication : public Function
		{
		protected:
			std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;
		};

		class Equality : public Function
		{
		protected:
			std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;
		};

		class Comparison : public Function
		{
		protected:
			std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;

			virtual bool compare(double, double) const = 0;
		};

		class LessThan : public Comparison
		{
		protected:
			bool compare(double, double) const override;
		};

		class GreaterThan : public Comparison
		{
		protected:
			bool compare(double, double) const override;
		};

		class NotLessThan : public Comparison
		{
		protected:
			bool compare(double, double) const override;
		};

		class NotGreaterThan : public Comparison
		{
		protected:
			bool compare(double, double) const override;
		};

		class Negation : public Function
		{
		protected:
			std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;
		};

		class CreatePoint : public Function
		{
		protected:
			std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;
		};

		class CreateVector : public Function
		{
		protected:
			std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const override;
		};
	}
}