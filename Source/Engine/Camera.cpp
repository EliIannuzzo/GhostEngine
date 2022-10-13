#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Update()
{
	m_Transform = LookAt(Vector3(0.f, 0.f, 0.f));
}

Transform Camera::LookAt(Vector3 _Target)
{
	return Transform(glm::lookAt(
		glm::vec3(m_Transform.mTranslation.X, m_Transform.mTranslation.Y, m_Transform.mTranslation.Z),
		glm::vec3(_Target.X, _Target.Y, _Target.Z),
		glm::vec3(0.f, 1.f, 0.f)
	));
}