#ifndef renderengine_h
#define renderengine_h
#include<GL/glew.h>
#include<glfw3.h>
#include<iostream>
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>

//#include "lighting.h"


using namespace std;
using namespace glm;
//using namespace light_engine;
namespace renderengine {


	class render_engine {

	protected:
		const char* vertex_model = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"layout (location = 1) in vec3 aNormal;\n"
			"layout (location = 2) in vec2 aTexCoords;\n"

			"out vec2 TexCoords;\n"

			"uniform mat4 model;\n"
			"uniform mat4 view;\n"
			"uniform mat4 projection;\n"

			"void main()\n"
			"{\n"
			"TexCoords = aTexCoords;\n"
			"gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
			"}\0";

		const char* vertex = "#version 330 core\n"
			"layout (location=0) in vec3 aPos;\n"
			"layout (location=1) in vec3 aColor;\n"
			"out vec3 color;\n"
			"uniform mat4 transform;\n"
			"void main()\n"
			"{\n"
			"gl_Position= transform*vec4(aPos,1.0f);\n"
			"color= aColor;\n"
			"}\0";
		
		const char* vertex_3d = "#version 330 core\n"
			"layout (location=0) in vec3 aPos;\n"
			"layout (location=1) in vec3 aColor;\n"
			"out vec3 color;\n"
			"uniform mat4 model;\n"
			"uniform mat4 projection;\n"
			"uniform mat4 view;\n"
			"void main()\n"
			"{\n"
			"gl_Position = projection*view*model*vec4(aPos,1.0f);\n"
			"color=aColor;\n"
			"}\0";
		const char* fragment = "#version 330 core\n"
			"in vec3 color;\n"
			"out vec4 frag;\n"
			"void main()\n"
			"{\n"
			"frag= vec4(color,1.0f);\n"
			"}\0";;

		const char* fragment_model = "#version 330 core\n"
			"out vec4 FragColor;\n"

			"in vec2 TexCoords;\n"

			"uniform sampler2D texture_diffuse1;\n"

			"void main()\n"
			"{\n"
			"FragColor = texture(texture_diffuse1, TexCoords);\n"
			"}\0";
	public:


		inline unsigned int vertcompile(render_engine const &);
		inline unsigned int fragcompile(render_engine const &);
		inline unsigned int program(render_engine const &);
		inline unsigned int vert3dcompile(render_engine const &);
		inline unsigned int program3d(render_engine const &);
		inline unsigned int vertcompilemodel(render_engine const &);
		inline unsigned int fragmentcompilemodel(render_engine const &);
		inline unsigned int programmodel(render_engine const &);
	};

	unsigned int render_engine::vertcompilemodel(render_engine const &a)
	{
		const char* avertex = a.vertex;
		unsigned int vshad = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vshad, 1, &avertex, NULL);
		glCompileShader(vshad);
		int success;
		char infolog[512];
		glGetShaderiv(vshad, GL_COMPILE_STATUS, &success);
		if (!success)
		{


			glGetShaderInfoLog(vshad, 512, NULL, infolog);
			std::cout << "Error in vertex shader" << std::endl;
			return -1;

		}


		return vshad;

	}
	unsigned int render_engine::vertcompile(render_engine const &a)
	{
		const char* avertex = a.vertex;
		unsigned int vshad = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vshad, 1, &avertex, NULL);
		glCompileShader(vshad);
		int success;
		char infolog[512];
		glGetShaderiv(vshad, GL_COMPILE_STATUS, &success);
		if (!success)
		{


			glGetShaderInfoLog(vshad, 512, NULL, infolog);
			std::cout << "Error in vertex shader" << std::endl;
			return -1;

		}


		return vshad;
	}

	unsigned int render_engine::fragmentcompilemodel(render_engine const &b)
	{
		const char* afragment = b.fragment;
		unsigned int fshad = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fshad, 1, &afragment, NULL);
		glCompileShader(fshad);
		int success;
		char infolog[512];
		glGetShaderiv(fshad, GL_COMPILE_STATUS, &success);
		if (!success)
		{

			glGetShaderInfoLog(fshad, 512, NULL, infolog);
			std::cout << "Error in fragment shader" << std::endl;
			return -1;

		}

		return fshad;
	}
	unsigned int render_engine::vert3dcompile(render_engine const &a)
	{
		const char* avertex = a.vertex_3d;
		unsigned int vshad = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vshad, 1, &avertex, NULL);
		glCompileShader(vshad);
		int success;
		char infolog[512];
		glGetShaderiv(vshad, GL_COMPILE_STATUS, &success);
		if (!success)
		{


			glGetShaderInfoLog(vshad, 512, NULL, infolog);
			std::cout << "Error in vertex shader" << std::endl;
			return -1;

		}


		return vshad;
	}
	unsigned int render_engine::fragcompile(render_engine const &b)
	{

		const char* afragment = b.fragment;
		unsigned int fshad = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fshad, 1, &afragment, NULL);
		glCompileShader(fshad);
		int success;
		char infolog[512];
		glGetShaderiv(fshad, GL_COMPILE_STATUS, &success);
		if (!success)
		{

			glGetShaderInfoLog(fshad, 512, NULL, infolog);
			std::cout << "Error in fragment shader" << std::endl;
			return -1;

		}

		return fshad;


	}

	unsigned int render_engine::program(render_engine const &a)
	{

		unsigned int program = glCreateProgram();
		unsigned int x = vertcompile(a);
		unsigned int y = fragcompile(a);
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

	unsigned int render_engine::programmodel(render_engine const &a)
	{
		unsigned int program = glCreateProgram();
		unsigned int x = vertcompilemodel(a);
		unsigned int y = fragmentcompilemodel(a);
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


	unsigned int render_engine::program3d(render_engine const &a)
	{

		unsigned int program = glCreateProgram();
		unsigned int x = vert3dcompile(a);
		unsigned int y = fragcompile(a);
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



	class buffer {



	public:


		inline void allocate_buffers(float size, const void* vertices, float size_index, const void* vert_index);
		inline void allocate_buffer(float size, const void* vertices);






	};

	void buffer::allocate_buffers(float size, const void* vertices, float size_index, const void* vert_index)
	{
		unsigned int vao;
		unsigned int vbo;
		unsigned int ebo;

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_index, vert_index, GL_STATIC_DRAW);


		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);



	}
	void buffer::allocate_buffer(float size, const void* vertices)
	{


		unsigned int vao;
		unsigned int vbo;
		

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

		

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		


	}


	class depth {
	public:
		inline void depthtest()
		{

			glEnable(GL_DEPTH_TEST);

		}

	};



	class windowgl :public buffer {

	
	public:
		GLFWwindow *window;
		//inline void open_window(int width, int height);
		inline void initgl();
		//inline void display(unsigned int program, unsigned int size, int width, int height);
		
	};

    

	void windowgl::initgl()
	{

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	}



	class transformation:protected render_engine {

	protected:
		mat4 trans;
		
	public:
		inline friend transformation scale(transformation const &);
		inline friend transformation rotate(transformation const &);
		inline friend transformation translate(transformation const &);
		inline void transform_engine_scale(transformation const &);
		inline void transform_engine_rotate(transformation const &);
		inline void transform_engine_translate(transformation const &);
		inline void transform_engine_reset(transformation const &);
		inline void transform_3d_engine(transformation const &,unsigned int const &,unsigned int const &);
		inline friend transformation rot(transformation const &a,float const &degree)
			
	{

			transformation b;
			b.trans = glm::rotate(b.trans, radians(degree), vec3(1.0f, 0.0f, 0.0f));
			return b;

		}
		inline friend transformation trans_late(transformation const &a, vec3  const &b)
		{
			transformation c = a;
			vec3 bz = b;
			
			c.trans = glm::translate(c.trans,bz);
			return c;

		}

		inline friend transformation scale_3d(transformation const &);
	};

	transformation scale_3d(transformation const &v)
	{
		
			transformation c;
			c.trans = glm::scale(v.trans, vec3(0.1f, 0.1f, 0.1f));
			return c;
		

	}

	  transformation   scale(transformation const &a)
	{

		  transformation b;
		 b.trans  =  glm::scale(a.trans, vec3(0.5f, 0.5f, 0.5f));
		return b;

	}
	transformation rotate(transformation const &a)
	 {
		 transformation b;
		b.trans = glm::rotate(a.trans,(float)glfwGetTime(),vec3(0.0f,0.0f,1.0f));
		return b;
	 }

	 transformation  translate(transformation const &a)
	 {
		 transformation b;
		 b.trans = glm::translate(a.trans,vec3(2.5f,-0.5f,0.0f));
		 return b;
	}
	 void transformation::transform_engine_scale(transformation const &a)
	 {
		 render_engine rene;
		 unsigned int progr = rene.program(rene);
		 transformation b;
		 b = scale_3d(a);
		 unsigned int transformloc = glGetUniformLocation(progr,"transform");
		 glUniformMatrix4fv(transformloc,1,GL_FALSE,value_ptr(b.trans));


	 }
	 void transformation::transform_engine_rotate(transformation const  &a)
	 {
		 render_engine rene;
		 unsigned int progr = rene.program(rene);
		 transformation b;
		 b = rotate(a);
		 unsigned int transformloc = glGetUniformLocation(progr, "transform");
		 glUniformMatrix4fv(transformloc, 1, GL_FALSE, value_ptr(b.trans));


	 }

	 void transformation::transform_engine_translate(transformation const &a)
	 {
		 render_engine rene;
		 unsigned int progr = rene.program(rene);
		 transformation b;
		 b = translate(a);
		 unsigned int transformloc = glGetUniformLocation(progr, "transform");
		 glUniformMatrix4fv(transformloc, 1, GL_FALSE, value_ptr(b.trans));


	 }
	 void transformation::transform_engine_reset(transformation const &a)
	 {
		 transformation b = a;
		 b.trans = mat4(1.0f);
		 render_engine rene;
		 unsigned int progr = rene.program(rene);
		 unsigned int transformloc = glGetUniformLocation(progr, "transform");
		 glUniformMatrix4fv(transformloc, 1, GL_FALSE, value_ptr(b.trans));



	 }

	 void transformation::transform_3d_engine(transformation const &a,unsigned int const &width,unsigned int const &height)
	 {

		 render_engine rene;
		 unsigned int progr = rene.program3d(rene);
		 transformation view = a;
		 view.trans = mat4(1.0f);
		 transformation model=a;
		 model.trans = mat4(1.0f);
		 transformation projection = a;
		 projection.trans = mat4(1.0f);
		 model = rot(model, -55.0f);
		 view = trans_late(view, vec3(0.0f, 0.0f, -0.5f));
		 projection.trans = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
		 unsigned int model_loc = glGetUniformLocation(progr,"model");
		 unsigned int view_loc = glGetUniformLocation(progr, "view");
		 unsigned int projection_loc = glGetUniformLocation(progr, "projection");
		 glUniformMatrix4fv(model_loc, 1, GL_FALSE, value_ptr(model.trans));
		 glUniformMatrix4fv(view_loc, 1, GL_FALSE, value_ptr(view.trans));
		 glUniformMatrix4fv(projection_loc,1,GL_FALSE,value_ptr(projection.trans));


	 }


	 class camera:protected render_engine{

	 protected:
		 mat4 cam;
		 vec3 cam_pos;
	     vec3 cam_front;
		 vec3 cam_up;
		 float deltatime = 0.0f;
		 float lasttime = 0.0f;
		 bool firstmouse;
		 float yaw;
		 float pitch;
		 float fov;
		 float lastx;
		 float lasty;

	 public:
		 inline void cam_rotation(camera const &, unsigned int const &, unsigned int const &);
		 inline void cam_movement(camera const &, unsigned int const &, unsigned int const &);
		 inline void put_value(unsigned int const &width,unsigned int const &height)
		 {
			 float x1 = 0.0f;
			 float y1 = 0.0f;
			  vec3 x = vec3(0.0f, 0.0f, 3.0f);
			  vec3 y = vec3(0.0f, 0.0f, -1.0f);
			  vec3 z = vec3(0.0f, 1.0f, 0.0f);
			  bool fm = true;
			  float fovy = 45.0f;
			  float pitch_m = 0.0f;
			  float yaw_m = -90.0f;
			  float l_x = width / 2.0f;
			  float l_y = height / 2.0f;

			 camera cami;
			 cami.cam_pos = x;
			 cami.cam_front = y;
			 cami.cam_up = z;
			 cami.deltatime = x1;
			 cami.lasttime = y1;
			 cami.firstmouse = fm;
			 cami.fov = fovy;
			 cami.pitch = pitch_m;
			 cami.yaw = yaw_m;
			 cami.lastx = l_x;
			 cami.lasty = l_y;
			
			 
		 }
		 inline void  get_cam_front_usingvec(vec3 const &a,camera const &cami)
		 {
			 camera cam_v = cami;
			 cam_v.cam_front = a;
			// return cam_v.cam_front;
		 }

		 inline vec3 get_cam_pos(camera const &x)
		 {

			 return x.cam_pos;
		 }
		 inline vec3 get_cam_front(camera const &x)
		 {
			 return x.cam_front;
		 }
		 inline vec3 get_cam_up(camera const &x)
		 {
			 return x.cam_up;
		 }
		 inline float get_deltatime(camera const &x)
		 {
			 return x.deltatime;
		 }
		 inline float get_lasttime(camera const &x)
		 {
			 return x.lasttime;
		 }
		 
		 inline float get_fov(camera const &x)
		 {
			 return x.fov;
		 }
		 inline float get_lastx(camera const &x)
		 {
			 return x.lastx;
		 }
		 inline float get_lasty(camera const &x)
		 {
			 return x.lasty;
		 }
		 inline float get_pitch(camera const &x)
		 {
			 return x.pitch;
		 }
		 inline float get_yaw(camera const &x)
		 {
			 return x.yaw;
		 }
		 inline bool get_firstmouse(camera const &x)
		 {
			 return x.firstmouse;
		 }




		 inline void delta_cam(camera const &a,unsigned int const &width,unsigned int const &height)
		 {
			 camera cam_time = a;
			 cam_time.put_value(width,height);
			 float currenttime = glfwGetTime();
			 cam_time.deltatime = currenttime - cam_time.lasttime;
			 cam_time.lasttime= currenttime;

		 }
		 inline mat4 cam_mouse(camera const &a) {
			 camera cam_ii = a;
			 cam_ii.cam = mat4(1.0f);
			 return cam_ii.cam;
		 }


	 };



	 void camera::cam_movement(camera const &a, unsigned int const &width, unsigned int const &height)
	 {

		 render_engine rene;
		 unsigned int progr=rene.program3d(rene);

		 
		 
		 camera cam_project = a;
		 cam_project.put_value(width,height);
		 cam_project.cam = mat4(1.0f);
		 cam_project.cam = glm::perspective(radians(45.0f), (float)width / (float)height, 1.0f, 100.0f);
		 unsigned int projection_cam = glGetUniformLocation(progr,"projection");
		 glUniformMatrix4fv(projection_cam,1,GL_FALSE,value_ptr(cam_project.cam));

		 camera cam_view = a;
		 cam_view.put_value(width,height);
		 cam_view.cam = mat4(1.0f);
		 cam_view.cam = glm::lookAt(cam_view.get_cam_pos(cam_view), cam_view.get_cam_pos(cam_view) + cam_view.get_cam_front(cam_view), cam_view.get_cam_up(cam_view));
		 unsigned  int view_cam_loc = glGetUniformLocation(progr, "view");
		 glUniformMatrix4fv(view_cam_loc, 1, GL_FALSE, value_ptr(cam_view.cam));

		 
		 camera cam_model = a;
		 cam_model.put_value(width,height);
		 cam_model.cam = mat4(1.0f);
		 cam_model.cam = glm::rotate(cam_model.cam, glm::radians(-60.0f), vec3(1.0f, 3.0f, 5.0f));
		 unsigned int model_cam_loc = glGetUniformLocation(progr, "model");
		 glUniformMatrix4fv(model_cam_loc, 1, GL_FALSE, value_ptr(cam_model.cam));

		 


	 }


	 void camera::cam_rotation(camera const &a, unsigned int const &width, unsigned int const &height)
	 {

		 render_engine rene;
		 unsigned int progr = rene.program3d(rene);
		 camera cam_model = a;
		 cam_model.cam = glm::mat4(1.0f);
		 camera cam_view = a;
		 cam_view.cam = mat4(1.0f);
		 camera cam_projection = a;
		 cam_projection.cam = mat4(1.0f);

		 cam_projection.cam = glm::perspective(radians(45.0f),(float)width/(float)height,0.1f,100.0f);
		 unsigned int projection_cam_loc = glGetUniformLocation(progr,"projection");
		 glUniformMatrix4fv(projection_cam_loc,1,GL_FALSE,value_ptr(cam_projection.cam));


		 float radius = 10.0f;
		 float camx = sin(glfwGetTime())*radius;
		 float camz = cos(glfwGetTime())*radius;
		 cam_view.cam = glm::lookAt(vec3(camx,0.0f,camz),vec3(0.0f,0.0f,0.0f),vec3(0.0f,1.0f,0.0f));
		 unsigned int view_cam_loc = glGetUniformLocation(progr,"view");
		 glUniformMatrix4fv(view_cam_loc, 1, GL_FALSE, value_ptr(cam_view.cam));

		 cam_model.cam = glm::rotate(cam_model.cam,glm::radians(-60.0f),vec3(1.0f,3.0f,5.0f));
		 unsigned int model_cam_loc = glGetUniformLocation(progr,"model");
		 glUniformMatrix4fv(model_cam_loc,1,GL_FALSE,value_ptr(cam_model.cam));


	 }



	 class input:protected camera,public windowgl{

	 protected:
		 mat4 in_cam;

	 public:

		 inline void input_view(GLFWwindow *z,unsigned int const &width,unsigned int const &height)
		 {

			 camera cam_in;
			 cam_in.put_value(width,height);
			 float time = cam_in.get_deltatime(cam_in);
			 
			 float cameraspeed = 2.5 * time;
			 if (glfwGetKey(z, GLFW_KEY_W) == GLFW_PRESS)
			 {
				 cam_in.get_cam_pos(cam_in) += cameraspeed * cam_in.get_cam_front(cam_in);
				 cout << "f" << endl;
			 }
			 if (glfwGetKey(z, GLFW_KEY_S) == GLFW_PRESS)
			 {
				 cam_in.get_cam_pos(cam_in) -= cameraspeed * cam_in.get_cam_front(cam_in);

			 }

			 if (glfwGetKey(z, GLFW_KEY_A) == GLFW_PRESS)
			 {
				 cam_in.get_cam_pos(cam_in) -= glm::normalize(glm::cross(cam_in.get_cam_front(cam_in), cam_in.get_cam_up(cam_in)))*cameraspeed;

			 }

			 if (glfwGetKey(z, GLFW_KEY_D) == GLFW_PRESS)
			 {
				 cam_in.get_cam_pos(cam_in) += glm::normalize(glm::cross(cam_in.get_cam_front(cam_in), cam_in.get_cam_up(cam_in)))*cameraspeed;
			 }


		 }
		 inline void mouse_callback(GLFWwindow *z, camera const &a, unsigned int const &width, unsigned int const &height,double const &xpos,double const &ypos)
		 {

			 camera cam_mou=a;
			 cam_mou.put_value(width, height);
			 bool fmouse = cam_mou.get_firstmouse(cam_mou);
			 float lastx = cam_mou.get_lastx(cam_mou);
			 float lasty = cam_mou.get_lasty(cam_mou);
			 float pitch = cam_mou.get_pitch(cam_mou);
			 float yaw = cam_mou.get_yaw(cam_mou);
			 if (fmouse == true)
			 {

				 lastx = xpos;
				 lasty = ypos;
				 fmouse = false;
			 }
			 float xoffset = xpos - lastx;
			 float yoffset = ypos - lasty;
			 lastx = xpos;
			 lasty = ypos;
			 float sensitivity = 0.1f;
			 xoffset *= sensitivity;
			 yoffset *= sensitivity;
			 pitch += xoffset;
			 yaw += yoffset;
			 if (pitch > 89.0f)
			 {
				 pitch = 89.0f;
			 }
			 if (yaw <= -89.0f)
			 {
				 yaw = -89.0f;
			 }

			 vec3 front;
			 front.x = cos(radians(yaw))*cos(radians(pitch));
			 front.y = sin(radians(pitch));
			 front.z = sin(radians(yaw))*cos(radians(pitch));
			
			 cam_mou.get_cam_front_usingvec(front, cam_mou);
			 
            






				}


		 inline void screen_callback(GLFWwindow *z, camera const &b, double const &xoffset, double const &yoffset,unsigned int const &width,unsigned int height)
		 {
			 camera cam_scroll = b;
			 cam_scroll.put_value( width, height);
			 float fovy = cam_scroll.get_fov(cam_scroll);
			 if (fovy >= 1.0f && fovy <= 45.0f)
			 {
				 fovy -= yoffset;
			 }
			 if (fovy <= 1.0f)
			 {
				 fovy = 1.0f;
			 }
			 if (fovy >= 45.0f)
			 {
				 fovy = 45.0f;
			 }

			 
		 }


		 inline void cam_scroll(unsigned int const & width, unsigned int const &height, camera const &a, double const &xpos, double const &ypos)
		 {

			 render_engine rene;
			 unsigned int progr = rene.program3d(rene);


			 
			 camera cam_project = a;
			 cam_project.put_value(width, height);
			 mat4 cam_p=cam_project.cam_mouse(cam_project);
			 cam_p = glm::perspective(radians(45.0f), (float)width / (float)height, 1.0f, 100.0f);
			 unsigned int projection_cam = glGetUniformLocation(progr, "projection");
			 glUniformMatrix4fv(projection_cam, 1, GL_FALSE, value_ptr(cam_p));

			 camera cam_view = a;
			 cam_view.put_value(width, height);
			 mat4 cam_v = cam_view.cam_mouse(cam_view);
			 input in;
			 GLFWwindow *z;
			 in.mouse_callback(z,cam_view,width,height,xpos,ypos);
			 cam_v = glm::lookAt(cam_view.get_cam_pos(cam_view), cam_view.get_cam_pos(cam_view) + cam_view.get_cam_front(cam_view), cam_view.get_cam_up(cam_view));
			 unsigned  int view_cam_loc = glGetUniformLocation(progr, "view");
			 glUniformMatrix4fv(view_cam_loc, 1, GL_FALSE, value_ptr(cam_v));


			 camera cam_model = a;
			 cam_model.put_value(width, height);
			 mat4 cam_m = cam_model.cam_mouse(cam_model);
			 cam_m = glm::rotate(cam_m, glm::radians(-60.0f), vec3(1.0f, 3.0f, 5.0f));
			 unsigned int model_cam_loc = glGetUniformLocation(progr, "model");
			 glUniformMatrix4fv(model_cam_loc, 1, GL_FALSE, value_ptr(cam_m));



		 }





	 };



	 

}































#endif