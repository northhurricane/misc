#ifndef _FTRC_H_
#define _FTRC_H_


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
};

#endif //_FTRC_H_

