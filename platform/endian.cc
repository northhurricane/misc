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

int main(int argc, const char *argv[])
{
  if (ENDIANNESS == 'l')
    cout << "little endian." << endl;
  else
    cout << "big endian." << endl;

  return 0;
}
