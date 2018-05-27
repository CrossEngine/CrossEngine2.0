
if (NOT EXISTS "D:/Development/c++/CrossEngineDevelopment/CrossEngine2.0/cmake-build-debug/ext/glfw/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: \"D:/Development/c++/CrossEngineDevelopment/CrossEngine2.0/cmake-build-debug/ext/glfw/install_manifest.txt\"")
endif()

file(READ "D:/Development/c++/CrossEngineDevelopment/CrossEngine2.0/cmake-build-debug/ext/glfw/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")

foreach (file ${files})
  message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  if (EXISTS "$ENV{DESTDIR}${file}")
    exec_program("C:/Users/rogan/AppData/Local/JetBrains/Toolbox/apps/CLion/ch-0/182.2574.4/bin/cmake/bin/cmake.exe" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif()
  elseif (IS_SYMLINK "$ENV{DESTDIR}${file}")
    EXEC_PROGRAM("C:/Users/rogan/AppData/Local/JetBrains/Toolbox/apps/CLion/ch-0/182.2574.4/bin/cmake/bin/cmake.exe" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing symlink \"$ENV{DESTDIR}${file}\"")
    endif()
  else()
    message(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  endif()
endforeach()

