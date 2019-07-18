#ifndef shader_h
#define shader_h
#include<sstream>
#include<iostream>
#include<fstream>
#include<string>
#include<glm.hpp>
#include<GL/glew.h>
#include<glfw3.h>

using namespace std;
class Shader {

public:
	unsigned int id;
	Shader(const char* vertexpath, const char* fragmentpath, const char* geometrypath = nullptr)
	{
		string vertexcode;
		string fragmentcode;
		string geometrycode;
		ifstream vshaderfile;
		ifstream fshaderfile;
		ifstream gshaderfile;
		vshaderfile.exceptions(ifstream::failbit | ifstream::badbit);
		fshaderfile.exceptions(ifstream::failbit | ifstream::badbit);
		gshaderfile.exceptions(ifstream::failbit | ifstream::badbit);
		try {

			vshaderfile.open(vertexpath);
			fshaderfile.open(fragmentpath);
			stringstream vshaderstream, fshaderstream;
			vshaderstream << vshaderfile.rdbuf();
			fshaderstream << fshaderfile.rdbuf();
			vshaderfile.close();
			fshaderfile.close();
			vertexcode = vshaderstream.str();
			fragmentcode = fshaderstream.str();
			if (geometrypath != nullptr)
			{
				gshaderfile.open(geometrypath);
				stringstream gshaderstream;
				gshaderstream << gshaderfile.rdbuf();
				gshaderfile.close();
				geometrycode = gshaderstream.str();


			}


		}
		catch(ifstream::failure e){
			cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << "\n";

		}
		const char* vertexshadercode = vertexcode.c_str();
		const char* fragmentshadercode = fragmentcode.c_str();
		const char* geometryshadercode;
		unsigned int geometry;
		unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex,1,&vertexshadercode,NULL);
		glCompileShader(vertex);
		checkerror(vertex, "VERTEX");

		unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentshadercode, NULL);
		glCompileShader(fragment);
		checkerror(fragment, "FRAGMENT");

		if (geometrypath != nullptr)
		{
			geometryshadercode = geometrycode.c_str();
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &geometryshadercode, NULL);
			glCompileShader(geometry);
			checkerror(geometry, "GEOMETRY");

		}
		id = glCreateProgram();
		glAttachShader(id,vertex);
		glAttachShader(id, fragment);
		if (geometrypath != nullptr)
		{

			glAttachShader(id, geometry);

		}
		glLinkProgram(id);
		checkerror(id, "program");
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if (geometrypath != nullptr)
		{
			glDeleteShader(geometry);
		}




	}
	void use() {


		glUseProgram(id);

	}
	void setBool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string &name, const glm::vec2 &value) const
	{
		glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
	}
	void setVec2(const std::string &name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string &name, const glm::vec3 &value) const
	{
		glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string &name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string &name, const glm::vec4 &value) const
	{
		glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
	}
	void setVec4(const std::string &name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string &name, const glm::mat2 &mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string &name, const glm::mat3 &mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string &name, const glm::mat4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	private:

		void checkerror(unsigned int shader, string type)
		{
			int success;
			char infolog[1024];
			if (type != "program")
			{
				glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					glGetShaderInfoLog(shader, 1024, NULL, infolog);
					std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infolog << "\n -- --------------------------------------------------- -- " << std::endl;

				}
				else
				{
					cout << "YEAH SHADERS ARE COMPILED" << endl;
				}
			}
			else
			{
				glGetProgramiv(shader, GL_LINK_STATUS, &success);
				if (!success)
				{
					glGetProgramInfoLog(shader, 1024, NULL, infolog);
					std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infolog << "\n -- --------------------------------------------------- -- " << std::endl;
				}
				else
				{
					cout << "YEAH PROGRAM IS COMPILED" << endl;
				}
			}






		}
	 









};





#endif shader_h

