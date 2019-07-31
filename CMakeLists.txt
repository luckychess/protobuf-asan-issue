cmake_minimum_required(VERSION 3.14)
project(protobuf_asan_issue)

set(CMAKE_CXX_STANDARD 14)

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS endpoint.proto)

add_executable(protobuf_asan_issue main.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(protobuf_asan_issue ${Protobuf_LIBRARIES})
