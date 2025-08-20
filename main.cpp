#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;
const GLint WIDTH = 800, HEIGHT = 600;
GLuint VBO, VAO, shaderProgram;

static const char* vertexShader = "                             \n\
#version 330                                                    \n\
                                                                \n\
layout (location = 0) in vec2 pos;                              \n\
void main() {                                                   \n\
    gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);                 \n\
}                                                               \n\
";

static const char* fragmentShader = "                           \n\
#version 330                                                    \n\
                                                                \n\
uniform in vec3 triColor;                                       \n\
                                                                \n\
                                                                \n\
void main() {                                                   \n\
		color = vec3(tricolor, 1.0);                            \n\
}                                                               \n\
";

void  criaTriangulo() {
    GLfloat vertices[] = {
        0.0f, 1.0f,   // V�rtice 1
        -1.0f, -1.0f, // V�rtice 2
        1.0f, -1.0f   // V�rtice 3

    };

	// Cria o VAO e o VBO
    glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


};

// Fun��o de inicializa��o
void Inicializa() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glClearColor(0.75, 0.0, 0.80, 0.85);
}

// Fun��o de desenho
void Desenha() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.3, 0.0, 0.3);

    glBegin(GL_TRIANGLES);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(-1.0, -1.0, 0.0);
    glVertex3f(1.0, -1.0, 0.0);
    glEnd();

    glFlush();
}

int main() {
    // Inicializa o GLFW
    if (!glfwInit()) {
        std::cerr << "Falha ao inicializar o GLFW" << std::endl;
        return -1;
    }

    // Configura��es do contexto OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Vers�o maior do OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Vers�o menor do OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Perfil Core

    // Cria uma janela vis�vel
    GLFWwindow* window = glfwCreateWindow(800, 600, "eae rapazeada", nullptr, nullptr);
    if (!window) {
        std::cerr << "Falha ao criar a janela GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Torna o contexto OpenGL atual
    glfwMakeContextCurrent(window);

    // Inicializa o GLEW
    glewExperimental = GL_TRUE; // Garante suporte a extens�es modernas
    if (glewInit() != GLEW_OK) {
        std::cerr << "Falha ao inicializar o GLEW" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Exibe informa��es sobre a vers�o do OpenGL
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    // Inicializa o OpenGL
    Inicializa();

    // Loop principal
    while (!glfwWindowShouldClose(window)) {
        // Desenha a cena
        Desenha();

        // Troca os buffers
        glfwSwapBuffers(window);

        // Processa eventos
        glfwPollEvents();
    }

    // Finaliza o programa
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
