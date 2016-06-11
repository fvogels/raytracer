#include "scripting/environment.h"
#include "scripting/objects/symbol.h"
#include <assert.h>
#include <map>

namespace scripting
{
	class Frame
	{
	public:
		Frame() = default;

		bool is_bound(const Symbol&) const;
		std::shared_ptr<Object> lookup(const Symbol&) const;
		void bind(const Symbol&, std::shared_ptr<Object>);

	private:
		std::map<std::string, std::shared_ptr<Object>> bindings;
	};
}

struct scripting::Environment::Impl
{
	Impl(std::shared_ptr<scripting::Frame>, std::shared_ptr<scripting::Environment>);

	bool is_bound(const Symbol&) const;
	std::shared_ptr<Object> lookup(const Symbol&) const;
	void bind(const Symbol&, std::shared_ptr<Object>);

	std::shared_ptr<scripting::Frame> frame;
	std::shared_ptr<scripting::Environment> parent;
};


using namespace scripting;

bool scripting::Environment::Impl::is_bound(const Symbol& symbol) const
{
	return frame->is_bound(symbol) || (parent != nullptr && parent->is_bound(symbol));
}

std::shared_ptr<Object> scripting::Environment::Impl::lookup(const Symbol& symbol) const
{
	if ( frame->is_bound(symbol) )
	{
		return frame->lookup(symbol);
	}
	else if (parent != nullptr)
	{
		return parent->lookup(symbol);
	}
	else
	{
		throw std::runtime_error("Unbound symbol");
	}
}

void scripting::Environment::Impl::bind(const Symbol& symbol, std::shared_ptr<Object> object)
{
	frame->bind(symbol, object);
}

bool scripting::Frame::is_bound(const Symbol& symbol) const
{
	return bindings.find(symbol.name()) != bindings.end();
}

std::shared_ptr<Object> scripting::Frame::lookup(const Symbol& symbol) const
{
	assert(is_bound(symbol));

	return bindings.at(symbol.name());
}

void scripting::Frame::bind(const Symbol& symbol, std::shared_ptr<Object> object)
{
	bindings[symbol.name()] = object;
}

scripting::Environment::Impl::Impl(std::shared_ptr<Frame> frame, std::shared_ptr<Environment> parent)
	: frame(frame), parent(parent)
{
	// NOP
}

scripting::Environment::Environment()
	: Environment(nullptr)
{
	// NOP
}

scripting::Environment::Environment(std::shared_ptr<Environment> parent)
	: m_pimpl(std::make_unique<scripting::Environment::Impl>(std::make_shared<Frame>(), parent))
{
	// NOP
}

scripting::Environment::~Environment()
{
	// NOP
}

bool scripting::Environment::is_bound(const Symbol& symbol) const
{
	return m_pimpl->is_bound(symbol);
}

std::shared_ptr<Object> scripting::Environment::lookup(const Symbol& symbol) const
{
	return m_pimpl->lookup(symbol);
}

void scripting::Environment::bind(const Symbol& symbol, std::shared_ptr<Object> value)
{
	return m_pimpl->bind(symbol, value);
}

std::shared_ptr<Environment> scripting::extend(std::shared_ptr<Environment> environment)
{
	return std::make_shared<Environment>(environment);
}