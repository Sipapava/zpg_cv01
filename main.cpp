//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>

//krokovat zdrojak
//nehce absolutni cesty,ani bakalraka,
// projekt s relativnimi cestami, schopni upravit zdrojak, reakce na klavesnici, pohyb mysi, stistk tlacitek, vykreslen ctverce, co je rgb,

//byla varianta s globalni promennou
//bool rotate = false;

struct windowState {
	int rotate;
	int direction;
	float actualTime;
	float lastTime;
	float diff;
	float timer;
	int degree;
	int speed;
};

static void error_callback(int error, const char* description) { fputs(description, stderr); }

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	windowState* state = (windowState*)glfwGetWindowUserPointer(window);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
		printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
	}

	else if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		state->speed += 1;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		if (state->speed > 0) {
			state->speed -= 1;
		}
		
	}

	
}

static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

static void window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

static void cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }

static void button_callback(GLFWwindow* window, int button, int action, int mode) { //funkce registrovaen na callbacku, z GLFW musi mit pevne danou strukturu, jmeno uz libovolne
	if (action == GLFW_PRESS) {
		windowState* state = (windowState*)glfwGetWindowUserPointer(window);
		printf("button_callback [%d,%d,%d]\n", button, action, mode);
		state->rotate = 1;
		state->direction = -(state->direction);
	}


}

//GLM test

// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

// Camera matrix
glm::mat4 View = glm::lookAt(
	glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
	glm::vec3(0, 0, 0), // and looks at the origin
	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
);
// Model matrix : an identity matrix (model will be at the origin)
glm::mat4 Model = glm::mat4(1.0f);




int main(void)
{
	GLFWwindow* window;
	
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(640, 480, "ZPG", NULL, NULL); //poseldni paramtery jsou monitor a share kontext
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window); //opengl volani budou nyni aktivni na tomto okne
	glfwSwapInterval(1); //nastavi v sync s monitorem obnovovaci frekvenci

	windowState state = { 0,1,0,0,0,0,0,1};
	glfwSetWindowUserPointer(window, &state); //ulozeni ukazatele na tento state do okna, lze vybrat z callbacku

	// Sets the key callback
	//na zaklade se to ma tocit

	glfwSetKeyCallback(window, key_callback);

	glfwSetCursorPosCallback(window, cursor_callback);

	glfwSetMouseButtonCallback(window, button_callback); //api funkce GLFW

	glfwSetWindowFocusCallback(window, window_focus_callback);

	glfwSetWindowIconifyCallback(window, window_iconify_callback);

	glfwSetWindowSizeCallback(window, window_size_callback);


	int width, height;
	glfwGetFramebufferSize(window, &width, &height); //zisk aktualni veliksoti framebufferu v pixelech
	float ratio = width / (float)height;
	glViewport(0, 0, width, height); //urceni vykreslovaci oblasti


	glMatrixMode(GL_PROJECTION); //mod prace s projekcni matici
	glLoadIdentity(); //resetovani aktualni matice, vycisteni transformaci
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f); //nastaveni ortogonalni projekce, prvni parametry definuji svisle ohraniceni po x
	//dalsi jsou bottom a top, a near a far, promitaci plocha z=0
	

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT); //vycisti buffer

		glMatrixMode(GL_MODELVIEW); //prepnti na modelview matiic
		glLoadIdentity(); //loadne matici

		

		//toto ma rotovat 
		if (state.rotate == 1) {
			state.actualTime = (float)glfwGetTime();
			state.diff = state.actualTime - state.lastTime;
			state.lastTime = state.actualTime;
			state.timer += state.diff;
		}

		if (state.timer >= 0.005) {
			state.degree += (state.direction * state.speed);
			state.timer = 0;
			glTranslatef(-0.6f, 0.4f, 0.f);
			glRotatef((state.degree), 0.f, 0.f, 1.f);
			glTranslatef(0.6f, -0.4f, 0.f);
		}
		
		//vykresleni fixni pipeline, nebudeme moct pouzivat
		//fixni pipleine krok za krokem, nahrazeni shadery
		//moderni openGl, programovatelna pipeline
		glBegin(GL_QUADS); //zacatek a konec vykresleni 4uhelniku
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-0.6f, -0.4f, 0.f);

		glColor3f(0.f, 1.f, 0.f); //set bravy
		glVertex3f(0.6f, -0.4f, 0.f); //nastaveni vrcholu



		glColor3f(1.f, 1.f, 0.f);
		glVertex3f(0.6f, 0.4f, 0.f);

		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(-0.6f, 0.4f, 0.f);


		glEnd();
		glfwSwapBuffers(window); //pro vykresleni, swap bufferu, rychlejsi vykreslovani

		glfwPollEvents(); //zpracovani vstupu
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}