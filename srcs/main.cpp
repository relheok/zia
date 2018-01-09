//
// EPITECH PROJECT, 2018
// main
// File description:
// juniqu_v
//

#include "module_manager/ModuleManager.hpp"

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	ModuleManager	p;
	ModuleManager	p1("Const by var.");
	ModuleManager	p2(p);
	//p
	std::cout << "test p:" << p.getTest() << std::endl;
	//p1
	std::cout << "test p1:" << p1.getTest() << std::endl;
	//p2
	std::cout << "test p2:" << p2.getTest() << std::endl;
	p2.setTest("Set work.");
	std::cout << "test set:" << p2.getTest() << std::endl;
	//=
	p = p1;
	std::cout << "test = :"<< p.getTest() << std::endl;
	return (0);
}
