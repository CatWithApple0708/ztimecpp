//
// Created by zhaohe on 19-10-16.
//

#include "logger_helper.hpp"
#include "zwtimecpp/core/utils/string_utils.hpp"
using namespace std;
using namespace zwsd;
using namespace core;

#define LOG_PACKET(value) \
  logger->log(lev, "* packet {}: {}", #value, basicPacket->value);

#define LOG_SUB_PACKET(value) \
  logger->log(lev, "* subpacket {}: {}", #value, subPacket->value);

#define LOG_PARAMETER()                                                        \
  for (int i = 0; i < subPacket->parameterNum; i++) {                          \
    UP_buf_t buf = UPParameter_get_buf(subPacket->parameters[i]);              \
    if (buf.buf == NULL || buf.len > MAX_SUPPORT_PACKET_LENGTH) {              \
      logger->log(lev, "* subpacket {}: error parameter %p %u", "parameter",   \
                  buf.buf, buf.len);                                           \
    } else {                                                                   \
      vector<uint8_t> parameter = vector<uint8_t>(buf.buf, buf.buf + buf.len); \
      logger->log(lev, "* subpacket {}:off {},buf {}{},bool {},int32_t {}",    \
                  "parameter", i, parameter, parameter.size(),                 \
                  UPParameter_get_bool(subPacket->parameters[i]),              \
                  UPParameter_get_int32(subPacket->parameters[i]));            \
    }                                                                          \
  }

void UartProtocolV1LoggerHelper::dump(logger_t logger, level::level_enum lev,
                        UP_packet_container_t* packContainer) {
  if (!logger) return;

  if (packContainer == NULL) {
    logger->log(lev, "* container == {}", "nullptr");
    return;
  }

  if (packContainer->basic_packet.packet_type == kReceiptPacket) {
    UP_general_receipt_t* subPacket = &packContainer->packet.general_receipt;
    UP_basic_packet_t* basicPacket = &packContainer->basic_packet;

    LOG_PACKET(packet_type);
    LOG_PACKET(serial_num);
    LOG_PACKET(packet_length);

    LOG_SUB_PACKET(serial_num);
    LOG_SUB_PACKET(error_code);
    LOG_SUB_PACKET(parameterNum);

    LOG_PARAMETER();
  } else if (packContainer->basic_packet.packet_type == kShakeHandPacket) {
    UP_shake_hand_packet_t* subPacket =
        &packContainer->packet.shake_hand_packet;
    UP_basic_packet_t* basicPacket = &packContainer->basic_packet;

    LOG_PACKET(packet_type);
    LOG_PACKET(serial_num);
    LOG_PACKET(packet_length);
    // LOG_SUB_PACKET(serial_num);
    // LOG_SUB_PACKET(error_code);
  } else if (packContainer->basic_packet.packet_type == kPingPacket) {
    UP_ping_packet_t* subPacket = &packContainer->packet.ping_packet;
    UP_basic_packet_t* basicPacket = &packContainer->basic_packet;

    LOG_PACKET(packet_type);
    LOG_PACKET(serial_num);
    LOG_PACKET(packet_length);

  } else if (packContainer->basic_packet.packet_type ==
             kHardwareOperatePacket) {
    UP_hardware_operat_packet_t* subPacket =
        &packContainer->packet.hardware_opearte_packet;
    UP_basic_packet_t* basicPacket = &packContainer->basic_packet;

    LOG_PACKET(packet_type);
    LOG_PACKET(serial_num);
    LOG_PACKET(packet_length);

    LOG_SUB_PACKET(module_type);
    LOG_SUB_PACKET(operate_code);
    LOG_SUB_PACKET(module_num);
    LOG_SUB_PACKET(data_point);
    LOG_SUB_PACKET(parameterNum);

    LOG_PARAMETER();
  } else if (packContainer->basic_packet.packet_type ==
             kSystemEventReportPacket) {
    UP_system_event_report_packet_t* subPacket =
        &packContainer->packet.system_event_report_packet;
    UP_basic_packet_t* basicPacket = &packContainer->basic_packet;

    LOG_PACKET(packet_type);
    LOG_PACKET(serial_num);
    LOG_PACKET(packet_length);

    LOG_SUB_PACKET(event);
    LOG_SUB_PACKET(parameterNum);

    LOG_PARAMETER();
  } else {
    UP_basic_packet_t* basicPacket = &packContainer->basic_packet;
    LOG_PACKET(packet_type);
    LOG_PACKET(serial_num);
    LOG_PACKET(packet_length);
  }
  vector<uint8_t> buf(packContainer->raw_data,
                      packContainer->raw_data + packContainer->useful_size);
  logger->log(lev, "* receive : {}", StringUtils::bytesToString(buf));

  return;
}

#define LOG_BASIC_PACKET_CONFIG(value) \
  logger->log(lev, "* packet {}: {}", #value, basicPacket->value);

#define LOG_SUB_PACKET_CONFIG(value) \
  logger->log(lev, "* subpacket {}: {}", #value, subPacket->value);

#define LOG_SUB_PACKET_CONFIG_DATAPOINT() \
  logger->log(lev, "* subpacket {}: {:#04x}", "dataPoint", subPacket->dataPoint);

#define LOG_SUB_PACKET_PARAMETER()                                             \
  if (subPacket->parameter_container &&                                        \
      subPacket->parameter_container->parameters) {                            \
    std::vector<uint8_t> buf(subPacket->parameter_container->parameters,       \
                             subPacket->parameter_container->parameters +      \
                                 subPacket->parameter_container->useful_size); \
    logger->log(lev, "* subpacket {}: {}", "parameter_container raw value",    \
                buf);                                                          \
  } else {                                                                     \
    logger->log(lev, "* subpacket {}: {}", "parameter_container", "nullptr");  \
  }

#define LOG_SUB_PACKET_BUF() \
  { logger->log(lev, "* bin : {}", StringUtils::bytesToString(packet->buf)); }

void UartProtocolV1LoggerHelper::dump(logger_t logger, level::level_enum lev,
                        shared_ptr<UartProtocolV1Packet> packet) {
  if (logger->level() > lev) {
    return;
  }
                          
  if (!logger) return;

  if (!packet) {
    logger->log(lev, "* container == {}", "nullptr");
    return;
  }

  if (packet->basicPacket.type == kReceiptPacket) {
    UPPacketConfig_basic_packet_t* basicPacket = &packet->basicPacket;
    UPPacketConfig_general_receipt_packet_t* subPacket =
        &packet->config.general_receipt_packet;
    LOG_BASIC_PACKET_CONFIG(serial_num)
    LOG_BASIC_PACKET_CONFIG(route)
    LOG_BASIC_PACKET_CONFIG(type)
    LOG_SUB_PACKET_CONFIG(serial_num);
    LOG_SUB_PACKET_CONFIG(error_code);
    LOG_SUB_PACKET_PARAMETER();
  } else if (packet->basicPacket.type == kShakeHandPacket) {
    UPPacketConfig_basic_packet_t* basicPacket = &packet->basicPacket;
    UPPacketConfig_shakehand_packet_t* subPacket =
        &packet->config.shakehand_packet;

    LOG_BASIC_PACKET_CONFIG(serial_num)
    LOG_BASIC_PACKET_CONFIG(route)
    LOG_BASIC_PACKET_CONFIG(type)

  } else if (packet->basicPacket.type == kPingPacket) {
    UPPacketConfig_basic_packet_t* basicPacket = &packet->basicPacket;
    UPPacketConfig_ping_packet_t* subPacket = &packet->config.ping_packet;

    LOG_BASIC_PACKET_CONFIG(serial_num)
    LOG_BASIC_PACKET_CONFIG(route)
    LOG_BASIC_PACKET_CONFIG(type)

  } else if (packet->basicPacket.type == kHardwareOperatePacket) {
    UPPacketConfig_basic_packet_t* basicPacket = &packet->basicPacket;
    UPPacketConfig_hardware_operate_packet_t* subPacket =
        &packet->config.hardware_operate_packet;

    LOG_BASIC_PACKET_CONFIG(serial_num)
    LOG_BASIC_PACKET_CONFIG(route)
    LOG_BASIC_PACKET_CONFIG(type)

    LOG_SUB_PACKET_CONFIG(moduleType)
    LOG_SUB_PACKET_CONFIG(moduleNum)
    LOG_SUB_PACKET_CONFIG(operate_code)
    LOG_SUB_PACKET_CONFIG_DATAPOINT()
    LOG_SUB_PACKET_PARAMETER();

  } else if (packet->basicPacket.type == kSystemEventReportPacket) {
    UPPacketConfig_basic_packet_t* basicPacket = &packet->basicPacket;
    UPPacketConfig_genernal_system_report_packet_t* subPacket =
        &packet->config.genernal_system_report_packet;
    LOG_BASIC_PACKET_CONFIG(serial_num)
    LOG_BASIC_PACKET_CONFIG(route)
    LOG_BASIC_PACKET_CONFIG(type)
    LOG_SUB_PACKET_CONFIG(event)
    LOG_SUB_PACKET_PARAMETER();
  } else {
    UPPacketConfig_basic_packet_t* basicPacket = &packet->basicPacket;
    LOG_BASIC_PACKET_CONFIG(serial_num)
    LOG_BASIC_PACKET_CONFIG(route)
    LOG_BASIC_PACKET_CONFIG(type)
  }
  LOG_SUB_PACKET_BUF();
}