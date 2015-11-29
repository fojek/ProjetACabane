## Fonctions mySQL
### Installer mysql (mdp "cabane")

	sudo apt-get install mysql-server --fix-missing
	sudo apt-get install mysql-client php5-mysql

### Utiliser mysql

#### Se connecter "root"
	mysql -uroot -hlocalhost -p 

#### Nouvelle BDD
	CREATE DATABASE cabaneDB;

#### Creer un usager
	CREATE USER 'cabaneUser'@'localhost' IDENTIFIED BY 'cabane';
	GRANT ALL PRIVILEGES ON *.* TO 'cabaneUser'@'localhost';
	FLUSH PRIVILEGES;

#### Se deconnecter : ctrl-c

#### Se connecter en utilisant un user
	mysql -ucabane -hlocalhost cabaneDB -p

#### Commandes diverses
	show databases;
	show tables;
	select * from xx;
	select xx from xx where xx = 'xx';
	describe db;   #montre l'architecture de la db ou table
	select Host,User,Password from user;
	create table temperature (temperature DOUBLE);
	insert into temperature (temperature) values(10.05),(10),(9.95),(-2.45);

## Pour accéder à partir de c++

Il faut installer ``libmysqlclient-dev``
Pour compiler, utiliser : ``g++ -Wall -o "%e" "%f" -L/usr/lib/mysql -lmysqlclient``
``Geany`` est un bon équivalent à ``Notepad++``, et permet de construire directement. 

### Voici un exemple fonctionnel qui retourne la température dans cabaneDB/temperature:

	#include <iostream>
	#include <mysql/mysql.h>
	#include <iomanip>
	#include <fstream>
	
	MYSQL *connection, mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int query_state, a;
	
	int main(){
		mysql_init(&mysql);
		connection = mysql_real_connect(&mysql,"localhost","root","cabane", "cabaneDB",0,0,0);
		if(connection==NULL) std::cout << mysql_error(&mysql) << std::endl;
		
		query_state=mysql_query(connection, "select * from temperature");
		
		if(query_state!=0){
		  std::cout<<mysql_error(connection)<<std::endl<<std::endl;
		  return 1;
		}
		
		res=mysql_store_result(connection);
		std::cout<<"Les donnees de temperature entrées :"<<std::endl<<std::endl;
		
		while((row=mysql_fetch_row(res))!=NULL){
		  std::cout<<std::left;
		  std::cout<<std::setw(18)<<row[0]<<std::endl;
		}
		
		std::cout<<std::endl<<std::endl;
		return 1;
	}
