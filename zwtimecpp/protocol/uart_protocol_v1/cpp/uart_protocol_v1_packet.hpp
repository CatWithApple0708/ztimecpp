//
// Created by zhaohe on 19-10-5.
//

#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <memory>
#include <mutex>
#include <set>
#include <sstream>
#include <string>
#include <vector>
extern "C" {
#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_packet.h"
}

namespace zwsd {
using namespace std;
/**
 * @brief 串口协议，硬件操作包
 */
class UartProtocolV1Packet {
 public:
  UP_parameters_container_t paramterContainer;
  UPPacketConfig_basic_packet_t basicPacket;
  UPPacketConfig_t config;
  vector<uint8_t> buf;

  UartProtocolV1Packet() {}

 public:

  /**
   * @brief Create a Shake Hand Packet object
   *
   * @param serial_num
   * @return shared_ptr<UartProtocolV1Packet>
   */
  static shared_ptr<UartProtocolV1Packet> createShakeHandPacket(
      uint8_t serial_num,uint8_t route) {
    shared_ptr<UartProtocolV1Packet> packet(new UartProtocolV1Packet());
    packet->config.shakehand_packet = UPShakeHandPacket_construct_config();
    return UP_construct_packet_wappter(packet, serial_num, route,
                                       kShakeHandPacket);
  }
  /**
   * @brief Create a Ping Packet object
   *
   * @param serial_num
   * @return shared_ptr<UartProtocolV1Packet>
   */
  static shared_ptr<UartProtocolV1Packet> createPingPacket(uint16_t serial_num,
                                                           uint8_t route) {
    shared_ptr<UartProtocolV1Packet> packet(new UartProtocolV1Packet());
    packet->config.ping_packet = UPPingPacket_construct_config();
    return UP_construct_packet_wappter(packet, serial_num, route, kPingPacket);
  }

  /**
   * @brief Create a Receipt object　构造回执包
   *
   * @tparam T
   * @param serial_num
   * @param order_serial_num
   * @param error_code
   * @param args
   * @return shared_ptr<UartProtocolV1Packet>
   */
  template <class... T>
  static shared_ptr<UartProtocolV1Packet> createReceipt(
      uint16_t serial_num, uint8_t route, UP_error_code_t error_code,
      T... args) {
    shared_ptr<UartProtocolV1Packet> packet(new UartProtocolV1Packet());
    UPParametersContainer_initialize(&packet->paramterContainer);
    UPParametersContainer_push_value_wappter(&packet->paramterContainer,
                                             args...);
    packet->config.general_receipt_packet =
        UPGeneralReceiptPacket_construct_config(error_code,
                                                &packet->paramterContainer);
    return UP_construct_packet_wappter(packet, serial_num, route,
                                       kReceiptPacket);
  }
  /**
   * @brief Create a Hardware Operate Packet object 构造硬件操作包
   *
   * @tparam T
   * @param serial_num
   * @param moduleType
   * @param moduleNum
   * @param operate_code
   * @param dataPoint
   * @param args
   * @return shared_ptr<UartProtocolV1Packet>
   */
  template <class... T>
  static shared_ptr<UartProtocolV1Packet> createHardwareOperatePacket(
      uint16_t serial_num, uint8_t route, UP_module_type_code_t moduleType,
      uint8_t moduleNum, UP_operate_code_t operate_code, uint16_t dataPoint,
      T... args) {
    shared_ptr<UartProtocolV1Packet> packet(new UartProtocolV1Packet());
    UPParametersContainer_initialize(&packet->paramterContainer);
    UPParametersContainer_push_value_wappter(&packet->paramterContainer,
                                             args...);
    packet->config.hardware_operate_packet =
        UPHardwareOperatePacket_construct_config(moduleType, moduleNum,
                                                 operate_code, dataPoint,
                                                 &packet->paramterContainer);
    return UP_construct_packet_wappter(packet, serial_num, route,
                                       kHardwareOperatePacket);
  }

  template <class... T>
  static shared_ptr<UartProtocolV1Packet> createSystemEventPacket(
      uint16_t serial_num, uint8_t route, UP_GenernalSystemEvent_t event,
      T... args) {
    shared_ptr<UartProtocolV1Packet> packet(new UartProtocolV1Packet());
    UPParametersContainer_initialize(&packet->paramterContainer);
    UPParametersContainer_push_value_wappter(&packet->paramterContainer,
                                             args...);
    packet->config.genernal_system_report_packet =
        UPGenernalSystemReportPacket_construct_config(
            event, &packet->paramterContainer);
    return UP_construct_packet_wappter(packet, serial_num, route,
                                       kSystemEventReportPacket);
  }

  /**
   * @brief 辅助构造参数列表方法
   *
   * @tparam T
   * @tparam Targs
   * @param container
   * @param value
   * @param values
   */
  template <typename T, typename... Targs>
  static void UPParametersContainer_push_value_wappter(
      UP_parameters_container_t* container, T value, Targs... values) {
    if (container) {
      UPParametersContainer_push_value_wappter(container, value);
      UPParametersContainer_push_value_wappter(container, values...);
    }
  }

 private:
  static shared_ptr<UartProtocolV1Packet> UP_construct_packet_wappter(
      shared_ptr<UartProtocolV1Packet>& packet, uint16_t serial_num,
      uint8_t route, PacketType_t type) {
    packet->basicPacket =
        UPBasicPacketConfig_construct_route(serial_num, route, type);
    uint8_t pbuf[MAX_SUPPORT_PACKET_LENGTH];
    UP_buf_t buf = UP_construct_packet2(packet->basicPacket, packet->config,
                                        pbuf, ARRARY_SIZE(pbuf));
    if (buf.buf == nullptr) return nullptr;
    packet->buf = vector<uint8_t>(buf.buf, buf.buf + buf.len);
    return packet;
  }

  static void UPParametersContainer_push_value_wappter(
      UP_parameters_container_t* container){};
  static void UPParametersContainer_push_value_wappter(
      UP_parameters_container_t* container, int32_t value) {
    UPParametersContainer_push_int32(container, value);
  }
  static void UPParametersContainer_push_value_wappter(
      UP_parameters_container_t* container, vector<int32_t> value) {
    for (auto& var : value) UPParametersContainer_push_int32(container, var);
  }
  static void UPParametersContainer_push_value_wappter(
      UP_parameters_container_t* container, bool value) {
    UPParametersContainer_push_bool(container, value);
  }
  static void UPParametersContainer_push_value_wappter(
      UP_parameters_container_t* container, vector<uint8_t>& value) {
    UPParametersContainer_push_buf(container, value.data(), value.size());
  }
};
}
