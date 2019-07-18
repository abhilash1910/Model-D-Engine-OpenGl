
#ifndef  mesh_h
#define mesh_h
#include<string>
#include<fstream>
#include<vector>
#include<glm.hpp>
#include<iostream>
#include<GL/glew.h>
#include<glfw3.h>
#include<matrix.hpp>
#include "shader.h"
#include<gtc/matrix_transform.hpp>

using namespace std;


	struct vertex {


		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 textcoord;
		glm::vec3 tangent;
		glm::vec3 bitangent;






	};


	struct texture {


		GLuint id;
		string type;
		string path;

	};


	class mesh{
	private:
		unsigned int VAO, VBO, EBO;
		void setupmesh() {



			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vertex), &vertices[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*(sizeof(GLuint)), &indices[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, textcoord));
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, tangent));
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, bitangent));
			
			glBindVertexArray(0);

		}
		
	public:
		vector<vertex> vertices;
		vector<GLuint> indices;
		vector<texture> textures;
		mesh(vector<vertex> vertices, vector<GLuint> indices, vector<texture> textures)
		{

			this->vertices = vertices;
			this->indices = indices;
			this->textures = textures;
			setupmesh();
		}

		void draw(Shader shader)
		{
			unsigned int diffuseNr = 1;
			unsigned int specularNr = 1;
			unsigned int normalNr = 1;
			unsigned int heightNr = 1;

			for (unsigned int i = 0; i < textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				string name = textures[i].type;
				string number;
				if (name == "texture_diffuse")
				{
					number = to_string(diffuseNr++);
				}
				else if (name == "texture_specular")
				{
					number = to_string(specularNr++);
				}
				else if (name == "texture_normal")
				{
					number = to_string(normalNr++);
				}
				else if (name == "texture_height")
				{
					number = to_string(heightNr++);
				}

				glUniform1i(glGetUniformLocation(shader.id,(name+number).c_str()),i);
				glBindTexture(GL_TEXTURE_2D, textures[i].id);


			}


			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			glActiveTexture(GL_TEXTURE0);

		}



	};








#endif 
