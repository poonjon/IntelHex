#ifndef _18C_H
#define _18C_H

#if defined (__XC8)
  #include <xc.h>
#elif defined (__18CXX)
  #include <P18F4520.h>
#else
  #include "p18f4520.h"
#endif // __18CXX

#endif //_18C_H