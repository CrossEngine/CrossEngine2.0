/**************************************************************
 * Program Title: CrossEngine
 * Filename: IOFile.cpp
 * Author: Blake Rogan
 * Last modified: 30/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/IO/IOFile.hpp>

CrossEngine::IO::IOFile::IOFile(const CrossEngine::Util::String &filename, CrossEngine::IO::OpenMode mode) {
    switch (mode) {
        case Open_Read:
            handle = PHYSFS_openRead(filename.c_str());
            break;
        case Open_Write:
            handle = PHYSFS_openWrite(filename.c_str());
            break;
        case Open_Append:
            handle = PHYSFS_openAppend(filename.c_str());
            break;
    }
}

CrossEngine::IO::IOFile::~IOFile() {
    PHYSFS_close(handle);
}

PHYSFS_sint64 CrossEngine::IO::IOFile::Read(void *buffer, PHYSFS_uint64 len) {
    return PHYSFS_readBytes(handle, buffer, len);
}

PHYSFS_sint64 CrossEngine::IO::IOFile::Write(const void *buffer, PHYSFS_uint64 len) {
    return PHYSFS_writeBytes(handle, buffer, len);
}

PHYSFS_sint64 CrossEngine::IO::IOFile::Tell() {
    return PHYSFS_tell(handle);
}

bool CrossEngine::IO::IOFile::Seek(PHYSFS_uint64 pos, CrossEngine::IO::SeekDir dir) {
    switch (dir) {
        case Seek_Begin:
            return PHYSFS_seek(handle, pos) != 0;
        case Seek_Current:
            return PHYSFS_seek(handle, Tell() + pos) != 0;
        case Seek_End:
            return PHYSFS_seek(handle, Tell() - pos) != 0;
    }
    return false;
}
