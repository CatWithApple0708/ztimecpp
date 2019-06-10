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
   * @param maxSplits 10 最多分离的数量
   * @return vector<string> {192,168,1,198}
   */
  static inline vector<string> split(const string& str, const char* delims,
                                     unsigned int maxSplits) {
    if (str.empty()) {
      return;
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
};

}  // namespace core
}  // namespace zwsd
