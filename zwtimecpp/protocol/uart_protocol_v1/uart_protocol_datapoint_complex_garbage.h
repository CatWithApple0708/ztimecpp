#pragma once
#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_struct.h"


DEFINE_DATA_POINT(ComplexGarbage) {
  DEFINE_DATA_POINT_ENTRY(ComplexGarbage, ModuleReset, 0x0100)
}
DEFINE_DATA_END(ComplexGarbage);
