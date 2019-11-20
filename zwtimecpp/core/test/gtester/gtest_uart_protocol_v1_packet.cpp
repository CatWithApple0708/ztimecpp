#include "gtest/gtest.h"
#include "zwtimecpp/protocol/uart_protocol_v1/cpp/uart_protocol_v1_packet.hpp"
extern "C" {
#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_v1.h"
}
#include <functional>

#ifndef ARRARY_SIZE
#define ARRARY_SIZE(arrary) sizeof(arrary) / sizeof(arrary[0])
#endif
using namespace std;
using namespace zwsd;
namespace {
typedef function<void(uart_protocol_handler_t* hander,
                      UP_packet_process_ret_t process_statu,
                      UP_packet_container_t* container)>
    UP_packet_container_cb_cpp_t;
UP_packet_container_cb_cpp_t UP_packet_container_cb_cpp;
static void UP_packet_container_cb(uart_protocol_handler_t* hander,
                            UP_packet_process_ret_t process_statu,
                            UP_packet_container_t* container) {
  if (UP_packet_container_cb_cpp) {
    UP_packet_container_cb_cpp(hander, process_statu, container);
  }
}
static void call_up_process_raw_data(uart_protocol_handler_t* handler,
                                    UP_packet_container_cb_cpp_t cb) {
  UP_packet_container_cb_cpp = cb;
  UP_process_raw_data(handler, UP_packet_container_cb);
}

static UP_parameters_container_t* parameterConstruct(
    vector<int32_t> int32_value_table, bool bool_value_table) {
  UP_parameters_container_t* para_container = UPParametersContainer_get();
  for (auto var : int32_value_table) {
    UPParametersContainer_push_int32(para_container, var);
  }
  UPParametersContainer_push_bool(para_container, bool_value_table);
  return para_container;
}
}

/**
 * @brief 测试参数是否正确
 *
 * @param packet
 * @param int32_value_table
 * @param bool_value_table
 */
static void parameterCheck(UP_parameter_packet_t* packet,
                           vector<int32_t> int32_value_table,
                           bool bool_value_table) {
  int off = 0;
  for (auto var : int32_value_table) {
    EXPECT_EQ(UPParameter_get_int32(packet[off]), var);
    off++;
  }
  EXPECT_EQ(UPParameter_get_bool(packet[off]), bool_value_table);
}

class TestGeneralReceiptPacket {
 public:
  void TestGeneralReceiptPacketConstructAndParse(
      uint8_t packetSerialNum, uint8_t route,UP_error_code_t error_code,
      vector<int32_t> int32_value_table, bool bool_value_table) {
    /**
     * @brief 测试参数构造
     */
    auto cpppacket = UartProtocolV1Packet::createReceipt(
        packetSerialNum, route, error_code, int32_value_table,
        bool_value_table);
    UP_buf_t packet;
    packet.buf = cpppacket->buf.data();
    packet.len = cpppacket->buf.size();

    uart_protocol_handler_t uart_protocol_handler;
    uart_protocol_handler_init(&uart_protocol_handler);

    /**解析包 */
    UPProcessPushRawDataRet_t ret = UP_process_push_raw_data(
        &uart_protocol_handler, packet.buf, packet.len);

    EXPECT_TRUE(ret.success);
    EXPECT_TRUE(ret.error_code == kErrorCode_Success);
    EXPECT_TRUE(ret.shouldProcessRawDataNow);

    int receive_packet = 0;
    call_up_process_raw_data(
        &uart_protocol_handler, [&](uart_protocol_handler_t* ret_hander,
                                    UP_packet_process_ret_t ret_process_statu,
                                    UP_packet_container_t* container) {
          receive_packet++;

          EXPECT_EQ(ret_process_statu.error_code, kErrorCode_Success);
          EXPECT_EQ(ret_process_statu.receive_packet_serial_num,
                    packetSerialNum);
          EXPECT_TRUE(container != NULL);
          EXPECT_TRUE(ret_hander == &uart_protocol_handler);

          EXPECT_EQ(container->useful_size, packet.len);

          EXPECT_EQ(container->basic_packet.packet_type, kReceiptPacket);

          EXPECT_EQ(container->basic_packet.serial_num, packetSerialNum);

          //通用回执包验证
          EXPECT_EQ(container->packet.general_receipt.error_code, error_code);
          EXPECT_EQ(container->basic_packet.route,route);

          //测试构造参数
          EXPECT_EQ(container->packet.general_receipt.parameterNum,
                    int(int32_value_table.size() + 1));
          parameterCheck(container->packet.general_receipt.parameters,
                         int32_value_table, bool_value_table);
        });
    EXPECT_TRUE(receive_packet == 1);
  }
};

class TestPingPacket {
 public:
  void test(uint8_t packetSerialNum,uint8_t route) {

    PacketType_t packetType = kPingPacket;
    auto cpppacket = UartProtocolV1Packet::createPingPacket(
        packetSerialNum,route);
    UP_buf_t packet;
    packet.buf = cpppacket->buf.data();
    packet.len = cpppacket->buf.size();

    uart_protocol_handler_t uart_protocol_handler;
    uart_protocol_handler_init(&uart_protocol_handler);

    /**解析包 */
    UPProcessPushRawDataRet_t ret = UP_process_push_raw_data(
        &uart_protocol_handler, packet.buf, packet.len);

    EXPECT_TRUE(ret.success);
    EXPECT_TRUE(ret.error_code == kErrorCode_Success);
    EXPECT_TRUE(ret.shouldProcessRawDataNow);

    int receive_packet = 0;
    call_up_process_raw_data(
        &uart_protocol_handler, [&](uart_protocol_handler_t* ret_hander,
                                    UP_packet_process_ret_t ret_process_statu,
                                    UP_packet_container_t* container) {
          receive_packet++;

          EXPECT_EQ(ret_process_statu.error_code, kErrorCode_Success);
          EXPECT_EQ(ret_process_statu.receive_packet_serial_num,
                    packetSerialNum);
          EXPECT_TRUE(container != NULL);
          EXPECT_TRUE(ret_hander == &uart_protocol_handler);

          EXPECT_EQ(container->useful_size, packet.len);

          EXPECT_EQ(container->basic_packet.packet_type, packetType);

          EXPECT_EQ(container->basic_packet.serial_num, packetSerialNum);
          EXPECT_EQ(container->basic_packet.route, route);

          // Ping包测试
        });
    EXPECT_TRUE(receive_packet == 1);
  }
};

class TestShakeHandPacket {
 public:
  void test(uint8_t packetSerialNum,uint8_t route) {
    PacketType_t packetType = kPingPacket;
    auto cpppacket =
        UartProtocolV1Packet::createShakeHandPacket(packetSerialNum, route);
    UP_buf_t packet;
    packet.buf = cpppacket->buf.data();
    packet.len = cpppacket->buf.size();

    // UP_construct_packet(basic_packt, packet_config);

    uart_protocol_handler_t uart_protocol_handler;
    uart_protocol_handler_init(&uart_protocol_handler);

    /**解析包 */
    UPProcessPushRawDataRet_t ret = UP_process_push_raw_data(
        &uart_protocol_handler, packet.buf, packet.len);

    EXPECT_TRUE(ret.success);
    EXPECT_TRUE(ret.error_code == kErrorCode_Success);
    EXPECT_TRUE(ret.shouldProcessRawDataNow);

    int receive_packet = 0;
    call_up_process_raw_data(
        &uart_protocol_handler, [&](uart_protocol_handler_t* ret_hander,
                                    UP_packet_process_ret_t ret_process_statu,
                                    UP_packet_container_t* container) {
          receive_packet++;

          EXPECT_EQ(ret_process_statu.error_code, kErrorCode_Success);
          EXPECT_EQ(ret_process_statu.receive_packet_serial_num,
                    packetSerialNum);
          EXPECT_TRUE(container != NULL);
          EXPECT_TRUE(ret_hander == &uart_protocol_handler);

          EXPECT_EQ(container->useful_size, packet.len);

          EXPECT_EQ(container->basic_packet.packet_type, kShakeHandPacket);

          EXPECT_EQ(container->basic_packet.serial_num, packetSerialNum);

          EXPECT_EQ(container->basic_packet.route, route);

          // subpacket验证
        });
    EXPECT_TRUE(receive_packet == 1);
  }
};

class TestSystemEventReport {
 public:
  void test(uint8_t packetSerialNum, uint8_t route,UP_GenernalSystemEvent_t systemEvent,
            vector<int32_t> int32_value_table, bool bool_value_table) {
    auto cpppacket = UartProtocolV1Packet::createSystemEventPacket(
        packetSerialNum, route, systemEvent, int32_value_table,
        bool_value_table);
    UP_buf_t packet;
    packet.buf = cpppacket->buf.data();
    packet.len = cpppacket->buf.size();

    uart_protocol_handler_t uart_protocol_handler;
    uart_protocol_handler_init(&uart_protocol_handler);

    /**解析包 */
    UPProcessPushRawDataRet_t ret = UP_process_push_raw_data(
        &uart_protocol_handler, packet.buf, packet.len);

    EXPECT_TRUE(ret.success);
    EXPECT_TRUE(ret.error_code == kErrorCode_Success);
    EXPECT_TRUE(ret.shouldProcessRawDataNow);

    int receive_packet = 0;
    call_up_process_raw_data(
        &uart_protocol_handler, [&](uart_protocol_handler_t* ret_hander,
                                    UP_packet_process_ret_t ret_process_statu,
                                    UP_packet_container_t* container) {
          receive_packet++;

          EXPECT_EQ(ret_process_statu.error_code, kErrorCode_Success);
          EXPECT_EQ(ret_process_statu.receive_packet_serial_num,
                    packetSerialNum);
          EXPECT_TRUE(container != NULL);
          EXPECT_TRUE(ret_hander == &uart_protocol_handler);

          EXPECT_EQ(container->useful_size, packet.len);

          EXPECT_EQ(container->basic_packet.packet_type, kSystemEventReportPacket);

          EXPECT_EQ(container->basic_packet.serial_num, packetSerialNum);
          // subpacket验证
          EXPECT_EQ(container->packet.system_event_report_packet.event,
                    systemEvent);

          EXPECT_EQ(container->packet.system_event_report_packet.parameterNum,
                    (int)(int32_value_table.size() + 1));
          parameterCheck(
              container->packet.system_event_report_packet.parameters,
              int32_value_table, bool_value_table);

          EXPECT_EQ(container->basic_packet.route, route);

        });
    EXPECT_TRUE(receive_packet == 1);
  }
};

class TestHardwareOperatePacket {
 public:
  void test(uint8_t serial_num,uint8_t route, UP_module_type_code_t moduleType,
            uint8_t moduleNum, UP_operate_code_t operate_code,
            uint16_t dataPoint, vector<int32_t> int32_value_table,
            bool bool_value_table) {
    auto cpppacket = UartProtocolV1Packet::createHardwareOperatePacket(
        serial_num, route, moduleType, moduleNum, operate_code, dataPoint,
        int32_value_table, bool_value_table);
    UP_buf_t packet;
    packet.buf = cpppacket->buf.data();
    packet.len = cpppacket->buf.size();

    uart_protocol_handler_t uart_protocol_handler;
    uart_protocol_handler_init(&uart_protocol_handler);

    /**解析包 */
    UPProcessPushRawDataRet_t ret = UP_process_push_raw_data(
        &uart_protocol_handler, packet.buf, packet.len);

    EXPECT_TRUE(ret.success);
    EXPECT_TRUE(ret.error_code == kErrorCode_Success);
    EXPECT_TRUE(ret.shouldProcessRawDataNow);

    int receive_packet = 0;
    call_up_process_raw_data(
        &uart_protocol_handler, [&](uart_protocol_handler_t* ret_hander,
                                    UP_packet_process_ret_t ret_process_statu,
                                    UP_packet_container_t* container) {
          receive_packet++;

          EXPECT_EQ(ret_process_statu.error_code, kErrorCode_Success);
          EXPECT_EQ(ret_process_statu.receive_packet_serial_num, serial_num);
          EXPECT_TRUE(container != NULL);
          EXPECT_TRUE(ret_hander == &uart_protocol_handler);

          EXPECT_EQ(container->useful_size, packet.len);

          EXPECT_EQ(container->basic_packet.packet_type,
                    kHardwareOperatePacket);

          EXPECT_EQ(container->basic_packet.serial_num, serial_num);
          // subpacket验证

          EXPECT_EQ(container->packet.hardware_opearte_packet.data_point,
                    dataPoint);
          EXPECT_EQ(container->packet.hardware_opearte_packet.module_num,
                    moduleNum);
          EXPECT_EQ(container->packet.hardware_opearte_packet.module_type,
                    moduleType);
          EXPECT_EQ(container->packet.hardware_opearte_packet.operate_code,
                    operate_code);

          EXPECT_EQ(container->packet.hardware_opearte_packet.parameterNum,
                    int(int32_value_table.size() + 1));
          parameterCheck(container->packet.hardware_opearte_packet.parameters,
                         int32_value_table, bool_value_table);

          EXPECT_EQ(container->basic_packet.route, route);

        });
    EXPECT_TRUE(receive_packet == 1);
  }
};

TEST(TestUartPortocolV1Cpp, testUPparameterContainerPushxxx) {
  /**
   * @brief 简单测试ParameterContainerPush
   *
   */
  {
    uint8_t table[] = {0x00, 0x04, 0x00, 0x00, 0x00, 0x01};
    UP_parameters_container_t* para_container = UPParametersContainer_get();
    UPParametersContainer_push_int32(para_container, 1);
    EXPECT_TRUE(memcmp(table, para_container->parameters, sizeof(table)) == 0);
  }

  {
    uint8_t table[] = {0x00, 0x04, 0x80, 0x00, 0x00, 0x01};
    UP_parameters_container_t* para_container = UPParametersContainer_get();
    UPParametersContainer_push_int32(para_container, -1);
    EXPECT_TRUE(memcmp(table, para_container->parameters, sizeof(table)) == 0);
  }
  {
    uint8_t table[] = {0x00, 0x01, 0x01};
    UP_parameters_container_t* para_container = UPParametersContainer_get();
    UPParametersContainer_push_bool(para_container, true);
    EXPECT_TRUE(memcmp(table, para_container->parameters, sizeof(table)) == 0);
  }
  {
    uint8_t table[] = {0x00, 0x01, 0x00};
    UP_parameters_container_t* para_container = UPParametersContainer_get();
    UPParametersContainer_push_bool(para_container, false);
    EXPECT_TRUE(memcmp(table, para_container->parameters, sizeof(table)) == 0);
  }
}

TEST(TestUartPortocolV1Cpp, testParameterContainer) {
  TestGeneralReceiptPacket tester;
  tester.TestGeneralReceiptPacketConstructAndParse(1, 1, kErrorCode_Success,
                                                   {1, 2, 3, -1, -3, -5}, true);

  tester.TestGeneralReceiptPacketConstructAndParse(
      2, 2, kErrorCode_packetIsTooLong, {1, 3, 6, 3, 4, -5}, false);

  tester.TestGeneralReceiptPacketConstructAndParse(
      3, 3, kErrorCode_receivePacketOverflow, {1, 1, 3, 9, 6, -5}, true);

  tester.TestGeneralReceiptPacketConstructAndParse(
      4, 4, kErrorCode_moduleNotSupport, {1, 10, 3, -1, -3, -5}, false);

  tester.TestGeneralReceiptPacketConstructAndParse(
      5, 5, kErrorCode_DataPointNotSupport, {1, -2, 3, 1, -3, -5}, true);
}

TEST(TestUartPortocolV1Cpp, test1) {
  /**
   * @brief 测试硬件回执包
   */
  TestGeneralReceiptPacket tester;
  tester.TestGeneralReceiptPacketConstructAndParse(
      6, 6, kErrorCode_packetIsTooLong, {1, 2, 3, -1, -3, -5}, false);

  /**
   * @brief 测试ping包
   *
   */
  TestPingPacket testPing;
  testPing.test(0,0);
  for (size_t i = 0; i < 256; i++) testPing.test(i,i);

  /**
   * @brief 握手
   *
   */
  TestShakeHandPacket shakeHandPacket;
  shakeHandPacket.test(0,0);
  for (size_t i = 0; i < 256; i++) shakeHandPacket.test(i,i);

  /**
   * @brief 测试系统事件上报包
   *
   */
  TestSystemEventReport testSystemEventReport;
  testSystemEventReport.test(0x01,0x01, kSystemSetup, {1, 2, 3, -1, -3, -5},
                             true);

  /**
   * @brief 测试硬件模块操作包
   */
  TestHardwareOperatePacket testHardwareOperatePacket;

  testHardwareOperatePacket.test(0x01,0x01, MTC_HumanSensor, 1, kOperateCode_read, 1,
                                 {1, 2, 3, -1, -3, -5}, true);
  for (size_t i = 0; i < 256; i++)
    testHardwareOperatePacket.test(i, i, MTC_HumanSensor, 1, kOperateCode_read,
                                   i, {1, 2, 3, -1, -3, -5}, true);
}

static void testSendPacket(int packetNum, int sendTimes) {
  uint8_t sendBuf[1024 * 1024] = {0};
  size_t sendLength = 0;

  UP_buf_t packet;
  for (int i = 0; i < packetNum; i++) {
    packet = UPGenernalSystemReportPacket_construct(
        0, kSystemSetup,
        parameterConstruct({1, 2, -3, -4}, true));
    memcpy(sendBuf + sendLength, packet.buf, packet.len);
    sendLength += packet.len;
  }

  uart_protocol_handler_t uart_protocol_handler;
  uart_protocol_handler_init(&uart_protocol_handler);
  int receive_packet = 0;
  int each_packet_size = sendLength / sendTimes;
  int remain_size = sendLength % sendTimes;
  for (int i = 0; i < sendTimes; i++) {
    UPProcessPushRawDataRet_t ret = UP_process_push_raw_data(
        &uart_protocol_handler, sendBuf + each_packet_size * i,
        each_packet_size);
    EXPECT_TRUE(ret.success);

    call_up_process_raw_data(
        &uart_protocol_handler,
        [&](uart_protocol_handler_t* ret_hander,
            UP_packet_process_ret_t ret_process_statu,
            UP_packet_container_t* container) { receive_packet++; });
  }
  if (remain_size != 0) {
    UPProcessPushRawDataRet_t ret = UP_process_push_raw_data(
        &uart_protocol_handler, sendBuf + each_packet_size * sendTimes,
        remain_size);
    EXPECT_TRUE(ret.success);
    call_up_process_raw_data(
        &uart_protocol_handler,
        [&](uart_protocol_handler_t* ret_hander,
            UP_packet_process_ret_t ret_process_statu,
            UP_packet_container_t* container) { receive_packet++; });
  }
  EXPECT_EQ(receive_packet, packetNum);
}

static void testSendPacketWithErrorPacket(int packetNum, int sendTimes) {
  uint8_t sendBuf[1024 * 1024] = {0};
  size_t sendLength = 0;

  UP_buf_t packet;
  uint8_t fakePacet[] = {1, 2, 3, 4};
  for (int i = 0; i < packetNum; i++) {
    packet = UPGenernalSystemReportPacket_construct(
        0, kSystemSetup,
        parameterConstruct({1, 2, -3, -4}, true));
    memcpy(sendBuf + sendLength, packet.buf, packet.len);
    sendLength += packet.len;
    memcpy(sendBuf + sendLength, fakePacet, sizeof(fakePacet));
    sendLength += sizeof(fakePacet);
  }

  uart_protocol_handler_t uart_protocol_handler;
  uart_protocol_handler_init(&uart_protocol_handler);
  int receive_packet = 0;
  int each_packet_size = sendLength / sendTimes;
  int remain_size = sendLength % sendTimes;
  for (int i = 0; i < sendTimes; i++) {
    UPProcessPushRawDataRet_t ret = UP_process_push_raw_data(
        &uart_protocol_handler, sendBuf + each_packet_size * i,
        each_packet_size);
    EXPECT_TRUE(ret.success);

    call_up_process_raw_data(
        &uart_protocol_handler,
        [&](uart_protocol_handler_t* ret_hander,
            UP_packet_process_ret_t ret_process_statu,
            UP_packet_container_t* container) { receive_packet++; });
  }
  if (remain_size != 0) {
    UPProcessPushRawDataRet_t ret = UP_process_push_raw_data(
        &uart_protocol_handler, sendBuf + each_packet_size * packetNum,
        remain_size);
    EXPECT_TRUE(ret.success);
    call_up_process_raw_data(
        &uart_protocol_handler,
        [&](uart_protocol_handler_t* ret_hander,
            UP_packet_process_ret_t ret_process_statu,
            UP_packet_container_t* container) { receive_packet++; });
  }
  EXPECT_EQ(receive_packet, packetNum);
}

TEST(TestUartPortocolV1Cpp, test2) {
  /**
   * @brief
   * 构造三个包，分2次下发,正确解析出三个包
   */
  testSendPacket(3, 2);

  /**
   * @brief
   * 构造一个包，分3次下发,正确解析出一个包
   */
  testSendPacket(1, 3);
  /**
   * @brief 在包前面添加错误packet,在包后面添加错误packet
   */

  testSendPacketWithErrorPacket(3, 2);
  testSendPacketWithErrorPacket(1, 3);
}
