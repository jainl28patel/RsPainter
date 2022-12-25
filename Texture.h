//
// Created by Jainil Patel on 23/12/22.
//

#ifndef RASPAINTER_TEXTURE_H
#define RASPAINTER_TEXTURE_H

class Texture {
private :
    unsigned int texture1;
public:
    Texture(const std::string& path, GLenum format) {
        stbi_set_flip_vertically_on_load(1);
    // ---------- TEXTURE 1 ----------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    // Wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Filtering Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int height, width, nrChannels;
    unsigned char* data = stbi_load(std::filesystem::path(path).c_str(), &width, &height, &nrChannels, 0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    }

    ~Texture() {
        glDeleteTextures(1, &texture1);
    }

    void bind(unsigned int slot) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, texture1);
    }

    void unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
};

#endif //RASPAINTER_TEXTURE_H
