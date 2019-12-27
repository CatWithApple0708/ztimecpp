//
// Created by zwsd
//

#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "zwtimecpp/core/base/base_event.hpp"
#include "zwtimecpp/core/utils/better-enums/enum.h"
extern "C" {
#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_parse.h"
#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_struct.h"
}
#include "zwtimecpp/core/exception/base_exception.hpp"
namespace zwsd {
using namespace std;
using namespace core;
class UartProtocolV1ReceivePacket {
  UP_packet_container_t container;

 public:
  UartProtocolV1ReceivePacket(UP_packet_container_t container)
      : container(container) {
  }

  UP_packet_container_t &getContainer() { return container; };

  int getParmeterNum() {
    if (container.basic_packet.packet_type == kReceiptPacket) {
      /* code */
      return container.packet.general_receipt.parameterNum;
    } else if (container.basic_packet.packet_type == kShakeHandPacket) {
      return 0;
    } else if (container.basic_packet.packet_type == kPingPacket) {
      return 0;
    } else if (container.basic_packet.packet_type == kHardwareOperatePacket) {
      return container.packet.hardware_opearte_packet.parameterNum;
    } else if (container.basic_packet.packet_type == kSystemEventReportPacket) {
      return container.packet.system_event_report_packet.parameterNum;
    } else {
      return 0;
    }
    return 0;
  }

  template <typename T>
  T getParameter(int off, T defalutValue) {
    T value = defalutValue;
    if (off + 1 > getParmeterNum() || off + 1 > MAX_SUPPORT_PARAMETER) {
      return value;
    }
    getParameterInternal(value, off);
    return value;
  }

  template <typename T>
  T getParameter(int off) {
    T value;
    if (off + 1 > getParmeterNum() || off + 1 > MAX_SUPPORT_PARAMETER) {
      throw BaseException(
          "UartProtocolV1ReceivePacket parameterNum is overflow");
      return value;
    }
    getParameterInternal(value, off);
    return value;
  }

 private:
  void getParameterInternal(bool &value, int off) {
    value = UPParameter_get_bool(
        container.packet.hardware_opearte_packet.parameters[off]);
  }
  void getParameterInternal(int32_t &value, int off) {
    value = UPParameter_get_int32(
        container.packet.hardware_opearte_packet.parameters[off]);
  }
  void getParameterInternal(float &value, int off) {
    value = UPParameter_get_float(
        container.packet.hardware_opearte_packet.parameters[off]);
  }
  void getParameterInternal(vector<uint8_t> &value, int off) {
    UP_buf_t buf = UPParameter_get_buf(
        container.packet.hardware_opearte_packet.parameters[off]);
    value = vector<uint8_t>(buf.buf, buf.buf + buf.len);
  }
};
}