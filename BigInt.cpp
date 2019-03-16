#include "BigInt.h"
#include <math.h>
#include <iostream>



int signum(const int & a){
    if (a >= 0){
        return 1;
    }
    return -1;
}

void swap(BigInt &a, BigInt &b){
    BigInt tmp = a;
    a = b;
    b = tmp;
}

BigInt absul(const BigInt& a){
    BigInt res = a;
    res.sign = 1;
    return res;
}

BigInt BigInt::operator - () const{
    BigInt res = *this;
    res.sign += -1;
    return res;
}

BigInt Simple_Substr(const BigInt& left, const BigInt& right){
    BigInt res = left;
    int max_len = std::max(left.count_number, right.count_number);
    for (int i = 0; i < max_len; ++i){
        if (res.value[i] >= right.value[i]){
            res.value[i] -= right.value[i];
        }
        else {
            res.value[i] -= (right.value[i] - 10);
            res.value[i+1] -= 1;
        }
    }
    int zero = max_len-1;
    while (!res.value[zero] && zero){
        --res.count_number;
        --zero;
    }
    return res;
}

BigInt Simple_Sum(const BigInt& left, const BigInt& right){
    BigInt res = left;
    int max_len = std::max(left.count_number, right.count_number);
    for (int i = 0; i < max_len; ++i){
        if (res.value[i] + right.value[i] >= 10){
            res.value[i] = (res.value[i] + right.value[i]) % 10;
            res.value[i+1] += 1;
            if (i+1 == max_len){
                ++res.count_number;
            }    
        }
        else {
            res.value[i] += right.value[i]; 
        }
    }
    return res;
}

BigInt::BigInt(){
    count_number = 0;
    value = new int[max_size];
    sign = 1;
}

BigInt::BigInt(const int & a){
    count_number = 0;
    value = new int[max_size];
    sign = signum(a);
    int tmp = std::abs(a);
    while (tmp) {
        value[count_number] = tmp % 10;
        tmp /= 10;
        ++count_number;
    }
}

BigInt::BigInt(const String & a){
    count_number = a.size();
    value = new int[max_size];
    if (a[0] == '-'){
        sign = -1;
        count_number -= 1;
        for (int i = 1; i < a.size(); ++i){
            value[count_number-i] = a[i]-48;
        }
    }
    else {
        sign = 1;
        for (int i = 0; i < a.size(); ++i){
            value[count_number-1-i] = a[i]-48;
        }
    } 
}

BigInt::BigInt(const BigInt & right){
    count_number = right.count_number;
    value = new int[max_size];
    sign = right.sign;
    for (int i = 0; i < count_number; ++i){
        value[i] = right.value[i];
    }
}

BigInt::~BigInt(){
    delete[] value;
}

BigInt& BigInt::operator = (const BigInt & right){
    count_number = right.count_number;
    value = new int[max_size];
    sign = right.sign;
    for (int i = 0; i < count_number; ++i){
        value[i] = right.value[i];
    }
    return *this;
}

std::ostream& operator << (std::ostream & out, const BigInt &a){
    if (a.sign == -1){
        std::cout<<'-';
    }
    for (int i = 0; i < a.count_number; ++i){
        std::cout<<a.value[a.count_number-i-1];
    }
    if (a.count_number == 0){
        std::cout<<0;
    }
    return out;
}

int operator < (const BigInt & left, const BigInt & right){
    if (left.sign > right.sign){
        return 0;
    }
    else if (left.sign < right.sign){
        return 1;
    }
    else {
        if ((left.count_number < right.count_number && left.sign == 1) ||
            (left.count_number > right.count_number && left.sign == -1)){
            return 1;
        }
        else if ((left.count_number > right.count_number && left.sign == 1) ||
                 (left.count_number < right.count_number && left.sign == -1) ){
            return 0;
        }
        else {
            for (int i = left.count_number - 1; i >= 0; --i){
                if ((left.value[i] < right.value[i] && left.sign == 1) ||
                    (left.value[i] > right.value[i] && left.sign == -1)){
                    return 1;
                }
                else if ((left.value[i] > right.value[i] && left.sign == 1) ||
                         (left.value[i] < right.value[i] && left.sign == -1)){
                    return 0;
                }
            }
            return 0;
        }
    }
}

int operator > (const BigInt & left, const BigInt & right){
    return right < left;
}

int operator == (const BigInt & left, const BigInt & right){
    if (left.count_number != right.count_number || left.sign != right.sign){
        return 0;
    }
    else {
        for (int i = left.count_number - 1; i >= 0; --i){
            if (left.value[i] != right.value[i]){
                return 0;
            }
        }
        return 1;
    }
}

BigInt operator - (const BigInt & left, const BigInt & right){
    if (left.sign == 1 && left.sign == right.sign){
        if (left > right || left == right){
            return Simple_Substr(left, right);
        }
        else {
            BigInt res = Simple_Substr(right, left);
            res.sign = -1;
            return res;
        }
    }
    else if (left.sign == -1 && left.sign == right.sign){
        if (left < right){
            BigInt res = Simple_Substr(absul(left), absul(right));
            res.sign = -1;
            return res;
        }
        else {
            return Simple_Substr(absul(right), absul(left));
        }
    }
    else if (left.sign == -1){
        if (absul(left) > right){
            BigInt res = Simple_Sum(absul(left), absul(right));
            res.sign = -1;
            return res; 
        }
        else { 
            BigInt res = Simple_Sum(absul(right), absul(left));
            res.sign = -1;
            return res;
        }
    }
    else {
        if (left > absul(right)){
            return Simple_Sum(left, absul(right));
        }
        else {
            return Simple_Sum(absul(right), left);
        }
    }
}


BigInt operator + (const BigInt & left, const BigInt & right){
    if (left.sign == 1 && right.sign == 1){
        if (left > right){
            return Simple_Sum(left, right);
        }
        else {
            return Simple_Sum(right, left);
        }
    }
    else if (left.sign == -1 && right.sign == -1){
        if (left < right){
            BigInt res = Simple_Sum(absul(left), absul(right));
            res.sign = -1;
            return res;
        }
        else {
            BigInt res = Simple_Sum(absul(right), absul(left));
            res.sign = -1;
            return res;
        }    
    }
    else if (left.sign == 1){
        return left - absul(right);
    }
    else {
        return right - absul(left); 
    }
}


BigInt& BigInt::operator ++ (){
    if (sign == 1){
        int len = count_number;
        value[0] += 1;
        for (int i = 0; i < len; ++i){
            if (value[i] >= 10){
                value[i] %= 10;
                value[i+1] += 1;
                if (i+1 == len){
                    ++count_number;
                }
            }
            else {
                break;
            }
        }
        return *this;
    }
    else {
        int len = count_number;
        value[0] -= 1;
        for (int i = 0; i < len; ++i){
            if (value[i] < 0){
                value[i] += 10;
                value[i+1] -= 1;
            }
            else {
               break;
            }
        }
        while (!value[len-1]){
            --count_number;
            --len;
        }
        return *this;
    }
}

BigInt& BigInt::operator -- (){
    if (sign == -1){    
        int len = count_number;
        value[0] += 1;
        for (int i = 0; i < len; ++i){
            if (value[i] >= 10){
                value[i] %= 10;
                value[i+1] += 1;
                if (i+1 == len){
                    ++count_number;
                }
            }
            else {
                break;
            }
        }
        return *this;
    }
    else if (!count_number || (count_number == 1 && !value[0])){
        value[0] = 1;
        sign = -1;
        count_number = 1;
        return *this;
    }
    else {        
        int len = count_number;
        value[0] -= 1;
        for (int i = 0; i < len; ++i){
            if (value[i] < 0){
                value[i] += 10;
                value[i+1] -= 1;
            }
            else {
               break;
            }
        }
        while (!value[len-1]){
            --count_number;
            --len;
        }
        return *this;
    }
}


















