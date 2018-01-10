//
// EPITECH PROJECT, 2018
// main
// File description:
// juniqu_v
//

#include "config_manager/ConfigManager.hpp"

int	main(int ac, char **av)
{
	try 
	{
		std::string path((ac == 2) ? (av[1]) : (""));
		zia::api::ConfigManager p(path);
		if (ac == 2)
		{
			try 
			{
				p.CheckPath();
			}
			catch (std::exception &err)
			{
				std::cerr << err.what() << std::endl;
				// call the last method of parsing for launch conf with default value
				return (2);
			}
		}
		else
		{
			std::cout << "no conf file !" << std::endl;
			// call the last method of parsing for launch conf with default value
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (-1);
	}
	return (0);
}
