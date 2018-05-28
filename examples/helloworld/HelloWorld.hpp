/**************************************************************
 * Program Title: Hello World
 * Filename: HelloWorld.hpp
 * Author: Blake Rogan
 * Last modified: 27/05/2018
 * Description:
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_HELLOWORLD_HPP
#define CROSSENGINE_HELLOWORLD_HPP

#include <iostream>
#include <CrossEngine.hpp>

class HelloWorld: public CrossEngine::Application::Application {
public:

    int MainLoop() override;

    void Exit() override;

};

DEFINE_APPLICATION(HelloWorld);


#endif //CROSSENGINE_HELLOWORLD_HPP
