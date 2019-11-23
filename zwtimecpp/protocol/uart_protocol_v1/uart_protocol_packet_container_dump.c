#include "uart_protocol_packet_container_dump.h"

#define MAX_PRINT_LINE (20)
#define SPRINTF(fmt, ...)                                                     \
  {                                                                           \
    snprintf(&buf[line_num][0], ARRARY_SIZE(buf[0]) - 1, fmt, ##__VA_ARGS__); \
    if (line_num < MAX_PRINT_LINE) line_num++;                                \
  }

char** up_packet_container_dump(UP_packet_container_t* container,
                                int* str_size) {
  static char buf[MAX_PRINT_LINE][128] = {{0}};
  static char* retbuf[MAX_PRINT_LINE + 1] = {NULL};

  if (container == NULL) {
    *str_size = 1;
    retbuf[0] = "container is null";
    retbuf[1] = NULL;
    return retbuf;
  }
  UP_basic_packet_t* basicPacket = &container->basic_packet;
  int line_num = 0;

  SPRINTF("* packet_type: %s", PacketType_to_str(basicPacket->packet_type));
  SPRINTF("* serial_num: %d", basicPacket->serial_num);
  SPRINTF("* route: %d", basicPacket->route);
  SPRINTF("* packet_length: %d", basicPacket->packet_length);

  int parameterNum = 0;
  UP_parameter_packet_t* parameter_packet = NULL;

  if (container->basic_packet.packet_type == kReceiptPacket) {
    UP_general_receipt_t* subPacket = &container->packet.general_receipt;
    SPRINTF("*  error_code: %s", ErrorCode_to_str(subPacket->error_code));

    parameter_packet = subPacket->parameters;
    parameterNum = subPacket->parameterNum;

  } else if (container->basic_packet.packet_type == kShakeHandPacket) {
    //UP_shake_hand_packet_t* subPacket = &container->packet.shake_hand_packet;

  } else if (container->basic_packet.packet_type == kPingPacket) {
    //UP_ping_packet_t* subPacket = &container->packet.ping_packet;

  } else if (container->basic_packet.packet_type == kHardwareOperatePacket) {
    UP_hardware_operat_packet_t* subPacket =
        &container->packet.hardware_opearte_packet;

    SPRINTF("*  module_type: %s", ModuleType_to_str(subPacket->module_type));
    SPRINTF("*  operate_code: %s", OperateCode_to_str(subPacket->operate_code));
    SPRINTF("*  module_num: %d", subPacket->module_num);
    SPRINTF("*  data_point: 0x%x", subPacket->data_point);

    parameter_packet = subPacket->parameters;
    parameterNum = subPacket->parameterNum;

  } else if (container->basic_packet.packet_type == kSystemEventReportPacket) {
    UP_system_event_report_packet_t* subPacket =
        &container->packet.system_event_report_packet;
    SPRINTF("*  event: %s", GenernalSystemEvent_to_str(subPacket->event));

    parameter_packet = subPacket->parameters;
    parameterNum = subPacket->parameterNum;

  } else {
  }

  if (parameter_packet) {
    for (int i = 0; i < parameterNum; i++) {
      SPRINTF("*  parameter[%d]: asInt32 %d", i,
              UPParameter_get_int32(parameter_packet[i]));
    }
  }

  *str_size = line_num;
  for (int i = 0; i < line_num; i++) {
    retbuf[i] = buf[i];
    retbuf[i + 1] = NULL;
  }
  return retbuf;
}
char* up_packet_container_dump_in_one_line(UP_packet_container_t* container) {
  static char buf[100] = {0};
  if (!container) return "container is null";

  UP_basic_packet_t* basicPacket = &container->basic_packet;
  if (container->basic_packet.packet_type == kReceiptPacket) {
    //UP_general_receipt_t* subPacket = &container->packet.general_receipt;
    snprintf(&buf[0], ARRARY_SIZE(buf) - 1, "%s|seq:%d,r:%d|",
             PacketType_to_str(basicPacket->packet_type),
             basicPacket->serial_num, basicPacket->route);

  } else if (container->basic_packet.packet_type == kShakeHandPacket) {
    //UP_shake_hand_packet_t* subPacket = &container->packet.shake_hand_packet;
    snprintf(&buf[0], ARRARY_SIZE(buf) - 1, "%s|seq:%d,r:%d|",
             PacketType_to_str(basicPacket->packet_type),
             basicPacket->serial_num, basicPacket->route);

  } else if (container->basic_packet.packet_type == kPingPacket) {
    //UP_ping_packet_t* subPacket = &container->packet.ping_packet;
    snprintf(&buf[0], ARRARY_SIZE(buf) - 1, "%s|seq:%d,r:%d|",
             PacketType_to_str(basicPacket->packet_type),
             basicPacket->serial_num, basicPacket->route);

  } else if (container->basic_packet.packet_type == kHardwareOperatePacket) {
    UP_hardware_operat_packet_t* subPacket =
        &container->packet.hardware_opearte_packet;
    if (subPacket->parameterNum == 0) {
      snprintf(&buf[0], ARRARY_SIZE(buf) - 1,
               "%s|seq:%d,r:%d|"
               "mt:%s,mn:%d,dp:0x%x,pn:%d|",
               PacketType_to_str(basicPacket->packet_type),  //
               basicPacket->serial_num,                      //
               basicPacket->route,                           //
               ModuleType_to_str(subPacket->module_type),    //
               subPacket->module_num,                        //
               subPacket->data_point,                        //
               subPacket->parameterNum                       //
               );
    } else  {
      snprintf(&buf[0], ARRARY_SIZE(buf) - 1,
               "%s|seq:%d,r:%d|"
               "mt:%s,mn:%d,dp:0x%x,pn:%d,p1:%d|",
               PacketType_to_str(basicPacket->packet_type),  //
               basicPacket->serial_num,                      //
               basicPacket->route,                           //
               ModuleType_to_str(subPacket->module_type),    //
               subPacket->module_num,                        //
               subPacket->data_point,                        //
               subPacket->parameterNum,                      //
               UPParameter_get_int32(subPacket->parameters[0]));
    }

  } else if (container->basic_packet.packet_type == kSystemEventReportPacket) {
    //UP_system_event_report_packet_t* subPacket =
      //  &container->packet.system_event_report_packet;
    snprintf(&buf[0], ARRARY_SIZE(buf) - 1, "%s|seq:%d,r:%d|",
             PacketType_to_str(basicPacket->packet_type),
             basicPacket->serial_num, basicPacket->route);
  } else {
  }
  return buf;
}
