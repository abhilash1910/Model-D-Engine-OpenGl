"#version 330 core\n"
"out vec4 FragColor;\n"

"in vec2 TexCoords;\n"

"uniform sampler2D texture_diffuse1;\n"

"void main()\n"
"{\n"    
    "FragColor = texture(texture_diffuse1, TexCoords);\n"
"}\0"