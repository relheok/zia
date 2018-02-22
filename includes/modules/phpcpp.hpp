#ifndef CPPMODULE_HPP_
# define CPPMODULE_HPP_

# include <iostream>
# include <memory>
# include "module.h"
# include "http.h"
# include "conf.h"
# include "net.h"

namespace zia::api {
  class     cppModule : public Module {
  public:
    cppModule();
    cppModule(const cppModule &);
    cppModule &operator=(const cppModule &);
    ~cppModule();
    
    bool          initComponent();
    std::string   getName() const;
    void          setName(std::string const &);
    void	  getModule();
    virtual bool  config(const Conf& conf);
    virtual bool  exec(HttpDuplex& http);
    
  private:
    std::unique_ptr<cppModule>  _ptr{nullptr};
    std::string			_name;
  };
}

#endif /* end of include guard: CPPMODULE_HPP_ */
