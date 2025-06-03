#include "Sprite.h"

// Define STB_IMAGE_IMPLEMENTATION para que a implementação seja incluída
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" // Inclua aqui novamente para a implementação

Sprite::Sprite(const std::string& texturePath, Shader* shader, float width, float height)
    : spriteShader(shader), position(0.0f, 0.0f), scale(width, height), rotation(0.0f)
{
    setupMesh(width, height);
    textureID = loadTexture(texturePath);
}

Sprite::~Sprite()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteTextures(1, &textureID);
    // Não delete o shader aqui, pois ele pode ser compartilhado por outros sprites
}

void Sprite::setPosition(const glm::vec2& position)
{
    this->position = position;
}

void Sprite::setScale(const glm::vec2& scale)
{
    this->scale = scale;
}

void Sprite::setRotation(float angle)
{
    this->rotation = angle;
}

void Sprite::draw()
{
    spriteShader->use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * scale.x, 0.5f * scale.y, 0.0f)); // Move o ponto de rotação para o centro
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, 0.0f)); // Move de volta
    model = glm::scale(model, glm::vec3(scale, 1.0f));

    spriteShader->setMat4("model", model);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Sprite::setupMesh(float width, float height)
{
    // O exercício pede um quadrilátero 1x1 centrado na origem
    // Com as coordenadas de textura mapeadas corretamente.
    // Ajustaremos a escala no shader.
    float vertices[] = {
        // Posições        // Coordenadas de Textura
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, // Top-left
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // Top-right
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // Bottom-right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f  // Bottom-left
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    GLuint VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Atributo de posição
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Atributo de coordenada de textura
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

GLuint Sprite::loadTexture(const std::string& path)
{
    GLuint textureID_local;
    glGenTextures(1, &textureID_local);
    glBindTexture(GL_TEXTURE_2D, textureID_local);

    // Configurações de wrapping e filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture at path: " << path << std::endl;
    }
    stbi_image_free(data);
    return textureID_local;
}