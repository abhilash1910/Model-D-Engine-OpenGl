#include<GL/glew.h>

#include <glfw3.h>
#include<filesystem>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include<fstream>
#include<sstream>
#include "render_engine.h"

#include "shader.h"
#include "camera.h"
#include "model.h"

#include "lighting.h"
#include <iostream>
using namespace std;
using namespace renderengine;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera cam(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (glewInit() == GLEW_OK)
	{
		cout << "Yeah" << endl;
	}

	cout << "Enter your engine choice: 1 for 2D ,2 for 3D " << endl;
	unsigned int dec;
	cin >> dec;

	if (dec == 1)
	{
		cout << "2D Engine" << endl;

		render_engine ren;
		unsigned int vertexsh = ren.vertcompile(ren);
		unsigned int fragsh = ren.fragcompile(ren);
		unsigned int prog = ren.program(ren);




		float vertices[] = {
			0.0f,0.0f,0.0f, 1.0f,0.0f,1.0f,
			0.5f, 0.0f, 0.0f,1.0f,0.0f,0.0f,
			0.0f, 0.5f, 0.0f, 0.0f,0.5f,1.0f,
			 0.0f,  -0.5f, 0.0f,1.0f,1.0f,0.0f,
			 -0.5f,0.0f,0.0f,0.0f,1.0f,1.0f,


			 -1.0f,0.0f,0.0f,1.0f,0.0f,1.0f,
			-0.5f, 0.0f, 0.0f,1.0f,0.0f,0.0f,
			-1.0f, 0.5f, 0.0f, 0.0f,0.5f,1.0f,
			 -1.0f,-0.5f, 0.0f,1.0f,1.0f,0.0f,
			 -1.5f,0.0f,0.0f,0.0f,1.0f,1.0f,

			 1.0f,0.0f,0.0f,1.0f,0.0f,1.0f,
			1.5f, 0.0f, 0.0f,1.0f,0.0f,0.0f,
			1.0f, 0.5f, 0.0f, 0.0f,0.5f,1.0f,
			 1.0f,  -0.5f, 0.0f,1.0f,1.0f,0.0f,
			 0.5f,0.0f,0.0f,0.0f,1.0f,1.0f,

			 0.0f,0.5f,0.0f,1.0f,0.0f,1.0f,
			0.0f, 1.0f, 0.0f,1.0f,0.0f,0.0f,
			0.0f, 1.5f, 0.0f, 0.0f,0.5f,1.0f,
			 -0.5f,  1.0f, 0.0f,1.0f,1.0f,0.0f,
			 0.5f,1.0f,0.0f,0.0f,1.0f,1.0f,

			  0.0f,-0.5f,0.0f,1.0f,0.0f,1.0f,
			0.0f, -1.0f, 0.0f,1.0f,0.0f,0.0f,
			0.0f, -1.5f, 0.0f, 0.0f,0.5f,1.0f,
			 -0.5f, -1.0f, 0.0f,1.0f,1.0f,0.0f,
			 0.5f,-1.0f,0.0f,0.0f,1.0f,1.0f,

			 -1.0f,0.5f,0.0f,1.0f,0.0f,1.0f,
			-1.0f, 1.0f, 0.0f,1.0f,0.0f,0.0f,
			-1.0f, 1.5f, 0.0f, 0.0f,0.5f,1.0f,
			 -1.5f,  1.0f, 0.0f,1.0f,1.0f,0.0f,
			-0.5f,1.0f,0.0f,1.0f,1.0f,0.0f,

			-1.0f,-0.5f,0.0f,1.0f,0.0f,1.0f,
			-1.0f, -1.0f, 0.0f,1.0f,0.0f,0.0f,
			-1.0f, -1.5f, 0.0f, 0.0f,0.5f,1.0f,
			 -1.5f,  -1.0f, 0.0f,1.0f,1.0f,0.0f,
			-0.5f,-1.0f,0.0f,1.0f,1.0f,0.0f,

			1.0f,-0.5f,0.0f,1.0f,0.0f,1.0f,
			1.0f, -1.0f, 0.0f,1.0f,0.0f,0.0f,
			1.0f, -1.5f, 0.0f, 0.0f,0.5f,1.0f,
			 1.5f,  -1.0f, 0.0f,1.0f,1.0f,0.0f,
			0.5f,-1.0f,0.0f,0.0f,1.0f,1.0f,

			1.0f,0.5f,0.0f,1.0f,0.0f,1.0f,
			1.0f, 1.0f, 0.0f,1.0f,0.0f,0.0f,
			1.0f, 1.5f, 0.0f, 0.0f,0.5f,1.0f,
			 1.5f,  1.0f, 0.0f,1.0f,1.0f,0.0f,
			0.5f,1.0f,0.0f,0.0f,1.0f,1.0f,

			0.75f,0.25f,0.0f,1.0f,0.0f,1.0f,
			0.75f, 0.75f, 0.0f,1.0f,0.0f,0.0f,
			0.25f, 0.75f, 0.0f, 0.0f,0.5f,1.0f,
			 0.25f,  0.25f, 0.0f,1.0f,1.0f,0.0f,


		};

		unsigned int indices[] = {
			0,1,2,
			0,1,3,
			0,3,4,
			0,2,4,

			4,5,7,
			4,5,8,
			5,8,9,
			5,7,9,

			1,10,12,
			1,10,13,
			10,11,12,
			10,11,13,

			2,16,19,
			2,16,18,
			16,17,18,
			16,17,19,

			3,21,23,
			3,21,24,
			21,22,23,
			21,22,24,

			7,26,28,
			7,26,29,
			26,27,28,
			26,27,29,


			8,31,34,
			8,31,33,
			31,32,33,
			31,32,34,

			13,36,39,
			13,36,38,
			36,37,38,
			36,37,39,

			12,41,44,
			12,41,43,
			41,42,43,
			41,42,44,

			45,46,47,
			45,48,47


		};

		windowgl gl;


		unsigned int size = sizeof(vertices);
		const void* data;
		data = vertices;
		unsigned int size_index = sizeof(indices);
		const void* data_index;
		data_index = indices;

		buffer buf;
		buf.allocate_buffers(size, data, size_index, data_index);


		gl.initgl();
		// Our own OpenGL initialization
		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear the color buffer with current clearing color


			glUseProgram(prog);
			// render the triangle
			//glTranslatef(0.5f, 0.4f, 0.0f);


			transformation trans;
			trans.transform_engine_rotate(trans);
			//cam.cam_movement(cam,width,height);
			//cam.cam_rotation(cam, width, height);
			glDrawElements(GL_TRIANGLES, size_index, GL_UNSIGNED_INT, 0);

			trans.transform_engine_reset(trans);

			glDrawElements(GL_TRIANGLES, size_index, GL_UNSIGNED_INT, 0);


			glFlush();



			glfwSwapBuffers(window);
			glfwPollEvents();


		}


		glfwTerminate();
	}


	// configure global opengl state
	// -----------------------------
	else if (dec == 2)
	{
	cout << "3d engine" << endl;
		glEnable(GL_DEPTH_TEST);

		// build and compile shaders
		// -------------------------
		Shader ourShader("C:/Users/User/source/repos/engine/engine/shaders/model.vs", "C:/Users/User/source/repos/engine/engine/shaders/model.frag");

		// load models
		// -----------
		model ourModel("C:/Users/User/source/repos/engine/engine/model/nanosuit/nanosuit.obj");

		// draw in wireframe
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// render loop
		// -----------
		while (!glfwWindowShouldClose(window))
		{
			// per-frame time logic
			// --------------------
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			// input
			// -----
			processInput(window);

			// render
			// ------
			glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// don't forget to enable shader before setting uniforms
			ourShader.use();

			// view/projection transformations
			glm::mat4 projection = glm::perspective(glm::radians(cam.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			glm::mat4 view = cam.GetViewMatrix();
			ourShader.setMat4("projection", projection);
			ourShader.setMat4("view", view);

			// render the loaded model
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
			model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
			ourShader.setMat4("model", model);
			ourModel.draw(ourShader);

			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		// glfw: terminate, clearing all previously allocated GLFW resources.
		// ------------------------------------------------------------------
		glfwTerminate();
	}
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	cam.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	cam.ProcessMouseScroll(yoffset);
}