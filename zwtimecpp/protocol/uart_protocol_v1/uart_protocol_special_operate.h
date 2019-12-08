#pragma once
#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_struct.h"


DEFINE_DATA_POINT(SpecialOperate0) {
  DEFINE_DATA_POINT_ENTRY(SpecialOperate0, ModuleReset, 0x0100)
}
DEFINE_DATA_END(SpecialOperate0);
