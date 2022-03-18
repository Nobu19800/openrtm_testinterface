cmake_minimum_required(VERSION 3.1)

set(target TestIF)
project(${target} CXX)

find_package(OpenRTM REQUIRED)



add_definitions(${OPENRTM_CFLAGS})
link_directories(${OPENRTM_LIBRARY_DIRS})

add_library(${target} SHARED ${target}.cpp TestInPortConsumer.cpp TestInPortConsumer.h TestInPortProvider.cpp TestInPortProvider.h TestOutPortConsumer.cpp TestOutPortConsumer.h TestOutPortProvider.cpp TestOutPortProvider.h)
target_link_libraries(${target} ${OPENRTM_LIBRARIES})
target_include_directories(${target} SYSTEM PRIVATE ${OPENRTM_INCLUDE_DIRS})
set_target_properties(${target} PROPERTIES PREFIX "")