#include "imaging/color-mapper.h"


color Grayscale::operator ()(double x) const
{
	return colors::white() * x;
}