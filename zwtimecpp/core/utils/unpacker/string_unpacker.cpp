#include "string_unpacker.hpp"
#include "zwtimecpp/core/utils/string_utils.hpp"
using namespace std;
using namespace zwsd;
using namespace core;

void StringUnpacker::feddata(const char* rawData, size_t len,
                             StringUnpackerOnString_t unpacker) {
  if (nullDelims) {
    /* code */
    int strBeginOff = 0;
    for (unsigned i = 0; i < len; ++i) {
      if (rawData[i] < '\0' || rawData[i] > 127 /*删除线*/) {
        vector<uint8_t> input(rawData, rawData + len);
        logger->error(
            "{} feddata encounter error input {} off {}, rawData{} ,delim is "
            "{}",
            name, (uint8_t)rawData[i], i, input, "\\0");
        buf.clear();
        return;
      }
      if (rawData[i] == '\0') {
        buf.insert(buf.size(), &rawData[strBeginOff]);
        if (unpacker) unpacker(buf);
        buf.erase();
        strBeginOff = i + 1;
      } else if (rawData[i] != '\0' && i + 1 == len) {
        buf.insert(buf.size(),
                   string(&rawData[strBeginOff],
                          &rawData[strBeginOff] + len - strBeginOff));
        logger->info("buf {}", buf);
      }
    }

  } else {
    //如果不是以\0为为分割符号StringUnpacker是不允许输入\0的,否则会造成部分数据丢失
    for (unsigned i = 0; i < len; ++i) {
      if (rawData[i] <= '\0' /*这里没有写错，是小于等于 */ ||
          rawData[i] > 127 /*删除线*/) {
        vector<uint8_t> input(rawData, rawData + len);
        logger->error(
            "{} feddata encounter error input {} off {}, rawData{} ,delim is "
            "{}",
            name, (uint8_t)rawData[i], i, input, delim);

        buf.clear();
        return;
      }
    }

    if (len != 0) {
      buf.insert(buf.size(), rawData, len);
      int off = 0;
      std::vector<string> result = StringUtils::splitByStrDelim(buf, delim);
      string back = result.back();
      result.pop_back();
      for (auto& var : result) {
        if (unpacker) unpacker(var);
      }
      buf = back;
    }
  }

  if (maxSize >= 0 && buf.size() > (size_t)maxSize) {
    logger->error("{} cache buf is overflow  curSize:{} > maxSize:{}", name,
                  buf.size(), maxSize);
    buf.clear();
  }
}