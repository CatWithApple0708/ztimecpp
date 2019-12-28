#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "zwtimecpp/core/core.hpp"
#include "zwtimecpp/core/logger/logger.hpp"
#include "zwtimecpp/core/test/test_utils/runner_manager.hpp"
#include "zwtimecpp/core/thread/thread.hpp"
#include "zwtimecpp/core/utils/argh/argh.h"
#include "zwtimecpp/core/utils/better-enums/enum.h"
#include "zwtimecpp/core/utils/memory_utils.hpp"
#include "zwtimecpp/core/utils/nlohmann/json.hpp"
using namespace std;
using namespace zwsd;
using namespace core;

class SpeedTest : public Runner {
  ENABLE_LOGGER(SpeedTest);
  atomic<int32_t> receiveOrSendKB;
  int fileLen = 1;
  atomic<int32_t> receiveOrSendKBNotClear;
  atomic<float> speed;
  unique_ptr<Thread> thread;

 public:
  virtual void run(int argc, const char **argv) override;
  virtual string introduction(logger_t logForHelp) override {
    logger->info("{}\n\t{}", "-s", "server");
    logger->info("{}\n\t{}", "-f", "测试文件");
    logger->info("{}\n\t{}", "-p", "端口");
    logger->info("{}\n\t{}", "-a", "ip address");
    return "";
  }

  void startTimer() {
    thread.reset(new Thread("SpeedTest", [this]() {
      while (true) {
        receiveOrSendKB = 0;
        ThisThread().sleepForMs(1000);
        speed = receiveOrSendKB / 1000;
        if (fileLen == 0) {
          fileLen = 1;
        }

        if (speed.load() > 1024 * 1024) {
          printf("trans %.2f%%  %.2f G/s \n",
                 (float)receiveOrSendKBNotClear / fileLen * 100,
                 speed.load() / 1024 / 1024);
        } else if (speed.load() > 1024 ) {
          printf("trans %.2f%%  %.2f M/s \n",
                 (float)receiveOrSendKBNotClear / fileLen * 100,
                 speed.load() / 1024);
        } else {
          printf("trans %.2f%%  %.2f kb/s \n",
                 (float)receiveOrSendKBNotClear / fileLen * 100, speed.load());
        }
      }
    }));
  }

  int setupAsClient(string ip, string portstr, string file_path) {
    int port = atoi(portstr.c_str());
    //创建TCP通信socket
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket == -1) {
      perror("create socketfd is fail\n");
      return -1;
    }

    //目的地址
    struct sockaddr_in dest_addr = {0};
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    dest_addr.sin_addr.s_addr = inet_addr(ip.c_str());

    int ret = -1;
    //请求连接目标地址

    ret = connect(tcp_socket, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (ret != 0)  //连接成功
    {
      perror("connect failed\n");
      return -1;
    }

    printf("\nConnect succeed!\n");

    char file_name[128] = {0};   //文件路径
    char file_info[2048] = {0};  //文件信息

    char buf[1024] = {0};

    //获取用户输入的文件路径

    //从文件路径中获取文件名，如"test/a.txt" ==> "a.txt"
    strncpy(file_name, basename(file_path.c_str()), sizeof(file_name));

    //打开文件
    int fd = open(file_path.c_str(), O_RDWR);
    if (fd == -1) {
      printf("open [%s]  failed", file_path.c_str());
      return -1;
    }

    //计算文件大小
    int len = lseek(fd, 0, SEEK_END);

    //文件光标偏移到文件开始位置
    lseek(fd, 0, SEEK_SET);

    //将文件大小和文件名存放到file_info
    sprintf(file_info, "%d", len);
    strcpy(file_info + 16, file_name);

    // 将需要上传的文件名告诉对方
    size_t writeret = write(tcp_socket, file_info, 144);
    if (writeret != 144) {
    }

    int send_len = 0;  //记录发送了多少字节
    fileLen = len;
    while (1) {
      bzero(buf, sizeof(buf));
      //读取数据
      ret = read(fd, buf, sizeof(buf));
      if (ret <= 0) {
        printf("send file[%s] succeed!!!!\n", file_name);
        break;
      }

      //发送数据
       writeret = write(tcp_socket, buf, ret);
       if (writeret < 0) {
       }

       send_len += ret;  //统计发送了多少字节
       receiveOrSendKB += ret;
       receiveOrSendKBNotClear += ret;

       //上传文件的百分比
       //   printf("uploading %.2f%%  %.2f kb/s \n", (float)send_len / len *
       //   100,
       //          speed.load());
    }

    // 关闭文件
    close(fd);
    //关闭通信socket
    close(tcp_socket);
    return 0;
  }

  int setupAsServer(string prot) {
    //判断命令行参数是否匹配
    //创建tcp通信socket
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket == -1) {
      perror("create socketfd failed\n");
      return -1;
    }

    //绑定地址
    struct sockaddr_in local_addr = {0};
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(atoi(prot.c_str()));
    local_addr.sin_addr.s_addr = INADDR_ANY;  //让系统自动检测本地网卡IP并绑定
    int ret =
        bind(tcp_socket, (struct sockaddr *)&local_addr, sizeof(local_addr));
    if (ret == -1) {
      perror("bind  failed\n");
      return -1;
    }

    //设置监听队列
    ret = listen(tcp_socket, 5);
    if (ret == -1) {
      perror("listen is fail\n");
      return -1;
    }

    //客户端地址信息
    struct sockaddr_in client_addr = {0};
    socklen_t len = sizeof(client_addr);

    printf("server is running\n");

    //通信socket
    int new_socket = 0;

    while (1) {
      //等待客户端的请求
      new_socket = accept(tcp_socket, (struct sockaddr *)&client_addr, &len);
      if (new_socket < 0) {
        perror("accept error\n");
        continue;
      }

      //输出对方的IP地址信息
      printf("client connected [%s:%d]\n", inet_ntoa(client_addr.sin_addr),
             ntohs(client_addr.sin_port));

      char file_len[16] = {0};    //文件长度
      char file_name[128] = {0};  //文件名称
      char buf[1024] = {0};       //数据缓冲区
      //读取文件大小和文件名称
      ssize_t readret = read(new_socket, buf, sizeof(buf));
      if (readret < 0) {
      }

      strncpy(file_len, buf, sizeof(file_len));  //取出文件大小
      strncpy(file_name, buf + sizeof(file_len),
              sizeof(file_name));  //取出文件名称

      printf("ready receive!!!! file name:[%s] file size:[%s] \n", file_name,
             file_len);

      //新的文件名
      sprintf(buf, "recv-%s", file_name);

      //创建新文件
      int fd = open(buf, O_RDWR | O_CREAT | O_TRUNC, 0666);

      int size = atoi(file_len);  //文件大小
      int write_len = 0;          //记录已写入的字节数
      fileLen = size;
      //接收文件
      while (1) {
        bzero(buf, 1024);

        //接收文件数据
        ret = read(new_socket, buf, sizeof(buf));
        if (ret <= 0) {
          printf("\n [recv-%s] receive file done!!!\n", file_name);
          break;
        }

        //将数据写入文件
        ret = write(fd, buf, ret);
        receiveOrSendKB += ret;
        write_len += ret;  //记录写入的字节数
        receiveOrSendKBNotClear += ret;

        //动态的输出接收进度
        // printf("uploading %.2f%%  %.2f kb/s\n", (float)write_len / size * 100,
        //        speed.load());
      }

      break;
    }

    //关闭socket
    close(new_socket);
    close(tcp_socket);

    return 0;
  }
};

void SpeedTest::run(int argc, const char **argv) {
//命令行参数demo ./runner_main SpeedTest -n name
//--string_full_name -b bool_value -i int_value
#if 0

logger->info(
"string_short_name {} string_full_name {} int_value {} times {} "
"bool_value{}",
string_short_name, string_full_name, int_value, times, bool_value);
#endif
  Core::initialize();
  shared_ptr<Core> core = Core::Instance();

  argh::parser cmdl;
  string file;
  string port;
  string address;
  bool server = false;
  cmdl.add_params({"s", "f", "p", "a"});
  cmdl.parse(argc, argv);
  server = cmdl["s"];

  cmdl("-f", 1) >> file;
  cmdl("-p", 1) >> port;
  cmdl("-a", 1) >> address;

  if (server) {
    logger->info("start server {}", port);
    startTimer();
    setupAsServer(port);

  } else {
    logger->info("start client {}:{} {}", address, port, file);
    startTimer();
    setupAsClient(address, port, file);
  }

  ThisThread().sleep();
}

ENABLE_TEST2(SpeedTest, "SpeedTest")
