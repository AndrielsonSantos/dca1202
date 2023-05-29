#include <iostream>
#include "Sculptor.h"

using namespace std;

int main()
{
    int a, b, c;
    a = 100;
    b = 100;
    c = 100;
    Sculptor s(a,b,c);
    // LIMITES
    s.setColor(0.25,.65,0.25,1);
    s.putSphere(50,17,16,5);
    s.putSphere(50,25,16,2);
    s.putBox(50,50,25,28,16,16);
    s.setColor(0.85,.85,0.85,1);
    s.putBox(50,52,25,27,16,25);
    s.putBox(50,52,16,27,24,26);
    s.writeOFF("granada.off");


}
