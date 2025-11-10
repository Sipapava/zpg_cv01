#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>



Texture::Texture(const std::string& filename, const std::string& typeName)
    : type(typeName)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);

    if (!data) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        id = 0;
        return;
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    GLenum format;
    if (channels == 1)      format = GL_RED;
    else if (channels == 3) format = GL_RGB;
    else if (channels == 4) format = GL_RGBA;
    else                    format = GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
}

Texture::Texture(const std::vector<std::string>& faces, const std::string& typeName)
    : type(typeName)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(false); 

    for (GLuint i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);
        if (data)
        {
            GLenum format = GL_RGB;
            if (channels == 1)      format = GL_RED;
            else if (channels == 3) format = GL_RGB;
            else if (channels == 4) format = GL_RGBA;

            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cerr << "Failed to load cubemap texture: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

Texture::~Texture() {
    if (id != 0) {
        glDeleteTextures(1, &id);  
        id = 0;                  
    }
}

bool Texture::BindTexture() {
    if (this->id == 0)
        return false;

    if ( type == "skybox") {
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->id);
    }
    else {
        glBindTexture(GL_TEXTURE_2D, this->id);
    }

    return true;
}

//change
bool Texture::ActiveTexture(){
    //if type diffuse 0
    glActiveTexture(GL_TEXTURE0);
    //if type.....
    //gl active 1...
    return true;
}



int Texture::GetSlot() {
    /*
    if (type == "texture_diffuse") return 0;
    if (type == "texture_specular") return 1;
    if (type == "texture_normal") return 2;
    if (type == "texture_ambient") return 3;
    */
    return 0; // default
}

std::string& Texture::GetType() {
    return type;
}

Texture::Texture()
{
    this->type = "texture_test";
    int width = 1; int height = 1;
    
    unsigned char* data = new unsigned char[width * height * 4];
    for (int i = 0; i < width * height * 4; i += 4) {
        data[i + 0] = 0;   // R
        data[i + 1] = 0;   // G
        data[i + 2] = 0;   // B
        data[i + 3] = 0;   // A 
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    GLenum format = GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format,
        width, height, 0,
        format, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    delete[] data;
}