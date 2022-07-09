#ifndef _ZABRODA_UTILITY_H_
#define _ZABRODA_UTILITY_H_

#include <concepts>

namespace zabroda::math {
	template<typename T, T eps = 1e-5f>
	bool compare_floats(T f1, T f2)
	{
		return abs(f1 - f2) < eps;
	}
}

#endif