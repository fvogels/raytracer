#pragma once

namespace math
{
	template<typename R, typename... Ts>
	struct Function
	{
		virtual R operator ()(Ts... ts) const = 0;
	};
}