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
#include "zwtimecpp/protocol/uart_protocol_v1/uart_protocol_v1.h"
}

using namespace std;
using namespace zwsd;
using namespace core;

class ShowUartProtocolV1 : public Runner {
  ENABLE_LOGGER(ShowUartProtocolV1);

 public:
  virtual void run(int argc, const char **argv) override;
  virtual string introduction(logger_t logForHelp) override {
    logger->info("-------------------{}-----------------------", getName());
    return "";
  }
};

void ShowUartProtocolV1::run(int argc, const char **argv) {
#if 0
  argh::parser cmdl;
  cmdl.add_params({"m", "u"});
  cmdl.parse(argc, argv);
#endif
  logger->info("basic_packet_header size {}",
               sizeof(UPAnalysis_basic_packet_header_t));
  logger->info("basic_packet_tail size {}",
               sizeof(UPAnalysis_basic_packet_tail_t));
  logger->info("genernal_receipt_packet_header size {}",
               sizeof(UPAnalysis_genernal_receipt_packet_header_t));
  logger->info("shake_hand_packet_header size {}",
               sizeof(UPAnalysis_shake_hand_packet_header_t));
  logger->info("ping_packet_header size {}",
               sizeof(UPAnalysis_ping_packet_header_t));
  logger->info("hardware_operate_packet_header size {}",
               sizeof(UPAnalysis_hardware_operate_packet_header_t));
  logger->info("system_event_report_packet size {}",
               sizeof(UPAnalysis_system_event_report_packet_t));
}
ENABLE_TEST(ShowUartProtocolV1);
