#include "modulo.h"

BigInt abs(const BigInt& a){
    if (a > 0 || a == 0){
        return a;
    }
    return -a;
} 

modulo::modulo(const BigInt& res) {
    if (res > 0){
        BigInt tmp = res;
        while (tmp > n){
            tmp = tmp - n;
            
        }
        this_value = tmp; 
    }
    else {
        BigInt tmp = res;
        while (tmp < 0){
            tmp = tmp + n;
        }
        this_value = tmp;
    }
}

modulo::modulo(const modulo& res){
    this_value = res.this_value;
}

modulo::modulo(){
    this_value = 0;
}

modulo::~modulo(){
}

modulo& modulo:: operator = (const modulo& res){
    this_value = res.this_value;
    return *this;
}


std::ostream & operator << (std::ostream & out, const modulo & res){
    std::cout<<res.this_value;
    return out;
}

int operator == (const modulo& left, const modulo& right){
    if (left.this_value == right.this_value){
        return 1;
    }
    return 0;
}

int operator != (const modulo& left, const modulo& right){
    return !(left == right);
}

modulo operator + (const modulo& left, const modulo& right){
    std::cout<<left.this_value<<" "<<right.this_value<<'\n';
    modulo res(left.this_value + right.this_value);
    return res;
}






