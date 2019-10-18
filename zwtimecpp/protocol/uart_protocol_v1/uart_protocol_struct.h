#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "zwtimecpp/core/utils/cutils/compiler_config.h"
#include "zwtimecpp/core/utils/cutils/loop_queue.h"

#ifndef MAX_SUPPORT_PACKET_LENGTH
#define MAX_SUPPORT_PACKET_LENGTH (2048)
#endif

#ifndef MAX_SUPPORT_PACKET_PARAMETER_SIZE
#define MAX_SUPPORT_PACKET_PARAMETER_SIZE (1024)
#endif

#ifndef MAX_SUPPORT_PARAMETER
#define MAX_SUPPORT_PARAMETER (10)
#endif

#define MAX_UART_RECEIVE_BUF_NUM (2)

#define UNMATCHED_SERIAL_NUM (0xff)

/**
 * @brief
 * 协议基本约定
 * 大小端: 大端
 *
 * 缩写:
 * UP = uart_protocol
 */
/************************************包类型**********************************/

typedef enum {
  kUnkownPacketType = -1,
  kReceiptPacket = 0,
  kShakeHandPacket = 1,
  kPingPacket = 2,
  kHardwareOperatePacket = 3,
  kSystemEventReportPacket = 4,
} PacketType_t;

typedef enum {
  kGarbageStm32End = 0x01,
} DeviceType_t;

typedef enum {
  kSystemSetup = 0x00, /*系统启动 */
} UP_GenernalSystemEvent_t;

/**
 * @brief 错误码
 */
typedef enum {
  kErrorCode_Success = 0,
  kErrorCode_packetIsTooLong = 1,
  kErrorCode_receivePacketOverflow = 2,
  kErrorCode_moduleNotSupport = 3,
  kErrorCode_DataPointNotSupport = 4,
  kErrorCode_OperationNotSupport = 5,
  kErrorCode_NotSupportPacketType = 6,
  kErrorCode_parsePacketFail = 7,
  kErrorCode_packetFormatError = 8,
  kErrorCode_moduleNumNotSupport = 9,
  kErrorCode_powerIsInActive = 10,
} UP_error_code_t;
/**
 * @brief 操作码
 */
typedef enum {
  kOperateCode_read = 0,
  kOperateCode_write = 1,
  kOperateCode_report = 2,
  kOperateCode_openInitiativeReport = 3,
  kOperateCode_openPeriodReport = 4,
  kOperateCode_setReportPeriod = 5,
  kOperateCode_reportRequest = 6,
} UP_operate_code_t;
/**
 * @brief 模块编号
 */
typedef enum {
  // MTC module type code
  MTC_NotSet = 0x0000,
  MTC_HumanSensor = 0x0001,
  MTC_IndicatorLight = 0x0002,
  MTC_Light = 0x0003,
  MTC_Key = 0x0004,
  MTC_UltrasonicSensor = 0x0005,
  MTC_LightSensor = 0x0006,
  MTC_Gps = 0x0007,
  MTC_CardReader = 0x0008,
  MTC_HandProtection = 0x0009,
  MTC_OverflowDetector = 0x000a,
  MTC_GarbageDumpingWindowsMotor = 0x000b,
  MTC_GarbageDoorMotor = 0x000c,
  MTC_Weighing = 0x000d,
  MTC_Uart = 0x000e,
} UP_module_type_code_t;

typedef enum {
  UPDPMotorState_close,
  UPDPMotorState_closing,
  UPDPMotorState_open,
  UPDPMotorState_opening
} UPDPMotorState_t;

/**
 * @brief 数据点定义
 */
#define DEFINE_DATA_POINT(name,destribe) typedef enum

#define DEFINE_DATA_POINT_ENTRY(modue_name, data_point_name, value) \
  UPDP##modue_name##_##data_point_name = 0x0100,

#define DEFINE_DATA_END(name) UPDP##name##_t;

/**
 * @brief TODO:将下面的枚举修改成使用宏'定义的形式
 * DEFINE_DATA_POINT
 * DEFINE_DATA_POINT_ENTRY
 * DEFINE_DATA_END
 */
typedef enum {
  UPDPCommon_power = 0x0000,
} UPDPCommon_t;

typedef enum {
  UPDPHumanSensor_HummanEvent = 0x0100,
} UPDPHumanSensor_t;

typedef enum {
  UPDPIndicatorLight_invalid = 0x0100,
} UPDPIndicatorLight_t;
typedef enum {
  UPDPLight_invalid = 0x0100,
} UPDPLight_t;

typedef enum {
  UPDPKey_State = 0x0100,
  UPDPKey_PressDownEvent = 0x0101,
  UPDPKey_PressUpEvent = 0x0102,
  UPDPKey_PressKeepingEvent = 0x0103,
} UPDPKey_t;
typedef enum {
  UPDPUltrasonicSensor_distance = 0x0100,
} UPDPUltrasonicSensor_t;
typedef enum {
  UPDPLightSensor_intensity = 0x0100,
  UPDPLightSensor_boolintensity = 0x0101,
} UPDPLightSensor_t;
typedef enum {
  UPDPGps_location = 0x0100,
} UPDPGps_t;
typedef enum {
  UPDPCardReader_rfid = 0x0100,
  UPDPCardReader_2dcode = 0x0101,
} UPDPCardReader_t;
typedef enum {
  UPDPHandProtection_value = 0x0100,
} UPDPHandProtection_t;

DEFINE_DATA_POINT(Overflow, "满溢检测数据点") {
  DEFINE_DATA_POINT_ENTRY(Overflow, value, 0x0100)
}
DEFINE_DATA_END(Overflow)

DEFINE_DATA_POINT(GarbageDumpingWindowsMoto, "垃圾箱倾倒倒口电机") {
  DEFINE_DATA_POINT_ENTRY(GarbageDumpingWindowsMoto, action, 0x0100)
  DEFINE_DATA_POINT_ENTRY(GarbageDumpingWindowsMoto, status, 0x0101)
}
DEFINE_DATA_END(GarbageDumpingWindowsMoto)

DEFINE_DATA_POINT(GarbageDoorMoto, "垃圾箱门电机") {
  DEFINE_DATA_POINT_ENTRY(GarbageDoorMoto, action, 0x0100)
  DEFINE_DATA_POINT_ENTRY(GarbageDoorMoto, status, 0x0101)
}
DEFINE_DATA_END(GarbageDoorMoto)

DEFINE_DATA_POINT(Weighting, "称重") {
  DEFINE_DATA_POINT_ENTRY(Weighting, wight, 0x0100)
}
DEFINE_DATA_END(Weighting)

DEFINE_DATA_POINT(Uart, "串口透传") {
  DEFINE_DATA_POINT_ENTRY(Uart, write, 0x0100)
  DEFINE_DATA_POINT_ENTRY(Uart, report, 0x0101)
  DEFINE_DATA_POINT_ENTRY(Uart, baudrate, 0x0102)
}
DEFINE_DATA_END(Uart)

typedef struct {
  uint8_t *buf;
  size_t length;
} UP_parameter_packet_t;

/**
 * @brief 通用回执包 0x00
 */
typedef struct UP_general_receipt_s UP_general_receipt_t;
struct UP_general_receipt_s {
  uint8_t serial_num;
  uint8_t error_code;
  int parameterNum;  //参数的数量
  UP_parameter_packet_t parameters[MAX_SUPPORT_PARAMETER];
};
/**
 * @brief 硬件操作包 0x03
 */
typedef struct UP_hardware_operat_packet_s UP_hardware_operat_packet_t;
struct UP_hardware_operat_packet_s {
  UP_module_type_code_t module_type;
  uint8_t module_num;
  uint16_t data_point;
  UP_operate_code_t operate_code;
  int parameterNum;  //参数的数量
  UP_parameter_packet_t parameters[MAX_SUPPORT_PARAMETER];
};
/**
 * @brief 通用系统事件上报包
 */
typedef struct {
  UP_GenernalSystemEvent_t event;
  int parameterNum;  //参数的数量
  UP_parameter_packet_t parameters[MAX_SUPPORT_PARAMETER];
} UP_system_event_report_packet_t;

typedef struct UP_shake_hand_packet_s UP_shake_hand_packet_t;
struct UP_shake_hand_packet_s {
  uint8_t pad;/*占位，无任何意义*/
};

typedef struct UP_ping_packet_s UP_ping_packet_t;
struct UP_ping_packet_s {
  uint8_t pad; /*占位，无任何意义*/
};

/**************************************基础包***********************************
 */
typedef struct UP_basic_packet_s UP_basic_packet_t;
struct UP_basic_packet_s {
  PacketType_t packet_type;
  uint8_t serial_num;
  uint16_t packet_length;
  uint8_t *packet;
};

/***************************************辅助结构**********************************
 */

/**
 * @brief 硬件操作参数
 */
typedef struct UP_operate_para_s UP_operate_para_t;
struct UP_operate_para_s {
  uint16_t length;
  uint8_t *value;
};

typedef struct UP_packet_container_s UP_packet_container_t;
struct UP_packet_container_s {
  /*原始数据,不要修改这里面的数值*/
  uint8_t raw_data[MAX_SUPPORT_PACKET_LENGTH];
  size_t useful_size;

  /*基础包内容*/
  UP_basic_packet_t basic_packet;
  union {
    UP_general_receipt_t general_receipt;
    UP_hardware_operat_packet_t hardware_opearte_packet;
    UP_shake_hand_packet_t shake_hand_packet;
    UP_ping_packet_t ping_packet;
    UP_system_event_report_packet_t system_event_report_packet;
  } packet;
};

typedef struct UP_buf_s UP_buf_t;
struct UP_buf_s {
  uint8_t *buf;
  size_t len;
};

/**
 * @brief 辅助类，用于构造包
 */
typedef struct UP_module_config_s UP_module_config_t;
struct UP_module_config_s {
  UP_module_type_code_t moduleType;
  uint8_t moduleNum;
  uint16_t dataPoint;
};

typedef struct UP_packet_process_ret_s UP_packet_process_ret_t;
struct UP_packet_process_ret_s {
  uint8_t receive_packet_serial_num;
  UP_error_code_t error_code;
};

/***************************************handler**********************************
 */
typedef struct uart_protocol_handler_s uart_protocol_handler_t;
struct uart_protocol_handler_s {
  uint8_t receiveqbuf[MAX_SUPPORT_PACKET_LENGTH + 10];
  loop_queue_u8_t receiveq;
  uint8_t processbuf[MAX_SUPPORT_PACKET_LENGTH];
  size_t usefullSize;
  UP_packet_container_t container;
};


