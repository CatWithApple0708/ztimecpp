//
// Created by zhaohe on 19-5-21.
//

#pragma once
#include <memory>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include "zwtimecpp/core/event/base_event.hpp"
namespace zwsd {
namespace core{
using namespace std;

template <class T>
class EventHandler {
  public:

	/**
	 * \brief Default constructor that enforces the template type
	 */
	EventHandler() {
		// An error here indicates you're trying to implement EventHandler with a type that is not derived from Base
		static_assert(std::is_base_of<BaseEvent, T>::value, "EventHandler<T>: T must be a class derived from BaseEvent");
	}


	/**
	 * \brief Empty virtual destructor
	 */
	virtual ~EventHandler() { }


	/**
	 * \brief Pure virtual method for implementing the body of the listener
	 *
	 * @param The event instance
	 */
	virtual void onEvent(T &) = 0;


	/**
	 * \brief Dispatches a generic event to the appropriate listener method
	 *
	 * This method is called by the EventBus and dispatches to the correct method by
	 * dynamic casting the event parameter to the template type for this handler.
	 *
	 * @param e The event to dispatch
	 */
	void dispatch(BaseEvent & e) {
		onEvent(dynamic_cast<T &>(e));
	}
};
}
}


