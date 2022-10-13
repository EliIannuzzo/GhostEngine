#pragma once
#include "Vector.h"

class Quaternion
{
public:
	float X, Y, Z, W;


	//< Constructors >--------------------------------------------------------------------------------------------------
	Quaternion();
	Quaternion(float _X, float _Y, float _Z, float _W);
	Quaternion(const Vector3& _Euler);

	//< Getters >-------------------------------------------------------------------------------------------------------

	static Quaternion GetIdentity() { return Quaternion(); }

	Vector3 GetUp()			const	{ return *this * Vector3::UpVector();		}
	Vector3 GetDown()		const	{ return *this * Vector3::DownVector();		}
	Vector3 GetLeft()		const	{ return *this * Vector3::LeftVector();		}
	Vector3 GetRight()		const	{ return *this * Vector3::RightVector();	}
	Vector3 GetForward()	const	{ return *this * Vector3::ForwardVector();	}
	Vector3 GetBackward()	const	{ return *this * Vector3::BackwardVector(); }

	Vector3 RotateVector(Vector3 _V)	const;
	Vector3 UnrotateVector(Vector3 _V)	const;

	Quaternion Inverse() const;

	bool IsNormalized() const;
	float SizeSquared() const;

	//< Operator Overloads >--------------------------------------------------------------------------------------------
	Quaternion& operator=(const Quaternion& _Q)			{ X =  _Q.X; Y =  _Q.Y; Z =  _Q.Z; W =  _Q.W; return *this; }
	Quaternion& operator+=(const Quaternion& _Q)		{ X += _Q.X; Y += _Q.Y; Z += _Q.Z; W += _Q.W; return *this; }
	Quaternion& operator-=(const Quaternion& _Q)		{ X -= _Q.X; Y -= _Q.Y; Z -= _Q.Z; W -= _Q.W; return *this; }
	Quaternion& operator/=(const Quaternion& _Q)		{ X /= _Q.X; Y /= _Q.Y; Z /= _Q.Z; W /= _Q.W; return *this; }
	Quaternion& operator*=(const Quaternion& _Q)
	{
		X =  X * _Q.W + Y * _Q.Z - Z * _Q.Y + W * _Q.X;
		Y = -X * _Q.Z + Y * _Q.W + Z * _Q.X + W * _Q.Y;
		Z =  X * _Q.Y - Y * _Q.X + Z * _Q.W + W * _Q.Z;
		W = -X * _Q.X - Y * _Q.Y - Z * _Q.Z + W * _Q.W;
		return *this;
	}

	Quaternion operator+(const Quaternion& _Q) const	{ return Quaternion( X + _Q.X, Y + _Q.Y, Z + _Q.Z, W + _Q.W); }
	Quaternion operator-(const Quaternion& _Q) const	{ return Quaternion( X - _Q.X, Y - _Q.Y, Z - _Q.Z, W - _Q.W); }
	Quaternion operator/(const Quaternion& _Q) const	{ return Quaternion( X / _Q.X, Y / _Q.Y, Z / _Q.Z, W / _Q.W); }
	Quaternion operator*(const Quaternion& _Q) const
	{
		return Quaternion(
			 X * _Q.W + Y * _Q.Z - Z * _Q.Y + W * _Q.X,
			-X * _Q.Z + Y * _Q.W + Z * _Q.X + W * _Q.Y,
			 X * _Q.Y - Y * _Q.X + Z * _Q.W + W * _Q.Z,
			-X * _Q.X - Y * _Q.Y - Z * _Q.Z + W * _Q.W
		);
	}
																			 
	Vector3 operator*(const Vector3& _V) const		{ return RotateVector(_V); }

	bool operator==(const Quaternion& _Q)			{ return X==_Q.X && Y==_Q.Y && Z==_Q.Z && W==_Q.W; }
	bool operator!=(const Quaternion& _Q)			{ return X!=_Q.X || Y!=_Q.Y || Z!=_Q.Z || W!=_Q.W; }
};

inline Vector3 operator*(const Vector3& _V, const Quaternion& _Q) { return _Q.operator*(_V); }
