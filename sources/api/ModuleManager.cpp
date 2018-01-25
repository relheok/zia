#include "ModuleManager.hpp"

namespace zia::api {
  ModuleManager::ModuleManager() {
    _loader.reset(new ModuleLoader);
  }

  ModuleManager::ModuleManager(ModuleManager const &copy) {
    (void)copy;
  }

  ModuleManager  &ModuleManager::operator=(ModuleManager const &copy) {
    (void)copy;
    return (*this);
  }

  ModuleManager::~ModuleManager() {}

  void            ModuleManager::init(ModulePathList const &modules, Conf &conf) {
    for (ModulePathList::const_iterator it = modules.begin(); it < modules.end(); it++) {
      try {
        if (!_loader.get()->loadModule(it->first, it->second)->config(conf))
          throw ModuleManagerError("can't config module " + it->second);
      } catch (ModuleLoaderError &e) {
        std::cerr << e.what() << '\n';
      }
    }
  }

  Module  *ModuleManager::reloadModule(std::string const &path, std::string const &name, Conf &conf) {
    try {
      Module *module = _loader.get()->reloadModule(path, name);
      if (!module->config(conf))
        throw ModuleManagerError("can't config module " + name);
      return (module);
    } catch (ModuleNotFoundError &e) {
      std::cerr << e.what() << '\n';
    }
    return (nullptr);
  }

  Module    *getModuleByName(std::string const &name) {
    try {
      return (_loader.get()->getModuleByName(name));
    } catch (ModuleNotFoundError &e) {
      std::cerr << e.what() << '\n';
    }
    return (nullptr);
  }
}
