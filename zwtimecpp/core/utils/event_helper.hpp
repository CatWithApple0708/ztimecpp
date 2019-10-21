#pragma once
#include "zwtimecpp/core/utils/memory_utils.hpp"
#define START_PROCESS_EVENT(baseEvent)            \
  {                                               \
    shared_ptr<BaseEvent> pbaseEvent = baseEvent; \
    if (false) {
#define CASE_EVENT(eventType)             \
  }                                       \
  else if (instanceof <eventType>(ptr)) { \
    shared_ptr<eventType> event = dpc<eventType>(pbaseEvent);

#define END_PROCESS_EVENT() \
  }                         \
  }

#define zprocess_event(baseEvent)               \
  shared_ptr<BaseEvent> pbaseEvent = baseEvent; \
  if (false)
#define zcase_event(eventType)            \
  }                                       \
  else if (instanceof <eventType>(ptr)) { \
    shared_ptr<eventType> event = dpc<eventType>(pbaseEvent);

/**/