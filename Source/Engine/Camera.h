#pragma once
#include <iostream>
#include <memory>
#include "Math/MathLibrary.h"

class Transform;


class Camera
{
public:
	Camera();
	~Camera();

	Transform m_Transform;

	void Update();

	Transform LookAt(Vector3 _Target);
};

