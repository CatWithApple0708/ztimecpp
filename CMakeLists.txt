cmake_minimum_required(VERSION
	3.13)
project(ztimecpp)
set(CMAKE_CXX_STANDARD 14)
include_directories(
	.
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -pthread -fexceptions -pthread  -ffunction-sections  -rdynamic -funwind-tables -fasynchronous-unwind-tables -fomit-frame-pointer")

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
	zwtimecpp/core/base/system_state.hpp
	zwtimecpp/core/helper/exception_helper.hpp zwtimecpp/core/core.hpp zwtimecpp/core/exception/thread_unjointed_exception.hpp zwtimecpp/core/base/exception_handler.hpp zwtimecpp/core/base/thread_info.hpp)

add_library(zwtimecpp
	${CORE_RES}
	)

add_executable(core_test
	zwtimecpp/core/test/core_test.cpp
	zwtimecpp/core/test/test_utils/tester_manager.cpp zwtimecpp/core/test/test_utils/tester_manager.hpp zwtimecpp/core/test/test_back_ward.cpp zwtimecpp/core/test/test_exception.cpp zwtimecpp/core/test/test_thread.cpp)
target_link_libraries(
	core_test
	zwtimecpp
)
add_dependencies(core_test
	zwtimecpp
)

