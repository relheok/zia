#include "module_manager/ModuleManager.hpp"

namespace zia::api {
  ModuleManager::ModuleManager() {}

  ModuleManager::ModuleManager(ModuleManager const &copy) : ModuleLoader()  {
    _modules = copy._modules;
  }

  ModuleManager  &ModuleManager::operator=(ModuleManager const &copy) {
    _modules = copy._modules;
    return (*this);
  }

  ModuleManager::~ModuleManager() {}

  void            ModuleManager::init(ModulePathList const &modules, Conf &conf) {
    for (ModulePathList::const_iterator it = modules.begin(); it < modules.end(); it++) {
      zia::Logger::getInstance().info("Module : " + it->first);
      try {
        if (!loadModule(it->second, it->first)->config(conf))
          throw ModuleManagerError("can't config module " + it->first);
      } catch (std::exception &e) {
        zia::Logger::getInstance().error(e.what());
      }
    }
  }

  Module  *ModuleManager::reloadModule(std::string const &path, std::string const &name, Conf &conf) {
    try {
      Module *module = reloadModuleByName(path, name);
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
}
