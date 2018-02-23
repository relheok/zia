#ifndef __GETPOST_H__
# define __GETPOST_H__

#include <string>
#include <stdlib.h>
#include <map>
#include <new>

std::string	urlDecode(std::string str);
void		initializeGet(std::map <std::string, std::string> &Get);
void		initializePost(std::map <std::string, std::string> &Post);
int		getpost_test();

#endif /*__GETPOST_H__*/
