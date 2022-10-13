#pragma once
#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(const char* _VertexPath, const char* _FragmentPath);

	void Use();
	
	// utility uniform functions
	void SetBool(const std::string& _Name, bool _Value) const;
	void SetInt(const std::string& _Name, int _Value) const;
	void SetFloat(const std::string& _Name, float _Value) const;
	void SetVector3(const std::string& _Name, float _Vector[3]) const;
	void SetMatrix4(const std::string& _Name, glm::mat4 _M) const;

	unsigned int mID;
};

