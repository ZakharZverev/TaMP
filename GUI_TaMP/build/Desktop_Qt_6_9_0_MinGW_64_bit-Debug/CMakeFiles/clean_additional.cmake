# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TIMP_KKZM_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TIMP_KKZM_autogen.dir\\ParseCache.txt"
  "TIMP_KKZM_autogen"
  )
endif()
