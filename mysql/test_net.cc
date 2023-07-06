/*
g++ -g test_net.cc -o test_net -I /usr/include/mysql/ -L txsql5.7/normal-work/lib/ -lmysqlclient
*/

#include "mysql.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

const char * sql = "select 1;";

void print_time()
{
  time_t t;
  time(&t);
  printf("time is %s\n", ctime(&t));
}

int connect_server(MYSQL **mysql_)
{
  my_bool reconnect = 1;
  unsigned int read_timeout = 3, write_timeout = 3;
  *mysql_ = NULL;

  MYSQL *mysql = mysql_init(NULL);
  if (!mysql)
  {
    puts("MySQL init faild, out of memory?");
    return EXIT_FAILURE;
  }

  mysql_options(mysql, MYSQL_OPT_RECONNECT, &reconnect);
  mysql_options(mysql, MYSQL_OPT_READ_TIMEOUT, &read_timeout);
  mysql_options(mysql, MYSQL_OPT_WRITE_TIMEOUT, &write_timeout);

  if (!mysql_real_connect(mysql,       /* MYSQL structure to use */
                          "localhost", /* server hostname or IP address */ 
                          "root",   /* mysql user */
                          "",       /* password */
                          "",       /* default database to use, NULL for none */
                          0,        /* port number, 0 for default */
                          "/data2/mywork/txsql/8.0/normal-30-4/bld-debug/mysql-test/var/tmp/mysqld.1.sock", /* socket file or named pipe name */
                          CLIENT_FOUND_ROWS /* connection flags */ )) {
    printf("Connect failed.\nError message:%s.\n", mysql_error(mysql));
    return EXIT_FAILURE;
  }
  printf("connection id: %ld succeed.\n", mysql_thread_id(mysql));
  *mysql_ = mysql;
  return EXIT_SUCCESS;
}

int probe_server(MYSQL *mysql_)
{
  MYSQL_STMT *stmt = NULL;
  stmt = mysql_stmt_init(mysql_);
  if (!stmt)
  {
    printf(" mysql_stmt_init() failed.\nError message:%s.\n", mysql_error(mysql_));
    return EXIT_FAILURE;
  }

  if (mysql_stmt_prepare(stmt, sql, strlen(sql)))
  {
    fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    return EXIT_FAILURE;
  }
  fprintf(stdout, "SELECT prepare succeed.\n");

  int counter = 0;
  while (true)
  {
    if (mysql_stmt_execute(stmt))
    {
      printf("mysql_stmt_execute(), failed. Error message : ");
      printf("%s\n", mysql_stmt_error(stmt));
      break;
    }
    if (mysql_stmt_store_result(stmt))
    {
      printf("mysql_stmt_store_result(), failed. Error message : ");
      printf("%s\n", mysql_stmt_error(stmt));
      break;
    }
    if (mysql_stmt_free_result(stmt))
    {
      printf("mysql_stmt_free_result(), failed. Error message : ");
      printf("%s\n", mysql_stmt_error(stmt));
      break;
    }
    counter++;
    if (counter == 100)
    {
      printf("Succeed 100 times.\n");
      counter = 0;
    }
    sleep(3);
  }
  print_time();
  return EXIT_FAILURE;
}


int main(int argc, const char *argv[])
{
  MYSQL *mysql = NULL;
  MYSQL_STMT *stmt = NULL;

  int r = 0;
  while (true)
  {
    mysql = NULL;
    connect_server(&mysql);
    if (mysql == NULL)
    {
      continue;
    }
    r = probe_server(mysql);
    mysql_close(mysql);
    printf("Probe failed. Try it again in 3 second later.\n");
    sleep(3);
  }
  
  return 0;
}

