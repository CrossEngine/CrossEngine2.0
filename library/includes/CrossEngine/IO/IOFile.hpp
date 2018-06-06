/**************************************************************
 * Program Title: CrossEngine
 * Filename: IOFile.hpp
 * Author: Blake Rogan
 * Last modified: 30/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_IOFILE_HPP
#define CROSSENGINE_IOFILE_HPP

#include <CrossEngine/config.h>
#include <CrossEngine/Util/Util.hpp>
#include <CrossEngine/Logging/Logging.hpp>

#include <physfs.h>

namespace CrossEngine {
    namespace IO {

        /**
         *
         */
        enum OpenMode {
            Open_Read,
            Open_Write,
            Open_Append
        };

        /**
         *
         */
        enum SeekDir {
            Seek_Begin,
            Seek_Current,
            Seek_End
        };

        /**
         *
         */
        class IOFile {
        private:
            PHYSFS_File* handle; /** */
        public:
            /**
             *
             * \param filename
             * \param mode
             */
            CrossEngineAPI IOFile(const Util::String& filename, OpenMode mode);

            /**
             *
             */
            CrossEngineAPI ~IOFile();

            /**
             *
             * \param buffer
             * \param len
             * \return
             */
            CrossEngineAPI PHYSFS_sint64 Read(void* buffer, PHYSFS_uint64 len);

            /**
             *
             * \param buffer
             * \param len
             * \return
             */
            CrossEngineAPI PHYSFS_sint64 Write(const void* buffer, PHYSFS_uint64 len);

            /**
             *
             * \return
             */
            CrossEngineAPI PHYSFS_sint64 Tell();

            /**
             *
             * \param pos
             * \param dir
             * \return
             */
            CrossEngineAPI bool Seek(PHYSFS_uint64 pos, SeekDir dir);
        };

        /**
         *
         */
        typedef Util::Memory::Shared<IOFile> SharedIOFile;


        /**
         *
         * \tparam Args
         * \param args
         * \return
         */
        template <class ...Args>
        CrossEngineAPI SharedIOFile CreateIOFile(Args...args) {
            return Util::Memory::Allocate<IOFile>(args...);
        }
    }
}


#endif //CROSSENGINE_IOFILE_HPP
