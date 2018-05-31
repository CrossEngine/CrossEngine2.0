/**************************************************************
 * Program Title: CrossEngine
 * Filename: IOSystem.cpp
 * Author: Blake Rogan
 * Last modified: 30/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/IO/IOSystem.hpp>
#include <CrossEngine/Application/Application.hpp>
#include <physfs.h>

CrossEngine::IO::IOSystem::IOSystem(const char* init) {
    PHYSFS_init(init);
    PHYSFS_setSaneConfig(
            GetApplication()->GetVendorShortName().c_str(),
            GetApplication()->GetApplicationShortName().c_str(),
            nullptr,
            0,
            0
    );
    log = CrossEngine::Logging::GetLogger("IOSystem");
    log->info("IO Initialised");
    log->info("Write Directory: {}", GetWriteDir());
}

CrossEngine::IO::IOSystem::~IOSystem() {
    PHYSFS_deinit();
}

CrossEngine::Util::String CrossEngine::IO::IOSystem::GetWriteDir() const {
    return PHYSFS_getWriteDir();
}

bool CrossEngine::IO::IOSystem::Exists(const CrossEngine::Util::String &filename) {
    return PHYSFS_exists(filename.c_str()) != 0;
}

CrossEngine::IO::SharedIOFile
CrossEngine::IO::IOSystem::Open(const CrossEngine::Util::String &filename, CrossEngine::IO::OpenMode mode) {
    return CrossEngine::Util::Memory::Allocate<CrossEngine::IO::IOFile>(filename, mode);
}
