#include <cmath>
#include <iostream>
#include <vector>
#include "Sculptor.h"
#include "figurageometrica.h"

using namespace std;

int main()
{
    int a, b, c;
    a = 100;
    b = 100;
    c = 100;
    Sculptor s(a,b,c);
    // LIMITES

    PutSphere z1(50,17,16,5,0.25,0.65,0.25,1);
    CutSphere z3(10,10,10,4);
    PutSphere z2(50,25,16,2,0.25,0.65,0.25,1);
    PutBox b1(50,50,25,28,16,16,0.25,0.65,0.25,1);
    PutBox b2(50,52,25,27,16,25,0.85,.85,0.85,1);
    PutBox b3(50,52,16,27,24,26,0.85,.85,0.85,1);
    z1.draw(s);
    z2.draw(s);
    z3.draw(s);
    b1.draw(s);
    b2.draw(s);
    b3.draw(s);

//    Modo parte I
//    s.setColor(0.25,.65,0.25,1);
//    s.putSphere(50,17,16,5);
//    s.putSphere(50,25,16,2);
//    s.putBox(50,50,25,28,16,16);
//    s.setColor(0.85,.85,0.85,1);
//    s.putBox(50,52,25,27,16,25);
//    s.putBox(50,52,16,27,24,26);
    s.writeOFF("granada.off");
};
