#pragma once
#include <cli/cliasyncsession.h>
#include <cli/clifilesession.h>
#include "cli/cli.h"
#include "cli/clilocalsession.h"  // include boost asio

#if BOOST_VERSION < 106600
#define CLI_START(rootMenu)                                                \
  boost::asio::io_service ioc;                                             \
  cli::Cli clivar(std::move(rootMenu));                                    \
  clivar.ExitAction(                                                       \
      [](auto &out) { out << "Goodbye and thanks for all the fish.\n"; }); \
  cli::CliLocalTerminalSession localSession(clivar, ioc, std::cout, 200);  \
  localSession.ExitAction([&ioc](auto &out) {                              \
    out << "Closing App...\n";                                             \
    ioc.stop();                                                            \
  });                                                                      \
  boost::asio::io_service::work work(ioc);                                 \
  ioc.run();

#else

#define CLI_START(rootMenu)                                                \
  boost::asio::io_context ioc;                                             \
  cli::Cli clivar(std::move(rootMenu));                                    \
  clivar.ExitAction(                                                       \
      [](auto &out) { out << "Goodbye and thanks for all the fish.\n"; }); \
  cli::CliLocalTerminalSession localSession(clivar, ioc, std::cout, 200);  \
  localSession.ExitAction([&ioc](auto &out) {                              \
    out << "Closing App...\n";                                             \
    ioc.stop();                                                            \
  });                                                                      \
  auto work = boost::asio::make_work_guard(ioc);                           \
  ioc.run();

#endif