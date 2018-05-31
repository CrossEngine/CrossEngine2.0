/**************************************************************
 * Program Title: CrossEngine_BuildNumber
 * Filename: OpenGLRenderer.hpp
 * Author: Blake Rogan
 * Last modified: 31/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_BUILDNUMBER_OPENGLRENDERER_HPP
#define CROSSENGINE_BUILDNUMBER_OPENGLRENDERER_HPP

#include <glad/glad.h>

#include <CrossEngine/config.h>
#include <CrossEngine/Util/Util.hpp>
#include <CrossEngine/Render/Renderer.hpp>
#include <CrossEngine/Logging/Logging.hpp>
#include <CrossEngine/EventBus/EventBus.hpp>
#include <CrossEngine/Window/WindowEvents.hpp>

#define GLFW_INCLUDE_NONE 1
#include <GLFW/glfw3.h>

#include <thread>
#include <atomic>

namespace CrossEngine {
    namespace Render {
        class OpenGLRenderer: public Renderer {
        private:

        public:

            CrossEngineAPI bool Setup(GLFWwindow* window) override;

            CrossEngineAPI bool Render(GLFWwindow* window) override;

            CrossEngineAPI bool Teardown(GLFWwindow* window) override;
        };
    }
}


#endif //CROSSENGINE_BUILDNUMBER_OPENGLRENDERER_HPP
