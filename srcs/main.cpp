//
// EPITECH PROJECT, 2018
// main
// File description:
// juniqu_v
//

#include "module_manager/ModuleManager.hpp"

int	main()
{
	std::vector<std::string> mod_name;
	std::vector<std::string> mod_path;

	mod_name.push_back("php");
	mod_name.push_back("ssl");
	mod_name.push_back("gzip");
	mod_name.push_back("caca");

	mod_path.push_back("/usr/bin");
	mod_path.push_back("/usr/bin/openssl");
	mod_path.push_back("/usr/lib");
	mod_path.push_back("/usr");
	

	ModuleManager p(mod_name, mod_path);

	if (p.init_start() == false)
	{
		std::cerr << "init start failed" << std::endl;
		return (-1);
	}
	else
		std::cout << "init start work" << std::endl;
	
	if (p.run() == false)
	{
		std::cerr << "run failed" << std::endl;
		return (-1);
	}
	else
		std::cout << "run work" << std::endl;
	return (0);
}
