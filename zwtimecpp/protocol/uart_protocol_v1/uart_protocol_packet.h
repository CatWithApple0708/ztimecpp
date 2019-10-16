//
// Created by zhaohe on 19-10-4.
//
// 此文件中的方法均不支持重入
#pragma once
#include <string.h>
#include "zwtimecpp/core/utils/cutils/compiler_config.h"
#include "zwtimecpp/core/utils/cutils/marco_utils.h"
#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_struct.h"

/**
 * @WARNING:
 * 
 */

typedef struct {
  uint8_t parameters[MAX_SUPPORT_PACKET_PARAMETER_SIZE];
  size_t useful_size;
} UP_parameters_container_t;

typedef struct {
  uint16_t serial_num;
  PacketType_t type;
} UPPacketConfig_basic_packet_t;
typedef struct { uint8_t pad; } UPPacketConfig_shakehand_packet_t;
typedef struct { uint8_t pad; } UPPacketConfig_ping_packet_t;
typedef struct {
  UP_module_type_code_t moduleType;
  uint8_t moduleNum;
  UP_operate_code_t operate_code;
  uint16_t dataPoint;
  UP_parameters_container_t* parameter_container;
} UPPacketConfig_hardware_operate_packet_t;

typedef struct {
  UP_GenernalSystemEvent_t event;
  UP_parameters_container_t* parameter_container;
} UPPacketConfig_genernal_system_report_packet_t;

typedef struct {
  uint8_t serial_num;
  UP_error_code_t error_code;
  UP_parameters_container_t* parameter_container;
} UPPacketConfig_general_receipt_packet_t;

typedef union {
  UPPacketConfig_shakehand_packet_t shakehand_packet;
  UPPacketConfig_ping_packet_t ping_packet;
  UPPacketConfig_hardware_operate_packet_t hardware_operate_packet;
  UPPacketConfig_genernal_system_report_packet_t genernal_system_report_packet;
  UPPacketConfig_general_receipt_packet_t general_receipt_packet;
} UPPacketConfig_t;
/******************************参数列表构造**********************************/
/**
 * @brief 构造参数的时候最好加上一个BUILD_ASSERT
 * 例如，构造参数列表,int32_t,uint32_t,bool,添加下面这个assert
 *
 * BUILD_ASSERT(3*UP_EACH_PARAMETR_MIN_SIZE+sizeof(int32_t)+sizeof(uint32_t)+sizeof(bool)
 * < UPParametersContainer_get_max_support_size())
 */
#define UP_EACH_PARAMETR_MIN_SIZE (sizeof(uint16_t))

#define UPParametersContainer_get_max_support_size() \
  (ARRARY_SIZE(((UP_parameters_container_t*)(0))->parameters))

UP_parameters_container_t* UPParametersContainer_get();
static INLINE UP_parameters_container_t* UPParametersContainer_initialize(
    UP_parameters_container_t* paramer_c) {
  if (paramer_c != NULL) {
    memset(paramer_c, 0, sizeof(*paramer_c));
  }
  return paramer_c;
};

/**
 * @brief
 *
 * @param container
 * @param value
 * @return true 添加参数成功
 * @return false 失败，可能原因是parameter参数buf不够大
 */
bool UPParametersContainer_push_int32(UP_parameters_container_t* container,
                                      int32_t value);
bool UPParametersContainer_push_uint32(UP_parameters_container_t* container,
                                       uint32_t value);
bool UPParametersContainer_push_bool(UP_parameters_container_t* container,
                                     bool value);
bool UPParametersContainer_push_buf(UP_parameters_container_t* container,
                                    uint8_t* buf, uint16_t length);

/******************************packet构造**********************************/
/**
 * @Usage:
 *
 * UP_parameters_container_t* para_container = UPParametersContainer_get();
 * UPParametersContainer_push_int32(para_container,1);
 * UPParametersContainer_push_uint32(para_container,1);
 *
 * UPPacketConfig_basic_packet_t basic_packt =
 *   UPBasicPacketConfig_construct(serial_num,kHardwareOperatePacket);
 *
 * UPPacketConfig_t packet_config;
 * packet_config.hardware_operate_packet =
 *  UPHardwareOperatePacket_construct_config(MTC_HandProtection,0-moduleNum,
 *                          kOperateCode_report,UPDPKey_PressDownEvent,para_container);
 *
 * UP_buf_t packet = UP_construct_packet(basic_packt,packet_config);
 *
 */
/**
 * 构造基础包
 */
UPPacketConfig_basic_packet_t UPBasicPacketConfig_construct(uint16_t serial_num,
                                                            PacketType_t type);

/**
* @brief 构造packet
*
* @param basic_packt
* @param packet_config
* @return UP_buf_t
* @WARNING:此方法不可重入，如需可重入调用UP_construct_packet2
*/
UP_buf_t UP_construct_packet(UPPacketConfig_basic_packet_t basic_packt,
                             UPPacketConfig_t packet_config);

UP_buf_t UP_construct_packet2(UPPacketConfig_basic_packet_t basic_packt,
                              UPPacketConfig_t packet_config, uint8_t* data,
                              size_t length);

/**
 * @brief 构造握手包
 *
 */
UPPacketConfig_shakehand_packet_t UPShakeHandPacket_construct_config();
/**
 * @brief 构建握手包
 * 
 * @param serial_num 
 * @return UP_buf_t 
 */
static INLINE UP_buf_t UPShakeHandPacket_construct(uint16_t serial_num
                                                   ) {
  UPPacketConfig_basic_packet_t bpc =
      UPBasicPacketConfig_construct(serial_num, kShakeHandPacket);
  UPPacketConfig_t pc;
  pc.shakehand_packet = UPShakeHandPacket_construct_config();
  return UP_construct_packet(bpc, pc);
};
static INLINE UP_buf_t UPShakeHandPacket_construct2(uint16_t serial_num,
                                                    
                                                    uint8_t* data,
                                                    size_t length) {
  UPPacketConfig_basic_packet_t bpc =
      UPBasicPacketConfig_construct(serial_num, kShakeHandPacket);
  UPPacketConfig_t pc;
  pc.shakehand_packet = UPShakeHandPacket_construct_config();
  return UP_construct_packet2(bpc, pc, data, length);
};
/**
 * @brief 构造ping包
 *
 * @return UPPacketConfig_ping_packet_t
 */
UPPacketConfig_ping_packet_t UPPingPacket_construct_config();
/**
 * @brief 构建ping包
 *
 * @param serial_num
 * @return UP_buf_t
 */
static INLINE UP_buf_t UPPingPacket_construct(uint16_t serial_num
                                              ) {
  UPPacketConfig_basic_packet_t bpc =
      UPBasicPacketConfig_construct(serial_num, kPingPacket);
  UPPacketConfig_t pc;
  pc.ping_packet = UPPingPacket_construct_config();
  return UP_construct_packet(bpc, pc);
};
static INLINE UP_buf_t UPPingPacket_construct2(uint16_t serial_num,
                                               uint8_t* data,
                                               size_t length) {
  UPPacketConfig_basic_packet_t bpc =
      UPBasicPacketConfig_construct(serial_num, kPingPacket);
  UPPacketConfig_t pc;
  pc.ping_packet = UPPingPacket_construct_config();
  return UP_construct_packet2(bpc, pc, data, length);
};

/**
 * @brief 构造硬件操作包
 *
 * @param moduleType
 * @param moduleNum
 * @param operate_code
 * @param dataPoint
 * @param parameter_container
 * @return UPPacketConfig_hardware_operate_packet_t
 */
UPPacketConfig_hardware_operate_packet_t
UPHardwareOperatePacket_construct_config(
    UP_module_type_code_t moduleType, uint8_t moduleNum,
    UP_operate_code_t operate_code, uint16_t dataPoint,
    UP_parameters_container_t* parameter_container);
/**
 * @brief 打包硬件操作包
 * 
 * @param serial_num 
 * @param moduleType 
 * @param moduleNum 
 * @param operate_code 
 * @param dataPoint 
 * @param parameter_container 
 * @return UP_buf_t 
 */
static INLINE UP_buf_t UPHardwareOperatePacket_construct(
    uint16_t serial_num,  UP_module_type_code_t moduleType,
    uint8_t moduleNum, UP_operate_code_t operate_code, uint16_t dataPoint,
    UP_parameters_container_t* parameter_container) {
  UPPacketConfig_basic_packet_t bpc =
      UPBasicPacketConfig_construct(serial_num, kHardwareOperatePacket);
  UPPacketConfig_t pc;
  pc.hardware_operate_packet = UPHardwareOperatePacket_construct_config(
      moduleType, moduleNum, operate_code, dataPoint, parameter_container);
  return UP_construct_packet(bpc, pc);
};
static INLINE UP_buf_t UPHardwareOperatePacket_construct2(
    uint16_t serial_num,  UP_module_type_code_t moduleType,
    uint8_t moduleNum, UP_operate_code_t operate_code, uint16_t dataPoint,
    UP_parameters_container_t* parameter_container, uint8_t* data,
    size_t length) {
  UPPacketConfig_basic_packet_t bpc =
      UPBasicPacketConfig_construct(serial_num, kHardwareOperatePacket);
  UPPacketConfig_t pc;
  pc.hardware_operate_packet = UPHardwareOperatePacket_construct_config(
      moduleType, moduleNum, operate_code, dataPoint, parameter_container);
  return UP_construct_packet2(bpc, pc, data, length);
};

/**
 * @brief 构造系统事件上报包
 *
 * @param event
 * @param parameter_container
 * @return UPPacketConfig_genernal_system_report_packet_t
 */
UPPacketConfig_genernal_system_report_packet_t
UPGenernalSystemReportPacket_construct_config(
    UP_GenernalSystemEvent_t event,
    UP_parameters_container_t* parameter_container);
/**
 * @brief 打包系统上报包
 * 
 * @param serial_num 
 * @param event 
 * @param parameter_container 
 * @return UP_buf_t 
 */
static INLINE UP_buf_t UPGenernalSystemReportPacket_construct(
    uint16_t serial_num,  UP_GenernalSystemEvent_t event,
    UP_parameters_container_t* parameter_container) {
  UPPacketConfig_basic_packet_t bpc =
      UPBasicPacketConfig_construct(serial_num, kSystemEventReportPacket);
  UPPacketConfig_t pc;
  pc.genernal_system_report_packet =
      UPGenernalSystemReportPacket_construct_config(event, parameter_container);
  return UP_construct_packet(bpc, pc);
};
static INLINE UP_buf_t UPGenernalSystemReportPacket_construct2(
    uint16_t serial_num,  UP_GenernalSystemEvent_t event,
    UP_parameters_container_t* parameter_container, uint8_t* data,
    size_t length) {
  UPPacketConfig_basic_packet_t bpc =
      UPBasicPacketConfig_construct(serial_num, kSystemEventReportPacket);
  UPPacketConfig_t pc;
  pc.genernal_system_report_packet =
      UPGenernalSystemReportPacket_construct_config(event, parameter_container);
  return UP_construct_packet2(bpc, pc, data, length);
};

/**
 * @brief 构建通用回执包
 *
 * @param serial_num
 * @param error_code
 * @param parameter_container
 * @return UPPacketConfig_general_receipt_packet_t
 */
UPPacketConfig_general_receipt_packet_t UPGeneralReceiptPacket_construct_config(
    uint8_t order_serial_num, UP_error_code_t error_code,
    UP_parameters_container_t* parameter_container);
/**
 * @brief 构造通用回执包
 *
 * @param serial_num
 * @param order_serial_num
 * @param error_code
 * @param parameter_container
 * @return UP_buf_t
 */
static INLINE UP_buf_t UPGGeneralReceiptPacket_construct(
    uint16_t serial_num,  uint8_t order_serial_num,
    UP_error_code_t error_code,
    UP_parameters_container_t* parameter_container) {
  UPPacketConfig_basic_packet_t bpc =
      UPBasicPacketConfig_construct(serial_num, kReceiptPacket);
  UPPacketConfig_t pc;
  pc.general_receipt_packet = UPGeneralReceiptPacket_construct_config(
      order_serial_num, error_code, parameter_container);
  return UP_construct_packet(bpc, pc);
};
static INLINE UP_buf_t UPGGeneralReceiptPacket_construct2(
    uint16_t serial_num,  uint8_t order_serial_num,
    UP_error_code_t error_code, UP_parameters_container_t* parameter_container,
    uint8_t* data, size_t length) {
  UPPacketConfig_basic_packet_t bpc =
      UPBasicPacketConfig_construct(serial_num, kReceiptPacket);
  UPPacketConfig_t pc;
  pc.general_receipt_packet = UPGeneralReceiptPacket_construct_config(
      order_serial_num, error_code, parameter_container);
  return UP_construct_packet2(bpc, pc, data, length);
};