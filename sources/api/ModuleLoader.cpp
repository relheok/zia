#include "ModuleLoader.hpp"

namespace zia::api {
  ModuleLoader::ModuleLoader() {}

  ModuleLoader::ModuleLoader(ModuleLoader const &copy) {
    _name = copy._name;
  }

  ModuleLoader  &ModuleLoader::operator=(ModuleLoader const &copy) {
    _name = copy._name;
    return (*this);
  }

  ModuleLoader::~ModuleLoader() {
    delete _module.release();
    if (_plib)
      dlclose(_plib);
  }

  Module      *ModuleLoader::loadModule(std::string const &path, std::string const &name) {
    void      *ptr;
    myModule  fptr;

    _name = name;
    if (!(_plib = dlopen(path.c_str(), RTLD_LAZY)) || !(ptr = dlsym(_plib, "create")))
      throw ModuleError("can't open module " + name);
    fptr = (myModule)ptr;
    _module.reset((*fptr)());
    return _module.get();
  }
}
