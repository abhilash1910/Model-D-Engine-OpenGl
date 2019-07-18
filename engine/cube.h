#pragma once
#include<iostream>
#include<vector>
#include<GL/glew.h>
#include<glfw3.h>
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include<sstream>
#include<fstream>
#include "SOIL2/SOIL2.h"



using namespace std;

float plane[] = { 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
};



class cube {

public:
	
	inline void buff();
	inline unsigned int loadtex(const char* path);





};

void cube::buff()
{
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(plane), &plane, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*(sizeof(float)),(void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * (sizeof(float)), (void*)3);
	glBindVertexArray(0);



}

unsigned int cube::loadtex(const char* path)
{
	unsigned int textureid;
	glGenTextures(1, &textureid);
	int width, height, nrcomponents;
	unsigned char* data = SOIL_load_image(path,&width,&height,0,SOIL_LOAD_RGB);
	if (data)
	{
		GLenum format;
		format = GL_RGB;
		glBindTexture(GL_TEXTURE_2D,textureid);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		SOIL_free_image_data(data);

	}
	else
	{ 
		cout << "Failed to load texture" << (const char*)path << endl;
		SOIL_free_image_data(data);
	
	
	}

	return textureid;



}



