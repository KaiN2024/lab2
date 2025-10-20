#define GLEW_DLL
#define GLF_DLL

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "Shader.h" // библиотека для работы с шейдерами

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: Failed to initialize GLFW\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Создание окна
    GLFWwindow* window = glfwCreateWindow(512, 512, "Main", NULL, NULL);
    if (!window) {
        fprintf(stderr, "ERROR: Failed to create window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum ret = glewInit();
    if (GLEW_OK != ret) {
        fprintf(stderr, "ERROR: GLEW %s\n", glewGetErrorString(ret));
        return 1;
    }

    // Вершины прямоугольника
    float vertices[] = {
        // позиции         
        -0.5f, -0.3f, 0.0f,  1.0f, 0.0f, 0.0f, // левый нижний
         0.5f, -0.3f, 0.0f,  0.0f, 1.0f, 0.0f, // правый нижний
         0.5f,  0.3f, 0.0f,  0.0f, 0.0f, 1.0f, // правый верхний
        -0.5f,  0.3f, 0.0f,  1.0f, 1.0f, 0.0f  // левый верхний
    };

    // Индексы для EBO
    unsigned int indices[] = {
        0, 1, 2,  // первый треугольник
        2, 3, 0   // второй треугольник
    };

    // Создание VAO, VBO, EBO
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Настройка VAO
    glBindVertexArray(VAO);

    // Настройка VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Настройка EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Атрибут позиций (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Атрибут цветов (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Загрузка шейдеров
    Shader ourShader("vertex.shader", "fragment.shader");

    // Главный цикл
    while (!glfwWindowShouldClose(window)) {
        // Очистка экрана
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Использование шейдерной программы
        ourShader.use();

        // Передача времени в шейдер для анимации цвета
        float timeValue = glfwGetTime();
        ourShader.setFloat("time", timeValue);

        // Рисуем прямоугольник
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Очистка
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}