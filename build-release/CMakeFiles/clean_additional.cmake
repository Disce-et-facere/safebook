# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\safebook_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\safebook_autogen.dir\\ParseCache.txt"
  "safebook_autogen"
  )
endif()
