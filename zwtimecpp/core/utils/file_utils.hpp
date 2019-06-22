//
// Created by zhaohe on 19-5-31.
//

#pragma once
#include <fstream>
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

#ifdef _MSC_VER
#include <windows.h>
#else
#include <pthread.h>
#include <unistd.h>
#endif

/**
 * 文件工具类。
 *
 * @author <a href="http://www.xfyun.cn">讯飞开放平台</a>
 */
class FileUtil {
 public:
  static bool exist(const string &path);

  static bool isDirectory(const string &path);

  /**
   * 当目录路径不存在时创建目录。
   *
   * @param path 路径，以"/"结尾
   */
  static bool makeDirIfNoExist(const string &path);

  static bool delFile(const string &filePath);

  static string readFileAsString(const string &filePath);

  static string getCurrentTime();

  /**
   * @brief
   * @note
   * @param  fileName: 文件名字
   * @param  suffix:　文件后缀
   * @param  maxNum: name.txt name1.txt name2.txt ..... nameMax.txt 
   * @retval
   */
  static string getRepetitionFileName(string fileName, string suffix,
                                      int maxNum = -1);
  static string getRepetitionDirName(string fileName, int maxNum = -1);

  static bool writeToFile(const string &fileName, const std::vector<char> &buf);

  static bool writeToFile(const string &fileName, const string &buf);

  // static void moveFile(string src, string des);

  /**
   * 新分配Buffer，读取文件到Buffer，Buffer使用完之后需要使用者手动释放。
   *
   * @return Buffer地址，文件读取错误返回NULL
   */
  static std::vector<char> readFileAsBuffer(const string &filePath);

  class DataFileHelper {
   private:
    pthread_mutex_t mMutex;

    const string mFileDir;

    fstream mIn;

    fstream mOut;

   public:
    DataFileHelper(const string &fileDir);

    ~DataFileHelper();

    bool openReadFile(const string &filePath, bool inCurrentDir = true);

    int read(char *buffer, int bufferLen);

    string readLine();

    void rewindReadFile();

    void closeReadFile();

    void createWriteFile(const string &suffix, bool append);

    void createWriteFile(const string &filename, const string &suffix,
                         bool append, bool inCurrentDir = true);

    bool write(const char *data, int dataLen, int offset, int writeLen);

    void closeWriteFile();

    void closeFile();
  };
};
}  // namespace core
}  // namespace zwsd
