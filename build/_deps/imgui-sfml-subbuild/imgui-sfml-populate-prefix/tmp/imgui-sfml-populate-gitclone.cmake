# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

if(EXISTS "C:/Users/colli/Code/Coding Theory/build/_deps/imgui-sfml-subbuild/imgui-sfml-populate-prefix/src/imgui-sfml-populate-stamp/imgui-sfml-populate-gitclone-lastrun.txt" AND EXISTS "C:/Users/colli/Code/Coding Theory/build/_deps/imgui-sfml-subbuild/imgui-sfml-populate-prefix/src/imgui-sfml-populate-stamp/imgui-sfml-populate-gitinfo.txt" AND
  "C:/Users/colli/Code/Coding Theory/build/_deps/imgui-sfml-subbuild/imgui-sfml-populate-prefix/src/imgui-sfml-populate-stamp/imgui-sfml-populate-gitclone-lastrun.txt" IS_NEWER_THAN "C:/Users/colli/Code/Coding Theory/build/_deps/imgui-sfml-subbuild/imgui-sfml-populate-prefix/src/imgui-sfml-populate-stamp/imgui-sfml-populate-gitinfo.txt")
  message(STATUS
    "Avoiding repeated git clone, stamp file is up to date: "
    "'C:/Users/colli/Code/Coding Theory/build/_deps/imgui-sfml-subbuild/imgui-sfml-populate-prefix/src/imgui-sfml-populate-stamp/imgui-sfml-populate-gitclone-lastrun.txt'"
  )
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "C:/Users/colli/Code/Coding Theory/build/_deps/imgui-sfml-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: 'C:/Users/colli/Code/Coding Theory/build/_deps/imgui-sfml-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe"
            clone --no-checkout --config "advice.detachedHead=false" "https://github.com/SFML/imgui-sfml" "imgui-sfml-src"
    WORKING_DIRECTORY "C:/Users/colli/Code/Coding Theory/build/_deps"
    RESULT_VARIABLE error_code
  )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once: ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/SFML/imgui-sfml'")
endif()

execute_process(
  COMMAND "C:/Program Files/Git/cmd/git.exe"
          checkout "82dc2033e51b8323857c3ae1cf1f458b3a933c35" --
  WORKING_DIRECTORY "C:/Users/colli/Code/Coding Theory/build/_deps/imgui-sfml-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: '82dc2033e51b8323857c3ae1cf1f458b3a933c35'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe" 
            submodule update --recursive --init 
    WORKING_DIRECTORY "C:/Users/colli/Code/Coding Theory/build/_deps/imgui-sfml-src"
    RESULT_VARIABLE error_code
  )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: 'C:/Users/colli/Code/Coding Theory/build/_deps/imgui-sfml-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy "C:/Users/colli/Code/Coding Theory/build/_deps/imgui-sfml-subbuild/imgui-sfml-populate-prefix/src/imgui-sfml-populate-stamp/imgui-sfml-populate-gitinfo.txt" "C:/Users/colli/Code/Coding Theory/build/_deps/imgui-sfml-subbuild/imgui-sfml-populate-prefix/src/imgui-sfml-populate-stamp/imgui-sfml-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: 'C:/Users/colli/Code/Coding Theory/build/_deps/imgui-sfml-subbuild/imgui-sfml-populate-prefix/src/imgui-sfml-populate-stamp/imgui-sfml-populate-gitclone-lastrun.txt'")
endif()
