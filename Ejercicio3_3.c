//programa en C para consultar los datos de la base de datos
//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void main ()
{
	MYSQL *conn;
	int err;
	int i=0;
	// struct for keeping the results of the querys 
	MYSQL_RES *result;
	MYSQL_ROW row;
	char query [80];
	//we create the connection with MYSQL server
	conn = mysql_init(NULL);
	if (conn==NULL)
	{
		printf ("Conection failed: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicialize the conection 
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "OYSL_DB",0, NULL, 0);
	if (conn==NULL)
	{
		printf ("Fail trying to inicialize the connetion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	char name[20];
	printf("Write one of these names to know the games won by the player (VittoelGanso, Mario, Judit, Miguel, Eda, Aitana, Aida o Pablo): \n");
	scanf("%s", name);
	sprintf(query,"SELECT Game.date,Game.ID FROM Game WHERE winner='%s';", name);
	err=mysql_query (conn, query);
	if (err!=0)
	{
		printf ("Failure trying to make the query  %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//we get the result of the query
	result = mysql_store_result (conn);
	// The result is an array structure in which each
	// row contains the data of one person and successive
	// columns contain each of the person's data
	// we go through each row of the result one by one
	// now we get the next row
	row = mysql_fetch_row (result);
	if (row == NULL)
		printf ("%s ha ganado %d partidas\n", name, i);
	else
		while (row !=NULL)
		{
			i++;
			// we get the next row
			row = mysql_fetch_row (result);
		}
	if (i != 0)
		printf("%s ha ganado %d partidas\n", name, i);	
	mysql_close (conn);
}	
