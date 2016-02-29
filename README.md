### ProjetCabane v0.3_win32

Programme de contrôle de l'automatisation de l'érablière.

Version 0.3 :
 - Version compilable et fonctionnelle sur win7
 - meilleure gestion du timeout de koyo
 
#### Description

##### Software :
 - Build avec QT Creator et minGW
 - Application principale en c++
 - Interface avec QT Designer
 - Module de communication avec Koyo : https://github.com/SimplyAutomationized/PythonKoyo/blob/master/Koyo.py
 - Module de communication avec Arduino

##### Hardware :
 - PC avec win7
 - Koyo DL06
 - PCB Arduino (Cabanuino)

##### Déploiement :

Pour déployer l'application, besoin des dll de QT. Copier tous les dll de Qt/minGW/bin et ../plugins dans le répertoire du déploiement, ouvrir l'application et puis supprimer tous les dll. 

###### Special thanks to https://github.com/SimplyAutomationized for his koyo lib! 

#### Historique

2016-02-29 | Version compilable et fonctionnelle win32. Je dois ajouter les scripts python. Nouvelle branche pour la version win32.

2016-01-12 | Ajout de la section d'historique! Hier, j'ai enlevé des accents qui étaient commentés et qui causait une erreur (!) dans commKoyo.py. Aujourd'hui j'ai validé que les modules ultrason vont fonctionner avec de l'eau. J'ai révisé la liste des tâches. À présent je vais travailler sur une branche, histoire de garder une version compilable et fonctionnelle. Création de la branche pour les E/S.
