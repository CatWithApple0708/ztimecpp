cmake_minimum_required(VERSION 3.13)
project(ztimecpp)
set(CMAKE_CXX_STANDARD 14)
include_directories(
	.
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -pthread -fexceptions  -ffunction-sections  -rdynamic -funwind-tables -fasynchronous-unwind-tables -fomit-frame-pointer")
set(CORE_RES
	zwtimecpp/core/thread/thread.cpp
	zwtimecpp/core/thread/thread.hpp
	zwtimecpp/core/exception/base_exception.hpp
	zwtimecpp/core/exception/base_exception.cpp
	zwtimecpp/core/utils/backward/backward.hpp
	zwtimecpp/core/interlog/simple_logger.cpp zwtimecpp/core/interlog/simple_logger.hpp zwtimecpp/core/jobs/thread_pool_task_scheduler.cpp zwtimecpp/core/jobs/thread_pool_task_scheduler.hpp zwtimecpp/core/event/base_event.cpp zwtimecpp/core/event/base_event.hpp zwtimecpp/core/core.cpp zwtimecpp/core/core.hpp zwtimecpp/core/exception/exception_handler.cpp zwtimecpp/core/exception/exception_handler.hpp zwtimecpp/core/event/event_handler.hpp zwtimecpp/core/object.cpp zwtimecpp/core/object.hpp)

add_library(ztimecpp SHARED
	library.cpp
	library.h
	${CORE_RES}
	)

add_executable(core_test
	zwtimecpp/core/test/core_test.cpp
	zwtimecpp/core/test/test_back_ward.hpp)
target_link_libraries(
	core_test
	ztimecpp
)
add_dependencies(core_test
	ztimecpp
)

