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
  KSystemWhoAmI = 0x01,
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
  kErrorCode_CmdNotSupport = 11,
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
  MTC_Weighting = 0x000d,
  MTC_Uart = 0x000e,
  MTC_GripMotor = 0x000f,
  MTC_GarbageSensor = 0x0010,
  MTC_PhotoLight = 0x0011,
  MTC_DryGarbageUart = 0x0012,
  MTC_WetGarbageUart = 0x0013,
  MTC_GarbageConveyer = 0x0014,
  MTC_PhotoSensor = 0x0015,
} UP_module_type_code_t;

typedef enum {
  UPDPMotorState_close,
  UPDPMotorState_closing,
  UPDPMotorState_open,
  UPDPMotorState_opening
} UPDPMotorState_t;

/**
 * 传输带状态
*/
typedef enum {
  UPDPConveyerState_stop,
  UPDPConveyerState_forward_moving,//正向运动
  UPDPConveyerState_reverse_moving //反向运动
} UPDPConveyerState_t;

/**
 * @brief 数据点定义
 */
#define DEFINE_DATA_POINT(name) typedef enum

#define DEFINE_DATA_POINT_ENTRY(modue_name, data_point_name, value) \
  UPDP##modue_name##_##data_point_name = value,

#define DEFINE_DATA_END(name) UPDP##name##_t;

/**
 * @brief TODO:将下面的枚举修改成使用宏'定义的形式
 * DEFINE_DATA_POINT
 * DEFINE_DATA_POINT_ENTRY
 * DEFINE_DATA_END
 */
DEFINE_DATA_POINT(Common) {
  DEFINE_DATA_POINT_ENTRY(Common, power, 0x0000)
}
DEFINE_DATA_END(Common);

DEFINE_DATA_POINT(HumanSensor) {
  DEFINE_DATA_POINT_ENTRY(HumanSensor, HummanEvent, 0x0100)
}
DEFINE_DATA_END(HumanSensor);

DEFINE_DATA_POINT(GarbageSensor) {
  DEFINE_DATA_POINT_ENTRY(GarbageSensor, value, 0x0100)
}
DEFINE_DATA_END(GarbageSensor);

DEFINE_DATA_POINT(PhotoSensor) {
  DEFINE_DATA_POINT_ENTRY(PhotoSensor, value, 0x0100)
}
DEFINE_DATA_END(PhotoSensor);

DEFINE_DATA_POINT(IndicatorLight) {
  DEFINE_DATA_POINT_ENTRY(IndicatorLight, invalid, 0x0100)
}
DEFINE_DATA_END(IndicatorLight);

DEFINE_DATA_POINT(Light) {
  DEFINE_DATA_POINT_ENTRY(Light, invalid, 0x0100)
}
DEFINE_DATA_END(Light);

DEFINE_DATA_POINT(Key) {
  DEFINE_DATA_POINT_ENTRY(Key, State, 0x0100)
  DEFINE_DATA_POINT_ENTRY(Key, PressDownEvent, 0x0101)
  DEFINE_DATA_POINT_ENTRY(Key, PressUpEvent, 0x0102)
  DEFINE_DATA_POINT_ENTRY(Key, PressKeepingEvent, 0x0103)
}
DEFINE_DATA_END(Key)

DEFINE_DATA_POINT(UltrasonicSensor) {
  DEFINE_DATA_POINT_ENTRY(UltrasonicSensor, distance, 0x0100)
}
DEFINE_DATA_END(UltrasonicSensor);

DEFINE_DATA_POINT(LightSensor) {
  DEFINE_DATA_POINT_ENTRY(LightSensor, intensity, 0x0100)
  DEFINE_DATA_POINT_ENTRY(LightSensor, boolintensity, 0x0101)
}
DEFINE_DATA_END(LightSensor);

DEFINE_DATA_POINT(Gps) {
  DEFINE_DATA_POINT_ENTRY(Gps, write, 0x0100)
  DEFINE_DATA_POINT_ENTRY(Gps, report, 0x0101)
  DEFINE_DATA_POINT_ENTRY(Gps, baudrate, 0x0102)
}
DEFINE_DATA_END(Gps);

DEFINE_DATA_POINT(DryGarbageUart) {
  DEFINE_DATA_POINT_ENTRY(DryGarbageUart, write, 0x0100)
  DEFINE_DATA_POINT_ENTRY(DryGarbageUart, report, 0x0101)
  DEFINE_DATA_POINT_ENTRY(DryGarbageUart, baudrate, 0x0102)
}
DEFINE_DATA_END(DryGarbageUart);

DEFINE_DATA_POINT(WetGarbageUart) {
  DEFINE_DATA_POINT_ENTRY(WetGarbageUart, write, 0x0100)
  DEFINE_DATA_POINT_ENTRY(WetGarbageUart, report, 0x0101)
  DEFINE_DATA_POINT_ENTRY(WetGarbageUart, baudrate, 0x0102)
}
DEFINE_DATA_END(WetGarbageUart);

DEFINE_DATA_POINT(CardReader) {
  DEFINE_DATA_POINT_ENTRY(CardReader, write, 0x0100)
  DEFINE_DATA_POINT_ENTRY(CardReader, report, 0x0101)
  DEFINE_DATA_POINT_ENTRY(CardReader, baudrate, 0x0102)
  DEFINE_DATA_POINT_ENTRY(CardReader, reportRfidOrQR, 0x0103)
  DEFINE_DATA_POINT_ENTRY(CardReader, reportRfid, 0x0104)
  DEFINE_DATA_POINT_ENTRY(CardReader, reportQR, 0x0105)
}

DEFINE_DATA_END(CardReader);
DEFINE_DATA_POINT(HandProtection) {
  DEFINE_DATA_POINT_ENTRY(HandProtection, value, 0x0100)
}
DEFINE_DATA_END(HandProtection);

DEFINE_DATA_POINT(OverflowDetector) {
  DEFINE_DATA_POINT_ENTRY(OverflowDetector, value, 0x0100)
}
DEFINE_DATA_END(OverflowDetector)

DEFINE_DATA_POINT(GarbageDumpingWindowsMotor) {
  DEFINE_DATA_POINT_ENTRY(GarbageDumpingWindowsMotor, action, 0x0100)
  DEFINE_DATA_POINT_ENTRY(GarbageDumpingWindowsMotor, status, 0x0101)
}
DEFINE_DATA_END(GarbageDumpingWindowsMotor)

DEFINE_DATA_POINT(GarbageConveyerMotor) {
  DEFINE_DATA_POINT_ENTRY(GarbageConveyerMotor, action, 0x0100)
  DEFINE_DATA_POINT_ENTRY(GarbageConveyerMotor, status, 0x0101)
}
DEFINE_DATA_END(GarbageConveyerMotor)

DEFINE_DATA_POINT(GripMotor) {
  DEFINE_DATA_POINT_ENTRY(GripMotor, action, 0x0100)
  DEFINE_DATA_POINT_ENTRY(GripMotor, status, 0x0101)
}
DEFINE_DATA_END(GripMotor)

DEFINE_DATA_POINT(GarbageDoorMotor) {
  DEFINE_DATA_POINT_ENTRY(GarbageDoorMotor, action, 0x0100)
  DEFINE_DATA_POINT_ENTRY(GarbageDoorMotor, status, 0x0101)
}
DEFINE_DATA_END(GarbageDoorMotor)

DEFINE_DATA_POINT(Weighting) {
  DEFINE_DATA_POINT_ENTRY(Weighting, wight, 0x0100)
}
DEFINE_DATA_END(Weighting)

DEFINE_DATA_POINT(Uart) {
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
  uint8_t pad; /*占位，无任何意义*/
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
