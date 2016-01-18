## Commandes pour Git
### Pour cloner (on ajoute --recursive pour downloader les sous-modules)

	git clone https://github.com/nomdudepot --recursive
	git clone https://github.com/nomdudepot --branch nomdelabranche --recursive

### Mettre a jour

	git pull

### Accepter les changements

	git add fichiersnonsuivis
	git commit -a

### Mettre a jour en ligne

	git push

### Sous-modules :

	git submodule add https://github.com/nomdudepot repertoire/
	git submodule init nomdudepot

## A valider
 - [ ] Fonctionnement de branch
 - [ ] Fonctionnement de pull request
