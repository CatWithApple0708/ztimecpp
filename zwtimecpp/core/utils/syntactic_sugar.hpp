#pragma once
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>
namespace zwsd {
namespace core {
using namespace std;
void ztry(function<void()> call, function<void(string errorMsg)> onErrorMsg = nullptr) {
  try {
    if (call) call();
  } catch (const std::exception& e) {
    if (onErrorMsg) onErrorMsg(e.what());
  }
}
}
}  // namespace zwsd