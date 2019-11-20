//
// Created by zhaohe on 19-10-4.
//

#include "uart_protocol_parse.h"
#include <string.h>
#include "zwtimecpp/core/utils/cutils/marco_utils.h"
#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_packet_struct_internal.h"

void uart_protocol_handler_init(uart_protocol_handler_t* handler) {
  loop_queue_init_u8(&handler->receiveq, handler->receiveqbuf,
                     ARRARY_SIZE(handler->receiveqbuf));
  handler->usefullSize = 0;
}

UPProcessPushRawDataRet_t UP_process_push_raw_data(
    uart_protocol_handler_t* handler, const uint8_t* buf, size_t size) {
  UPProcessPushRawDataRet_t ret;
  bool success = loop_queue_push_some_u8(&handler->receiveq, buf, size);
  if (success == false) {
    ret.success = false;
    ret.error_code = kErrorCode_receivePacketOverflow;
    ret.shouldProcessRawDataNow = true;
    return ret;
  }

  ret.success = true;
  ret.error_code = kErrorCode_Success;
  for (size_t i = 0; i < size; i++) {
    if (buf[i] == TAIL) {
      ret.shouldProcessRawDataNow = true;
    }
  }
  return ret;
}
static void sUP_process_raw_data_internal(uart_protocol_handler_t* handler,
                                  UP_packet_container_cb_t on_container) {
  int beginProcessOff = 0;
  while (true) {
    //找到包头
    UPAnalysis_basic_packet_header_t* packet_header = NULL;
    bool findHeader = false;
    if (handler->usefullSize - beginProcessOff <
        sizeof(UPAnalysis_basic_packet_header_t)) {
      break;
    }

    for (size_t i = beginProcessOff;
         i + sizeof(UPAnalysis_basic_packet_header_t) < handler->usefullSize;
         i++) {
      packet_header =
          (UPAnalysis_basic_packet_header_t*)&handler->processbuf[i];
      if (packet_header->header[0] == HEADER_FIRST &&
          packet_header->header[1] == HEADER_SECOND) {
        beginProcessOff = i;
        findHeader = true;
        break;
      }
      beginProcessOff = i;
    }
    if (!findHeader) {
      break;
    }

    int remainUsefulDataSize = handler->usefullSize - beginProcessOff;
    if (remainUsefulDataSize >= sizeof(UPAnalysis_basic_packet_header_t)) {
      size_t internalPacketLength =
          UPIBasicPacketHeader_get_packet_length(packet_header);
      size_t totalLength = sizeof(UPAnalysis_basic_packet_header_t) +
                           internalPacketLength + 1 /*tail*/;
      size_t tailOff = beginProcessOff +
                       sizeof(UPAnalysis_basic_packet_header_t) +
                       internalPacketLength;

      //情况一，完整的包
      if (remainUsefulDataSize >= totalLength &&
          handler->processbuf[tailOff] == TAIL) {
        UP_packet_process_ret_t process_ret = UPPacketContainer_construct(
            &handler->container, (uint8_t*)packet_header, totalLength);
        if (process_ret.error_code == kErrorCode_Success) {
          on_container(handler, process_ret, &handler->container);
          beginProcessOff += totalLength;
        } else {
          on_container(handler, process_ret, NULL);
          beginProcessOff += 1;
        }
      }
      //情况二，包的长度过长
      else if (totalLength > UPPacketContainer_get_packet_max_size()) {
        UP_packet_process_ret_t process_ret = {
            .receive_packet_serial_num = 0xff,
            .error_code = kErrorCode_packetIsTooLong};
        on_container(handler, process_ret, NULL);
        beginProcessOff += 1;
      }
      //情况三，没有找到包尾部
      else if (remainUsefulDataSize >= totalLength &&
               handler->processbuf[tailOff] != TAIL) {
        beginProcessOff += 1;
      }
      else {
        //情况四，缓冲区数据不够
        break;
      }
    }
  }
  //移除处理过的数据
  memmove(handler->processbuf, handler->processbuf + beginProcessOff,
          handler->usefullSize - beginProcessOff);
  handler->usefullSize = handler->usefullSize - beginProcessOff;

  //逻辑不应该运行到此处,此处仅是为了保证逻辑的正确性
  if (handler->usefullSize >= ARRARY_SIZE(handler->processbuf)) {
    handler->usefullSize = 0;
  }
}
void UP_process_raw_data(uart_protocol_handler_t* handler,
                         UP_packet_container_cb_t on_container) {
  /*TODO: */
  //处理包的buffer必须大于一个完整的包
  BUILD_ASSERT(ARRARY_SIZE(handler->processbuf) >= MAX_SUPPORT_PACKET_LENGTH);
  BUILD_ASSERT(ARRARY_SIZE(handler->processbuf) >=
               (UPPacketContainer_get_packet_max_size()));

  if (on_container == NULL) {
    loop_queue_clear_u8(&handler->receiveq);
    handler->usefullSize = 0;
    return;
  }

  while (true) {
    //从缓冲buffer中取出适量的数据
    int pop_size = ARRARY_SIZE(handler->processbuf) - handler->usefullSize;
    int real_pop_size = 0;
    if (pop_size != 0) {
      real_pop_size = loop_queue_pop_some_u8(
          &handler->receiveq, handler->processbuf + handler->usefullSize,
          pop_size);
    }

    if (real_pop_size == 0) {
      break;
    }
    handler->usefullSize += real_pop_size;
    sUP_process_raw_data_internal(handler, on_container);
  }
  return;
}

/**
 * @brief
 */
static int sUPPacketContainerConstruct_parse_parameter(
    uint8_t* paramter, size_t length, UP_parameter_packet_t* paramter_table,
    size_t paramter_table_size) {
  if (length == 0) {
    return 0;
  }
  uint16_t cur_para_off = 0;
  int parameter_num = 0;

  for (size_t i = 0; i < length; i++) {
    if (cur_para_off + sizeof(uint16_t) > length - 1) {
      break;
    }
    if (i >= paramter_table_size) {
      break;
    }
    uint8_t* cur_parameter_begin = &paramter[cur_para_off];
    uint16_t parameter_size = BIG_ENGINE_UINT8S_TO_UINT16(
        cur_parameter_begin[0], cur_parameter_begin[1]);
    paramter_table[i].buf = &cur_parameter_begin[2];
    paramter_table[i].length = parameter_size;
    parameter_num += 1;
    cur_para_off += sizeof(uint16_t) + parameter_size;
  }
  return parameter_num;
};

void sUPPacketContainerConstruct_assign_basic_packet(
    UP_basic_packet_t* basic_packet, UPAnalysis_basic_packet_header_t* header) {
  basic_packet->packet_type = (PacketType_t)header->packet_type;
  basic_packet->serial_num = header->serial_num;
  basic_packet->packet_length =
      BIG_ENGINE_UINT8S_TO_UINT16(header->length[0], header->length[1]);
  basic_packet->packet = header->packet;
  basic_packet->route = header->route;
  return;
}

/****************************UP_packet_container_t************************************/
/**
 * @brief 构造　UP_packet_container_t
 *
 * @param container
 * @param packet
 * @param length
 * @return true　 构造成功
 * @return false　构造失败
 */
UP_packet_process_ret_t UPPacketContainer_construct(
    UP_packet_container_t* container, uint8_t* packet, size_t length) {
  UP_packet_process_ret_t ret;
  UPAnalysis_basic_packet_header_t* header =
      (UPAnalysis_basic_packet_header_t*)packet;

  if (ARRARY_SIZE(container->raw_data) < length) {
    ret.error_code = kErrorCode_packetIsTooLong;
    ret.receive_packet_serial_num = header->serial_num;
    return ret;
  }
  memcpy(container->raw_data, packet, length);
  container->useful_size = length;

  /**
   * @brief 解析kReceiptPacket
   *
   */
  if (header->packet_type == kReceiptPacket) {
    UP_basic_packet_t* basic_packet = &container->basic_packet;
    UP_general_receipt_t* general_receipt = &container->packet.general_receipt;

    //为basic_packet赋值
    sUPPacketContainerConstruct_assign_basic_packet(basic_packet, header);

    //为general_receipt赋值
    if (basic_packet->packet_length <
        sizeof(UPAnalysis_genernal_receipt_packet_header_t)) {
      ret.error_code = kErrorCode_packetFormatError;
      ret.receive_packet_serial_num = header->serial_num;
      return ret;
    } else {
      UPAnalysis_genernal_receipt_packet_header_t* analysis_genernal_receipt =
          (UPAnalysis_genernal_receipt_packet_header_t*)basic_packet->packet;

      general_receipt->serial_num = analysis_genernal_receipt->serial_num;
      general_receipt->error_code = analysis_genernal_receipt->error_code;
      //解析参数
      int parameter_length =
          basic_packet->packet_length -
          sizeof(UPAnalysis_genernal_receipt_packet_header_t);

      //为参数赋值
      int parameterNum = sUPPacketContainerConstruct_parse_parameter(
          analysis_genernal_receipt->parameter, parameter_length,
          general_receipt->parameters,
          ARRARY_SIZE(general_receipt->parameters));

      general_receipt->parameterNum = parameterNum;

      ret.error_code = kErrorCode_Success;
      ret.receive_packet_serial_num = basic_packet->serial_num;
      return ret;
    }
  }
  /**
   * @brief kShakeHandPacket
   *
   */
  else if (header->packet_type == kShakeHandPacket) {
    UP_basic_packet_t* basic_packet = &container->basic_packet;
    UP_shake_hand_packet_t* shake_hand_packet =
        &container->packet.shake_hand_packet;
    //为basic_packet赋值
    sUPPacketContainerConstruct_assign_basic_packet(basic_packet, header);
    //为shake_hand_packet赋值
    shake_hand_packet->pad = 0;

    ret.error_code = kErrorCode_Success;
    ret.receive_packet_serial_num = basic_packet->serial_num;
    return ret;
  }

  /**
   * @brief 解析kPingPacket
   *
   */
  else if (header->packet_type == kPingPacket) {
    UP_basic_packet_t* basic_packet = &container->basic_packet;
    UP_ping_packet_t* ping_packet = &container->packet.ping_packet;
    //为basic_packet赋值
    sUPPacketContainerConstruct_assign_basic_packet(basic_packet, header);
    //为shake_hand_packet赋值
    ping_packet->pad = 0;

    ret.error_code = kErrorCode_Success;
    ret.receive_packet_serial_num = basic_packet->serial_num;
    return ret;
  }
  /**
   * @brief 解析kHardwareOperatePacket
   *
   */
  else if (header->packet_type == kHardwareOperatePacket) {
    UP_basic_packet_t* basic_packet = &container->basic_packet;
    UP_hardware_operat_packet_t* hardware_operat_packet =
        &container->packet.hardware_opearte_packet;
    //为basic_packet赋值
    sUPPacketContainerConstruct_assign_basic_packet(basic_packet, header);
    //为shake_hand_packet赋值
    if (basic_packet->packet_length  <
        sizeof(UPAnalysis_hardware_operate_packet_header_t)) {
      ret.error_code = kErrorCode_packetFormatError;
      ret.receive_packet_serial_num = header->serial_num;
      return ret;
    } else {
      UPAnalysis_hardware_operate_packet_header_t* analysis_packet =
          (UPAnalysis_hardware_operate_packet_header_t*)basic_packet->packet;

      hardware_operat_packet->module_num = analysis_packet->module_num;
      hardware_operat_packet->data_point = BIG_ENGINE_UINT8S_TO_UINT16(
          analysis_packet->data_point[0], analysis_packet->data_point[1]);
      hardware_operat_packet->operate_code =
          (UP_operate_code_t)analysis_packet->operate_code;
      hardware_operat_packet->module_type =
          (UP_module_type_code_t)BIG_ENGINE_UINT8S_TO_UINT16(
              analysis_packet->module_type[0], analysis_packet->module_type[1]);
      //解析参数
      int parameter_length =
          basic_packet->packet_length -
          sizeof(UPAnalysis_hardware_operate_packet_header_t);
      int parameterNum = 0;
      if (parameter_length > 0) {
        parameterNum = sUPPacketContainerConstruct_parse_parameter(
            analysis_packet->parameter, parameter_length,
            hardware_operat_packet->parameters,
            ARRARY_SIZE(hardware_operat_packet->parameters));
      }
      //为参数赋值
      hardware_operat_packet->parameterNum = parameterNum;
      ret.error_code = kErrorCode_Success;
      ret.receive_packet_serial_num = basic_packet->serial_num;
      return ret;
    }
  }
  /**
   * @brief 系统事件上报包
   *
   */
  else if (header->packet_type == kSystemEventReportPacket) {
    UP_basic_packet_t* basic_packet = &container->basic_packet;
    UP_system_event_report_packet_t* system_event_report_packet =
        &container->packet.system_event_report_packet;
    //为basic_packet赋值
    sUPPacketContainerConstruct_assign_basic_packet(basic_packet, header);
    //为shake_hand_packet赋值
    if (basic_packet->packet_length <
        sizeof(UPAnalysis_system_event_report_packet_t)) {
      ret.error_code = kErrorCode_packetFormatError;
      ret.receive_packet_serial_num = header->serial_num;
      return ret;
    } else {
      UPAnalysis_system_event_report_packet_t* analysis_packet =
          (UPAnalysis_system_event_report_packet_t*)basic_packet->packet;

      system_event_report_packet->event =
          (UP_GenernalSystemEvent_t)BIG_ENGINE_UINT8S_TO_UINT16(
              analysis_packet->system_event_type[0],
              analysis_packet->system_event_type[1]);

      //解析参数
      int parameter_length = basic_packet->packet_length -
                             sizeof(UPAnalysis_system_event_report_packet_t);

      //为参数赋值
      int parameterNum = sUPPacketContainerConstruct_parse_parameter(
          analysis_packet->parameter, parameter_length,
          system_event_report_packet->parameters,
          ARRARY_SIZE(system_event_report_packet->parameters));

      system_event_report_packet->parameterNum = parameterNum;

      ret.error_code = kErrorCode_Success;
      ret.receive_packet_serial_num = basic_packet->serial_num;
      return ret;
    }
  }
  return ret;
}
/**
 * @brief 根据packet中获取bool值
 *
 * @param packet
 * @return true
 * @return false
 */
bool UPParameter_get_bool(UP_parameter_packet_t packet) {
  for (size_t i = 0; i < packet.length; i++) {
    if (packet.buf[i] > 0) return true;
  }
  return false;
}
#if 0
/**
 * @brief 根据packet获取uint32
 *
 * @param packet
 * @return uint32_t
 */
uint32_t UPParameter_get_uint32(UP_parameter_packet_t packet) {
  if (packet.length == 0) {
    return 0;
  } else if (packet.length == 1) {
    return BIG_ENGINE_UINT8S_TO_UINT32(0, 0, 0, packet.buf[0]);
  } else if (packet.length == 2) {
    return BIG_ENGINE_UINT8S_TO_UINT32(0, 0, packet.buf[0], packet.buf[1]);
  } else if (packet.length == 3) {
    return BIG_ENGINE_UINT8S_TO_UINT32(0, packet.buf[0], packet.buf[1],
                                       packet.buf[2]);
  } else {
    return BIG_ENGINE_UINT8S_TO_UINT32(packet.buf[0], packet.buf[1],
                                       packet.buf[2], packet.buf[3]);
  }
  return 0;
}
#endif
/**
 * @brief 根据packet获取int32
 *
 * @param packet
 * @return uint32_t
 */
int32_t UPParameter_get_int32(UP_parameter_packet_t packet) {
  if (packet.length == 0) {
    return 0;
  }

  bool positive = true;
  if ((packet.buf[0] & (0x01 << 7)) > 0) {
    positive = false;
  } else {
    positive = true;
  }

  int32_t value = 0;
  if (packet.length == 1) {
    value = BIG_ENGINE_UINT8S_TO_UINT32(0, 0, 0, packet.buf[0] & (~0x01 << 7));
  } else if (packet.length == 2) {
    value = BIG_ENGINE_UINT8S_TO_UINT32(0, 0, packet.buf[0] & (~0x01 << 7),
                                        packet.buf[1]);
  } else if (packet.length == 3) {
    value = BIG_ENGINE_UINT8S_TO_UINT32(0, packet.buf[0] & (~0x01 << 7),
                                        packet.buf[1], packet.buf[2]);
  } else {
    value = BIG_ENGINE_UINT8S_TO_UINT32((packet.buf[0] & (~0x01 << 7)),
                                        packet.buf[1], packet.buf[2],
                                        packet.buf[3]);
  }
  if (!positive) {
    value = -value;
  }
  return value;
}
/**
 * @brief 根据packet获取buf
 *
 * @param packet
 * @return uint32_t
 */
UP_buf_t UPParameter_get_buf(UP_parameter_packet_t packet) {
  UP_buf_t buf;
  buf.buf = packet.buf;
  buf.len = packet.length;
  return buf;
}