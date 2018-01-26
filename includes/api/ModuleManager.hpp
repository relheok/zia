#ifndef MODULEMANAGER_HPP_
# define MODULEMANAGER_HPP_

# include "ModuleLoader.hpp"

namespace zia::api {
  using ModulePathList = std::vector<std::pair<std::string, std::string>>;

  class     ModuleManager : public ModuleLoader {
  public:
    ModuleManager();
    ModuleManager(ModuleManager const &);
    ModuleManager  &operator=(ModuleManager const &);
    ~ModuleManager();

    /**
    * Load the [modules] passed as parameter (path, name) with [conf]
    * Exception : ModuleManagerError
    */
    void    init(ModulePathList const &, Conf &);

    /**
    * Reload the module [name] from [path] with [conf]
    * Exception : ModuleManagerError
    * \return a pointer to the module on success, nullptr otherwise
    */
    Module  *reloadModule(std::string const &path, std::string const &name, Conf &conf);
  };
}

#endif /* end of include guard: MODULEMANAGER_HPP_ */
