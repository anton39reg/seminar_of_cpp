#include <iostream>
#include "BigInt.h"

class modulo{
    friend std::ostream & operator << (std::ostream &, const modulo &);
    friend int operator == (const modulo&, const modulo&);
    friend int operator != (const modulo&, const modulo&);
    friend modulo operator + (const modulo& , const modulo&);
  private:
    BigInt n = 100;
    BigInt this_value;
  public:
    modulo();
    modulo(const modulo&);
    modulo(const BigInt&);
    ~modulo();
    modulo& operator = (const modulo&);
};
