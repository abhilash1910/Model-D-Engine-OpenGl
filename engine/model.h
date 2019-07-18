#pragma once
#include<iostream>
#include<sstream>
#include<fstream>
#include<glm.hpp>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include<vector>
#include<map>
#include<GL/glew.h>
#include<glfw3.h>
#include<matrix.hpp>
#include<gtc/matrix_transform.hpp>



#include "mesh.h"
#include "shader.h"

#include "SOIL2/SOIL2.h"

using namespace std;


unsigned int texturefromfile(const char* path, const string &directory, bool gamma = false);
class model {

public:
	vector<texture>  texturesloaded;
	vector<mesh> meshes;
	string directory;
	bool gammacorrection;

	model(string const &path, bool gamma = false) :gammacorrection(gamma)
	{
		loadmodel(path);
	}

	void draw(Shader shader)
	{
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			meshes[i].draw(shader);
		}

	}
private:
	void loadmodel(string const &path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "IMPORTER::ASSIMP" << importer.GetErrorString()<< "\n";
			return;
		}

		directory = path.substr(0, path.find_last_of('/'));
		processnode(scene->mRootNode, scene);

	}

	void processnode(aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* Mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processmesh(Mesh, scene));

		}
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processnode(node->mChildren[i], scene);
		}
	}

	mesh processmesh(aiMesh* Mesh,const aiScene *scene)
	{
		vector<vertex> vertices;
		vector<unsigned int> indices;
		vector<texture> textures;
		for (unsigned int i = 0; i < Mesh->mNumVertices; i++)
		{
			vertex vertex;
			glm::vec3 vector;
			vector.x = Mesh->mVertices[i].x;
			vector.y = Mesh->mVertices[i].y;
			vector.z = Mesh->mVertices[i].z;
			vertex.position = vector;

			vector.x = Mesh->mNormals[i].x;
			vector.y = Mesh->mNormals[i].y;
			vector.z = Mesh->mNormals[i].z;
			vertex.normal = vector;

			if (Mesh->mTextureCoords[0])
			{
				glm::vec2 vector;
				vector.x = Mesh->mTextureCoords[0][i].x;
				vector.y = Mesh->mTextureCoords[0][i].y;
				vertex.textcoord = vector;
			}
			else
			{
				vertex.textcoord = glm::vec2(0.0f, 0.0f);

			}

			vector.x = Mesh->mTangents[i].x;
			vector.y = Mesh->mTangents[i].y;
			vector.z = Mesh->mTangents[i].z;
			vertex.tangent = vector;

			vector.x = Mesh->mBitangents[i].x;
			vector.y = Mesh->mBitangents[i].y;
			vector.z = Mesh->mBitangents[i].z;
			vertex.bitangent = vector;

			vertices.push_back(vertex);
		}
		for (unsigned int i = 0; i < Mesh->mNumFaces; i++)
		{
			aiFace face = Mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		aiMaterial *material = scene->mMaterials[Mesh->mMaterialIndex];
		vector<texture> diffusemaps = loadmaterialtextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffusemaps.begin(), diffusemaps.end());

		vector<texture> specularmaps = loadmaterialtextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(),specularmaps.begin(),specularmaps.end());

		vector<texture> normalmap = loadmaterialtextures(material, aiTextureType_HEIGHT, "texture_normal");
		textures.insert(textures.end(), normalmap.begin(), normalmap.end());

		vector<texture> heightmap = loadmaterialtextures(material, aiTextureType_AMBIENT, "texture_height");
		textures.insert(textures.end(), heightmap.begin(), heightmap.end());
		return mesh(vertices, indices, textures);
	}

	vector<texture> loadmaterialtextures(aiMaterial *mat, aiTextureType type, string typeName)
	{
		vector<texture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
			aiString str;
			mat->GetTexture(type, 1, &str);
			bool skip = false;
			for (unsigned int j = 0; j < texturesloaded.size(); j++)
			{
				if (strcmp(texturesloaded[j].path.data(), str.C_Str()) == 0)
				{
					textures.push_back(texturesloaded[j]);
					skip = true;
					break;
				}

			}
			if (!skip)
			{
				texture texture;
				texture.id = texturefromfile(str.C_Str(), this->directory);
				texture.type = typeName;
				texture.path = str.C_Str();
				textures.push_back(texture);
				texturesloaded.push_back(texture);
				cout << texture.id << endl;


			}
		}
		
		return textures;
	}





};


unsigned int texturefromfile(const char* path, const string &directory, bool gamma)
{
	string filename = string(path);
	//cout << filename << endl;
	string ss = "texture_diffuse.png";
	filename = directory + '/' + filename +ss  ;
	cout << filename << endl;
	std::ifstream infile(filename);

	if (infile.good())
	{
		cout << "Good" << endl;
	}
	else
	{
		cout << "Not good" << endl;
	}
	unsigned int textureid;
	glGenTextures(1, &textureid);
	cout << textureid << endl;
	int height, width, nrcomponents;
	unsigned char *data = SOIL_load_image(filename.c_str(), &width, &height, 0,SOIL_LOAD_RGB);
	
	cout << height << width  << filename.c_str()<<endl;
	if (data)
	{
		GLenum format;
			format = GL_RGB;
		
		glBindTexture(GL_TEXTURE_2D, textureid);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		SOIL_free_image_data(data);

	}
	else
	{
		cout << "data is not there" << endl;
		std::cout << "Texture failed to load at path: " << (const char*)(path) << std::endl;
	
		SOIL_free_image_data(data);
	}

	return textureid;

}


