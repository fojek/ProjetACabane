#include <iostream>
#include <mysql/mysql.h>
#include <iomanip>
#include <fstream>
#include <unistd.h>
#include <sys/time.h>

MYSQL *connection, mysql;
MYSQL_RES *res;
MYSQL_ROW row;
int query_state, a;

int main(){
	
	mysql_init(&mysql);
	
	connection = mysql_real_connect(&mysql,"localhost","cabaneUser","cabane", "cabane",0,0,0);
	if(connection==NULL) std::cout << mysql_error(&mysql) << std::endl;
	
	
	query_state=mysql_query(connection, "INSERT INTO temperature(temperature) VALUES(0), (-1), (2), (3.14)");
	
	while (1) {

		usleep(1000000);
		
		query_state=mysql_query(connection, "INSERT INTO temperature(temperature) VALUES(0)");
		std::cout << "dude. ";
		
		};
	
	return 1;
}
