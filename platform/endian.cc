/*
字节序

就已知的情况，字节序取决于CPU的架构。如下列表，platform指的就是CPU架构

Platform         Endian Architecture
ARM*             Bi-Endian
DEC Alpha*       Little-Endian
HP PA-RISC 8000* Bi-Endian
IBM PowerPC*     Bi-Endian
Intel® 80x86     Little-Endian
Intel® IXP network
processors       Bi-Endian
Intel® Itanium®
processor family Bi-Endian
Java Virtual Machine* Big-Endian
MIPS*            Bi-Endian
Motorola 68k*    Big-Endian
Sun SPARC*       Big-Endian 

如何规划字节序在实现跨平台上的设计与实现

1,linux下通过htobe/htole,betoh/letoh系列函数完成，对于应用程序来说，确定序列化使用be或者
le的存储模式，在linux系统下，就确定了使用le系列或者be系列的函数。在其他系统下的序列化待
研究
2,C语言数据的序列化包括整数的序列化和浮点数。整数的序列化如1中描述。浮点数float和double
的序列化则没有可使用的接口，如MySQL的实现中，根据endian，进行字节的拷贝。

思考
1,如何避免使用过多的宏，导致代码的难以查看
2,如何尽可能的使代码清晰便于理解平台架构的层次

参考：
https://zh.wikipedia.org/wiki/%E5%AD%97%E8%8A%82%E5%BA%8F
http://www.pascal-man.com/navigation/faq-java-browser/jython/endian.pdf

endian.pdf在当前目录下存在一份拷贝
*/

#include <iostream>

using namespace std;

static union { char c[4]; unsigned long mylong; }
  endian_test = {{ 'l', '?', '?', 'b' } };

#define ENDIANNESS ((char)endian_test.mylong)

#include <stdint.h>

/*
  2 bytes int operation
*/
inline void pstore_16p(void *v, void *buf)
{
#ifdef _LITTLE_ENDIAN_
  (int16_t*)buf = v;
#else
  ((uint8_t*)buf)[0] = ((uint8_t*)&v)[1];
  ((uint8_t*)buf)[1] = ((uint8_t*)&v)[0];
#endif //
}

inline void pget_16p(void *v, void *buf)
{
#ifdef _LITTLE_ENDIAN_
  *(uint16_t)v = *(uint16_t*)buf;
#else
  ((uint8_t*)v)[1] = ((uint8_t*)buf)[0];
  ((uint8_t*)v)[0] = ((uint8_t*)buf)[1];
#endif //
}

inline void pstore_int16(int16_t v, void *buf)
{
  pstore_16p(&v, buf);
}

int16_t pget_int16(void *buf)
{
  int16_t v;
  pget_16p(&v, buf);
  return v;
}

void pstore_uint16(uint16_t v, void *buf)
{
  pstore_16p(&v, buf);
}

int16_t pget_uint16(void *buf)
{
  uint16_t v;
  pget_16p(&v, buf);
  return v;
}

void pstore_float(float v, void *buf)
{
}

float pget_flt(void *buf)
{
  return 0;
}

void pstore_dbl(double v, void *buf)
{
}

double pget_dbl(void *buf)
{
  return 0;
}

int main(int argc, const char *argv[])
{
  if (ENDIANNESS == 'l')
    cout << "little endian." << endl;
  else
    cout << "big endian." << endl;

  return 0;
}

