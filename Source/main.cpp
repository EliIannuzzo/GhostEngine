#include "Engine/Window.h"
#include "Engine/Shader.h"
#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#define STB_IMAGE_IMPLEMENTATION
#include "Engine/stb_image.h"
#include "Engine/Math/Transform.h"
#include "Engine/Math/Quaternion.h"
#include "Engine/Math/Vector.h"
#include "Engine/Math/MathLibrary.h"
#include "Engine/Camera.h"


Camera camera;

float vertices[] = {
	// positions          // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
	 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left 
};

float cubeVertices[] = {
	// positions          // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

void processInput(GLFWwindow* window);

int main()
{
	Window window = Window();
	window.Init();

	Shader shaderPipeline[2] = {
		Shader("Source/Shaders/basic.vs", "Source/Shaders/orange.fs"),
		Shader("Source/Shaders/basic.vs", "Source/Shaders/blue.fs")};

	Transform trans1 = Transform(
		Quaternion(45.0f * Vector3::ZAxis()),
		Vector3::ZeroVector(),
		Vector3::OneVector());
	shaderPipeline[0].Use();
	shaderPipeline[0].SetMatrix4("transform", trans1.GetMatrix());

	Transform trans2 = Transform(
		Quaternion::GetIdentity(),
		Vector3(0.5f, 0.5f, 0.5f),
		Vector3::OneVector());
	shaderPipeline[1].Use();
	shaderPipeline[1].SetMatrix4("transform", trans2.GetMatrix());

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
	   std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	//< Setup vertex buffers >
	//------------------------
	unsigned int VAOs[2], VBOs[2], EBOs[2];
	glGenVertexArrays(2, VAOs);		/// Generate vertex array objects, these store all subsequent bind calls.
	glGenBuffers(2, VBOs);			/// Generate vertex buffer objects, these store vertex data for the vertex shader.
	glGenBuffers(2, EBOs);			/// Generate element buffer objects, enable indexed rendering by storing vertex indices.


	//< Populate vertex buffer for first rectangle. >
	//-----------------------------------------------
	glBindVertexArray(VAOs[0]); /// Store these bind calls in the first array object.

	/// Store vertex data in first vertex buffer object.
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
// 	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//< Populate vertex buffer for first rectangle. >
	//-----------------------------------------------
	glBindVertexArray(VAOs[1]); /// Store these bind calls in the first array object.

	/// Store vertex data in first vertex buffer object.
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!window.ShouldClose())
	{
		//camera.m_Transform.mTranslation.X = sin(glfwGetTime()) * 10.0f;
		//camera.m_Transform.mTranslation.Z = cos(glfwGetTime()) * 10.0f;
		//camera.Update();

		processInput(window.mWindow);

		glEnable(GL_DEPTH_TEST);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our render program to render objects.
		shaderPipeline[0].Use();
		static int rot = 0;
		rot++;
		trans1.mRotation = Quaternion(((float)rot / 100.0f) * Vector3::ZAxis());
		shaderPipeline[0].SetMatrix4("transform", camera.m_Transform.GetMatrix());

// 		glm::mat4 model = glm::mat4(1.0f);
// 		glm::mat4 view = glm::mat4(1.0f);

		glm::vec3 cubePositions[] = {
		    glm::vec3( 0.0f,  0.0f,  0.0f), 
		    glm::vec3( 2.0f,  5.0f, -15.0f), 
		    glm::vec3(-1.5f, -2.2f, -2.5f),  
		    glm::vec3(-3.8f, -2.0f, -12.3f),  
		    glm::vec3( 2.4f, -0.4f, -3.5f),  
		    glm::vec3(-1.7f,  3.0f, -7.5f),  
		    glm::vec3( 1.3f, -2.0f, -2.5f),  
		    glm::vec3( 1.5f,  2.0f, -2.5f), 
		    glm::vec3( 1.5f,  0.2f, -1.5f), 
		    glm::vec3(-1.3f,  1.0f, -1.5f)
		};
		
		
		Transform model = Transform(Quaternion(Vector3((float)glfwGetTime() * 50.0f)));
		Transform view = Transform(Vector3(0.f, 0.f /*sin(glfwGetTime()) * 5.f*/,  -3.f));

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(80.0f), 800.f / 600.f, 0.1f, 100.f); // Projection matrix

		shaderPipeline[0].SetMatrix4("view", camera.m_Transform.GetMatrix());
		shaderPipeline[0].SetMatrix4("projection", projection);

		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAOs[0]);

		for (unsigned int i = 0; i < 10; i++)
		{
			float angle = 20.0f * i;
			model.mTranslation = Vector3(cubePositions[i].x, cubePositions[i].y, cubePositions[i].z);
			model.mRotation = Quaternion((float)glfwGetTime() * 50 + glm::radians(angle));
			shaderPipeline[0].SetMatrix4("model", model.GetMatrix());

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


// 		glBindVertexArray(VAOs[0]);
// 		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
// 
// 		shaderPipeline[1].Use();
// 		glBindTexture(GL_TEXTURE_2D, texture);
// 		glBindVertexArray(VAOs[1]);
// 		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		// Display back buffer
		glfwSwapBuffers(window.mWindow);

		// Poll window events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	const float cameraSpeed = 0.05f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.m_Transform.mTranslation += cameraSpeed * Vector3::DownVector();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.m_Transform.mTranslation -= cameraSpeed * Vector3::DownVector();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.m_Transform.mTranslation -= Math::Normalize((Vector3::CrossProduct(Vector3::DownVector(), Vector3::RightVector()))) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.m_Transform.mTranslation += Math::Normalize((Vector3::CrossProduct(Vector3::DownVector(), Vector3::RightVector()))) * cameraSpeed;
}