cmake_minimum_required(VERSION 2.8)
project(rocket)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined")
set(LIB_SRC
        rocket/common/log.cc
        rocket/common/config.cc
        rocket/common/util.cc
        rocket/net/eventLoop.cc
        rocket/net/fd_event.cc
        rocket/net/wakeup_fd.cc
        rocket/net/timer_event.cc
        rocket/net/timer.cc
        rocket/net/io_thread.cc
        rocket/net/io_thread_group.cc
        rocket/net/tcp/tcp_buffer.cc
        rocket/net/tcp/net_addr.cc
        rocket/net/tcp/tcp_acceptor.cc
        rocket/net/tcp/tcp_server.cc
        rocket/net/fd_event_group.cc
        rocket/net/tcp/tcp_connection.cc
        rocket/net/tcp/tcp_client.cc
        rocket/net/coder/tinypb_coder.cc
        rocket/net/coder/tinypb_protocol.cc
        rocket/net/rpc/rpc_dispatcher.cc
        rocket/net/rpc/rpc_controller.cc
        tests/order.pb.cc
        )

add_library(rocket SHARED ${LIB_SRC})

include_directories(.)
include_directories(/usr/include)#tinyxml头文件的路径
include_directories(/usr/local/include/google)#protobuf头文件
link_directories(/usr/local/lib)


set (TINYXML
                rocket/common/tinystr.cpp
                rocket/common/tinyxml.cpp
                rocket/common/tinyxmlerror.cpp
                rocket/common/tinyxmlparser.cpp)

add_library(tinyxml SHARED ${TINYXML})

set(LIB_LIB
    dl
    rocket
    pthread
    tinyxml
    protobuf
    )
add_executable(test_log tests/test_log.cc)
add_dependencies(test_log rocket)
target_link_libraries(test_log  ${LIB_LIB}) 


add_executable(test_eventloop tests/test_eventloop.cc)
add_dependencies(test_eventloop rocket)
target_link_libraries(test_eventloop  ${LIB_LIB}) 

add_executable(test_tcp tests/test_tcp.cc)
add_dependencies(test_tcp rocket)
target_link_libraries(test_tcp  ${LIB_LIB}) 

add_executable(test_tcp_client tests/test_tcp_client.cc)
add_dependencies(test_tcp_client rocket)
target_link_libraries(test_tcp_client rocket ${LIB_LIB}) 

add_executable(test_rpc_server tests/test_rpc_server.cc)
add_dependencies(test_rpc_server rocket)
target_link_libraries(test_rpc_server rocket ${LIB_LIB})

add_executable(test_rpc_client tests/test_rpc_client.cc)
add_dependencies(test_rpc_client rocket)
target_link_libraries(test_rpc_client rocket ${LIB_LIB})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)