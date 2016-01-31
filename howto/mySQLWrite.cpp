#include <iostream>
#include <mysql/mysql.h>
#include <iomanip>
#include <fstream>
#include <unistd.h>
#include <sys/time.h>
#include <string>
#include <sstream>

MYSQL *connection, mysql;
MYSQL_RES *res;
MYSQL_ROW row;
int query_state, a;
std::string base;
std::string myquery;
int dude2;

int main(){
	
	mysql_init(&mysql);
	
	connection = mysql_real_connect(&mysql,"localhost","root","cabane", "cabaneDB",0,0,0);
	if(connection==NULL) std::cout << mysql_error(&mysql) << std::endl;
	
	base = "insert into temperature (temperature) values(";
	
	while (1) {

		usleep(500000);
		
		myquery = base + std::to_string(dude2) + ")";
		
		query_state = mysql_query(connection, myquery.c_str());
		std::cout << "dude. ";
		
		dude2 += 1.25;
		
		if(dude2 > 10)
			dude2 = -3.1;
			
	};
	
	return 1;
}
