#include "string.h"
#include <iostream>
class BigInt {
    friend BigInt operator + (const BigInt &, const BigInt &);
    friend BigInt operator - (const BigInt &, const BigInt &);
    friend int operator == (const BigInt &, const BigInt &);
    friend int operator < (const BigInt &, const BigInt &);
    friend int operator > (const BigInt &, const BigInt &);
    friend std::ostream & operator << (std::ostream &, const BigInt &);
    friend BigInt Simple_Substr(const BigInt&, const BigInt&);
    friend BigInt Simple_Sum(const BigInt&, const BigInt&);
    friend BigInt absul(const BigInt&);
  private:
    int *value;
    int sign;
    int count_number;
    int max_size = 1000;
  public:
    BigInt();
    BigInt(const String &);
    BigInt(const int &);
    BigInt(const BigInt &);
    BigInt& operator = (const BigInt &);
    ~BigInt();
    BigInt& operator ++ ();
    BigInt& operator -- ();
    BigInt operator -() const;
};
