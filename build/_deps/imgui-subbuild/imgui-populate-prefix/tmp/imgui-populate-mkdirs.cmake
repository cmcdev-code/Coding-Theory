# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/colli/Code/Coding Theory/build/_deps/imgui-src"
  "C:/Users/colli/Code/Coding Theory/build/_deps/imgui-build"
  "C:/Users/colli/Code/Coding Theory/build/_deps/imgui-subbuild/imgui-populate-prefix"
  "C:/Users/colli/Code/Coding Theory/build/_deps/imgui-subbuild/imgui-populate-prefix/tmp"
  "C:/Users/colli/Code/Coding Theory/build/_deps/imgui-subbuild/imgui-populate-prefix/src/imgui-populate-stamp"
  "C:/Users/colli/Code/Coding Theory/build/_deps/imgui-subbuild/imgui-populate-prefix/src"
  "C:/Users/colli/Code/Coding Theory/build/_deps/imgui-subbuild/imgui-populate-prefix/src/imgui-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/colli/Code/Coding Theory/build/_deps/imgui-subbuild/imgui-populate-prefix/src/imgui-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/colli/Code/Coding Theory/build/_deps/imgui-subbuild/imgui-populate-prefix/src/imgui-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
