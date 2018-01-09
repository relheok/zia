#ifndef TESTMODULE_HPP_
# define TESTMODULE_HPP_

# include <iostream>
# include "conf.h"
# include "module.h"
# include "http.h"

typedef zia::api::Module *(*myModule)();

namespace zia::api {
  class   TestModule : public Module {
  public:
    TestModule();
    TestModule(TestModule const &);
    TestModule  &operator=(TestModule const &);
    virtual ~TestModule();

    // virtual bool config(const Conf &conf);
    virtual bool config();
    virtual bool exec(HttpDuplex& http);
  };
}

#endif /* end of include guard: TESTMODULE_HPP_ */
