/*
g++ -g test_prepare.cc -o test_prepare -I /usr/include/mysql/ -L /data2/run/txsql8/tpcc-dev/lib/ -lmysqlclient
export LD_LIBRARY_PATH=/data2/run/txsql8/tpcc-dev/lib/private/:/data2/run/txsql8/tpcc-dev/lib
*/

#include "mysql.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char * sql_ins = "insert into t1 values (?, ?);";
#define STRING_SIZE 50

int main(int argc, const char *argv[])
{
  MYSQL *mysql = NULL;
  MYSQL_STMT *stmt = NULL;
  my_bool reconnect = 1;

  mysql = mysql_init(mysql);
  if (!mysql)
  {
    puts("Init faild, out of memory?");
    return EXIT_FAILURE;
  }

  mysql_options(mysql, MYSQL_OPT_RECONNECT, &reconnect);

  if (!mysql_real_connect(mysql,       /* MYSQL structure to use */
                          "localhost",         /* server hostname or IP address */ 
                          "root",         /* mysql user */
                          "",          /* password */
                          "tdb1",           /* default database to use, NULL for none */
                          0,           /* port number, 0 for default */
                          "/data2/run/txsql8/tpcc-dev/mysql.sock", /* socket file or named pipe name */
                          CLIENT_FOUND_ROWS /* connection flags */ )) {
    puts("Connect failed\n");
    return EXIT_FAILURE;
  }
  printf("connection id: %ld\n", mysql_thread_id(mysql));
  
  stmt = mysql_stmt_init(mysql);
  if (!stmt)
  {
    fprintf(stderr, " mysql_stmt_init(), out of memory\n");
    exit(0);
  }

  if (mysql_stmt_prepare(stmt, sql_ins, strlen(sql_ins)))
  {
    fprintf(stderr, " mysql_stmt_prepare(), Insert failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    exit(0);
  }
  fprintf(stdout, " prepare, Insert successful\n");

  MYSQL_BIND    bind[2];
  char          str_data[STRING_SIZE];
  int           int_data;
  my_bool       is_null[2];
  unsigned long length[2];
  my_bool       error[2];

  /* field 1 INT COLUMN */
  bind[0].buffer_type= MYSQL_TYPE_LONG;
  bind[0].buffer= (void *)&int_data;
  bind[0].buffer_length= sizeof(int);
  bind[0].is_null= &is_null[0];
  bind[0].length= &length[0];
  bind[0].error= &error[0];
  /* field 2 STRING COLUMN */
  bind[1].buffer_type= MYSQL_TYPE_STRING;
  bind[1].buffer= (char *)str_data;
  bind[1].buffer_length= STRING_SIZE;
  bind[1].is_null= &is_null[1];
  bind[1].length= &length[1];
  bind[1].error= &error[1];

  int_data = 1;
  length[0] = sizeof(int);
  is_null[0] = 0;

  strcpy(str_data, "1");
  length[1] = strlen(str_data);
  is_null[1] = 0;
  /* Bind the result buffers */
  if (mysql_stmt_bind_param(stmt, bind))
  {
    fprintf(stderr, " mysql_stmt_bind_result() failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    exit(0);
  }

  if (mysql_stmt_execute(stmt))
  {
    fprintf(stderr, " mysql_stmt_execute(), failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  }

  return 0;
}

