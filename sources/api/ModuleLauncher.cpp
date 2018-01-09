#include "ModuleLauncher.hpp"

namespace zia::api {
  ModuleLauncher::ModuleLauncher() {}

  ModuleLauncher::ModuleLauncher(ModuleLauncher const &copy) {
    _name = copy._name;
  }

  ModuleLauncher  &ModuleLauncher::operator=(ModuleLauncher const &copy) {
    _name = copy._name;
    return (*this);
  }

  ModuleLauncher::~ModuleLauncher() {
    // if (_plib)
    //   dlclose(_plib);
  }

  Module      *ModuleLauncher::launchModule(std::string const &path, std::string const &name) {
    void      *ptr;
    myModule  fptr;

    _name = name;
    if (!(_plib = dlopen(path.c_str(), RTLD_LAZY)) || !(ptr = dlsym(_plib, "Create")))
      throw ModuleError("can't open module " + name);
    fptr = (myModule)ptr;
    _module.reset((*fptr)());
    return _module.get();
  }
}
