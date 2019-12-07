#ifndef __SOUND_UTLS_HPP__
#define __SOUND_UTLS_HPP__

#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <codecvt>
#include <cstdint>  // std::uint_least32_t
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
namespace zwsd {
namespace utils {

/**
 * @brief UrlEncode??
 *
 * @param x
 * @return unsigned char
 */
static inline unsigned char ToHex(unsigned char x) {
  return x > 9 ? x + 55 : x + 48;
}

static inline unsigned char FromHex(unsigned char x) {
  unsigned char y;
  if (x >= 'A' && x <= 'Z')
    y = x - 'A' + 10;
  else if (x >= 'a' && x <= 'z')
    y = x - 'a' + 10;
  else if (x >= '0' && x <= '9')
    y = x - '0';
  else
    assert(0);
  return y;
}

static inline std::string UrlEncode(const std::string &str) {
  std::string strTemp = "";
  size_t length = str.length();
  for (size_t i = 0; i < length; i++) {
    if (isalnum((unsigned char)str[i]) || (str[i] == '-') || (str[i] == '_') ||
        (str[i] == '.') || (str[i] == '~'))
      strTemp += str[i];
    else if (str[i] == ' ')
      strTemp += "+";
    else {
      strTemp += '%';
      strTemp += ToHex((unsigned char)str[i] >> 4);
      strTemp += ToHex((unsigned char)str[i] % 16);
    }
  }
  return strTemp;
}

static inline std::string UrlDecode(const std::string &str) {
  std::string strTemp = "";
  size_t length = str.length();
  for (size_t i = 0; i < length; i++) {
    if (str[i] == '+')
      strTemp += ' ';
    else if (str[i] == '%') {
      assert(i + 2 < length);
      unsigned char high = FromHex((unsigned char)str[++i]);
      unsigned char low = FromHex((unsigned char)str[++i]);
      strTemp += high * 16 + low;
    } else
      strTemp += str[i];
  }
  return strTemp;
}

/**
 * @brief 分词
 *
 * @param str   65292 ,  12290。  65307；  65306：
 * @return std::vector<std::string>
 */
static inline std::vector<std::string> split(std::string str, int word_size) {
  try {
    std::vector<std::string> result;
    std::string word;
    int idx = 0;

    bool enbale = false;

    // std::locale loc("en_US.UTF-8");
    // std::locale loc("zh_HK.UTF-8");
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;

    std::wstring ws = conv.from_bytes(str);
    std::wstring nws;
    //????????????
    for (wchar_t ch : ws) {
      //??????????
      // if (!ispunct(ch, loc)) {
      if (!(ch == 65292 || ch == 12290 || ch == 65307 || ch == 65306)) {
        nws.push_back(ch);
        if (idx > word_size) enbale = true;
      } else {
        if (enbale == true) {
          std::string ns = conv.to_bytes(nws);
          word += ns;
          result.push_back(word);
          word.clear();
          enbale = false;
          idx = 0;
        } else {
          nws.push_back(ch);
          std::string ns = conv.to_bytes(nws);
          word += ns;
        }
        nws.clear();
      }
      idx++;
    }
    if (idx != 0) {
      std::string ns = conv.to_bytes(nws);
      word += ns;
      result.push_back(word);
    }

    for (auto var : result) {
    }
    return result;
  } catch (const std::exception &e) {
    std::cout << "PlayControl::split Receive Expception " << e.what() << std::endl;
  }
  return {"分词失败,请检查本地字符集更新"};
}  // namespace utils

static inline std::vector<std::string> split(std::string str, char value) {
  std::vector<std::string> result;
  std::string word;
  int idx = 0;

  std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
  std::wstring ws = conv.from_bytes(str);
  std::wstring nws;
  for (wchar_t ch : ws) {
    // std::cout << "ch " << ch << std::endl;
    if ((ch == value)) {
      std::string ns = conv.to_bytes(nws);
      word += ns;
      result.push_back(word);
      word.clear();
      idx = 0;
    } else {
      nws.push_back(ch);
      std::string ns = conv.to_bytes(nws);
      word += ns;
      nws.clear();
      idx++;
    }
  }
  if (idx != 0) {
    std::string ns = conv.to_bytes(nws);
    word += ns;
    result.push_back(word);
  }
  return result;
}

static inline std::vector<int> UrlPunctuationSchedule(const std::string &str) {
  try {
    int s_idx = 0;
    std::vector<int> shedule_v;
    std::vector<int> shedule_idx_v;
    std::string word;
    int time;

    std::cout << "   size   " << str.size() << '\n';

    std::locale loc("en_US.UTF-8");
    // std::locale loc("zh_HK.UTF-8");
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::wstring ws = conv.from_bytes(str);
    std::wstring nws;
    //????????????
    for (wchar_t ch : ws) {
      //??????????
      s_idx++;
      if (!ispunct(ch, loc)) {
        if (ch >= 48 && ch <= 57) {
          time += 105;
        } else {
          time += 256;
        }
      } else {
        if (ch == 65292 || ch == 12290) {
          shedule_v.push_back(time);
        }
        time += 256;
      }
    }

    for (auto var : shedule_v) {
      int shedule = var * 100 / s_idx;
      shedule_idx_v.push_back(shedule);
    }

    return shedule_idx_v;
  } catch (const std::exception &e) {
    std::cout << "PlayControl::split Receive Expception " << e.what();
  }
}

}  // namespace utils
}  // namespace soundbox
#endif