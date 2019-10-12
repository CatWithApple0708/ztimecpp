//
// Created by zhaohe on 19-10-4.
//

#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_packet.h"
#include <string.h>
#include "zwtimecpp/core/utils/cutils/marco_utils.h"
#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_packet_struct_internal.h"

static UP_parameters_container_t container;
UP_parameters_container_t* UPParametersContainer_get() {
  container.useful_size = 0;
  return &container;
}

bool UPParametersContainer_push_int32(UP_parameters_container_t* container,
                                      int32_t value) {
  if (ARRARY_SIZE(container->parameters) <
      container->useful_size + sizeof(int32_t) + UP_EACH_PARAMETR_MIN_SIZE) {
    return false;
  }
  uint8_t* begin = &container->parameters[container->useful_size];
  uint32_t absolute_value = value > 0 ? value : -value;

  //设置长度
  begin[0] = (sizeof(int32_t) >> 8) & 0xff;
  begin[1] = (sizeof(int32_t) >> 0) & 0xff;

  //设置数据数值
  begin[2] = (absolute_value >> 24) & 0xff;
  begin[3] = (absolute_value >> 16) & 0xff;
  begin[4] = (absolute_value >> 8) & 0xff;
  begin[5] = (absolute_value >> 0) & 0xff;

  //设置符号位
  if (value < 0) {
    begin[2] = begin[2] | (0x01 << 8);
  }
  container->useful_size =
      container->useful_size + sizeof(int32_t) + UP_EACH_PARAMETR_MIN_SIZE;
  return true;
}
bool UPParametersContainer_push_bool(UP_parameters_container_t* container,
                                     bool value) {
  if (ARRARY_SIZE(container->parameters) <
      container->useful_size + 1 /*bool*/ + UP_EACH_PARAMETR_MIN_SIZE) {
    return false;
  }
  uint8_t* begin = &container->parameters[container->useful_size];

  //设置长度
  begin[0] = (1 >> 8) & 0xff;
  begin[1] = (1 >> 0) & 0xff;

  //设置数据数值
  begin[2] = 1;
  container->useful_size =
      container->useful_size + 1 + UP_EACH_PARAMETR_MIN_SIZE;

  return true;
}
bool UPParametersContainer_push_buf(UP_parameters_container_t* container,
                                    uint8_t* buf, uint16_t length) {
  if (ARRARY_SIZE(container->parameters) <
      container->useful_size + length /*bool*/ + UP_EACH_PARAMETR_MIN_SIZE) {
    return false;
  }
  uint8_t* begin = &container->parameters[container->useful_size];

  //设置长度
  begin[0] = (length >> 8) & 0xff;
  begin[1] = (length >> 0) & 0xff;

  //设置数据数值
  memcpy(&begin[2], buf, length);
  container->useful_size =
      container->useful_size + length + UP_EACH_PARAMETR_MIN_SIZE;
  return true;
}

UPPacketConfig_basic_packet_t UPBasicPacketConfig_construct(uint16_t serial_num,
                                                            PacketType_t type) {
  UPPacketConfig_basic_packet_t packet = {0};
  packet.serial_num = serial_num;
  packet.type = type;
  return packet;
}
UPPacketConfig_shakehand_packet_t UPShakeHandPacket_construct_config() {
  UPPacketConfig_shakehand_packet_t packet = {0};
  return packet;
}
UPPacketConfig_ping_packet_t UPPingPacket_construct_config() {
  UPPacketConfig_ping_packet_t packet = {0};
  return packet;
}

UPPacketConfig_hardware_operate_packet_t
UPHardwareOperatePacket_construct_config(
    UP_module_type_code_t moduleType, uint8_t moduleNum,
    UP_operate_code_t operate_code, uint16_t dataPoint,
    UP_parameters_container_t* parameter_container) {
  UPPacketConfig_hardware_operate_packet_t packet;
  memset(&packet, 0, sizeof(UPPacketConfig_hardware_operate_packet_t));

  packet.moduleType = moduleType;
  packet.moduleNum = moduleNum;
  packet.operate_code = operate_code;
  packet.dataPoint = dataPoint;
  packet.parameter_container = parameter_container;
  return packet;
}

UPPacketConfig_genernal_system_report_packet_t
UPGenernalSystemReportPacket_construct_config(
    UP_GenernalSystemEvent_t event,
    UP_parameters_container_t* parameter_container) {
  UPPacketConfig_genernal_system_report_packet_t packet;
  memset(&packet, 0, sizeof(UPPacketConfig_genernal_system_report_packet_t));
  packet.event = event;
  packet.parameter_container = parameter_container;
  return packet;
}

UPPacketConfig_general_receipt_packet_t UPGeneralReceiptPacket_construct_config(
    uint8_t serial_num, UP_error_code_t error_code,
    UP_parameters_container_t* parameter_container) {
  UPPacketConfig_general_receipt_packet_t packet = {0};
  packet.serial_num = serial_num;
  packet.error_code = error_code;
  packet.parameter_container = parameter_container;
  return packet;
}
UP_buf_t UP_construct_packet2(UPPacketConfig_basic_packet_t basic_packt,
                              UPPacketConfig_t packet_config,
                              uint8_t* packet_buf, size_t length) {
  UP_buf_t buf;
  buf.buf = NULL;
  buf.len = 0;

  UPAnalysis_basic_packet_header_t* header =
      (UPAnalysis_basic_packet_header_t*)&packet_buf[0];

  header->header[0] = HEADER_FIRST;
  header->header[1] = HEADER_SECOND;
  header->serial_num = basic_packt.serial_num;
  header->packet_type = (uint8_t)basic_packt.type;
  //包的长度最后计算赋值

  uint16_t packetLength = 0;
  if (length < sizeof(UPAnalysis_basic_packet_header_t) -
                   sizeof(UPAnalysis_basic_packet_tail_t)) {
    return buf;
  }
  uint16_t remainLength = length - sizeof(UPAnalysis_basic_packet_header_t) -
                          sizeof(UPAnalysis_basic_packet_tail_t);
  /**
   * @brief kReceiptPacket
   *
   */
  if (basic_packt.type == kReceiptPacket) {
    UPAnalysis_genernal_receipt_packet_header_t* sub_packet_header =
        (UPAnalysis_genernal_receipt_packet_header_t*)header->packet;
    UP_parameters_container_t* parameter_container =
        packet_config.general_receipt_packet.parameter_container;

    uint16_t parameter_length = 0;
    if (parameter_container != NULL) {
      parameter_length = parameter_container->useful_size;
    }
    //检查缓冲区长度
    packetLength =
        sizeof(UPAnalysis_genernal_receipt_packet_header_t) + parameter_length;

    if (packetLength > remainLength) {
      return buf;
    }

    sub_packet_header->error_code =
        (uint8_t)packet_config.general_receipt_packet.error_code;
    sub_packet_header->serial_num =
        (uint8_t)packet_config.general_receipt_packet.serial_num;

    if (parameter_container != NULL) {
      memcpy(sub_packet_header->parameter, parameter_container->parameters,
             parameter_container->useful_size);
    }
  }
  /**
   * @brief kShakeHandPacket
   *
   */
  else if (basic_packt.type == kShakeHandPacket) {
    UPAnalysis_shake_hand_packet_header_t* sub_packet_header =
        (UPAnalysis_shake_hand_packet_header_t*)header->packet;
    //检查缓冲区长度
    packetLength = sizeof(UPAnalysis_shake_hand_packet_header_t);
    if (packetLength > remainLength) {
      return buf;
    }

    sub_packet_header->pad = 0;

  }
  /**
   * @brief kPingPacket
   *
   */
  else if (basic_packt.type == kPingPacket) {
    UPAnalysis_ping_packet_header_t* sub_packet_header =
        (UPAnalysis_ping_packet_header_t*)header->packet;
    //检查缓冲区长度
    packetLength = sizeof(UPAnalysis_ping_packet_header_t);
    if (packetLength > remainLength) {
      return buf;
    }

    sub_packet_header->pad = 0;
  }
  /**
   * @brief kHardwareOperatePacket
   *
   */
  else if (basic_packt.type == kHardwareOperatePacket) {
    UPAnalysis_hardware_operate_packet_header_t* sub_packet_header =
        (UPAnalysis_hardware_operate_packet_header_t*)header->packet;

    UP_parameters_container_t* parameter_container =
        packet_config.hardware_operate_packet.parameter_container;

    uint16_t parameter_length = 0;
    if (parameter_container != NULL) {
      parameter_length = parameter_container->useful_size;
    }

    //检查缓冲区长度
    packetLength =
        sizeof(UPAnalysis_hardware_operate_packet_header_t) + parameter_length;
    if (packetLength > remainLength) {
      return buf;
    }

    sub_packet_header->module_type[0] =
        HIGH_UINT16(packet_config.hardware_operate_packet.moduleType);
    sub_packet_header->module_type[1] =
        LOW_UINT16(packet_config.hardware_operate_packet.moduleType);

    sub_packet_header->module_num =
        packet_config.hardware_operate_packet.moduleNum;

    sub_packet_header->data_point[0] =
        HIGH_UINT16(packet_config.hardware_operate_packet.dataPoint);
    sub_packet_header->data_point[1] =
        LOW_UINT16(packet_config.hardware_operate_packet.dataPoint);

    sub_packet_header->operate_code =
        (uint8_t)packet_config.hardware_operate_packet.operate_code;

    if (parameter_container != NULL) {
      memcpy(sub_packet_header->parameter, parameter_container->parameters,
             parameter_container->useful_size);
    }
  }
  /**
   * @brief kSystemEventReportPacket
   *
   */
  else if (basic_packt.type == kSystemEventReportPacket) {
    UPAnalysis_system_event_report_packet_t* sub_packet_header =
        (UPAnalysis_system_event_report_packet_t*)header->packet;

    UP_parameters_container_t* parameter_container =
        packet_config.genernal_system_report_packet.parameter_container;

    uint16_t parameter_length = 0;
    if (parameter_container != NULL) {
      parameter_length = parameter_container->useful_size;
    }

    //检查缓冲区长度
    packetLength =
        sizeof(UPAnalysis_system_event_report_packet_t) + parameter_length;
    if (packetLength > remainLength) {
      return buf;
    }

    sub_packet_header->system_event_type[0] =
        HIGH_UINT16(packet_config.genernal_system_report_packet.event);
    sub_packet_header->system_event_type[1] =
        LOW_UINT16(packet_config.genernal_system_report_packet.event);

    if (parameter_container != NULL) {
      memcpy(sub_packet_header->parameter, parameter_container->parameters,
             parameter_container->useful_size);
    }
  }
  /**
   * @brief kSystemEventReportPacket
   *
   */
  else {
    return buf;
  }

  buf.buf = packet_buf;
  buf.len = packetLength + sizeof(UPAnalysis_basic_packet_header_t) +
            sizeof(UPAnalysis_basic_packet_tail_t);

  return buf;
}

/**
 * @brief 构造消息
 *
 * @param basic_packt
 * @param packet_config
 * @return UP_buf_t
 */
UP_buf_t UP_construct_packet(UPPacketConfig_basic_packet_t basic_packt,
                             UPPacketConfig_t packet_config) {
  static uint8_t buf[MAX_SUPPORT_PACKET_LENGTH];
  return UP_construct_packet2(basic_packt, packet_config, buf,
                              ARRARY_SIZE(buf));
}