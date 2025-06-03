#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sprite.h" // Inclua sua classe Sprite
#include <iostream>
#include <vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Configurações
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // Inicialização do GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Criação da janela GLFW
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Sprites com Textura", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Inicialização do GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Configura o blending para transparência
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Compilação e ligação dos shaders
    Shader spriteShader("shaders/shader.vs", "shaders/shader.fs"); // Certifique-se de que os arquivos shader.vs e shader.fs estão na mesma pasta

    // Configura a matriz de projeção ortográfica
    // Mapeia as coordenadas de mundo para coordenadas de tela
    // (0,0) é o canto inferior esquerdo da tela
    glm::mat4 projection = glm::ortho(0.0f, (float)SCR_WIDTH, 0.0f, (float)SCR_HEIGHT, -1.0f, 1.0f);
    spriteShader.use();
    spriteShader.setMat4("projection", projection);

    // Criação de sprites
    std::vector<Sprite*> sprites;

    // Sprite 1
    Sprite* sprite1 = new Sprite("D:/Dev/Faculdade_pg/assets/textures/texture3.png", &spriteShader, 100.0f, 100.0f); // Largura e altura em pixels de tela
    sprite1->setPosition(glm::vec2(100.0f, 100.0f));
    sprite1->setRotation(45.0f);
    sprites.push_back(sprite1);

    // Sprite 2
    Sprite* sprite2 = new Sprite("D:/Dev/Faculdade_pg/assets/textures/texture2.png", &spriteShader, 150.0f, 150.0f);
    sprite2->setPosition(glm::vec2(400.0f, 300.0f));
    sprite2->setScale(glm::vec2(150.0f, 150.0f));
    sprites.push_back(sprite2);

    // Sprite 3
    Sprite* sprite3 = new Sprite("D:/Dev/Faculdade_pg/assets/textures/texture1.png", &spriteShader, 200.0f, 100.0f);
    sprite3->setPosition(glm::vec2(600.0f, 50.0f));
    sprite3->setRotation(-30.0f);
    sprites.push_back(sprite3);


    // Loop de renderização
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Desenha todos os sprites
        for (Sprite* s : sprites) {
            s->draw();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Limpeza
    for (Sprite* s : sprites) {
        delete s;
    }
    glfwTerminate();
    return 0;
}

// Processa todas as entradas do usuário
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Callback para redimensionamento da viewport quando a janela muda de tamanho
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}