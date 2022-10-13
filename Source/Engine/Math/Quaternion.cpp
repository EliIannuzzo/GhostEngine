#include "Quaternion.h"
#include "MathLibrary.h"

Quaternion::Quaternion()
	: X(0.0f), Y(0.0f), Z(0.0f), W(1.0f) {}

Quaternion::Quaternion(float _X, float _Y, float _Z, float _W) 
	: X(_X), Y(_Y), Z(_Z), W(_W) {}

Quaternion::Quaternion(const Vector3& _Euler)
    : Quaternion()
{
 	const float DEG_TO_RAD          = Math::PI / (180.f);
 	const float RADS_DIVIDED_BY_2   = DEG_TO_RAD / 2.f;
 	float SP, SY, SR;
 	float CP, CY, CR;
 
 	const float PitchNoWinding  = Math::Fmod(_Euler.Y, 360.0f);
 	const float YawNoWinding    = Math::Fmod(_Euler.Z, 360.0f);
 	const float RollNoWinding   = Math::Fmod(_Euler.X, 360.0f);
 
    Math::SinCos(SP, CP,    PitchNoWinding  *   RADS_DIVIDED_BY_2);
    Math::SinCos(SY, CY,    YawNoWinding    *   RADS_DIVIDED_BY_2);
    Math::SinCos(SR, CR,    RollNoWinding   *   RADS_DIVIDED_BY_2);
 
	X =  CR * SP * SY - SR * CP * CY;
	Y = -CR * SP * CY - SR * CP * SY;
	Z =  CR * CP * SY - SR * SP * CY;
	W =  CR * CP * CY + SR * SP * SY;
}

Vector3 Quaternion::RotateVector(Vector3 _V) const
{
	const Vector3 q(X, Y, Z);
	const Vector3 t = 2.0f * Vector3::CrossProduct(q, _V);
	const Vector3 result = _V + (W * t) + Vector3::CrossProduct(q, t);
	return result;
}

Vector3 Quaternion::UnrotateVector(Vector3 _V) const
{
	const Vector3 q(-X, -Y, -Z);
	const Vector3 t = 2.0f * Vector3::CrossProduct(q, _V);
	const Vector3 result = _V + (W * t) + Vector3::CrossProduct(q, t);
	return result;
}

Quaternion Quaternion::Inverse() const
{
	return Quaternion(-X, -Y, -Z, -W);
}

bool Quaternion::IsNormalized() const
{
	return (Math::Abs(1.f - SizeSquared()) < Math::THRESH_QUAT_NORMALIZED);
}

float Quaternion::SizeSquared() const
{
	return (X * X + Y * Y + Z * Z + W * W);
}