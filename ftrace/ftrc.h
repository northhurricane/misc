#ifndef _FTRC_H_
#define _FTRC_H_

#define MAX_NAME_LEN  (256)
#define BUFFER_SIZE (512)
#define END_CHAR (0)

#define FUNCTION_TRACE(name) FTrace(name)

/*
  初始化模块
*/
int ftrc_initialize();

class FTrace
{
public :
  FTrace(const char *func_name);
  ~FTrace();

private :
  char name_inner[MAX_NAME_LEN];
  void WriteLog(char *inf);
};

#endif //_FTRC_H_

