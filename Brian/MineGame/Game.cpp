#include "Game.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"
#include "Chunk.h"

bool m_Keys[1000];
void HandleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
        m_Keys[key] = true;
    else if (action == GLFW_RELEASE)
        m_Keys[key] = false;
}

Game::Game()
    : m_Width(640)
    , m_Height(480)
    , m_Camera(m_Width, m_Height, 90.f, 0.01f, 1000.0f)
{}

Game::~Game()
{
}

int Game::Init()
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(m_Width, m_Height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, HandleKeyInput);

    if (glewInit() != GLEW_OK)
        std::cout << "Glew init was not equal to GLEW_OK" << std::endl;

    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CW);

    glClearColor(0.3f, 0.2f, 0.8f, 1.f);

    m_Shader = Shader::CreateShader("shaders/shader");
    m_Shader->AddUniformLocation("model");
    m_Shader->AddUniformLocation("view");
    m_Shader->AddUniformLocation("projection");

    m_Chunk = new Chunk(m_Shader);
    m_Camera.GetTransform().GetPosition().z = 3.f;
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        Update();
    }

    Shader::ClearShaders();
    glfwTerminate();

    return 0;
}

void Game::HandleInput()
{
    float speed = 0.01f;
    glm::vec3 Direction(0.);
    if (m_Keys[GLFW_KEY_W])
    {
        Direction.z -= 1.;
    }
    if (m_Keys[GLFW_KEY_S])
    {
        Direction.z += 1.;
    }
    if (m_Keys[GLFW_KEY_A])
    {
        Direction.x -= 1.;
    }
    if (m_Keys[GLFW_KEY_D])
    {
        Direction.x += 1.;
    }
    if (m_Keys[GLFW_KEY_LEFT_SHIFT])
    {
        Direction.y -= 1.;
    }
    if (m_Keys[GLFW_KEY_SPACE])
    {
        Direction.y += 1.;
    }

    if (Direction.x != 0 || Direction.y != 0 || Direction.z != 0)
    {
        Direction = normalize(Direction) * speed;
        m_Camera.GetTransform().GetPosition() += Direction;
    }
}

void Game::Update()
{
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);
    
    HandleInput();

    glUseProgram(m_Shader->GetShaderProgram());

    glm::mat4 view = m_Camera.GetViewMatrix();
    glm::mat4 projection = m_Camera.GetProjectionMatrix();

    m_Shader->SetUniform("view", view);
    m_Shader->SetUniform("projection", projection);

    m_Chunk->Render();

    glfwSwapBuffers(window);
    glfwPollEvents();
}