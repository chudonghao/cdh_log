//
// Created by chudonghao on 2022/5/2.
//

#include <cdhlog_setup.hpp>

int main(int argc, char *argv[]) {
  cdhlog::Setup();

  CLOG_TRACE << 111;
  CLOG_DEBUG << 111;
  CLOG_INFO << 111;
  CLOG_WARN << 111;
  CLOG_ERROR << 111;
  CLOG_FATAL << 111;

  return 0;
}
