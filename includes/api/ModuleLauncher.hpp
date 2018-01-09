#ifndef MODULELAUNCHER_HPP_
# define MODULELAUNCHER_HPP_

# include <iostream>
# include <memory>
# include "module.h"
# include "Error.hpp"

typedef zia::api::Module *(*myModule)(std::string const &);

namespace zia::api {
  class     ModuleLauncher {
  public:
    ModuleLauncher();
    ModuleLauncher(ModuleLauncher const &);
    ModuleLauncher  &operator=(ModuleLauncher const &);
    ~ModuleLauncher();

    Module    *launchModule(std::string const &);

  private:
    std::unique_ptr<Module> _module{nullptr};
    std::string             _path;
  };
}

#endif /* end of include guard: MODULELAUNCHER_HPP_ */
