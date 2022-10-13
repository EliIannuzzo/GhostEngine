#pragma once
#include <cmath>
#include "Transform.h"
#include "Vector.h"
#include "Quaternion.h"
#include "MathStatics.h"

namespace Math
{
	float Fmod(float _X, float _Y);

	float TruncToFloat(float F);

	void SinCos(float& _ScalarSin, float& _ScalarCos, float _Value);

	template<class T>
	auto RadiansToDegrees(T const& _Radians)
	{
		return _Radians * (180.f / PI);
	}

	/**
	 * Converts degrees to radians.
	 * @param	DegVal			Value in degrees.
	 * @return					Value in radians.
	 */
	template<class T>
	auto DegreesToRadians(T const& _Degrees)
	{
		return _Degrees * (PI / 180.f);
	}

	/** Clamps X to be between Min and Max, inclusive */
	template< class T >
	T Clamp(const T _X, const T _Min, const T _Max)
	{
		return _X < _Min ? _Min : _X < _Max ? _X : _Max;
	}

	template< class T >
	T Abs(const T A)
	{
		return (A >= (T)0) ? A : -A;
	}

	inline float InvSqrt(float F)
	{
		return 1.0f / sqrtf(F);
	}

	inline Vector3 Normalize(Vector3 _Vector)
	{
		return _Vector.GetNormal();
	}
};

