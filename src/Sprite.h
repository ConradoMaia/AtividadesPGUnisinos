#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "stb_image.h" // Inclua o header da stb_image para carregar texturas
#include "Shader.h"    // AGORA INCLUA O NOVO ARQUIVO DE CABEÇALHO DO SHADER AQUI

class Sprite
{
public:
    // Construtor
    Sprite(const std::string& texturePath, Shader* shader, float width = 1.0f, float height = 1.0f);
    // Destrutor
    ~Sprite();

    // Métodos para transformação
    void setPosition(const glm::vec2& position);
    void setScale(const glm::vec2& scale);
    void setRotation(float angle); // Em graus

    // Método para desenhar o sprite
    void draw();

private:
    GLuint VAO;
    GLuint textureID;
    Shader* spriteShader; // Ponteiro para o objeto shader
    glm::vec2 position;
    glm::vec2 scale;
    float rotation; // Em graus

    // Métodos privados para inicialização
    void setupMesh(float width, float height);
    GLuint loadTexture(const std::string& path);
};