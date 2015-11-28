## Installer mysql (mdp "cabane")

$ sudo apt-get install mysql-server --fix-missing
$ sudo apt-get install mysql-client php5-mysql

## Utiliser mysql

# Se connecter "root"
$ mysql -uroot -hlocalhost -p 

# Nouvelle BDD
$ CREATE DATABASE cabaneDB;

# Creer un usager
$ CREATE USER 'cabaneUser'@'localhost' IDENTIFIED BY 'cabane';
$ GRANT ALL PRIVILEGES ON *.* TO 'cabaneUser'@'localhost';
$ FLUSH PRIVILEGES;

# Se deconnecter : ctrl-c

# Se connecter en utilisant un user
$ mysql -cUser -hlocalhost cabaneDB -p

# Commandes diverses
$ show databases;
$ show tables;
$ select * from xx;
$ select xx from xx where xx = 'xx';
$ describe db;   #montre l'architecture de la db ou table
$ select Host,User,Password from user;
$ create table temperature (temperature DOUBLE);
$ insert into temperature (temperature) values(10.05),(10),(9.95),(-2.45);
