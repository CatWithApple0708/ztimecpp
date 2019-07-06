cmake_minimum_required(VERSION 3.13)
project(ztimecpp)
set(CMAKE_CXX_STANDARD 14)
include_directories(. ./zwtimecpp/core/logger)

set(COMMON_FLAGS "")
set(
  COMMON_FLAGS
  "${COMMON_FLAGS} -Werror=return-type -Wfatal-errors  -Wall  -Wno-deprecated-declarations"
  )
# 栈信息配置
set(
  COMMON_FLAGS
  "${COMMON_FLAGS} -fexceptions  -ffunction-sections  -rdynamic -funwind-tables -fasynchronous-unwind-tables "
  )
# 调试和编译等级配置
set(COMMON_FLAGS "${COMMON_FLAGS} -O1 -g3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS} -std=c++14 -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ")

# ARCH can be x86 or arm32
if(${ARCH} MATCHES "x86")
  set(CMAKE_SYSTEM_NAME Linux)
  if(NOT CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER gcc)
  endif()
  if(NOT CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER g++)
  endif()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
elseif(${ARCH} MATCHES "arm32")
  set(CMAKE_SYSTEM_NAME Linux)
  if(NOT CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
  endif()
  if(NOT CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
  endif()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s ")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s -mfpu=neon")
else()
  message(FATAL_ERROR,"Not set ARCH,please set by exec `cmake .. -DARCH=????`")
endif()

set(CORE_RES
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
    zwtimecpp/core/utils/process/process_unix.cpp)

add_library(zwtimecpp ${CORE_RES})
target_link_libraries(zwtimecpp pthread)

add_executable(core_test
               zwtimecpp/core/test/core_test.cpp
               zwtimecpp/core/test/test_utils/tester_manager.cpp
               zwtimecpp/core/test/test_utils/tester_manager.hpp
               zwtimecpp/core/test/test_back_ward.cpp
               zwtimecpp/core/test/test_exception.cpp
               zwtimecpp/core/test/test_thread.cpp
               zwtimecpp/core/test/test_event_bus.cpp
               zwtimecpp/core/test/test_benchmark.cpp)
target_link_libraries(core_test zwtimecpp)
add_dependencies(core_test zwtimecpp)
