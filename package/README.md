# package zia

The open-source http zia server is only availble on Arch Linux.

## Installation
To install it thanks pacman, do:

1. Compile the zia project
2. Add the following lines at the end of your `/etc/pacman.conf`:


		[zia]
		SigLevel = Never
		Server = file:///path/to/zia/package

3. Update your packages:

		pacman -Syu

4. Install zia:

		pacman -S zia

## Uninstall:
Just run:

	pacman -Rsn zia

And remove the lines concerning the zia package in your `/etc/pacman.conf`.
