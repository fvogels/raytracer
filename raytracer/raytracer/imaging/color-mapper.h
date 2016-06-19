#pragma once

#include "imaging/color.h"
#include "math/function.h"

class ColorMapper : public math::Function<color, double>
{

};

class Grayscale : public ColorMapper
{
public:
	color operator ()(double) const override;
};