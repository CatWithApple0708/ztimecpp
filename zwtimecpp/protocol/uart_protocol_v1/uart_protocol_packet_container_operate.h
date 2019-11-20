//
// Created by zhaohe on 19-10-4.
//
#pragma once
#include "zwtimecpp/core/utils/cutils/marco_utils.h"
#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_struct.h"
/**
 * @brief
 * 修改UpPacketContainer中的字段不仅要修改相应结构体中的字段，还要修改原始数据中相应的字段
 */
#ifndef UART_PROTOCOL_PACKET_DISABLE_ROUTE
/**
 * @brief
 *
 * @param container
 * @param route
 */
void UPPacketContainer_set_route(UP_packet_container_t* container,
                                 uint8_t route) {
  container->basic_packet.route = route;
  UP_basic_packet_t* rawData = (UP_basic_packet_t*)container->raw_data;
  rawData->route = route;
};
#endif
/**
 * @brief UPPacketContainer_get_raw_data
 *
 * @param container
 * @return uint8_t*
 */
uint8_t* UPPacketContainer_get_raw_data(UP_packet_container_t* container) {
  return container->raw_data;
}
/**
 * @brief UPPacketContainer_get_raw_data_size
 *
 * @param container
 * @return size_t
 */
size_t UPPacketContainer_get_raw_data_size(UP_packet_container_t* container) {
  return container->useful_size;
}
