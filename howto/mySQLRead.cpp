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
	
	while (1) {
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
		usleep(100000);
	}
	return 1;
}
