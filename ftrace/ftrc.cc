#include "ftrc.h"
#include <stdint.h>
#include <string.h>

FTrace::FTrace(const char *name)
{
  //to : name写入log。
  int name_len = 0;

  name_len = strlen(name);
  if (name_len >= MAX_NAME_LEN)
  {
    strncpy(name_inner, name, name_len - 1);
    name_inner[MAX_NAME_LEN - 1] = END_CHAR;
  }
  else
  {
    strcpy(name_inner, name);
  }

  char buff[BUFFER_SIZE];
  buff[0] = END_CHAR;

  strcat(buff, "<");
  strcat(buff, name_inner);
  strcat(buff, ">");
  WriteLog(buff);
}

FTrace::~FTrace()
{
  //to : name写入log。
  char buff[BUFFER_SIZE];
  buff[0] = END_CHAR;

  strcat(buff, "</");
  strcat(buff, name_inner);
  strcat(buff, ">");
  WriteLog(buff);
}

void FTrace::WriteLog(char *)
{
  return;
}
