#ifndef TESTMODULE_HPP_
# define TESTMODULE_HPP_

# include <iostream>
# include "../server/api/conf.h"
# include "../server/api/module.h"
# include "../server/api/http.h"

typedef zia::api::Module *(*myModule)();

namespace zia::api {
  class   TestModule : public Module {
  public:
    TestModule();
    TestModule(TestModule const &);
    TestModule  &operator=(TestModule const &);
    virtual ~TestModule();

    virtual bool config(const Conf &conf);
    virtual bool exec(HttpDuplex &http);
    virtual void test();
  };
}

#endif /* end of include guard: TESTMODULE_HPP_ */
