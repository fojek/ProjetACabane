### ProjetCabane

Programme de contrôle de l'automatisation de l'érablière.

#### Description

##### Software :
 - Build avec QT Creator
 - Application principale en c++
 - Interface avec QT Designer
 - Module de communication avec Koyo : https://github.com/SimplyAutomationized/PythonKoyo/blob/master/Koyo.py

##### Hardware :
 - Raspberry Pi 2B
 - Koyo DL06
 - PCB Arduino (Cabanuino)
 - Boitiers SR04 (BatBassin)

###### Special thanks to https://github.com/SimplyAutomationized for his koyo lib! 

#### Tâches :

- [ ] E/S
    - [ ] Arduino via SPI :
        - [ ] Analog : Température & Pression
        - [ ] Digital : Niveaux des bassins
        - [ ] PCB Arduino (Cabanuino)
    - [ ] Koyo via Ethernet :
        - [x] Accès au PLC avec pythonKoyo 
        - [x] Accès bitwise aux E/S du koyo
        - [ ] Relier les boutons/affichages avec la classe Koyo
    - [ ] Sondes de niveau / Température :
        - [ ] 2x Boitier pour SR04 (batBassin)
        - [ ] Choisir le modèle de capteur de température
- [ ] Accès à distance
    - [ ] Recherche meilleur contrat données, abonnement
    - [ ] Test réception 3G dans la cabane
    - [ ] Test connection VNC
- [ ] Trends (Facultatif)
     - [ ] BDD (Temps Vs. Température, Pression, Niveaux, Transvideurs)
     - [ ] Thread R/W des données dans la BDD (intervalle ~ 5 secondes)
     - [ ] Affichage
         - [ ] Recherche d'une librairie graphique sur Git
         - [ ] Ajout du tab des trends


#### Historique

2016-01-12 | Ajout de la section d'historique! Hier, j'ai enlevé des accents qui étaient commentés et qui causait une erreur (!) dans commKoyo.py. Aujourd'hui j'ai validé que les modules ultrason vont fonctionner avec de l'eau. J'ai révisé la liste des tâches. À présent je vais travailler sur une branche, histoire de garder une version compilable et fonctionnelle. Création de la branche pour les E/S.
