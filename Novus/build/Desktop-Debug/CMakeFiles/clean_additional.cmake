# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Novus_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Novus_autogen.dir\\ParseCache.txt"
  "Novus_autogen"
  )
endif()
