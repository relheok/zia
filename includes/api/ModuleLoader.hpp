#ifndef MODULELAUNCHER_HPP_
# define MODULELAUNCHER_HPP_

# include <iostream>
# include <memory>
# include <dlfcn.h>
# include "module.h"
# include "Error.hpp"

namespace zia::api {
  typedef Module *(*myModule)();

  using ListItem = std::pair<Module *, void *>;
  using ModulesList = std::vector<ListItem>;

  class     ModuleLoader {
  public:
    ModuleLoader();
    ModuleLoader(ModuleLoader const &);
    ModuleLoader  &operator=(ModuleLoader const &);
    ~ModuleLoader();

    /**
    * Load the module from the location [path]
    * \return a pointer to the loaded module (automatically deleted at destruction)
    */
    Module        *loadModule(std::string const &path);

    /**
    * Getters
    */
    ModulesList   getModules() const;

  private:
    ModulesList     _modules;
  };
}

#endif /* end of include guard: MODULELAUNCHER_HPP_ */
