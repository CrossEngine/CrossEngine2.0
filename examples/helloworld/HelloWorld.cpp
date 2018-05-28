/**************************************************************
 * Program Title: Hello World
 * Filename: HelloWorld.cpp
 * Author: Blake Rogan
 * Last modified: 27/05/2018
 * Description:
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include "HelloWorld.hpp"

IMPLEMENT_APPLICATION(HelloWorld);

int HelloWorld::MainLoop() {
    log->info("Hello World");
    return Application::MainLoop();
}

void HelloWorld::Exit() {
    log->info("Shutdown");
    Application::Exit();
}
