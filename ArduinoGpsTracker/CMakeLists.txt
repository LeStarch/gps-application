project(ArduinoGpsTracker C CXX ASM)
cmake_minimum_required(VERSION 3.5)
set(BAREMETAL_SCHEDULER CACHE BOOL ON "Uses the baremtal scheduler")


include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime.cmake")
include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime-Code.cmake")
include("${FPRIME_PROJECT_ROOT}/fprime-arduino/fprime-arduino.cmake")

# Add component subdirectories
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Gps/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/RadioWrapper/")

# Add Topology subdirectory
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Top/")
