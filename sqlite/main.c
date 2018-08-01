#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
	char *str = NotUsed;
	printf("callback %s:%d\n", str, argc);
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *errmsg = NULL;

	if (argc < 2) {
		printf("usage: %s [database]\n", argv[0]);
		return -1;
	}

	if (sqlite3_open(argv[1], &db))
		printf("%s", sqlite3_errmsg(db));

	if (sqlite3_exec(db, "create table if not exists mytbl (id int, name text, pwr int, agi int, magic int)", callback, "now i create table", &errmsg))
		printf("%s", sqlite3_errmsg(db));

	if (sqlite3_exec(db, "insert into mytbl values (2, 'monkeyD', 100, 100, 30)", callback, "now i insert table", &errmsg))
		printf("%s", sqlite3_errmsg(db));

	if (SQLITE_OK != sqlite3_exec(db, "select * from sqlite_master", callback, "select sqlite_master", &errmsg))
		printf("%s", sqlite3_errmsg(db));

	if (SQLITE_OK != sqlite3_exec(db, "select * from mytbl where id=2", callback, "select mytbl", &errmsg))
		printf("%s", sqlite3_errmsg(db));

	sqlite3_close(db);
	return 0;
}
