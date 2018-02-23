# include "LogModule.hpp"

extern "C" {
  zia::api::LogModule *create() {
    return (new zia::api::LogModule);
  }
}

namespace zia::api {
  LogModule::LogModule() : _prio(100) {}

  LogModule::LogModule(LogModule const &copy) {
    (void)copy;
  }

  LogModule &LogModule::operator=(LogModule const &copy) {
    (void)copy;
    return (*this);
  }

  LogModule::~LogModule() {}

  bool LogModule::config(const Conf &conf) {
    (void)conf;
    return true;
  }

  bool LogModule::exec(HttpDuplex &http) {
    std::ofstream  file;
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);

    file.open(FILE_PATH);
    file << "Time : " << std::put_time(std::localtime(&now_c), "%c") << '\n';
    file.close();
    (void)http;
    return true;
  }

  unsigned int LogModule::getPriority() const {
    return _prio;
  }
}
