/**************************************************************
 * Program Title: CrossEngine
 * Filename: CrossEngine.hpp
 * Author: Blake Rogan
 * Last modified: 27/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_CROSSENGINE_HPP
#define CROSSENGINE_CROSSENGINE_HPP

#include <CrossEngine/Application/Application.hpp>

#define APPLICATION_GET_GET(app) app* GetApplication();
#define APPLICATION_MAIN_DEF(app) int main(int argc, const char** argv)

#define APPLICATION_GET_IMPL(app) static app *application = nullptr; app* GetApplication() {return application;}
#define APPLICATION_MAIN_IMPL(app) int main(int argc, const char** argv) {application = new app(); return application->MainLoop(argc, argv);}

#define DEFINE_APPLICATION(app) APPLICATION_GET_GET(app); APPLICATION_MAIN_DEF(app);
#define IMPLEMENT_APPLICATION(app) APPLICATION_GET_IMPL(app); APPLICATION_MAIN_IMPL(app);

#endif //CROSSENGINE_CROSSENGINE_HPP
