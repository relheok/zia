#include "ModuleLoader.hpp"

namespace zia::api {
  ModuleLoader::ModuleLoader() {}

  ModuleLoader::ModuleLoader(ModuleLoader const &copy) {
    _modules = copy.getModules();
  }

  ModuleLoader  &ModuleLoader::operator=(ModuleLoader const &copy) {
    _modules = copy.getModules();
    return (*this);
  }

  ModuleLoader::~ModuleLoader() {
    for (ModulesList::iterator it = _modules.begin(); it < _modules.end(); it++) {
      delete it->first;
      if (it->second)
        dlclose(it->second);
    }
  }

  Module      *ModuleLoader::loadModule(std::string const &path) {
    void      *ptr;
    void      *plib;
    myModule  fptr;
    Module    *module;

    if (!(plib = dlopen(path.c_str(), RTLD_LAZY)) || !(ptr = dlsym(plib, "create")))
      throw ModuleLoaderError("can't open module at location " + path);
    fptr = (myModule)ptr;
    module = (*fptr)();
    _modules.push_back(ListItem(module, plib));
    return module;
  }

  ModulesList  ModuleLoader::getModules() const {
    return _modules;
  }
}
