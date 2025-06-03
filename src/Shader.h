#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp> // Para glm::mat4
#include <glm/gtc/type_ptr.hpp> // Para glm::value_ptr

class Shader
{
public:
    unsigned int ID; // ID do programa shader

    // Construtor lê e constrói o shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // Usa/ativa o shader
    void use();
    // Funções utilitárias para uniformes
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const; // Adicionado para matrizes
};