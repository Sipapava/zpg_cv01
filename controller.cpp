#include "controller.h"
#include <stdio.h>
//Take care if we don't have a camera yet. make Conditions

Controller::Controller(Scene* scene) {
    this->rightMousePressed = false;
    this->scene = scene;
    lastX = 0;lastY = 0;
}
Controller::~Controller() {

}

bool Controller::setScene(Scene* scene) {
    this->scene = scene;
   
    if (this->scene) {
        return true;
    }
    return false;
    
}

void Controller::keyboardMovement(int key, int scancode, int action, int mods) {
   
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_W) {
            this->movementPressed[0] = true;
            
        }
        else if (key == GLFW_KEY_S) {
            this->movementPressed[1] = true;
        }
        else if (key == GLFW_KEY_D) {
            this->movementPressed[2] = true;
        }
        else if (key == GLFW_KEY_A) {
            this->movementPressed[3] = true;
        }
        else if (key == GLFW_KEY_F) {
            scene->getCamera()->setAttachedReflectors();
        }
    }
    else if (action == GLFW_RELEASE) {
       
        for (int i = 0; i < 4; i++) {
            this->movementPressed[i] = false;
           
        }
    }
}
static bool firstMouse = true;

void Controller::mouseMovement(double xpos, double ypos) {
    

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
        return;
    }

    if (rightMousePressed) {
        double dx = xpos - lastX;
        double dy = ypos - lastY;  
        
        scene->getCamera()->adjustTarget(dx, dy);
    }

    lastX = xpos;
    lastY = ypos;
}

void Controller::mousePress(int button, int action, int mods,double xM, double yM) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            rightMousePressed = true;
            
        }
        else if (action == GLFW_RELEASE) {
            rightMousePressed = false;
           
        }
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
           // printf("Clicked on depth\n");
            GLbyte color[4];
            GLfloat depth;
            GLuint index;

            GLint x = (GLint)xM;
            GLint y = (GLint)yM;

            int newy = (scene->getCamera()->GetResolutionY()) - y;

           glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
           glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
           glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

            //printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth%f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
            
            bool ret = this->scene->DeleteObject(index);
            if (!ret && index != 0) {
                
                if(depth > 0.977f){
                    depth = 0.977f;
                 }
                
                GLint viewport[4];
                glGetIntegerv(GL_VIEWPORT, viewport);

                glm::vec3 winPos(x, newy, depth);
                glm::vec3 worldPos = glm::unProject(
                    winPos,
                    scene->getCamera()->getViewMatrix(),
                    scene->getCamera()->getProjectionMatrix(),
                    glm::vec4(viewport[0], viewport[1], viewport[2], viewport[3])
                );

               
                scene->BuildObject(worldPos.x, worldPos.y, worldPos.z);
                
            }
           
            
        }
        
    }
}

void Controller::Update() {
    
    for (int i = 0; i < 4; i++) {
        switch (i) {
        case 0:
            if (this->movementPressed[0]) scene->getCamera()->moveForward();
            break;
        case 1:
            if (this->movementPressed[1]) scene->getCamera()->moveBackward();
            break;
        case 2:
            if(this->movementPressed[2]) scene->getCamera()->moveRight();
            break;
        case 3:
            if (this->movementPressed[3]) scene->getCamera()->moveLeft();
            break;
        }
    }
};