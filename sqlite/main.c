#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;

	if (argc < 2) {
		printf("usage: %s [database]\n", argv[0]);
		return -1;
	}

   if (sqlite3_open(argv[1], &db))
	printf("%s", sqlite3_errmsg(db));

   if (SQLITE_OK != sqlite3_exec(db, "select * from card_inf", callback, 0, &zErrMsg))
	printf("%s", sqlite3_errmsg(db));

   sqlite3_close(db);
   return 0;
}
