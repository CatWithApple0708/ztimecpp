#pragma once
#include "stdint.h"
#include "zwtimecpp/core/utils/cutils/compiler_config.h"

#define HEADER_FIRST (0x24)
#define HEADER_SECOND (0xdb)
#define TAIL (0x5e)
#define SPECIAL_PACKET_SERIAL_NUM (0xff)

/**
 * @brief 包头
 */
#pragma pack(1)
typedef struct {
  uint8_t header[2];
  uint8_t serial_num;
  uint8_t route;
  uint8_t length[2];
  uint8_t packet_type;
  uint8_t packet[];
} UPAnalysis_basic_packet_header_t;
#pragma pack()
/**
 * @brief 包尾
 *
 */
#pragma pack(1)
typedef struct { uint8_t tail; } UPAnalysis_basic_packet_tail_t;
#pragma pack()
/**
 * @brief 通用回执包
 * 0x00
 */
#pragma pack(1)
typedef struct UPAnalysis_genernal_receipt_packet_header_s {
  uint8_t serial_num;
  uint8_t error_code;
  uint8_t parameter[];
} UPAnalysis_genernal_receipt_packet_header_t;
#pragma pack()

/**
 * @brief 握手包
 * 0x01
 */
#pragma pack(1)
typedef struct { uint8_t pad; } UPAnalysis_shake_hand_packet_header_t;
#pragma pack()

/**
 * @brief Ping包
 * 0x02
 */
#pragma pack(1)
typedef struct { uint8_t pad; } UPAnalysis_ping_packet_header_t;
#pragma pack()

/**
 * @brief 硬件操作包
 * 0x03
 */
#pragma pack(1)
typedef struct {
  uint8_t module_type[2];
  uint8_t module_num;
  uint8_t data_point[2];
  uint8_t operate_code;
  uint8_t parameter[];
} UPAnalysis_hardware_operate_packet_header_t;
#pragma pack()

/**
 * @brief 硬件操作包
 * 0x03
 */
#pragma pack(1)
typedef struct {
  uint8_t system_event_type[2];
  uint8_t parameter[];
} UPAnalysis_system_event_report_packet_t;
#pragma pack()

#define BIG_ENGINE_UINT8S_TO_UINT16(byte0, byte1) \
  (((uint16_t)(byte0) << 8) + ((uint16_t)byte1))

#define BIG_ENGINE_UINT8S_TO_UINT32(byte0, byte1, byte2, byte3) \
  (((uint16_t)(byte0) << 24) + ((uint16_t)(byte1) << 16) +      \
   ((uint16_t)(byte2) << 8) + ((uint16_t)(byte3) << 0))

#define HIGH_UINT16(value) ((value >> 8) & 0xff)
#define LOW_UINT16(value) ((value >> 0) & 0xff)

static INLINE uint16_t UPIBasicPacketHeader_get_packet_length(
    UPAnalysis_basic_packet_header_t* header) {
  return BIG_ENGINE_UINT8S_TO_UINT16(header->length[0], header->length[1]);
}