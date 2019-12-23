#pragma once
#include "zwtimecpp/core/utils/compliler.h"

#ifdef KILE_STM32
#define INLINE __inline
#undef WHEAK
#define WHEAK
#endif

#ifndef INLINE
#define INLINE inline
#endif


