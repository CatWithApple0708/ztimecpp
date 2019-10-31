include_directories(. ./zwtimecpp/core/logger)
option(zwtimecpp_build_on_parent "zwtimecpp_build_on_parent" OFF)
if(NOT zwtimecpp_build_on_parent)
  cmake_minimum_required(VERSION 3.13)
  project(ztimecpp)
  set(CMAKE_CXX_STANDARD 14)
  message(STATUS "Compile in default config")
  ##############################################################################3
  #
  # 设置编译器相关配置
  #

  # 设置公共的环境变量 xxxx_COMMON
  set(
    C_AND_CXX_FLAGS_COMMON
    "-O1 -g3 -Werror=return-type -Werror=parentheses -Wfatal-errors  -Wall -Wno-deprecated-declarations -Wno-unused-variable -fexceptions  -ffunction-sections  -rdynamic -funwind-tables -fasynchronous-unwind-tables"
    )
  set(CMAKE_CXX_FLAGS_COMMON "-std=c++14 -pthread -Wno-reorder")
  set(CMAKE_C_FLAGS_COMMON "-std=c99")

  # 设置PC私有的宏定义 xxxx_PC_PRI
  set(C_AND_CXX_FLAGS_PC_PRI "")
  set(CMAKE_CXX_FLAGS_PC_PRI "")
  set(CMAKE_C_FLAGS_PC_PRI "")
  # 设置其他架构宏定义 xxxx_XX_PRI

  ##############################################################################3
  set(CMAKE_C_COMPILER gcc)
  set(CMAKE_CXX_COMPILER g++)
  set(
    CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} ${C_AND_CXX_FLAGS_COMMON} ${C_AND_CXX_FLAGS_PC_PRI} ${CMAKE_C_FLAGS_COMMON} ${CMAKE_C_FLAGS_PC_PRI}"
    )
  set(
    CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} ${C_AND_CXX_FLAGS_COMMON} ${C_AND_CXX_FLAGS_PC_PRI} ${CMAKE_CXX_FLAGS_COMMON} ${CMAKE_CXX_FLAGS_PC_PRI}"
    )
  include_directories(${COMMON_INCLUDE_DIRS} ${PC_INCLUDE_DIRS})
  link_directories(${PC_LINK_DIRS})
  link_libraries(${COMMON_LINK_LIBS} ${PC_LINK_LIBS})
  set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
else()
  message(STATUS "Compile in parent config")
endif()

add_library(
  zwtimecpp
  zwtimecpp/core/thread/thread.cpp
  zwtimecpp/core/thread/thread.hpp
  zwtimecpp/core/exception/base_exception.hpp
  zwtimecpp/core/exception/base_exception.cpp
  zwtimecpp/core/utils/backward/backward.hpp
  zwtimecpp/core/base/interlog/simple_logger.cpp
  zwtimecpp/core/base/interlog/simple_logger.hpp
  zwtimecpp/core/jobs/thread_pool_task_scheduler.cpp
  zwtimecpp/core/jobs/thread_pool_task_scheduler.hpp
  zwtimecpp/core/base/base_event.hpp
  zwtimecpp/core/event_bus.cpp
  zwtimecpp/core/event_bus.hpp
  zwtimecpp/core/base/object.hpp
  zwtimecpp/core/exception/null_expection.hpp
  zwtimecpp/core/exception_handle_center.cpp
  zwtimecpp/core/exception_handle_center.hpp
  zwtimecpp/core/utils/signal.hpp
  zwtimecpp/core/exception/unkown_type_exception.hpp
  zwtimecpp/core/exception/system_or_third_lib_exception.hpp
  zwtimecpp/core/utils/backward_helper.hpp
  zwtimecpp/core/system_state.hpp
  zwtimecpp/core/exception/exception_helper.hpp
  zwtimecpp/core/core.hpp
  zwtimecpp/core/exception/thread_unjointed_exception.hpp
  zwtimecpp/core/base/exception_handler.hpp
  zwtimecpp/core/base/thread_info.hpp
  zwtimecpp/core/utils/memory_utils.hpp
  zwtimecpp/core/utils/data.hpp
  zwtimecpp/core/utils/mapper/json_helper.hpp
  zwtimecpp/core/utils/file_utils.cpp
  zwtimecpp/core/utils/file_utils.hpp
  zwtimecpp/core/logger/logger_factory.cpp
  zwtimecpp/core/logger/logger_factory.hpp
  zwtimecpp/core/logger/logger.hpp
  zwtimecpp/core/utils/blocking_concurrent_queue_helper.cpp
  zwtimecpp/core/utils/blocking_concurrent_queue_helper.hpp
  zwtimecpp/core/utils/time_utils.cpp
  zwtimecpp/core/utils/time_utils.hpp
  zwtimecpp/core/utils/queue_utils.hpp
  zwtimecpp/core/benchmark/benchmark.cpp
  zwtimecpp/core/benchmark/benchmark.hpp
  zwtimecpp/core/constant.hpp
  zwtimecpp/core/benchmark/benchmark_factory.cpp
  zwtimecpp/core/benchmark/benchmark_factory.hpp
  zwtimecpp/core/event_priority.hpp
  zwtimecpp/core/utils/map_utils.cpp
  zwtimecpp/core/utils/map_utils.hpp
  zwtimecpp/core/utils/any.hpp
  zwtimecpp/core/utils/container_utils.hpp
  zwtimecpp/core/utils/compliler.h
  zwtimecpp/core/logger/default_logger_config.hpp
  zwtimecpp/core/utils/auto_call_when_exist.hpp
  zwtimecpp/core/cxvlogger/cxv_logger_factory.cpp
  zwtimecpp/core/cxvlogger/cxv_logger_factory.hpp
  zwtimecpp/core/core.cpp
  zwtimecpp/core/utils/backward/backward.cpp
  zwtimecpp/core/utils/fatall_error.hpp
  zwtimecpp/core/utils/type_name.hpp
  zwtimecpp/core/utils/instance.hpp
  zwtimecpp/core/utils/constant_utils.hpp
  #process
  zwtimecpp/core/utils/process/process.cpp
  zwtimecpp/core/utils/process/process.hpp
  zwtimecpp/core/utils/process/process_unix.cpp
  zwtimecpp/core/utils/vector_utils.hpp
  zwtimecpp/core/base/result.cpp
  zwtimecpp/core/base/result.hpp
  zwtimecpp/core/utils/cli_help.cpp
  zwtimecpp/core/utils/cli_help.hpp
  #cutils
  zwtimecpp/core/utils/cutils/arrary.c
  zwtimecpp/core/utils/cutils/arrary.h
  zwtimecpp/core/utils/cutils/infinite_arrary.c
  zwtimecpp/core/utils/cutils/infinite_arrary.h
  zwtimecpp/core/utils/cutils/loop_queue.c
  zwtimecpp/core/utils/cutils/loop_queue.h

  #protocol
  zwtimecpp/protocol/uart_protocol_v1/uart_protocol_packet_struct_internal.h
  zwtimecpp/protocol/uart_protocol_v1/uart_protocol_packet.c
  zwtimecpp/protocol/uart_protocol_v1/uart_protocol_packet.h
  zwtimecpp/protocol/uart_protocol_v1/uart_protocol_parse.c
  zwtimecpp/protocol/uart_protocol_v1/uart_protocol_parse.h
  zwtimecpp/protocol/uart_protocol_v1/uart_protocol_struct.h)
####################################################################
add_library(zwtimecpptest zwtimecpp/core/test/test_utils/runner_manager.cpp
                          zwtimecpp/core/test/test_utils/runner_manager.hpp)

set(GTESTERS zwtimecpp/core/test/gtester/gtest_arrary.cc
             zwtimecpp/core/test/gtester/gtest_infinite_arrary.cc
             zwtimecpp/core/test/gtester/gtest_loop_queue.cc
             zwtimecpp/core/test/gtester/gtest_uart_protocol_v1.cc
             zwtimecpp/core/test/gtester/gtest_string_utils.cpp
             )

if(NOT zwtimecpp_build_on_parent)
  #单独编译
  include_directories(./third/pc/include)
  link_directories(./third/pc/lib)
endif()
#####################################################################
#core_gtest_main
#
add_executable(core_gtest_main zwtimecpp/core/test/gtest_main.cpp ${GTESTERS})
target_link_libraries(core_gtest_main
                      zwtimecpp
                      zwtimecpptest
                      gtest
                      gmock)
add_dependencies(core_gtest_main zwtimecpp zwtimecpptest)
#####################################################################
#core_runner_main
#
add_executable(core_runner_main zwtimecpp/core/test/runner_main.cpp
zwtimecpp/core/test/runner/show_uart_v1_info.cc
)
target_link_libraries(core_runner_main zwtimecpp zwtimecpptest)
add_dependencies(core_runner_main zwtimecpp zwtimecpptest)
