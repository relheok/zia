##
## Makefile for basic in /home/koehle_j/tests/cpp/basic/package
## 
## Made by Jérémy Koehler
## Login   <koehle_j@epitech.net>
## 
## Started on  Fri Jan 19 13:13:47 2018 Jérémy Koehler
## Last update Wed Feb 21 13:28:08 2018 Jérémy Koehler
##

NAME	= zia

DEP	= ./$(NAME).db.tar.gz

all:	$(DEP)

$(DEP):
	@makepkg
	@repo-add ./$(NAME).db.tar.gz *.pkg.tar.xz
	@echo -e "\nPlease add the following lines at the end of your /etc/pacman.conf:"
	@echo -e "\e[1m[$(NAME)]\nSigLevel = Never\nServer = file://`pwd`\e[0m"

clean:
	@rm -rf src pkg $(NAME).db* $(NAME).files* *.pkg.tar.xz zia

re:	clean all
