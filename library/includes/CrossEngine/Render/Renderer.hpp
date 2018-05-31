/**************************************************************
 * Program Title: CrossEngine_BuildNumber
 * Filename: Renderer.hpp
 * Author: Blake Rogan
 * Last modified: 31/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_BUILDNUMBER_RENDERER_HPP
#define CROSSENGINE_BUILDNUMBER_RENDERER_HPP

#include <CrossEngine/config.h>
#include <CrossEngine/Util/Util.hpp>
#include <CrossEngine/Logging/Logging.hpp>
#include <CrossEngine/EventBus/EventBus.hpp>
#include <CrossEngine/Window/WindowEvents.hpp>

#define GLFW_INCLUDE_NONE 1
#include <GLFW/glfw3.h>

#include <thread>
#include <atomic>

namespace CrossEngine {
    namespace Render {
        class Renderer {
        private:

        protected:
            Logging::SharedLogger log;

        public:
            CrossEngineAPI Renderer();

            CrossEngineAPI ~Renderer();

            CrossEngineAPI virtual bool Setup(GLFWwindow* window);

            CrossEngineAPI virtual bool Render(GLFWwindow* window);

            CrossEngineAPI virtual bool Teardown(GLFWwindow* window);

        };

        typedef Util::Memory::Shared<Renderer> SharedRenderer;
    }
}


#endif //CROSSENGINE_BUILDNUMBER_RENDERER_HPP
