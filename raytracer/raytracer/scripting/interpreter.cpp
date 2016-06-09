#include "scripting/interpreter.h"
#include "scripting/Environment.h"

using namespace scripting;

class EvaluationVisitor : public SExpressionVisitor
{
public:
	EvaluationVisitor(std::shared_ptr<const SExpression> visited, std::shared_ptr<const Environment> environment)
		: m_visited(visited), m_environment(environment) { }

	void visit(const String&) override;
	void visit(const Number&) override;
	void visit(const Symbol&) override;
	void visit(const List&) override;
	void visit(const Function&) override;

	std::shared_ptr<const SExpression> result() const { return m_result; }

private:
	std::shared_ptr<const Environment> m_environment;
	std::shared_ptr<const SExpression> m_visited;
	std::shared_ptr<const SExpression> m_result;
};

void EvaluationVisitor::visit(const String& string)
{
	m_result = std::dynamic_pointer_cast<const String>(m_visited);
}

void EvaluationVisitor::visit(const Number& number)
{
	m_result = std::dynamic_pointer_cast<const Number>(m_visited);
}

void EvaluationVisitor::visit(const Symbol& symbol)
{
	m_result = m_environment->lookup(symbol);
}

void EvaluationVisitor::visit(const List& list)
{
	if (list.size() == 0)
	{
		m_result = std::dynamic_pointer_cast<const List>(m_visited);
	}
	else
	{
		// auto evaluated_head = evaluate(list.nth_element(0), m_environment);
		// TODO
		abort();
	}
}

void EvaluationVisitor::visit(const Function&)
{
	// TODO
	abort();
}

std::shared_ptr<const SExpression> scripting::evaluate(std::shared_ptr<const SExpression> value, std::shared_ptr<Environment> environment)
{
	EvaluationVisitor visitor(value, environment);

	value->accept(visitor);

	return visitor.result();
}