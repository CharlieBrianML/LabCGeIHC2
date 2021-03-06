#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificación de compatibilidad 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 1", nullptr, nullptr);
	
	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);

	Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		-0.5f,  0.0f, 0.0f,    1.0f,0.0f,0.0f,		//		 	0
		-0.8f, 0.4f, 0.0f,    0.0f,1.0f,0.0f,		//			1
		-0.5f, 0.8f, 0.0f,   0.0f,0.0f,1.0f,		// 			2
		 -0.2f,  0.4f, 0.0f,   1.0f,0.0f,1.0f,		//	 		3
		  0.1f,  0.0f, 0.0f,   1.0f,0.0f,1.0f,		//			4
		 0.1f,  0.8f, 0.0f,   1.0f,0.0f,1.0f,		//			5
		 0.8f,  0.8f, 0.0f,   1.0f,0.0f,1.0f,		//			6
		 0.8f,  0.0f, 0.0f,   1.0f,0.0f,1.0f,		//			7
		- 0.8f,  -0.1f, 0.0f,   1.0f,0.0f,1.0f,		//			8
		- 0.8f,  -0.7f, 0.0f,   1.0f,0.0f,1.0f,		//			9
		 0.0f,  -0.7f, 0.0f,   1.0f,0.0f,1.0f,		//			10
		 0.0f,  -0.1f, 0.0f,   1.0f,0.0f,1.0f,		//			11
		 0.1f,  -0.1f, 0.0f,   1.0f,0.0f,1.0f,		//			12
		 0.1f,  -0.7f, 0.0f,   1.0f,0.0f,1.0f,		//			13
		 0.8f,  -0.7f, 0.0f,   1.0f,0.0f,1.0f,		//			14
	};
	unsigned int indices[] = {  // note that we start from 0!
		//3,2,1,// second Triangle
		//0,1,3,
		0,1,2,
		2,3,0,
		8,9,10,
		8,11,10,
		4,5,6,
		6,7,4,
		12,13,14,
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid *)(0 * sizeof(int)));
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid *)(3 * sizeof(int)));
		//glDrawArrays(GL_TRIANGLES, 0,3);
		//glDrawElementsBaseVertex(GL_LINE, 4, GL_UNSIGNED_INT, 0,0);
		//glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0,0);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		//glDrawElementsBaseVertex(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, 0,0);
		//glDrawElementsBaseVertex(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, 0,2);
		glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, (GLvoid *)(3 * sizeof(int)));
		
		glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT,  (GLvoid *)(6 * sizeof(int)));
		glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT,  (GLvoid *)(9 * sizeof(int)));
		//glDrawElementsBaseVertex(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, 3,5);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid *)(12* sizeof(int)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid *)(15 * sizeof(int)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid *)(18 * sizeof(int)));

		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

