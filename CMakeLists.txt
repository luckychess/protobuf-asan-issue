cmake_minimum_required(VERSION 3.14)
project(protobuf_asan_issue)

set(CMAKE_CXX_STANDARD 14)

include(ExternalProject)

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS endpoint.proto)

SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
find_package(protobuf-mutator REQUIRED)

if(DEFINED ENV{LIB_FUZZING_ENGINE})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} $ENV{LIB_FUZZING_ENGINE}")
  set(fuzzing_engine "")
else()
  add_library(fuzzing_engine standalone_fuzz_target_runner.cpp)
  set(fuzzing_engine fuzzing_engine)
endif()

add_executable(protobuf_asan_issue main.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(protobuf_asan_issue ${Protobuf_LIBRARIES} protobuf-mutator ${fuzzing_engine})
