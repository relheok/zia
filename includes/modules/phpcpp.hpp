#ifndef CPPMODULE_HPP_
# define CPPMODULE_HPP_

# include <iostream>
# include <memory>
# include "IModule.hpp"
# include "http.h"
# include "conf.h"
# include "net.h"

namespace zia::api {
  class     cppModule : public IModule {
  public:
    cppModule();
    cppModule(const cppModule &);
    cppModule &operator=(const cppModule &);
    ~cppModule();

    bool          initComponent();
    virtual bool  config(const Conf& conf);
    virtual bool  exec(HttpDuplex& http);

    virtual unsigned int getPriority() const { return 1; }
  };
}

#endif /* end of include guard: CPPMODULE_HPP_ */
