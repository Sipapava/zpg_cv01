#pragma once

//remake, shaders will be loaded from files
//
extern const char* vertex_shader = 
"#version 330\n"
"layout(location=0) in vec3 vp;" 
"uniform mat4 modelMatrix;"
"void main () {"
"     gl_Position = vec4 (vp, 1.0) * modelMatrix;" //OPRAVIT! na vec4
"}";

extern const char* fragment_shader = 
"#version 330\n"
"out vec4 fragColor;" 
"void main () {"
"     fragColor = vec4 (0.5, 0.0, 0.5, 1.0);" 
"}";

extern const char* vertex_shader_color = 
"#version 330\n"
"layout(location = 0) in vec4 vp;"   
"layout(location = 1) in vec4 color;" 
"out vec4 fragColor;"

"uniform mat4 modelMatrix;" 

"void main () {"
"    gl_Position = modelMatrix * vp;" 
"	 fragColor = color;"
"}";

extern const char* fragment_shader_color = 
"#version 330\n"
"in vec4 fragColor;" 
"out vec4 outColor;"
"void main () {"
"     outColor = fragColor;" 
"}";