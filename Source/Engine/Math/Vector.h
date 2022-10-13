#pragma once
#include "MathStatics.h"

class Vector2
{
public:
	float X, Y;


	//< Constructors >---------------------------------------------------------------------------------------
	Vector2();
	Vector2(float _F);
	Vector2(float _X, float _Y);


	//< Operators >------------------------------------------------------------------------------------------
	Vector2& operator=(const Vector2& _V)		{ X  = _V.X;  Y = _V.Y; return *this; }
	Vector2& operator+=(const Vector2& _V)		{ X += _V.X; Y += _V.Y; return *this; }
	Vector2& operator-=(const Vector2& _V)		{ X -= _V.X; Y -= _V.Y; return *this; }
	Vector2& operator*=(const Vector2& _V)		{ X *= _V.X; Y *= _V.Y; return *this; }
	Vector2& operator/=(const Vector2& _V)		{ X /= _V.X; Y /= _V.Y; return *this; }

	Vector2 operator+(const Vector2& _V)		{ return Vector2(X + _V.X, Y + _V.Y); }
	Vector2 operator-(const Vector2& _V)		{ return Vector2(X - _V.X, Y - _V.Y); }
	Vector2 operator*(const Vector2& _V)		{ return Vector2(X * _V.X, Y * _V.Y); }
	Vector2 operator/(const Vector2& _V)		{ return Vector2(X / _V.X, Y / _V.Y); }

	bool operator==(const Vector2& _V)			{ return X == _V.X && Y == _V.Y; }
	bool operator!=(const Vector2& _V)			{ return X != _V.X && Y != _V.Y; }
};

class Vector3
{
public:
	float X, Y, Z;

	static const Vector3 ZeroVector()		{ return Vector3(0.0f); }
	static const Vector3 OneVector()		{ return Vector3(1.0f); }

	static const Vector3 UpVector()			{ return Vector3(0.0f,  0.0f,  1.0f); }
	static const Vector3 DownVector()		{ return Vector3(0.0f,  0.0f, -1.0f); }
	static const Vector3 LeftVector()		{ return Vector3(0.0f, -1.0f,  0.0f); }
	static const Vector3 RightVector()		{ return Vector3(0.0f,  1.0f,  0.0f); }
	static const Vector3 ForwardVector()	{ return Vector3(1.0f,  0.0f,  0.0f); }
	static const Vector3 BackwardVector()	{ return Vector3(-1.0f, 0.0f,  0.0f); }

	static const Vector3 XAxis()			{ return Vector3(1, 0, 0); }
	static const Vector3 YAxis()			{ return Vector3(0, 1, 0); }
	static const Vector3 ZAxis()			{ return Vector3(0, 0, 1); }

	//char* ToString();


	//< Constructors >---------------------------------------------------------------------------------------
	Vector3();
	Vector3(float _F);
	Vector3(float _X, float _Y, float _Z);

	//#todo Move to math library
	static Vector3 CrossProduct(const Vector3 _A, const Vector3 _B)
	{
		return _A ^ _B;
	}

	bool AnyNegativeValue() const { return X < 0.f || Y < 0.f || Z < 0.f; }

	Vector3 GetNormal(float _Tolerance = Math::KINDA_SMALL_NUMBER) const;

	//< Operators >------------------------------------------------------------------------------------------
	Vector3& operator=(const Vector3& _V)			{ X  = _V.X;  Y = _V.Y; Z  = _V.Z;	return *this; }
	Vector3& operator+=(const Vector3& _V)			{ X += _V.X; Y += _V.Y; Z += _V.Z;	return *this; }
	Vector3& operator-=(const Vector3& _V)			{ X -= _V.X; Y -= _V.Y; Z -= _V.Z;	return *this; }
	Vector3& operator*=(const Vector3& _V)			{ X *= _V.X; Y *= _V.Y; Z *= _V.Z;	return *this; }
	Vector3& operator/=(const Vector3& _V)			{ X /= _V.X; Y /= _V.Y; Z /= _V.Z;	return *this; }

	Vector3 operator+(const Vector3& _V) const		{ return Vector3(X + _V.X, Y + _V.Y, Z + _V.Z); }
	Vector3 operator-(const Vector3& _V) const		{ return Vector3(X - _V.X, Y - _V.Y, Z - _V.Z); }
	Vector3 operator*(const Vector3& _V) const		{ return Vector3(X * _V.X, Y * _V.Y, Z * _V.Z); }
	Vector3 operator/(const Vector3& _V) const		{ return Vector3(X / _V.X, Y / _V.Y, Z / _V.Z); }
	Vector3 operator^(const Vector3& _V) const		{ return Vector3(Y * _V.Z - Z * _V.Y, Z * _V.X - X * _V.Z, X * _V.Y - Y * _V.X); }
	
	Vector3 operator*(float _Scale) const			{ return Vector3(X * _Scale, Y * _Scale, Z * _Scale); }

	bool operator==(const Vector3& _V)				{ return X == _V.X && Y == _V.Y && Z == _V.Z; }
	bool operator!=(const Vector3& _V)				{ return X != _V.X || Y != _V.Y || Z != _V.Z; }
};

inline Vector3 operator*(float _Scale, const Vector3& _V) { return _V.operator*(_Scale); }