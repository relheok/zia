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
    Module    *module;

    _name = name;
    if (!(_plib = dlopen(path.c_str(), RTLD_LAZY)) || !(ptr = dlsym(_plib, "create")))
      throw ModuleLoaderError("can't open module " + name);
    fptr = (myModule)ptr;
    module = (*fptr)();
    _module.reset(module);
    return _module.get();
  }

  bool    con

  Module        *ModuleLoader::getModule() {
    return _module.get();
  }

  std::string   ModuleLoader::getName() const {
    return _name;
  }
}
