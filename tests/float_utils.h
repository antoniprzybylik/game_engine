#include <algorithm>
#include <type_traits>

template<typename T>
bool float_cmp(T a, T b)
{
	static_assert(std::is_floating_point<T>::value,
		      "T must be a floating-point type.");

	T precision = std::sqrt(std::numeric_limits<T>::epsilon());

	if (a == b)
		return true;

	if (a == T(0) || b == T(0) ||
	    (std::abs(a) + std::abs(b)) <
	    precision) {
		return true;
	}

	if ((a < T(0) && b > T(0)) ||
	    (a > T(0) && b < T(0))) {
		return false;
	}

	return (std::abs(a - b) /
	        std::min(std::abs(a), std::abs(b))) < precision;
}
