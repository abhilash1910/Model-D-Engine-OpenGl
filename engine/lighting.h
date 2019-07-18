#ifndef lightingengine_h
#define lightingengine_h
#include<GL/glew.h>
#include<glfw3.h>
#include<iostream>


#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include "render_engine.h"

using namespace std;
//using namespace renderengine;

namespace light_engine {

	class lightshader {

	protected:
		const char* lightvshader = "#version 330 core;\n"
			"layout (location=0) in vec3 aPos;\n"
			"uniform mat4 projection;\n"
			"uniform mat4 view;\n"
			"uniform mat4 model;\n"
			"void main()\n"
			"{\n"
			"gl_Position= projection * view * model * vec4(aPos,1.0f);\n"
			"}\0";
		const char* lightfshader = "#version 330 core;\n"
			"out vec4 fragcolor;\n"
			"vec4 objectcolor=vec4(1.0f,0.5f,0.31f,1.0f);\n"
			"vec4 lightcolor= vec4(1.0f,1.0f,1.0f,1.0f);\n"
			"void main()\n"
			"{\n"
			""
			"fragcolor = objectcolor * lightcolor;\n"
			"}\0";
		const char* fshader = "#version 330 core;\n"
			"out vec4 fragcolor;\n"
			"void main()\n"
			"{\n"
			"fragcolor= vec4(1.0f,1.0f,1.0f,1.0f);\n"
			"}\0";
		/*const char* vshader = "#version 330 core;\n"
			"layout (location=0) in vec3 aPos;\n"
			"uniform mat4 projection;\n"
			"uniform mat4 view;\n"
			"uniform mat4 model;\n"
			"void main()\n"
			"{\n"
			"gl_Position= projection*view*model*vec4(aPos,1.0f);\n"
			"}\0";
			*/
	public:
		inline unsigned int vert_compile_light(lightshader const &);
		inline unsigned int frag_compile_light(lightshader const &);
		inline unsigned int v_shader(lightshader const &);
		inline unsigned int f_shader(lightshader const &);
		inline unsigned int program_light(lightshader const &);
		inline unsigned int program_light_norm(lightshader const &);






	};

	unsigned int lightshader::vert_compile_light(lightshader const &a)
	{
		const char* v_light = a.lightvshader;
		unsigned int vlight = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vlight, 1, &v_light, NULL);
		glCompileShader(vlight);
		int success;
		char infolog[512];
		glGetShaderiv(vlight, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			std::cout << "Error in vertexlight shader" << std::endl;
			glGetShaderInfoLog(vlight, 512, NULL, infolog);

		}

		return vlight;

	}

	unsigned int lightshader::frag_compile_light(lightshader const &a)
	{
		const char* f_light = a.lightfshader;
		unsigned int flight = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(flight, 1, &f_light, NULL);
		glCompileShader(flight);
		int success;
		char infolog[512];
		glGetShaderiv(flight, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			std::cout << "Error in fragmentlight shader" << std::endl;
			glGetShaderInfoLog(flight, 512, NULL, infolog);

		}

		return flight;

	}

	unsigned int lightshader::v_shader(lightshader const &a)
	{
		const char* v_light_norm = a.lightvshader;
		unsigned int vlight_norm = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vlight_norm, 1, &v_light_norm, NULL);
		glCompileShader(vlight_norm);
		int success;
		char infolog[512];
		glGetShaderiv(vlight_norm, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			std::cout << "Error in vertexlight shader" << std::endl;
			glGetShaderInfoLog(vlight_norm, 512, NULL, infolog);

		}

		return vlight_norm;

	}

	unsigned int lightshader::f_shader(lightshader const &a)
	{
		const char* f_light_norm = a.fshader;
		unsigned int flight_norm = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(flight_norm, 1, &f_light_norm, NULL);
		glCompileShader(flight_norm);
		int success;
		char infolog[512];
		glGetShaderiv(flight_norm, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			std::cout << "Error in second fragment  shader" << std::endl;
			glGetShaderInfoLog(flight_norm, 512, NULL, infolog);

		}

		return flight_norm;

	}

	unsigned int lightshader::program_light(lightshader const &a)
	{

		unsigned int program = glCreateProgram();
		unsigned int x = vert_compile_light(a);
		unsigned int y = frag_compile_light(a);
		glAttachShader(program, x);
		glAttachShader(program, y);
		glLinkProgram(program);
		int success;
		char infolog[512];
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			std::cout << "Error in program" << std::endl;
			glGetProgramInfoLog(program, 512, NULL, infolog);
			return -1;

		}

		return program;


	}

	unsigned int lightshader::program_light_norm(lightshader const &a)
	{

		unsigned int program = glCreateProgram();
		unsigned int x = v_shader(a);
		unsigned int y = f_shader(a);
		glAttachShader(program, x);
		glAttachShader(program, y);
		glLinkProgram(program);
		int success;
		char infolog[512];
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			std::cout << "Error in program" << std::endl;
			glGetProgramInfoLog(program, 512, NULL, infolog);
			return -1;

		}

		return program;


	}


	class aloc_buffer {

	public:
		inline void allocate_buffer_light(float size, const void* vertices) {


			unsigned int VBO, cubeVAO;
			glGenVertexArrays(1, &cubeVAO);
			glGenBuffers(1, &VBO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindVertexArray(cubeVAO);


			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			unsigned int lightVAO;
			glGenVertexArrays(1, &lightVAO);
			glBindVertexArray(lightVAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
		}





	};


	class tranform_light :protected lightshader {

	protected:
		glm::mat4 trans_light;
	public:
		inline void transformation_light(tranform_light const &a, unsigned int const &width, unsigned int const &height)
		{
			lightshader rene;
			unsigned int progr = rene.program_light(rene);
			tranform_light projection = a;
			projection.trans_light = glm::mat4(1.0f);
			projection.trans_light = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f);
			tranform_light view = a;
			view.trans_light = glm::mat4(1.0f);
			view.trans_light = glm::translate(view.trans_light, glm::vec3(0.0f, 0.0f, -3.5f));
			tranform_light model = a;
			model.trans_light = glm::mat4(1.0f);
			model.trans_light = glm::rotate(model.trans_light, -60.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			
			unsigned int project_loc = glGetUniformLocation(progr, "projection");
			unsigned int view_loc = glGetUniformLocation(progr, "view");
			unsigned int model_loc = glGetUniformLocation(progr, "model");

			glUniformMatrix4fv(project_loc, 1, GL_FALSE, value_ptr(projection.trans_light));
			glUniformMatrix4fv(view_loc, 1, GL_FALSE, value_ptr(view.trans_light));
			glUniformMatrix4fv(model_loc, 1, GL_FALSE, value_ptr(model.trans_light));


		}

		inline void transformation_light_norm(tranform_light const &a, unsigned int const &width, unsigned int const &height)
		{
			lightshader rene;
			unsigned int progr = rene.program_light_norm(rene);
			tranform_light projection = a;
			projection.trans_light = glm::mat4(1.0f);
			projection.trans_light = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f);
			tranform_light view = a;
			view.trans_light = glm::mat4(1.0f);
			view.trans_light = glm::translate(view.trans_light, glm::vec3(0.0f, 0.0f, -5.5f));
			tranform_light model = a;
			model.trans_light = glm::mat4(1.0f);
			model.trans_light = glm::rotate(model.trans_light, -60.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			model.trans_light = glm::translate(model.trans_light, glm::vec3(1.2f, 1.0f, 2.0f));
			model.trans_light = glm::scale(model.trans_light, glm::vec3(0.2f));


			unsigned int project_loc = glGetUniformLocation(progr, "projection");
			unsigned int view_loc = glGetUniformLocation(progr, "view");
			unsigned int model_loc = glGetUniformLocation(progr, "model");

			glUniformMatrix4fv(project_loc, 1, GL_FALSE, value_ptr(projection.trans_light));
			glUniformMatrix4fv(view_loc, 1, GL_FALSE, value_ptr(view.trans_light));
			glUniformMatrix4fv(model_loc, 1, GL_FALSE, value_ptr(model.trans_light));


		}




	};




}














#endif