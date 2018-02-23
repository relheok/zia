# pragma once

# include <iostream>
# include <fstream>
# include <iomanip>

# include "IModule.hpp"

# define FILE_PATH "Logs"

typedef zia::api::Module *(*myModule)();

namespace zia::api {
  class LogModule : public IModule {
    public:
      LogModule();
      LogModule(LogModule const &);
      LogModule &operator=(LogModule const &);
      virtual ~LogModule();

      virtual bool config(const Conf &conf);
      virtual bool exec(HttpDuplex &http);
      virtual unsigned int getPriority() const;

    private:
      unsigned int  _prio;
  };
}
