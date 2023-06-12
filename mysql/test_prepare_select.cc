/*
g++ -g test_prepare.cc -o test_prepare -I /usr/include/mysql/ -L txsql5.7/normal-work/lib/ -lmysqlclient
*/

#include "mysql.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
  create database tdb;
  use tdb;
  create table t1 (id int, primary key(id));
  insert into t1 value (1);
  insert into t1 select (select max(id) from t1) + id;
*/
const char * sql = "select /*+ independent */ * from tdb.t1;";
#define STRING_SIZE 50

int main(int argc, const char *argv[])
{
  MYSQL *mysql = NULL;
  MYSQL_STMT *stmt = NULL;
  MYSQL_STMT *stmt2 = NULL;
  my_bool reconnect = 1;

  mysql = mysql_init(mysql);
  if (!mysql)
  {
    puts("Init faild, out of memory?");
    return EXIT_FAILURE;
  }

  mysql_options(mysql, MYSQL_OPT_RECONNECT, &reconnect);

  if (!mysql_real_connect(mysql,       /* MYSQL structure to use */
                          "localhost", /* server hostname or IP address */ 
                          "root",   /* mysql user */
                          "",       /* password */
                          "",       /* default database to use, NULL for none */
                          0,        /* port number, 0 for default */
                          "/data2/mywork/txsql/8.0/normal-30-4/bld-debug/mysql-test/var/tmp/mysqld.1.sock", /* socket file or named pipe name */
                          CLIENT_FOUND_ROWS /* connection flags */ )) {
    fprintf(stderr, " %s\n", mysql_error(mysql));
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

  if (mysql_stmt_prepare(stmt, sql, strlen(sql)))
  {
    fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    exit(0);
  }
  fprintf(stdout, " prepare successful\n");

  stmt2 = mysql_stmt_init(mysql);
  if (!stmt2)
  {
    fprintf(stderr, " mysql_stmt_init() 2 fail for %s\n", mysql_error(mysql));
    exit(0);
  }

  if (mysql_stmt_prepare(stmt2, sql, strlen(sql)))
  {
    fprintf(stderr, " mysql_stmt_prepare() 2, SELECT failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt2));
    exit(0);
  }

  if (mysql_stmt_execute(stmt))
  {
    fprintf(stderr, " mysql_stmt_execute(), failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  }
  if (mysql_stmt_store_result(stmt))
  {
    fprintf(stderr, " mysql_stmt_store_result(), failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  }
  if (mysql_stmt_free_result(stmt))
  {
    fprintf(stderr, " mysql_stmt_free_result(), failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  }

  fprintf(stdout, " prepare, SELECT successful\n");

  if (mysql_stmt_execute(stmt2))
  {
    fprintf(stderr, " mysql_stmt_execute() 2, failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt2));
  }

  return 0;
}

