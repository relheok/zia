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
    } catch (ModuleLoaderError &e) {
      std::cerr << e.what() << '\n';
    }
    return (nullptr);
  }

  Module    *ModuleManager::getModuleByName(std::string const &name) {
    try {
      return (_loader.get()->getModuleByName(name));
    } catch (ModuleNotFoundError &e) {
      std::cerr << e.what() << '\n';
    }
    return (nullptr);
  }

  void    ModuleManager::test() {
    ModulePathList modules;
    modules.push_back(std::make_pair("sources/modules/test_module.so", "test_module.so"));
    Conf conf;
    init(modules, conf);
    if (getModuleByName("toto"))
      throw TestError("getModuleByName");
    if (!getModuleByName("test_module.so"))
      throw TestError("getModuleByName");
    try {
      if (!reloadModule("sources/modules/test_module.so", "test_module.so", conf))
        throw TestError("reloadModule");
      if (reloadModule("sources/modules/test_module.s", "test_module.so", conf))
        throw TestError("reloadModule");
      if (reloadModule("sources/modules/test_module.so", "test_module.s", conf))
        throw TestError("reloadModule");
    } catch (ModuleManagerError &e) {
      std::cerr << e.what() << '\n';
      throw TestError("reloadModule");
    }
  }
}
