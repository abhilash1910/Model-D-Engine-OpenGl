#ifndef diffusedlight_h
#define diffusedlight_h

#include<GL/glew.h>
#include<glfw3.h>
#include<iostream>
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include "render_engine.h"

using namespace std;
using namespace renderengine;
using namespace glm;
vec3 lightPos(1.2f, 1.0f, 2.0f);

namespace diffused {

	class shaders {
	protected :
		const char* basicvlighting = "#version 330 core\n"
			"layout (location=0) in vec3 aPos;\n"
			"layout (location=1) in vec3 aNormal;\n"
			"unifrom mat4 projection;\n"
			"uniform mat4 view;\n"
			"uniform mat4 model;\n"
			"out vec3 Frag;\n"
			"out vec3 Normal;\n"
			"void main()\n"
			"{\n"
			"Frag=vec3(model* vec4(aPos,1.0f));\n"
			"gl_position= projection*view *vec4(Frag,1.0f);\n"
			"Normal = aNormal;\n"
			"}\0";

		const char* basicflighting = "#version 330 core\n"
			"out vec4 fragcolor;\n"
			"in vec3 Frag;\n"
			"in vec3 Normal;\n"
			"uniform vec3 lightpos;\n"
			"uniform vec3 objectcolor;\n"
			"uniform vec3 lightcolor;\n"
			"void main()\n"
			"{\n"
			//ambient light
			"float ambientlight= 0.1f;\n"
			"vec3 ambient=ambientlight*lightcolor;\n"
			//diffused light

			"vec3 norm= normalize(Normal);\n"
			"vec3 lightdir= normalize(lightpos-Frag);\n"
			"float diff=max(dot(norm,lightdir),0.0f);\n"
			"vec3 diffused= diff*lightcolor;\n"

			"vec3 result= (ambient + diffused) * objectcolor;\n"
			"fragcolor= vec4(result,1.0f);\n"
			"}\0";
		const char* lampvertex = "#version 330 core\n"
			"layout(location=0) in vec3 aPos;\n"
			"uniform mat4 projection;\n"
			"uniform mat4 view;\n"
			"uniform mat4 model;\n"
			"void main()\n"
			"{\n"
			"gl_Position= projection*view*model*vec4(aPos,1.0f);\n"
			"}\0";
		const char* lampfragment = "#version 330 core\n"
			"out vec4 fragcol;\n"
			"void main()\n"
			"{\n"
			"fragcol= vec4(1.0f);\n"
			"}\0";
	public:
		inline unsigned int basiclightvertex(shaders const &);
		inline unsigned int basiclightfragment(shaders const &);
		/*inline unsigned int lampvertex(shaders const &);
		inline unsigned int lampfragment(shaders const &);
		inline unsigned int programbasic(shaders const &);
		inline unsigned int programlamp(shaders const &);
		*/
	};

	unsigned int shaders::basiclightvertex(shaders const &a)
	{
	
		const char* v_shad = a.basicvlighting;
		unsigned int vertexbasic = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexbasic, 1, &v_shad, NULL);
		glCompileShader(vertexbasic);
		int succes;
		char infolog[512];
		glGetShaderiv(vertexbasic, GL_COMPILE_STATUS, &succes);
		if (!succes)
		{
			cout << "Energy in basic vertex shader" << endl;
			glGetShaderInfoLog(vertexbasic, 512, NULL, infolog);

		}

	
	
	
	
	}


	unsigned int shaders::basiclightfragment(shaders const &a)
	{
	
		const char* f_shad = a.basicflighting;
		unsigned int fragbasic = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(fragbasic, 1, &f_shad, NULL);
		glCompileShader(fragbasic);
		int success; 
		char infolog[512];
		glGetShaderiv(fragbasic, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			cout << "Energy in basic fragment shader" << endl;
			glGetShaderInfoLog(fragbasic, 512, NULL, infolog);
		
		}
	
	
	
	
	
	}






























}

































#endif