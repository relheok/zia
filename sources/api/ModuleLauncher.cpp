#include "ModuleLauncher.hpp"

namespace zia::api {
  ModuleLauncher::ModuleLauncher() {}

  ModuleLauncher::ModuleLauncher(ModuleLauncher const &copy) {
    _path = copy._path;
  }

  ModuleLauncher  &ModuleLauncher::operator=(ModuleLauncher const &copy) {
    _path = copy._path;
    return (*this);
  }

  ModuleLauncher::~ModuleLauncher() {}

  Module    *ModuleLauncher::launchModule(std::string const &path) {
    (void)path;
    return _module.get();
  }
}
