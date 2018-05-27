/**************************************************************
 * Program Title: CrossEngine
 * Filename: Application.hpp
 * Author: Blake Rogan
 * Last modified: 27/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_APPLICATION_HPP
#define CROSSENGINE_APPLICATION_HPP

#include <CrossEngine/Util/Memory.hpp>
#include <CrossEngine/Util/Containers.hpp>
#include <CrossEngine/Logging/Logging.hpp>

namespace CrossEngine {
    namespace Application {
        class Application {
        protected:
            Logging::SharedLogger log;
        public:

            Application();

            virtual Logging::SinksVector GetSinks();

            virtual int MainLoop(int argc, const char **argv);

//            virtual void OnInit();
//
//            virtual void OnLoop();

        };
    }
}

#endif //CROSSENGINE_APPLICATION_HPP
