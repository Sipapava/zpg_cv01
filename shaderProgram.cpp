#include "ShaderProgram.h"
#include "Light.h" 
#include <cstdio>

ShaderProgram::ShaderProgram(Shader* vertex,Shader* fragment) 
    : vertexShader(vertex), fragmentShader(fragment), shaderProgram(0)
{
    updatedCamera = false;
    updatedLight = false;
    

    view = nullptr;
    projection = nullptr;
    cameraPos = glm::vec3(0.0f, 0.5f, -2.0f);


   

    
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
        //add return  false;
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

bool ShaderProgram::resetShaderProgram() {
    if (shaderProgram != 0) {

        glUseProgram(0);

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
        glUniform1i(id, value); 
        return true;
    }
    return false;
}


void ShaderProgram::Notify(NotifyType type, void* data) {
    switch (type) {
    case NotifyType::CameraMatrix: {
        CameraData* camData = static_cast<CameraData*>(data);

        
        view = &camData->view;
        projection = &camData->projection;

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
        int id = light->id; 
        if (lightIdToIndex.find(id) != lightIdToIndex.end()) {
            int index = lightIdToIndex[id];
            lightsSlots[index].data = *light;
            lightsSlots[index].updated = false;
        }
        break;
    }
    case NotifyType::SpRegisterLight: {
        Light* light = static_cast<Light*>(data);
        int id = light->getId();

        if (nextFreeLightIndex < 5) {
            lightIdToIndex[id] = nextFreeLightIndex;

            ShaderLightSlot slot;
            slot.data = light->getLightData(); 
            slot.updated = false;

            lightsSlots.push_back(slot);
            ++nextFreeLightIndex;
        }
        break;
    }

    case NotifyType::SpUnfollowLight: {
        Light* light = static_cast<Light*>(data);
        int id = light->getId();

        auto it = lightIdToIndex.find(id);
        if (it != lightIdToIndex.end()) {
            int index = it->second;

            lightsSlots[index].updated = false;
            lightsSlots[index].data = LightData(); 

            lightIdToIndex.erase(it);
        }
        break;
    }
   
    default:
        break;
    }
}









void ShaderProgram::LightApply() {
    bool anyUp = false;
    for (size_t i = 0; i < lightsSlots.size(); ++i) {
        ShaderLightSlot& slot = lightsSlots[i];

        if (!slot.updated) {
            int id = slot.data.id;

            auto it = lightIdToIndex.find(id);
            if (it == lightIdToIndex.end()) {
              
                continue; 
            }

            int indexInShader = it->second;


            std::string typeName = "lights[" + std::to_string(indexInShader) + "].type";
            std::string posName = "lights[" + std::to_string(indexInShader) + "].lightPosition";
            std::string colorSpecName = "lights[" + std::to_string(indexInShader) + "].lightColor";
            std::string specularName = "lights[" + std::to_string(indexInShader) + "].specularIntensity";
            std::string shininessName = "lights[" + std::to_string(indexInShader) + "].shiness";
            std::string diffuseColorName = "lights[" + std::to_string(indexInShader) + "].diffuseColor";
            std::string attenuationName = "lights[" + std::to_string(indexInShader) + "].attenuation";
            std::string ambientName = "lights[" + std::to_string(indexInShader) + "].ambientColor";
            std::string directionName = "lights[" + std::to_string(indexInShader) + "].direction";
            std::string angleRName = "lights[" + std::to_string(indexInShader) + "].angleReflector";
            

            
            setUniform3(slot.data.position, posName.c_str());
            setUniform4(slot.data.colorSpecular, colorSpecName.c_str());
            setUniformFloat(slot.data.intensity, specularName.c_str());
            setUniformFloat(slot.data.shininess, shininessName.c_str());
            setUniform4(slot.data.diffuseColor, diffuseColorName.c_str());
            setUniformFloat(slot.data.attenuation, attenuationName.c_str());
            setUniform4(slot.data.ambientColor, ambientName.c_str());
            
            setUniformInt(slot.data.type, typeName.c_str());
            setUniform3(slot.data.direction, directionName.c_str());
            setUniformFloat(slot.data.angleReflector, angleRName.c_str());


          
            slot.updated = true;
            anyUp = true;
        }
    }

    if (anyUp) {
        setUniformInt(static_cast<int>(lightsSlots.size()), "numberOfLights");
       
    }
}




void ShaderProgram::ProjectionApply() {

    if (!updatedCamera) {
        
        this->setUniform3(cameraPos);
       
        this->setUniform(*view,"viewMatrix");
        this->setUniform(*projection, "projectMatrix");
        updatedCamera = true;
    }
}

void ShaderProgram::ProjectionApplySky() {

    if (!updatedCamera) {

        this->setUniform3(cameraPos);

        glm::mat4 viewNoTranslation = glm::mat4(glm::mat3(*view)); 
        this->setUniform(viewNoTranslation, "viewMatrix");
        this->setUniform(*projection, "projectMatrix");
        updatedCamera = true;
    }
}
