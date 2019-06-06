cmake_minimum_required(VERSION
	3.13)
project(ztimecpp)
set(CMAKE_CXX_STANDARD 14)
include_directories(
	.
	./zwtimecpp/core/logger
)
#ARCH can be x86 or arm32
if (${ARCH} MATCHES "x86")
	set(CMAKE_SYSTEM_NAME Linux)
	if (NOT CMAKE_C_COMPILER)
		set(CMAKE_C_COMPILER gcc)
	endif ()
	if (NOT CMAKE_CXX_COMPILER)
		set(CMAKE_CXX_COMPILER g++)
	endif ()
	set(CMAKE_C_FLAGS "-O1 -g -Wall -Wfatal-errors")
	set(CMAKE_CXX_FLAGS "-O1 -g -Wall -std=c++14 -Wno-deprecated-declarations -pthread -Wfatal-errors -DWEBRTC_POSIX -DWEBRTC_LINUX")
elseif (${ARCH} MATCHES "arm32")
	set(CMAKE_SYSTEM_NAME Linux)
	if (NOT CMAKE_C_COMPILER)
		set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
	endif ()
	if (NOT CMAKE_CXX_COMPILER)
		set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
	endif ()
	set(CMAKE_C_FLAGS "-O1 -g -Wall -Wfatal-errors -s -fexceptions  -ffunction-sections  -rdynamic -funwind-tables -fasynchronous-unwind-tables ")
	set(CMAKE_CXX_FLAGS "-O1 -g -Wall -std=c++14 -g3 -s -fexceptions  -ffunction-sections  -rdynamic -funwind-tables -fasynchronous-unwind-tables -mfpu=neon -Wno-deprecated-declarations -Wfatal-errors")
else ()
	message(FATAL_ERROR,"Not set ARCH,please set by exec `cmake .. -DARCH=????`")
endif ()

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
	zwtimecpp/core/exception/exception_helper.hpp zwtimecpp/core/core.hpp zwtimecpp/core/exception/thread_unjointed_exception.hpp zwtimecpp/core/base/exception_handler.hpp zwtimecpp/core/base/thread_info.hpp zwtimecpp/core/utils/memory_utils.hpp zwtimecpp/core/utils/data.hpp zwtimecpp/core/utils/mapper/json_helper.hpp zwtimecpp/core/utils/file_utils.cpp zwtimecpp/core/utils/file_utils.hpp zwtimecpp/core/logger/logger_factory.cpp zwtimecpp/core/logger/logger_factory.hpp zwtimecpp/core/logger/logger.hpp zwtimecpp/core/utils/blocking_concurrent_queue_helper.cpp zwtimecpp/core/utils/blocking_concurrent_queue_helper.hpp zwtimecpp/core/utils/time_utils.cpp zwtimecpp/core/utils/time_utils.hpp zwtimecpp/core/utils/queue_utils.hpp zwtimecpp/core/benchmark/benchmark.cpp zwtimecpp/core/benchmark/benchmark.hpp zwtimecpp/core/constant.hpp zwtimecpp/core/benchmark/benchmark_factory.cpp zwtimecpp/core/benchmark/benchmark_factory.hpp)

add_library(zwtimecpp
	${CORE_RES}
	)
target_link_libraries(zwtimecpp
	pthread
)

add_executable(core_test
	zwtimecpp/core/test/core_test.cpp
	zwtimecpp/core/test/test_utils/tester_manager.cpp zwtimecpp/core/test/test_utils/tester_manager.hpp zwtimecpp/core/test/test_back_ward.cpp zwtimecpp/core/test/test_exception.cpp zwtimecpp/core/test/test_thread.cpp zwtimecpp/core/test/test_event_bus.cpp zwtimecpp/core/test/test_benchmark.cpp)
target_link_libraries(
	core_test
	zwtimecpp
)
add_dependencies(core_test
	zwtimecpp
	)

