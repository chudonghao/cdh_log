//
// Created by chudonghao on 2022/5/2.
//

#include <cdhlog.h>

int main(int argc, char *argv[]) {
  cdhlog::Init();
  CLOG_TRACE << 1;
  CLOG_DEBUG << 2;
  CLOG_INFO << 3;
  CLOG_WARN << 4;
  CLOG_ERROR << 5;
  CLOG_FATAL << 6;
  return 0;
}
