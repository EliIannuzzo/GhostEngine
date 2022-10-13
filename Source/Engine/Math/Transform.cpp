#include "Transform.h"
#include <glm/gtx/matrix_decompose.hpp>
#include "MathLibrary.h"

Transform::Transform()
	: mRotation(0.f, 0.f, 0.f, 1.f)
	, mTranslation(0.f)
	, mScale(1.f)
{}

Transform::Transform(Quaternion _Rotation)
	: mRotation(_Rotation)
	, mTranslation(0.f)
	, mScale(1.f)
{}

Transform::Transform(Vector3 _Translation)
	: mRotation(0.f, 0.f, 0.f, 1.f)
	, mTranslation(_Translation)
	, mScale(1.f)
{}

Transform::Transform(Quaternion _Rotation, Vector3 _Translation, Vector3 _Scale)
	: mRotation(_Rotation)
	, mTranslation(_Translation)
	, mScale(_Scale)
{}

Transform::Transform(glm::mat4 _Matrix) : Transform()
{
	this->SetMatrix(_Matrix);
}

void Transform::SetMatrix(const glm::mat4& _Matrix)
{
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;

	bool result = glm::decompose(_Matrix, scale, rotation, translation, skew, perspective);
	
	if (result) {
		mTranslation = Vector3(translation.x, translation.y, translation.z);
		mScale = Vector3(scale.x, scale.y, scale.z);
		mRotation = Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
 	}
}

glm::mat4 Transform::GetMatrix()
{
	glm::mat4 matrix;
	matrix = glm::translate(matrix, glm::vec3(mTranslation.X, mTranslation.Y, mTranslation.Z));
	matrix *= glm::mat4_cast(glm::quat(mRotation.X, mRotation.Y, mRotation.Z, mRotation.W));
	matrix = glm::scale(matrix, glm::vec3(mScale.X, mScale.Y, mScale.Z));
	return matrix;
}

Transform Transform::Compose(const Transform& _A, const Transform& _B)
{
	return _A * _B;
}

Transform Transform::MakeRelative(const Transform& _A, const Transform& _RelativeTo)
{
	Transform Result;

	if (_A.mScale.AnyNegativeValue() || _RelativeTo.mScale.AnyNegativeValue())
	{
		// @note, if you have 0 scale with negative, you're going to lose rotation as it can't convert back to quat
		//GetRelativeTransformUsingMatrixWithScale(&Result, this, &Other);
		return Transform();
	}
	else
	{
		Vector3 SafeRecipScale3D = _A.GetSafeScaleReciprocal(_RelativeTo.mScale, Math::SMALL_NUMBER);

		if (_RelativeTo.mRotation.IsNormalized() == false)
		{
			return Transform();
		}

		Quaternion Inverse = _RelativeTo.mRotation.Inverse();

		return Transform(
			Inverse * _A.mRotation,
			(Inverse * (_A.mTranslation - _RelativeTo.mTranslation)) * (SafeRecipScale3D),
			_A.mScale * SafeRecipScale3D
		);
	}
}

Vector3 Transform::GetSafeScaleReciprocal(const Vector3& InScale, float Tolerance) const
{
	Vector3 SafeReciprocalScale;
	if (Math::Abs(InScale.X) <= Tolerance)
	{
		SafeReciprocalScale.X = 0.f;
	}
	else
	{
		SafeReciprocalScale.X = 1 / InScale.X;
	}

	if (Math::Abs(InScale.Y) <= Tolerance)
	{
		SafeReciprocalScale.Y = 0.f;
	}
	else
	{
		SafeReciprocalScale.Y = 1 / InScale.Y;
	}

	if (Math::Abs(InScale.Z) <= Tolerance)
	{
		SafeReciprocalScale.Z = 0.f;
	}
	else
	{
		SafeReciprocalScale.Z = 1 / InScale.Z;
	}

	return SafeReciprocalScale;
}