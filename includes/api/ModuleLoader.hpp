#ifndef MODULELAUNCHER_HPP_
# define MODULELAUNCHER_HPP_

# include <iostream>
# include <memory>
# include <dlfcn.h>
# include "module.h"
# include "Error.hpp"

typedef zia::api::Module *(*myModule)();

namespace zia::api {
  class     ModuleLoader {
  public:
    ModuleLoader();
    ModuleLoader(ModuleLoader const &);
    ModuleLoader  &operator=(ModuleLoader const &);
    ~ModuleLoader();

    /**
    * Load the module [name] from the location [path]
    */
    Module        *loadModule(std::string const &path, std::string const &name);

    /**
    * Call the config method of the loaded module with parameter [conf]
    * \return true on success, false otherwise
    */
    bool    configModule();

    /**
    * Getters
    */
    Module        *getModule();
    std::string   getName() const;

  private:
    std::unique_ptr<Module> _module{nullptr};
    std::string             _name;
    void                    *_plib{nullptr};
  };
}

#endif /* end of include guard: MODULELAUNCHER_HPP_ */
