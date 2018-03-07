# zia
zia is a linux HTTP server.

## Constraints
zia is our EPITECH third year-end project. We are not allowed to use the boost
library and we had to have ssl and a php modules.

## Commands
Run it with the default configuration file
(located at [conf/zia.json](conf/zia.json)):

	./zia

Run it with a specific configuration file:

	./zia -c /path/to/your/file.json
	
Reload configuration file:

	./zia -r

Graceful shutdown:

	./zia -s quit

Quick shutdown:

	./zia -s stop
	
## Package
Please see [package/README.md](package/README.md).

## Authors
Jérémy Koehler, Loris Sanchez, Maxime Maisonnas, Quentin Albertone,
Rodolphe Chazal and Virgile Junique
