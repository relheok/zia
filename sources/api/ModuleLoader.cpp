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
      delete it->module;
      dlclose(it->plib);
    }
  }

  Module      *ModuleLoader::loadModule(std::string const &path, std::string const &name) {
    void      *ptr;
    void      *plib;
    myModule  fptr;
    Module    *module;

    if (!(plib = dlopen(path.c_str(), RTLD_LAZY)) || !(ptr = dlsym(plib, "create")))
      throw ModuleLoaderError("can't open module " + name);
    fptr = (myModule)ptr;
    module = (*fptr)();
    ListItem item = {module, plib, name};
    _modules.push_back(item);
    return module;
  }

  Module      *ModuleLoader::reloadModule(std::string const &path, std::string const &name) {
    for (ModulesList::iterator it = _modules.begin(); it < _modules.end(); it++) {
      if (it->name.compare(name) == 0) {
        delete it->module;
        dlclose(it->plib);
        _modules.erase(it);
        return (loadModule(path, name));
      }
    }
    throw ModuleLoaderError("the module " + name + " wasn't loaded");
  }

  ModulesList  ModuleLoader::getModules() const {
    return _modules;
  }
}
