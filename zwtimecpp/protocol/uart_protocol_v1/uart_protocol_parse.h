//
// Created by zhaohe on 19-10-4.
//
#pragma once
#include "zwtimecpp/core/utils/cutils/marco_utils.h"
#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_struct.h"

/**
 * @demo
 * uart_protocol_handler_t *handler;
 * onInterrupt(){
 *   UPProcessPushRawDataRet_t ret =
 * UP_process_push_raw_data(handler,receiveData,length);
 *  if(!ret.success){
 *      回执错误消息(ret.error_code);
 *  }
 *
 *  if(ret.shouldProcessRawDataNow){
 *      put a Event To Task to call UP_process_raw_data
 *  }
 * }
 *
 * OnTask(){
 *
 *  while(true){
 *     UP_packet_container_t*container = UP_process_raw_data(handler);
 *     if(container == NULL){
 *          break;
 *     }
 *     //在这里解析消息
 *     .....
 *  }
 * }
 */

void uart_protocol_handler_init(uart_protocol_handler_t* handler);

/**
 * @brief　UP_process_push_raw_data 可以在中断中使用
 *
 * @param handler
 * @param rawData
 * @param length
 * @return true
 * @return false
 */
typedef struct {
  bool success;
  bool shouldProcessRawDataNow;
  UP_error_code_t error_code;
} UPProcessPushRawDataRet_t;

UPProcessPushRawDataRet_t UP_process_push_raw_data(
    uart_protocol_handler_t* handler, const uint8_t* buf, size_t size);

typedef void (*UP_packet_container_cb_t)(uart_protocol_handler_t* hander,
                                         UP_packet_process_ret_t process_statu,
                                         UP_packet_container_t* container);
/**
 * @brief UP_process_raw_data
 *
 * @param handler
 * @param container 用于存储解析出来的数据包，之所以外部提供，是因为
 * @param on_container
 */
void UP_process_raw_data(uart_protocol_handler_t* handler,
                         UP_packet_container_cb_t on_container);

/**********************UP_packet_container_t*************************************/
/**
 * @brief 获得UP_packet_container_t最大可以处理的包的大小
 *
 */
#define UPPacketContainer_get_packet_max_size() \
  (ARRARY_SIZE(((UP_packet_container_t*)(0))->raw_data))
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
    UP_packet_container_t* container, uint8_t* packet, size_t length);

/**********************解析UP_packet_container_t中的中的参数**********************/
/**
 * @brief 解析UP_packet_container_t中的中的参数
 *
 * @Usage:
 * UP_packet_container_t* container = ...;
 * if(container->packet.hardware_opearte_packet.parameterNum>=2){
 *  bool parameter0 =
 *     UPParameter_get_bool(
 *          container->packet.hardware_opearte_packet.parameters[0]);
 *  bool parameter1 =
 *      UPParameter_get_int32(
 *           container->packet.hardware_opearte_packet.parameters[1]);
 * }
 */
bool UPParameter_get_bool(UP_parameter_packet_t packet);
int32_t UPParameter_get_int32(UP_parameter_packet_t packet);
UP_buf_t UPParameter_get_buf(UP_parameter_packet_t packet);