/**************************************************************
 * Program Title: CrossEngine_BuildNumber
 * Filename: Window.hpp
 * Author: Blake Rogan
 * Last modified: 31/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_BUILDNUMBER_WINDOW_HPP
#define CROSSENGINE_BUILDNUMBER_WINDOW_HPP

#include <CrossEngine/config.h>
#include <CrossEngine/Util/Util.hpp>
#include <CrossEngine/Render/Shader.hpp>
#include <CrossEngine/Render/Renderer.hpp>
#include <CrossEngine/Logging/Logging.hpp>
#include <CrossEngine/EventBus/EventBus.hpp>
#include <CrossEngine/Render/RenderEvents.hpp>
#include <CrossEngine/Window/WindowEvents.hpp>

#define GLFW_INCLUDE_NONE 1

#include <GLFW/glfw3.h>

#include <thread>
#include <atomic>

namespace CrossEngine {
    namespace Window {

        enum RenderAPI {
            API_OpenGL,
            API_OpenGLES,
            API_Vulkan,
        };

        class Window {
        private:
            GLFWwindow *window;
            GLFWwindow *resourceContext;

            EventBus::EventBus::SharedEventBus windowBus;
            EventBus::EventBus::SharedEventBus renderBus;
            Render::SharedRenderer renderer;
            Render::ShaderSourceMap shaders;
            Render::ShaderProgramMap shaderPrograms;

            std::atomic_bool isRendering;
            std::atomic_bool paused;
            std::thread renderThread;


            Util::DeltaTime start = 0.0f;
            Util::DeltaTime now = 0.0f;
            Util::DeltaTime delta = 0.0f;

        public:
            CrossEngineAPI Window(
                    const Util::String &name,
                    int width,
                    int height,
                    RenderAPI api,
                    const EventBus::EventBus::SharedEventBus &eventBus,
                    const Render::SharedRenderer &renderer
            );

            CrossEngineAPI ~Window();

            CrossEngineAPI bool IsValid();

            CrossEngineAPI bool ShouldClose();

            CrossEngineAPI void Pulse();

            CrossEngineAPI void StartRenderLoop();

            CrossEngineAPI void StopRenderLoop();

            CrossEngineAPI bool IsPaused() const;

            CrossEngineAPI void SetPaused(bool paused);

            CrossEngineAPI GLFWwindow *GetWindow() const;

            CrossEngineAPI EventBus::EventBus::SharedEventBus GetWindowBus() const;

            CrossEngineAPI EventBus::EventBus::SharedEventBus GetRenderBus() const;

            template<class RendererType>
            CrossEngineAPI Util::Memory::Shared<RendererType> GetRenderer() const {
                return std::dynamic_pointer_cast<RendererType>(renderer);
            };

            CrossEngineAPI Render::SharedShaderSource
            LoadShaderSource(const Util::String &name, const Util::String &source, GLenum type);

            CrossEngineAPI Render::SharedShaderSource GetShaderSource(const Util::String &name);

            CrossEngineAPI Render::SharedShaderProgram
            LoadShaderProgram(const Util::String &name, const Render::ShaderSourceVector &sources);

            CrossEngineAPI Render::SharedShaderProgram GetShaderProgram(const Util::String &name);

        private:

            void PrivateRenderLoop();

        };

        typedef Util::Memory::Shared<Window> SharedWindow;
        typedef Util::Containers::Vector<SharedWindow> WindowVector;

        template<class ...Args>
        CrossEngineAPI SharedWindow CreateWindowT(Args...args) {
            return CrossEngine::Util::Memory::Allocate<Window>(args...);
        }
    }
}


#endif //CROSSENGINE_BUILDNUMBER_WINDOW_HPP
