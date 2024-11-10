# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\Muetzenfinder_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Muetzenfinder_autogen.dir\\ParseCache.txt"
  "Muetzenfinder_autogen"
  )
endif()
