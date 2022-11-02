#pragma once
#include <vector>

template<typename T, typename P>
double operator*(std::vector<T> vec1, std::vector<P> vec2)
{
	return { vec1[0] * vec2[0] + vec1[1] * vec2[1] };
}

template<typename T, typename P>
P operator*(T t, P p)
{
	return { t * p[0], t * p[1] };
}