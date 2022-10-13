#pragma once
#include "Quaternion.h"
#include "Vector.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"


class Transform
{
public:
	Quaternion	mRotation;
	Vector3		mTranslation;
	Vector3		mScale;

	Transform();
	Transform(glm::mat4 _Matrix);
	Transform(Quaternion _Rotation);
	Transform(Vector3 _Translation);
	Transform(Quaternion _Rotation, Vector3 _Translation, Vector3 _Scale);

	void SetMatrix(const glm::mat4& _Matrix);
	glm::mat4 GetMatrix();

	static Transform Compose(const Transform& _A, const Transform& _B);

	static Transform MakeRelative(const Transform& _A, const Transform& _RelativeTo);

	Vector3 GetSafeScaleReciprocal(const Vector3& InScale, float Tolerance) const;

	//< Operator Overloads >--------------------------------------------------------------------------------------------
	Transform& operator=(const Transform& _T) { mRotation = _T.mRotation; mTranslation = _T.mTranslation; mScale = _T.mScale; return *this; }
	Transform operator*(const Transform& _T) const
	{
		if (mScale.AnyNegativeValue() ||  _T.mScale.AnyNegativeValue())
		{
			// @note, if you have 0 scale with negative, you're going to lose rotation as it can't convert back to quat
			//MultiplyUsingMatrixWithScale(output, A, B);
			return Transform();
		}
		else
		{
			return Transform(
				_T.mRotation * mRotation,
				_T.mRotation * (_T.mScale * mTranslation) + _T.mTranslation, 
				mScale * _T.mScale
			);
		}
	}
};