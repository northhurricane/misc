/*
g++ -g test_prepare.cc -o test_prepare -I /usr/include/mysql/ -L txsql5.7/normal-work/lib/ -lmysqlclient
*/

#include "mysql.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char * sql = "update tsm4 set f1=f1+1 where f1=?;";
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
                          "/data2/run/txsql8/normal-work/mysql.sock", /* socket file or named pipe name */
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

  char sql[] = "insert into t1 values (?);";
  if (mysql_stmt_prepare(stmt, sql, strlen(sql)))
  {
    fprintf(stderr, " mysql_stmt_prepare(), INSERT failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    exit(0);
  }
  fprintf(stdout, " prepare, INSERT successful\n");

  MYSQL_BIND    bind[1];
  int           int_data;
  my_bool       is_null[1];
  unsigned long length[1];
  my_bool       error[1];

  /* INT COLUMN */
  bind[0].buffer_type= MYSQL_TYPE_LONG;  //设置第一个占位符的属性
  bind[0].buffer= (char *)&int_data;
  bind[0].length= &length[0];
  bind[0].buffer_length= sizeof(int);
  bind[0].is_null= &is_null[0];
  bind[0].error= &error[0];

  length[0] = sizeof(int);
  is_null[0] = 0;
  /* Bind the result buffers */
  if (mysql_stmt_bind_param(stmt, bind))
  {
    fprintf(stderr, " mysql_stmt_bind_result() failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    exit(0);
  }

  int_data = 10;
  if (mysql_stmt_execute(stmt))
  {
    fprintf(stderr, " mysql_stmt_execute(), failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  }
  int_data = 11;
  if (mysql_stmt_execute(stmt))
  {
    fprintf(stderr, " mysql_stmt_execute(), failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  }

  return 0;
}

