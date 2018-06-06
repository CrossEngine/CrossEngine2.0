/**************************************************************
 * Program Title: Hello World
 * Filename: HelloWorld.cpp
 * Author: Blake Rogan
 * Last modified: 27/05/2018
 * Description:
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include "HelloWorld.hpp"

CE_IMPLEMENT_APPLICATION(HelloWorld);

void HelloWorld::OnStartup() {
    log->info("Hello World");
    mainEventBus->Subscribe<ExampleEvent>(0, this);
    mainEventBus->Subscribe<ExampleEvent2>(0, this);
    mainEventBus->Subscribe<CrossEngine::Window::Events::MousePosEvent>(0, this);
    mainEventBus->Subscribe<CrossEngine::Window::Events::KeyEvent>(0, this);
    mainEventBus->Publish<ExampleEvent>(10);
    mainEventBus->Publish<ExampleEvent2>();
    window = windowManager->NewWindow<CrossEngine::Render::OpenGLRenderer>("Render Window", 800, 450);

    log->info("Building Shaders");

    auto vertex = window->LoadShaderSource(
            "vertex",
            {
                    "#version 330\n"
                    "layout(location=0) in vec3 vertex;\n"
                    "uniform mat4 mvp;\n"
                    "void main() {\n"
                    "    gl_Position = mvp * vec4(vertex, 1);\n"
                    "}"
            },
            GL_VERTEX_SHADER
    );
    CrossEngine::Util::CharVector fragmentSource;
    fragmentSource.push_back(
            (char *) "#version 330\n"
                     "out vec4 colour;\n"
    );
    fragmentSource.push_back(
            (char *) "void setColour() {\n"
                     "}"
    );
    fragmentSource.push_back(
            (char*) "void main() {\n"
                    "    colour = vec4(1, 0, 1, 1);\n"
                    "}"
    );

    auto fragment = window->LoadShaderSource(
            "fragment",
            fragmentSource,
            GL_FRAGMENT_SHADER
    );

    auto program = window->LoadShaderProgram("main", {vertex, fragment});

    auto object = window->CreateRenderObject();

    float x_offset = 5.0f;

    auto mesh1 = new CrossEngine::Render::Mesh{CrossEngine::Render::Mesh_Triangles};
    {
        mesh1->AddVertex(-1.0f + x_offset, -1.0f, 1.0f);
        mesh1->AddVertex(1.0f + x_offset, -1.0f, 1.0f);
        mesh1->AddVertex(1.0f + x_offset, 1.0f, 1.0f);
        mesh1->AddVertex(-1.0f + x_offset, 1.0f, 1.0f);

        mesh1->AddVertex(1.0f + x_offset, 1.0f, 1.0f);
        mesh1->AddVertex(1.0f + x_offset, 1.0f, -1.0f);
        mesh1->AddVertex(1.0f + x_offset, -1.0f, -1.0f);
        mesh1->AddVertex(1.0f + x_offset, -1.0f, 1.0f);

        mesh1->AddVertex(-1.0f + x_offset, -1.0f, -1.0f);
        mesh1->AddVertex(1.0f + x_offset, -1.0f, -1.0f);
        mesh1->AddVertex(1.0f + x_offset, 1.0f, -1.0f);
        mesh1->AddVertex(-1.0f + x_offset, 1.0f, -1.0f);

        mesh1->AddVertex(-1.0f + x_offset, -1.0f, -1.0f);
        mesh1->AddVertex(-1.0f + x_offset, -1.0f, 1.0f);
        mesh1->AddVertex(-1.0f + x_offset, 1.0f, 1.0f);
        mesh1->AddVertex(-1.0f + x_offset, 1.0f, -1.0f);

        mesh1->AddVertex(1.0f + x_offset, 1.0f, 1.0f);
        mesh1->AddVertex(-1.0f + x_offset, 1.0f, 1.0f);
        mesh1->AddVertex(-1.0f + x_offset, 1.0f, -1.0f);
        mesh1->AddVertex(1.0f + x_offset, 1.0f, -1.0f);

        mesh1->AddVertex(-1.0f + x_offset, -1.0f, -1.0f);
        mesh1->AddVertex(1.0f + x_offset, -1.0f, -1.0f);
        mesh1->AddVertex(1.0f + x_offset, -1.0f, 1.0f);
        mesh1->AddVertex(-1.0f + x_offset, -1.0f, 1.0f);

        mesh1->AddTriangle(0, 1, 2);
        mesh1->AddTriangle(0, 2, 3);

        mesh1->AddTriangle(4, 5, 6);
        mesh1->AddTriangle(4, 6, 7);

        mesh1->AddTriangle(8, 9, 10);
        mesh1->AddTriangle(8, 10, 11);

        mesh1->AddTriangle(12, 13, 14);
        mesh1->AddTriangle(12, 14, 15);

        mesh1->AddTriangle(16, 17, 18);
        mesh1->AddTriangle(16, 18, 19);

        mesh1->AddTriangle(20, 21, 22);
        mesh1->AddTriangle(20, 22, 23);
    }
    object->AddMesh(mesh1);

    auto mesh2 = new CrossEngine::Render::Mesh{CrossEngine::Render::Mesh_Triangles};
    {
        mesh2->AddVertex(-1.0f - x_offset, -1.0f, 1.0f);
        mesh2->AddVertex(1.0f - x_offset, -1.0f, 1.0f);
        mesh2->AddVertex(1.0f - x_offset, 1.0f, 1.0f);
        mesh2->AddVertex(-1.0f - x_offset, 1.0f, 1.0f);

        mesh2->AddVertex(1.0f - x_offset, 1.0f, 1.0f);
        mesh2->AddVertex(1.0f - x_offset, 1.0f, -1.0f);
        mesh2->AddVertex(1.0f - x_offset, -1.0f, -1.0f);
        mesh2->AddVertex(1.0f - x_offset, -1.0f, 1.0f);

        mesh2->AddVertex(-1.0f - x_offset, -1.0f, -1.0f);
        mesh2->AddVertex(1.0f - x_offset, -1.0f, -1.0f);
        mesh2->AddVertex(1.0f - x_offset, 1.0f, -1.0f);
        mesh2->AddVertex(-1.0f - x_offset, 1.0f, -1.0f);

        mesh2->AddVertex(-1.0f - x_offset, -1.0f, -1.0f);
        mesh2->AddVertex(-1.0f - x_offset, -1.0f, 1.0f);
        mesh2->AddVertex(-1.0f - x_offset, 1.0f, 1.0f);
        mesh2->AddVertex(-1.0f - x_offset, 1.0f, -1.0f);

        mesh2->AddVertex(1.0f - x_offset, 1.0f, 1.0f);
        mesh2->AddVertex(-1.0f - x_offset, 1.0f, 1.0f);
        mesh2->AddVertex(-1.0f - x_offset, 1.0f, -1.0f);
        mesh2->AddVertex(1.0f - x_offset, 1.0f, -1.0f);

        mesh2->AddVertex(-1.0f - x_offset, -1.0f, -1.0f);
        mesh2->AddVertex(1.0f - x_offset, -1.0f, -1.0f);
        mesh2->AddVertex(1.0f - x_offset, -1.0f, 1.0f);
        mesh2->AddVertex(-1.0f - x_offset, -1.0f, 1.0f);

        mesh2->AddTriangle(0, 1, 2);
        mesh2->AddTriangle(0, 2, 3);

        mesh2->AddTriangle(4, 5, 6);
        mesh2->AddTriangle(4, 6, 7);

        mesh2->AddTriangle(8, 9, 10);
        mesh2->AddTriangle(8, 10, 11);

        mesh2->AddTriangle(12, 13, 14);
        mesh2->AddTriangle(12, 14, 15);

        mesh2->AddTriangle(16, 17, 18);
        mesh2->AddTriangle(16, 18, 19);

        mesh2->AddTriangle(20, 21, 22);
        mesh2->AddTriangle(20, 22, 23);
    }
    object->AddMesh(mesh2);

    auto compiled = window->CompileRenderObject(&object);

    log->info("Shaders have been built");

    CrossEngine::Util::Math::Matrix4 model = CrossEngine::Util::Math::Matrix4(1.f);
    projection = glm::perspective(
            glm::radians(45.0f),
            800.f / 425.f,
            0.1f,
            100.f
    );

    angle = CrossEngine::Util::Math::Vector2(
            glm::radians(0.f),
            glm::radians(0.f)
    );

    angle = CrossEngine::Util::Math::Vector2(
            400, 225
    );

    cameraPosition = CrossEngine::Util::Math::Vector3(10, 0, 0);
    cameraUp = CrossEngine::Util::Math::Vector3(0, 1, 0);
    up = CrossEngine::Util::Math::Vector3(0, 1, 0);

    cameraFront = glm::normalize(
            CrossEngine::Util::Math::Vector3(
                    std::cos(glm::radians(angle.y)) * std::cos(glm::radians(angle.x)),
                    std::sin(glm::radians(angle.y)),
                    std::cos(glm::radians(angle.y)) * std::sin(glm::radians(angle.x))
            )
    );

    window->GetRenderer<CrossEngine::Render::OpenGLRenderer>()->AddRenderFunction(
            [this, program, compiled, model](CrossEngine::Window::Window *window1, CrossEngine::Util::DeltaTime delta) {

                view = glm::lookAt(
                        cameraPosition,
                        cameraPosition + cameraFront,
                        cameraUp
                );

                auto mvp = projection * view * model;

                glClear(GL_COLOR_BUFFER_BIT);
                glClearColor(1, 0, 0, 1);
                glViewport(0, 0, 800, 600);
                auto old = program->Bind();
                program->Matrix4("mvp", mvp);

                compiled->Render();

                program->Unbind(old);

            });

    window->GetRenderer<CrossEngine::Render::OpenGLRenderer>()->AddRenderFunction(
            [this](CrossEngine::Window::Window *window1, CrossEngine::Util::DeltaTime delta) {
                glFlush();
            });

    window->SetPaused(false);

//    window->CreateShader();

    Application::OnStartup();
}

void HelloWorld::OnShutdown() {
    log->info("Shutdown");
    window = nullptr;
    Application::OnShutdown();
}

void HelloWorld::HandleEvent(const CrossEngine::Util::Memory::Shared<ExampleEvent> &event) {
    log->info("Hello World");
}

void HelloWorld::HandleEvent(const CrossEngine::Util::Memory::Shared<ExampleEvent2> &event) {
    log->info("Hello World 2");
}

void
HelloWorld::HandleEvent(const CrossEngine::Util::Memory::Shared<CrossEngine::Window::Events::MousePosEvent> &event) {
//    log->info("On Mouse Move: {}x{}", event->GetX(), event->GetY());

    float sensitivity = 0.05f;

    if (firstMove) {
        old = CrossEngine::Util::Math::Vector2(
                event->GetX(),
                event->GetY()
        );
        firstMove = false;
    }

    auto offsetX = static_cast<float>((event->GetX() - old.x) * sensitivity);
    auto offsetY = static_cast<float>((old.y - event->GetY()) * sensitivity);

    old = CrossEngine::Util::Math::Vector2(
            event->GetX(),
            event->GetY()
    );

    angle += CrossEngine::Util::Math::Vector2(
            offsetX,
            offsetY
    );

    if (angle.y > 89.f) {
        angle.y = 89.f;
    }
    if (angle.y < -89.f) {
        angle.y = -89.f;
    }
    log->info("On Mouse Move: {}x{}", angle.x, angle.y);

    cameraFront = glm::normalize(
            CrossEngine::Util::Math::Vector3(
                    std::cos(glm::radians(angle.y)) * std::cos(glm::radians(angle.x)),
                    std::sin(glm::radians(angle.y)),
                    std::cos(glm::radians(angle.y)) * std::sin(glm::radians(angle.x))
            )
    );
}

void HelloWorld::HandleEvent(const CrossEngine::Util::Memory::Shared<CrossEngine::Window::Events::KeyEvent> &event) {
    auto scan = glfwGetKeyName(event->GetKey(), event->GetScan());
    log->info(
            "On Key Press: {} {} {} {} {}",
            event->GetKey(), event->GetScan(), event->GetAction(),
            event->GetMods(), scan ? scan : ""

    );
    if (event->GetAction() == GLFW_PRESS || event->GetAction() == GLFW_REPEAT) {
        float speed = 0.05f;

        if (event->GetKey() == GLFW_KEY_W) {
            cameraPosition += speed * cameraFront;
        }
        if (event->GetKey() == GLFW_KEY_S) {
            cameraPosition -= speed * cameraFront;
        }
        if (event->GetKey() == GLFW_KEY_A) {
            cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
        }
        if (event->GetKey() == GLFW_KEY_D) {
            cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
        }
    }
}

ExampleEvent::ExampleEvent(int value) {
    aValue = value;
}

int ExampleEvent::GetValue() const {
    return aValue;
}
