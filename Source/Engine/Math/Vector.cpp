#include "Vector.h"
#include "MathLibrary.h"

#pragma region Vector2
Vector2::Vector2()
	: Vector2(0) {}

Vector2::Vector2(float _F)
	: Vector2(_F, _F) {}

Vector2::Vector2(float _X, float _Y)
	: X(_X), Y(_Y) {}
#pragma endregion


#pragma region Vector3
Vector3::Vector3()
	: Vector3(0) {}

Vector3::Vector3(float _F) 
	: Vector3(_F, _F, _F) {}

Vector3::Vector3(float _X, float _Y, float _Z)
	: X(_X), Y(_Y), Z(_Z) {}

Vector3 Vector3::GetNormal(float _Tolerance /*= Math::KINDA_SMALL_NUMBER*/) const
{
	const float SquareSum = X * X + Y * Y + Z * Z;

	// Not sure if it's safe to add tolerance in there. Might introduce too many errors
	if (SquareSum == 1.f)
	{
		return *this;
	}
	else if (SquareSum < _Tolerance)
	{
		return Vector3::ZeroVector();
	}

	const float Scale = Math::InvSqrt(SquareSum);
	return Vector3(X * Scale, Y * Scale, Z * Scale);
}

#pragma endregion