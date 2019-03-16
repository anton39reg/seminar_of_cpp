#include "modulo.h"
#include <iostream>
int main(){
    modulo a(32);
    modulo b(75);
    modulo c(-23);
    BigInt tmp1(32), tmp2(77);
    std::cout<<tmp1+tmp2<<'\n';
    std::cout<<a<<" "<<b<<" "<<c<<" "<<'\n';
    std::cout<<(a + b)<<" "<<(a + c)<<'\n';
}
