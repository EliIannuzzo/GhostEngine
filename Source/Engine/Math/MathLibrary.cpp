#include "MathLibrary.h"

float Math::Fmod(float _X, float _Y)
{
	const float AbsY = fabsf(_Y);
	if (AbsY <= 1.e-8f)
	{
		//FmodReportError(X, Y);
		return 0.f;
	}
	const float div = (_X / _Y);
	// All floats where abs(f) >= 2^23 (8388608) are whole numbers so do not need truncation, and avoid overflow in TruncToFloat as they get even larger.
	const float Quotient = fabsf(div) < FLOAT_NON_FRACTIONAL ? TruncToFloat(div) : div;
	float IntPortion = _Y * Quotient;

	// Rounding and imprecision could cause IntPortion to exceed X and cause the result to be outside the expected range.
	// For example Fmod(55.8, 9.3) would result in a very small negative value!
	if (fabsf(IntPortion) > fabsf(_X))
	{
		IntPortion = _X;
	}

	const float Result = _X - IntPortion;
	// Clamp to [-AbsY, AbsY] because of possible failures for very large numbers (>1e10) due to precision loss.
	// We could instead fall back to stock fmodf() for large values, however this would diverge from the SIMD VectorMod() which has no similar fallback with reasonable performance.
	return Clamp(Result, -AbsY, AbsY);
}

float Math::TruncToFloat(float F)
{
	return truncf(F);
}

void Math::SinCos(float& _ScalarSin, float& _ScalarCos, float _Value)
{
	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	float quotient = (Math::INV_PI * 0.5f) * _Value;
	if (_Value >= 0.0f)
	{
		quotient = (float)((int)(quotient + 0.5f));
	}
	else
	{
		quotient = (float)((int)(quotient - 0.5f));
	}
	float y = _Value - (2.0f * PI) * quotient;

	// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
	float sign;
	if (y > Math::HALF_PI)
	{
		y = Math::PI - y;
		sign = -1.0f;
	}
	else if (y < -Math::HALF_PI)
	{
		y = -PI - y;
		sign = -1.0f;
	}
	else
	{
		sign = +1.0f;
	}

	float y2 = y * y;

	// 11-degree minimax approximation
	_ScalarSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

	// 10-degree minimax approximation
	float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
	_ScalarCos = sign * p;
}
