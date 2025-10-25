#include "ShaderProgram.h"
#include <cstdio>

ShaderProgram::ShaderProgram(Shader* vertex,Shader* fragment) //musi dostat fragment a vertex
    : vertexShader(vertex), fragmentShader(fragment), shaderProgram(0)
{
    updatedCamera = false;
    updatedLight = false;
    view  = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);
    cameraPos = glm::vec3(0.0f, 0.5f, -2.0f);

    // Shadery vytvarime venku

   

    
    shaderProgram = glCreateProgram();
    vertexShader->attachShader(shaderProgram);
    fragmentShader->attachShader(shaderProgram);
    glLinkProgram(shaderProgram);

    
    GLint status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Shader Program linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
        //pridat return na false;
    }
}

ShaderProgram::~ShaderProgram() {
    delete vertexShader;
    delete fragmentShader;
}

bool ShaderProgram::setShaderProgram() { 
    if (shaderProgram != 0) {
       
            glUseProgram(shaderProgram);
            
        return true;
    }
    return false;
}

bool ShaderProgram::setUniform(const glm::mat4& matrix) {
    GLint id = glGetUniformLocation(shaderProgram, "modelMatrix"); 
    if (id >= 0) { 
        glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(matrix));
        return true;
    }
    return false;
}

bool ShaderProgram::setUniform(const glm::mat4& matrix, const char* spMatrix) {
    GLint id = glGetUniformLocation(shaderProgram, spMatrix); 
    if (id >= 0) { 
        glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(matrix));
        return true;
    }
    return false;
}


bool ShaderProgram::setUniform3(const glm::vec3& cameraPos) {
    GLint id = glGetUniformLocation(shaderProgram, "cameraPos");
    if (id >= 0) {
        glUniform3fv(id, 1, glm::value_ptr(cameraPos));
       
        return true;
    }
    return false;
}

bool ShaderProgram::setUniform3(const glm::vec3& vector, const char* spVector) {
    GLint id = glGetUniformLocation(shaderProgram, spVector);
    if (id >= 0) {
        glUniform3fv(id, 1, glm::value_ptr(vector)); 
      
        return true;
    }
    return false;
}


bool ShaderProgram::setUniform4(const glm::vec4& vector, const char* spVector) {
    GLint id = glGetUniformLocation(shaderProgram, spVector);
    if (id >= 0) {
        glUniform4fv(id, 1, glm::value_ptr(vector));
        
        return true;
    }
    return false;
}

bool ShaderProgram::setUniformFloat(float value, const char* name) {
    GLint id = glGetUniformLocation(shaderProgram, name);
    if (id >= 0) {
        glUniform1f(id, value);
       
        return true;
    }
    return false;
}
bool ShaderProgram::setUniformInt(int value, const char* name) {
    GLint id = glGetUniformLocation(shaderProgram, name);
    if (id >= 0) {
        glUniform1i(id, value);  // <-- pro int
        return true;
    }
    return false;
}


void ShaderProgram::Notify(NotifyType type, void* data) {
    switch (type) {
    case NotifyType::CameraMatrix: {
        CameraData* cam = static_cast<CameraData*>(data);
        this->view = cam->view;
        this->projection = cam->projection;
        updatedCamera = false;
        break;
    }
    case NotifyType::CameraPos: {
        glm::vec3* camPos = static_cast<glm::vec3*>(data);
        this->cameraPos = *camPos;
        updatedCamera = false;
        break;
    }
    case NotifyType::LightChange: {
        LightData* light = static_cast<LightData*>(data);
        int id = light->id; // pøedpokládáme, že LightData obsahuje id svìtla
        if (lightIdToIndex.find(id) != lightIdToIndex.end()) {
            int index = lightIdToIndex[id];
            lightsSlots[index].data = *light;
            lightsSlots[index].updated = false;
        }
        break;
    }
    case NotifyType::SpRegisterLight: {
        Light* light = static_cast<Light*>(data);
        int id = light->GetId();

        if (nextFreeLightIndex < 5) {
            lightIdToIndex[id] = nextFreeLightIndex;

            ShaderLightSlot slot;
            slot.data = light->getLightData(); // metoda, která vrací LightData
            slot.updated = false;

            lightsSlots.push_back(slot);
            ++nextFreeLightIndex;
        }
        break;
    }

    case NotifyType::SpUnfollowLight: {
        Light* light = static_cast<Light*>(data);
        int id = light->GetId();

        auto it = lightIdToIndex.find(id);
        if (it != lightIdToIndex.end()) {
            int index = it->second;

            lightsSlots[index].updated = false;
            lightsSlots[index].data = LightData(); // vynulujeme, toto dfachat nebude

            lightIdToIndex.erase(it);
        }
        break;
    }
    default:
        break;
    }
}







#include <iostream> // nezapomeò pøidat

void ShaderProgram::LightApply() {
    bool anyUp = false;
    for (size_t i = 0; i < lightsSlots.size(); ++i) {
        ShaderLightSlot& slot = lightsSlots[i];

        if (!slot.updated) {
            int id = slot.data.id;

            // najdeme index v poli uniformù podle id
            auto it = lightIdToIndex.find(id);
            if (it == lightIdToIndex.end()) {
                std::cout << "[LightApply] Light ID " << id << " not found in map!\n";
                continue; // bezpeènost
            }

            int indexInShader = it->second;

            // debug print
            std::cout << "[LightApply] Updating Light ID: " << id
                << " at shader index: " << indexInShader << "\n";
            std::cout << "    Position: (" << slot.data.position.x << ", "
                << slot.data.position.y << ", " << slot.data.position.z << ")\n";
            std::cout << "    Color: (" << slot.data.color.r << ", "
                << slot.data.color.g << ", " << slot.data.color.b << ", "
                << slot.data.color.a << ")\n";
            std::cout << "    Intensity: " << slot.data.intensity
                << ", Shininess: " << slot.data.shininess << "\n";

            // pøipravíme názvy uniformù s indexem
            std::string posName = "lights[" + std::to_string(indexInShader) + "].lightPosition";
            std::string diffuseName = "lights[" + std::to_string(indexInShader) + "].lightColor";
            std::string specularName = "lights[" + std::to_string(indexInShader) + "].specularIntensity";
            std::string shininessName = "lights[" + std::to_string(indexInShader) + "].shiness";

            // aplikujeme hodnoty z lightsSlots
            setUniform3(slot.data.position, posName.c_str());
            setUniform4(slot.data.color, diffuseName.c_str());
            setUniformFloat(slot.data.intensity, specularName.c_str());
            setUniformFloat(slot.data.shininess, shininessName.c_str());

            // nastavíme updated = true
            slot.updated = true;
            anyUp = true;
        }
    }

    if (anyUp) {
        setUniformInt(static_cast<int>(lightsSlots.size()), "numberOfLights");
        std::cout << "[LightApply] numberOfLights updated to: " << lightsSlots.size() << "\n";
    }
}




void ShaderProgram::ProjectionApply() {

    if (!updatedCamera) {
        
        this->setUniform3(cameraPos);
       
        this->setUniform(view,"viewMatrix");
        this->setUniform(projection,"projectMatrix");
        updatedCamera = true;
    }
}
