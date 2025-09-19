#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

int main(void) {
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = glfwCreateWindow(640, 480, "Krychle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float)height;

    float fov = 45.0f;
    float near = 0.1f;
    float far = 100.0f;
    float aspect = width / (float)height;

    float top = near * tan(fov * 3.14159f / 360.0f);
    float bottom = -top;
    float right = top * aspect;
    float left = -right;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(left, right, bottom, top, near, far);

    float angle = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST); // zapnout hloubkový test

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // "kamera"
        glTranslatef(0.0f, 0.0f, -3.0f);
        glRotatef(angle, 1.f, 1.f, 0.f);

        // vykreslení krychle
        glBegin(GL_QUADS);

        // Přední strana (z = +0.5)
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);

        // Zadní strana (z = -0.5)
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);

        // Levá strana (x = -0.5)
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);

        // Pravá strana (x = +0.5)
        glColor3f(1.f, 1.f, 0.f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);

        // Horní strana (y = +0.5)
        glColor3f(0.f, 1.f, 1.f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);

        // Spodní strana (y = -0.5)
        glColor3f(1.f, 0.f, 1.f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);

        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();

        angle += 0.5f; // rotace
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
