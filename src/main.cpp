// Std. Includes
#include <string>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <opencv2/opencv.hpp>

// Properties
GLuint screenWidth = 800, screenHeight = 600;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Do_Movement();

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

// The MAIN function, from here we start our application and run our Game loop
int main(int argc, char **argv)
{	
	cv::Mat temp = cv::imread(argv[1]);

	std::vector<cv::Vec3b> colorsn;
	int cSize = temp.rows*temp.cols;

	for (int i = 0; i < temp.rows; i++) {
		for (int j = 0; j < temp.cols; j++) {
			colorsn.push_back({ temp.at<cv::Vec3b>(i, j) });
		}
	}
	// Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", nullptr, nullptr); // Windowed
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Initialize GLEW to setup the OpenGL Function pointers
	glewExperimental = GL_TRUE;
	glewInit();

	
	int colors[15][3] = {
		{ 12, 14, 14 },
		{ 42, 44, 44 },
		{ 72, 74, 74 },
		{ 102, 104, 104 },
		{ 132, 134, 134 },

		{ 200, 200, 40},
		{ 190, 200, 40 },
		{ 200, 190, 40 },
		{ 180, 200, 40 },
		{ 200, 180, 40 },

		{ 200, 200, 60 },
		{ 190, 200, 60 },
		{ 200, 190, 60 },
		{ 180, 200, 60 },
		{ 200, 180, 60 }
	};

	// Define the viewport dimensions
	glViewport(0, 0, screenWidth, screenHeight);

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);

	// Setup and compile our shaders
	//Shader ourShader();
	Shader ourShader;
	// Set up our vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
		//left bottom
		 -1.02f,  -1.02f,  1.02f, 0.0f, 0.0f, 1.0f,
		 -1.02f,  -1.00f,  1.02f, 0.0f, 0.0f, 1.0f,
		 -1.02f,  -1.00f, -1.02f, 0.0f, 0.0f, 0.0f,

		 -1.02f,  -1.00f, -1.02f, 0.0f, 0.0f, 0.0f,
		 -1.02f,  -1.02f, -1.02f, 0.0f, 0.0f, 0.0f,
		 -1.02f,  -1.02f,  1.02f, 0.0f, 0.0f, 1.0f,
		 

		 //ahead bottom
		 -1.02f,  -1.02f,  1.02f, 0.0f, 0.0f, 1.0f,
		 -1.02f,  -1.0f,   1.02f, 0.0f, 0.0f, 1.0f,
		  1.02f,  -1.0f,   1.02f, 1.0f, 0.0f, 1.0f,

		 -1.02f,  -1.02f,  1.02f, 0.0f, 0.0f, 1.0f,
		  1.02f,  -1.02f,  1.02f, 1.0f, 0.0f, 1.0f,
		  1.02f,  -1.0f,   1.02f, 1.0f, 0.0f, 1.0f,

		  
		  //ahead right
		  1.00f,   1.02f,  1.02f, 1.0f, 1.0f, 1.0f,
		  1.00f,  -1.02f,  1.02f, 1.0f, 0.0f, 1.0f,
		  1.02f,  -1.02f,  1.02f, 1.0f, 0.0f, 1.0f,

		  1.02f,  -1.02f,  1.02f, 1.0f, 0.0f, 1.0f,
		  1.02f,   1.02f,  1.02f, 1.0f, 1.0f, 1.0f,
		  1.00f,   1.02f,  1.02f, 1.0f, 1.0f, 1.0f,

		  
		  //ahead left
		 -1.00f,   1.02f,  1.02f, 0.0f, 1.0f, 1.0f,
		 -1.00f,  -1.02f,  1.02f, 0.0f, 0.0f, 1.0f,
		 -1.02f,  -1.02f,  1.02f, 0.0f, 0.0f, 1.0f,

		 -1.02f,  -1.02f,  1.02f, 0.0f, 0.0f, 1.0f,
		 -1.02f,   1.02f,  1.02f, 0.0f, 1.0f, 1.0f,
		 -1.00f,   1.02f,  1.02f, 0.0f, 1.0f, 1.0f,


		 //ahead top
		 -1.02f,   1.02f,  1.02f, 0.0f, 1.0f, 1.0f,
		 -1.02f,   1.0f,   1.02f, 0.0f, 1.0f, 1.0f,
		  1.02f,   1.0f,   1.02f, 1.0f, 1.0f, 1.0f,

		 -1.02f,   1.02f,  1.02f, 0.0f, 1.0f, 1.0f,
		  1.02f,   1.02f,  1.02f, 1.0f, 1.0f, 1.0f,
		  1.02f,   1.0f,   1.02f, 1.0f, 1.0f, 1.0f,


		  //back top
		 -1.02f,   1.02f, -1.02f, 0.0f, 1.0f, 0.0f,
		 -1.02f,   1.0f,  -1.02f, 0.0f, 1.0f, 0.0f,
		  1.02f,   1.0f,  -1.02f, 1.0f, 1.0f, 0.0f,

		 -1.02f,   1.02f, -1.02f, 0.0f, 1.0f, 0.0f,
		  1.02f,   1.02f, -1.02f, 1.0f, 1.0f, 0.0f,
		  1.02f,   1.0f,  -1.02f, 1.0f, 1.0f, 0.0f,


		  //back left
		 -1.00f,   1.02f, -1.02f, 0.0f, 1.0f, 0.0f,
		 -1.00f,  -1.02f, -1.02f, 0.0f, 0.0f, 0.0f,
		 -1.02f,  -1.02f, -1.02f, 0.0f, 0.0f, 0.0f,

		 -1.02f,  -1.02f, -1.02f, 0.0f, 0.0f, 0.0f,
		 -1.02f,   1.02f, -1.02f, 0.0f, 1.0f, 0.0f,
		 -1.00f,   1.02f, -1.02f, 0.0f, 1.0f, 0.0f,


		 //left top
		 -1.02f,   1.02f,  1.02f, 0.0f, 1.0f, 1.0f,
		 -1.02f,   1.00f,  1.02f, 0.0f, 1.0f, 1.0f,
		 -1.02f,   1.00f, -1.02f, 0.0f, 1.0f, 0.0f,

		 -1.02f,   1.00f, -1.02f, 0.0f, 1.0f, 0.0f,
		 -1.02f,   1.02f, -1.02f, 0.0f, 1.0f, 0.0f,
		 -1.02f,   1.02f,  1.02f, 0.0f, 1.0f, 1.0f,

		 //back bottom
		 -1.02f,  -1.02f, -1.02f, 0.0f, 0.0f, 0.0f,
		 -1.02f,  -1.0f,  -1.02f, 0.0f, 0.0f, 0.0f,
		  1.02f,  -1.0f,  -1.02f, 1.0f, 0.0f, 0.0f,

		 -1.02f,  -1.02f, -1.02f, 0.0f, 0.0f, 0.0f,
		  1.02f,  -1.02f, -1.02f, 1.0f, 0.0f, 0.0f,
		  1.02f,  -1.0f,  -1.02f, 1.0f, 0.0f, 0.0f,

		  //back right
		   1.00f,   1.02f, -1.02f, 1.0f, 1.0f, 0.0f,
		   1.00f,  -1.02f, -1.02f, 1.0f, 0.0f, 0.0f,
		   1.02f,  -1.02f, -1.02f, 1.0f, 0.0f, 0.0f,

		   1.02f,  -1.02f, -1.02f, 1.0f, 0.0f, 0.0f,
		   1.02f,   1.02f, -1.02f, 1.0f, 1.0f, 0.0f,
		   1.00f,   1.02f, -1.02f, 1.0f, 1.0f, 0.0f,

		   //right bottom
		    1.02f,  -1.02f,  1.02f, 1.0f, 0.0f, 1.0f,
		    1.02f,  -1.00f,  1.02f, 1.0f, 0.0f, 1.0f,
		    1.02f,  -1.00f, -1.02f, 1.0f, 0.0f, 0.0f,

		    1.02f,  -1.00f, -1.02f, 1.0f, 0.0f, 0.0f,
		    1.02f,  -1.02f, -1.02f, 1.0f, 0.0f, 0.0f,
		    1.02f,  -1.02f,  1.02f, 1.0f, 0.0f, 1.0f,

			 //right top
			 1.02f,  1.02f, 1.02f, 1.0f, 1.0f, 1.0f,
			 1.02f,  1.00f, 1.02f, 1.0f, 1.0f, 1.0f,
			 1.02f,  1.00f, -1.02f, 1.0f, 1.0f, 0.0f,

			 1.02f,  1.00f, -1.02f, 1.0f, 1.0f, 0.0f,
			 1.02f,  1.02f, -1.02f, 1.0f, 1.0f, 0.0f,
			 1.02f,  1.02f,  1.02f, 1.0f, 1.0f, 1.0f
			 
};
	
GLfloat cube[] = {

-0.005f, -0.005f,  0.000f,
0.005f, -0.005f,  0.000f,
0.005f,  0.005f,  0.000f,

-0.005f, -0.005f,  0.000f,
-0.005f,  0.005f,  0.000f,
0.005f,  0.005f,  0.000f,

0.000f, -0.005f, -0.005f,
0.000f, -0.005f, 0.005f,
0.000f,  0.005f, 0.005f,

0.000f, -0.005f, -0.005f,
0.000f,  0.005f, -0.005f,
0.000f,  0.005f, 0.005f
};
	int sizeOfFirts = sizeof(vertices) / sizeof(GLfloat);
	int sizeOfSecond = 72 * cSize;

	GLfloat *partOfBuff = new GLfloat[cSize * 6 * 12];
	for (int i = 0; i < cSize; i++) {
		GLfloat cp[6];
		for (int j = 0; j < 3; j++) {
			cp[j] = -1.0f + 0.007f*colorsn[i][j];
		}
		for (int j = 0; j < 3; j++) {
			cp[j + 3] = 0.0039f*colorsn[i][j];
		}

		for (int j = 0; j < 12; j++) {
			for (int k = 0; k < 3; k++) {
				partOfBuff[72*i + j * 6 + k] = cube[j * 3 + k] + cp[k];
			}
			for (int k = 0; k < 3; k++) {
				partOfBuff[72 * i + j * 6 + k + 3] = cp[k + 3];
			}
		}
	}
	
	GLfloat *supermassive = new GLfloat[sizeOfFirts + sizeOfSecond];	
	for (int i = 0; i < sizeOfFirts; i++) {
		supermassive[i] = vertices[i];
	}
	for (int i = 0; i < sizeOfSecond; i++) {
		supermassive[i + sizeOfFirts] = partOfBuff[i];
	}
	

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f)
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind our Vertex Array Object first, then bind and set our buffers and pointers.
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, (sizeOfFirts + sizeOfSecond)*sizeof(GLfloat), supermassive, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO

						  // Load and create a texture 

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check and call events
		glfwPollEvents();
		Do_Movement();

		// Clear the colorbuffer
		glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw our first triangle
		ourShader.Use();


		// Create camera transformation
		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection;
		projection = glm::perspective(camera.Zoom, (float)screenWidth / (float)screenHeight, 0.1f, 1000.0f);
		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);

		glm::mat4 model;
		model = glm::translate(model, cubePositions[0]);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, (sizeOfFirts + sizeOfSecond)/6 );

		glBindVertexArray(0);
		// Swap the buffers
		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}

// Moves/alters the camera positions based on user input
void Do_Movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}