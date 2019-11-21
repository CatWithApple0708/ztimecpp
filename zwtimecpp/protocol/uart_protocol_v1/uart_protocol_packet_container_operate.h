//
// Created by zhaohe on 19-10-4.
//
#pragma once
#include "zwtimecpp/core/utils/cutils/marco_utils.h"
#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_packet_struct_internal.h"
#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_struct.h"
/**
 * @brief
 * 修改UpPacketContainer中的字段不仅要修改相应结构体中的字段，还要修改原始数据中相应的字段
 */
/**
 * @brief
 *
 * @param container
 * @param route
 */
static INLINE void UPPacketContainer_set_route(UP_packet_container_t* container,
                                               uint8_t route) {
  container->basic_packet.route = route;
  UPAnalysis_basic_packet_header_t* rawData =
      (UPAnalysis_basic_packet_header_t*)container->raw_data;
  rawData->route = route;
};
/**
 * @brief UPPacketContainer_get_raw_data
 *
 * @param container
 * @return uint8_t*
 */
static INLINE uint8_t* UPPacketContainer_get_raw_data(UP_packet_container_t* container) {
  return container->raw_data;
}
/**
 * @brief UPPacketContainer_get_raw_data_size
 *
 * @param container
 * @return size_t
 */
static INLINE size_t UPPacketContainer_get_raw_data_size(UP_packet_container_t* container) {
  return container->useful_size;
}
