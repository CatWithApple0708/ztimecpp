//
// Created by zhaohe on 19-10-4.
//
// 此文件中的方法均不支持重入
#pragma once
#include "zwtimecpp/core/utils/cutils/marco_utils.h"
#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_struct.h"

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
UPPacketConfig_basic_packet_t UPBasicPacketConfig_construct(uint16_t serial_num,
                                                            PacketType_t type);
UPPacketConfig_shakehand_packet_t UPShakeHandPacket_construct_config();
UPPacketConfig_ping_packet_t UPPingPacket_construct_config();

UPPacketConfig_hardware_operate_packet_t
UPHardwareOperatePacket_construct_config(
    UP_module_type_code_t moduleType, uint8_t moduleNum,
    UP_operate_code_t operate_code, uint16_t dataPoint,
    UP_parameters_container_t* parameter_container);

UPPacketConfig_genernal_system_report_packet_t
UPGenernalSystemReportPacket_construct_config(
    UP_GenernalSystemEvent_t event,
    UP_parameters_container_t* parameter_container);

UPPacketConfig_general_receipt_packet_t UPGeneralReceiptPacket_construct_config(
    uint8_t serial_num, UP_error_code_t error_code,
    UP_parameters_container_t* parameter_container);

UP_buf_t UP_construct_packet(UPPacketConfig_basic_packet_t basic_packt,
                             UPPacketConfig_t packet_config);

UP_buf_t UP_construct_packet2(UPPacketConfig_basic_packet_t basic_packt,
                             UPPacketConfig_t packet_config,uint8_t* data,size_t length);
