#include "precompiled.h"

// Copyright 2002-2004 Frozenbyte Ltd.

#ifdef _MSC_VER
#  pragma warning(disable:4103)
#endif

#include "standard_package.h"
#include "input_file_stream.h"
#include "ifile_list.h"
#include "../editor/FindFileWrapper.h"
#include <string>
#include <unistd.h>
#include <boost/algorithm/string/case_conv.hpp>
#include "../util/Debug_MemoryManager.h"

#include "../util/crc32.h"

namespace frozenbyte {
    using namespace editor;
    using namespace std;

    namespace filesystem {
        namespace {
            void getFiles(const std::string &dir, const std::string &extension, IFileList &result)
            {
                string searchString = dir;
                searchString += "/";
                searchString += extension;

                editor::FindFileWrapper wrapper(searchString.c_str(), editor::FindFileWrapper::File);
                //printf("finding files in %s, filter = %s\n", dir.c_str(), extension.c_str());
                //int count = 0;
                for ( ; !wrapper.end(); wrapper.next() ) {
                    std::string fileName = dir + std::string("/") + wrapper.getName();
                    //count++;
                    result.addFile(fileName);
                }
                //printf("found %d files\n", count);
            }

            void iterateDir(const std::string &dir, const std::string &extension, IFileList &result)
            {
                getFiles(dir, extension, result);

                string searchString = dir;
                searchString += "/*";

                editor::FindFileWrapper wrapper(searchString.c_str(), editor::FindFileWrapper::Dir);
                for ( ; !wrapper.end(); wrapper.next() ) {
                    std::string currentDir = dir;
                    currentDir += "/";
                    currentDir += wrapper.getName();

                    result.addDir(currentDir);
                    iterateDir(currentDir, extension, result);
                }
            }

        } // unnamed

        StandardPackage::StandardPackage()
        {
        }

        StandardPackage::~StandardPackage()
        {
        }

        void StandardPackage::findFiles(const std::string &dir, const std::string &extension, IFileList &result)
        {
            iterateDir(dir, extension, result);
            //also check the directory name in lower case
            std::string lower = boost::algorithm::to_lower_copy(dir);
            if (lower != dir) {
                iterateDir(lower, extension, result);
            }
        }

        InputStream StandardPackage::getFile(const std::string &fileName)
        {
            return createInputFileStream(fileName);
        }

        bool StandardPackage::exists(const std::string& fileName) const {
            return access(fileName.c_str(), F_OK) == 0;
        }


        unsigned int StandardPackage::getCrc(const std::string &fileName)
        {
            /*
               InputStream strm = createInputFileStream(fileName);
               if(strm.getSize() != 0)
               {
                return 0xFFFFFFFF;
               }
               return 0;
             */
            return crc32_file( fileName.c_str() );
        }

    } // end of namespace filesystem
}     // end of namespace frozenbyte
