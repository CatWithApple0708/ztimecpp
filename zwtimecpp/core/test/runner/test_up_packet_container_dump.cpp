//
// Created by zhaohe on 19-6-19.
//
#include "zwtimecpp/core/test/test_utils/runner_manager.hpp"

#include "zwtimecpp/core/logger/logger.hpp"
#include "zwtimecpp/core/thread/thread.hpp"
#include "zwtimecpp/core/utils/argh/argh.h"
#include "zwtimecpp/core/utils/better-enums/enum.h"
#include "zwtimecpp/core/utils/memory_utils.hpp"
#include "zwtimecpp/core/utils/nlohmann/json.hpp"

extern "C" {
#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_packet_container_dump.h"
#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_v1.h"
}

using namespace std;
using namespace zwsd;
using namespace core;

class TestUpPacketContainerDumper : public Runner {
  ENABLE_LOGGER(TestUpPacketContainerDumper);

 public:
  virtual void run(int argc, const char **argv) override;
  virtual string introduction(logger_t logForHelp) override {
    logger->info("-------------------{}-----------------------", getName());
    return "";
  }
};

void TestUpPacketContainerDumper::run(int argc, const char **argv) {
#if 0
  argh::parser cmdl;
  cmdl.add_params({"m", "u"});
  cmdl.parse(argc, argv);
#endif
  UP_packet_container_t container;

  container.basic_packet.packet_type = kHardwareOperatePacket;
  container.basic_packet.route = 1;
  container.basic_packet.packet = NULL;
  container.basic_packet.packet_length = 10;

  container.packet.hardware_opearte_packet.module_type = MTC_Weighting;
  container.packet.hardware_opearte_packet.operate_code = kOperateCode_write;
  container.packet.hardware_opearte_packet.data_point = 0x01;
  container.packet.hardware_opearte_packet.module_num = 2;

  char buf[3] = {0, 0, 1};
  UP_parameter_packet_t parameter;
  parameter.buf = (uint8_t *)buf;
  parameter.length = 3;

  container.packet.hardware_opearte_packet.parameterNum = 1;
  container.packet.hardware_opearte_packet.parameters[0] = parameter;
  int str_size = 0;
  char **str_table = up_packet_container_dump(&container, &str_size);

  for (int i = 0; i < str_size; ++i) {
    logger->info("{}", string(str_table[i]));
  }

  logger->info("{}", string(up_packet_container_dump_in_one_line(&container)));
}
ENABLE_TEST2(TestUpPacketContainerDumper, "测试串口协议Dump方法");
