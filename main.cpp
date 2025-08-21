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
        0.0f, 1.0f,   // Vértice 1
        -1.0f, -1.0f, // Vértice 2
        1.0f, -1.0f   // Vértice 3

    };

	// Cria o VAO e o VBO
    glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
     glGenBuffers(1, &VBO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     
	    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	    glEnableVertexAttribArray(0);
	  glBindBuffer(GL_ARRAY_BUFFER, 0);
	 glBindVertexArray(0);
};


void adicionaTriangulo(GLuint program, char* shaderCode, GLenum type) {
	GLuint shader = glCreateShader(type);
    

    //converte char para GL_char
	const GLchar* code[1];
	code[0] = shaderCode;

	glShaderSource(shader, 1, code, NULL);
	glCompileShader(shader);
    
    //tratar os erros de compilacao

	glAttachShader(program, shader);
    

};

// Função de inicialização
void Inicializa() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glClearColor(0.75, 0.0, 0.80, 0.85);
}

// Função de desenho
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

    // Configurações do contexto OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Versão maior do OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Versão menor do OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Perfil Core

    // Cria uma janela visível
    GLFWwindow* window = glfwCreateWindow(800, 600, "eae rapazeada", nullptr, nullptr);
    if (!window) {
        std::cerr << "Falha ao criar a janela GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Torna o contexto OpenGL atual
    glfwMakeContextCurrent(window);

    // Inicializa o GLEW
    glewExperimental = GL_TRUE; // Garante suporte a extensões modernas
    if (glewInit() != GLEW_OK) {
        std::cerr << "Falha ao inicializar o GLEW" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Exibe informações sobre a versão do OpenGL
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

