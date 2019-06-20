//
// Created by zhaohe on 19-6-20.
//

#include "cxv_logger_factory.hpp"
#include "zwtimecpp/core/utils/file_utils.hpp"
#include "zwtimecpp/core/constant.hpp"
using namespace std;
using namespace zwsd;
using namespace core;
CxvLogger::CxvLogger(string name, bool enable) {
  this->enable = enable;
  if (!enable) {
    return;
  }
  string fileName;
  for (size_t i = 0; i < CoreConstant::MaxCxvLoggerFileNum; i++) {
    if (FileUtil::exist(fmt::format("{}{}.cxv", name, i))) {
      continue;
    } else {
      fileName = fmt::format("{}{}.cxv", name, i);
    }
  }
  if (fileName.empty()) {
    fileName = fmt::format("{}{}.cxv", name, "_reachMaxNumFile");
  }

  ofile.reset(
      new ofstream(name, std::ios::trunc | std::ios::binary | std::ios::out));
}
void CxvLogger::record_internal(const string& oneRecord) {
  if (!enable) return;
  ofile->write(oneRecord.data(), oneRecord.size());
}

cxvLogger_t CxvLoggerFactory::createCxvLogger(string name) {
  if (savePath.empty()) savePath = CoreConstant::CxvLoggerRootDir;

  string fullpath = savePath + "/" + name;
  cxvLogger_t cvxlogger;
  if (!FileUtil::makeDirIfNoExist(fullpath)) {
    logger->warn("create CxvLogger fail , make dir [{}] fail", fullpath);
    cvxlogger.reset(new CxvLogger("", false));
  } else {
    cvxlogger.reset(new CxvLogger(fullpath, enable));
  }
  return cvxlogger;
}
