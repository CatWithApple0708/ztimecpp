#pragma once

#include <sstream>
#include <string>
#include <vector>
namespace zwsd {
namespace core {

using namespace std;
class StringUtils {
 public:
  /**
   * @brief 字符串分离
   *
   * @param str "192.168.1.198"
   * @param delims "."
   * @param maxSplits 10 最多分离的数量 maxSplits == 0 无限切割
   * @return vector<string> {192,168,1,198}
   */
  static inline vector<string> split(const string& str, const char* delims,
                                     unsigned int maxSplits = 0) {
    if (str.empty()) {
      return {};
    }

    unsigned int numSplits = 0;
    // Use STL methods
    size_t start, pos;
    start = 0;
    vector<string> ret;
    do {
      pos = str.find_first_of(delims, start);

      if (pos == start) {
        ret.push_back(string());
        start = pos + 1;
      } else if (pos == string::npos ||
                 (maxSplits && numSplits + 1 == maxSplits)) {
        // Copy the rest of the string
        ret.emplace_back(string());
        *(ret.rbegin()) = string(str.data() + start, str.size() - start);
        break;
      } else {
        // Copy up to delimiter
        // ret.push_back( str.substr( start, pos - start ) );
        ret.push_back(string());
        *(ret.rbegin()) = string(str.data() + start, pos - start);
        start = pos + 1;
      }

      ++numSplits;

    } while (pos != string::npos);
    return move(ret);
  }

  static string& replaceAllDistinct(string& str, const string& old_value,
                                    const string& new_value) {
    for (string::size_type pos(0); pos != string::npos;
         pos += new_value.length()) {
      if ((pos = str.find(old_value, pos)) != string::npos) {
        str.replace(pos, old_value.length(), new_value);
      } else {
        break;
      }
    }
    return str;
  }

  static bool isLegalHex(char c) {
    if (c >= '0' && c <= '9') {
      return true;
    } else if (c >= 'A' && c <= 'F') {
      return true;
    } else if (c >= 'a' && c <= 'f') {
      return true;
    }
    return false;
  }
  /**
   * @brief 16进制转换成byte数组
   * 
   * @param in 
   * @param delims 分隔符，如果没有可写 "",
   * @param byteTable 输出byte数组
   * @return true 成功转换
   * @return false 出错
   */
  static bool hexStringToBytes(string in, string delims,
                               vector<uint8_t>& byteTable) {
    string hexTable;
    byteTable.clear();
    if (!delims.empty()) {
      hexTable = replaceAllDistinct(in, delims, "");
      /* code */
    } else {
      hexTable = in;
    }

    if (hexTable.length() % 2 != 0) {
      // printf("ss\n");
      return false;
    }

    try {
      for (unsigned i = 0; i < hexTable.length(); i += 2) {
        string hex = hexTable.substr(i, 2);
        // printf("ss1 %s\n", hex.c_str());

        if (!isLegalHex(hex.c_str()[0])) {
          return false;
        }
        if (!isLegalHex(hex.c_str()[1])) {
          return false;
        }

        int value = std::stoi(hex, 0, 16);
        byteTable.push_back((uint8_t)value);
      }
    } catch (const std::exception& e) {
      // printf("ss1\n");
      return false;
    }
    return true;
  }

  static bool decimalStringToBytes(string in, string delims,
                                   vector<uint8_t>& byteTable) {
    byteTable.clear();
    if (delims.empty()) return false;
    vector<string> decimalTable = split(in, delims.c_str());

    try {
      for (auto& var : decimalTable) {
        int value = std::stoi(var, 0, 10);
        if (value > 255) return false;
        byteTable.push_back((uint8_t)value);
      }
    } catch (const std::exception& e) {
      return false;
    }
    return true;
  }

  static char byteToChar(uint8_t byte) {
    if (byte < 10) {
      return '0' + byte;
    } else {
      return 'A' + (byte - 10);
    }
    throw std::out_of_range("byteToChar out of range");
    return 'x';
  }

  static string bytesToString(vector<uint8_t>& byteTable) {
    string ret;
    for (auto& var : byteTable) {
      uint8_t hight4 = var >> 4 & 0x0f;
      uint8_t low4 = var >> 0 & 0x0f;
      ret += byteToChar(hight4);
      ret += byteToChar(low4);
    }
    return ret;
  }
};

}  // namespace core
}  // namespace zwsd
