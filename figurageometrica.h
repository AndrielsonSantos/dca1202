#ifndef FIGURAGEOMETRICA_H
#define FIGURAGEOMETRICA_H

#include "Sculptor.h"

#include <cmath>
#include <vector>

using namespace std;

class FiguraGeometrica {
public:
    void draw(Sculptor &t);  // Método virtual para desenhar a figura
};


class PutVoxel : public FiguraGeometrica {
private:
    int x;
    int y;
    int z;
    float r;
    float g;
    float b;
    float a;
public:
    PutVoxel(int _x, int _y, int _z, float _r, float _g, float _b, float _a) {
        x = _x;
        y = _y;
        z = _z;
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }

    void draw(Sculptor &t) {
        t.v[x][y][z].show = 1;
        t.v[x][y][z].r = r;
        t.v[x][y][z].g = g;
        t.v[x][y][z].b = b;
    }
};

class CutVoxel : public FiguraGeometrica {
private:
    int x;
    int y;
    int z;
public:
    CutVoxel(int _x, int _y, int _z) {
        x = _x;
        y = _y;
        z = _z;
    }

    void draw(Sculptor &t) {
        t.v[x][y][z].show = 0;
    }
};

class PutBox : public FiguraGeometrica {
private:
    int x0;
    int x1;
    int y0;
    int y1;
    int z0;
    int z1;
    float r;
    float g;
    float b;
    float a;
public:
    PutBox(int _x0, int _x1, int _y0, int _y1, int _z0, int _z1, float _r, float _g, float _b, float _a) {
        cout << x0 << " " << x1 << " " << y0 << " \n";
        x0 = _x0;
        x1 = _x1;
        y0 = _y0;
        y1 = _y1;
        z0 = _z0;
        z1 = _z1;
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }

    void draw(Sculptor &t)   {
        vector<PutVoxel*> voxels;
        for (int i = x0; i<x1; i++){
            for (int j = y0; j<y1; j++){
                for (int k = z0; k<z1; k++){
                    voxels.push_back(new PutVoxel(i,j,k,r,g,b,a));
                }
            }
        }
        for (PutVoxel* voxel : voxels) {
            voxel->draw(t);
        }

        for (PutVoxel* voxel : voxels) {
            delete voxel;
        }
    }
};

class CutBox : public FiguraGeometrica {
private:
    int x0;
    int x1;
    int y0;
    int y1;
    int z0;
    int z1;
public:
    CutBox(int _x0, int _x1, int _y0, int _y1, int _z0, int _z1) {
        x0 = _x0;
        x1 = _x1;
        y0 = _y0;
        y1 = _y1;
        z0 = _z0;
        z1 = _z1;
    }

    void draw(Sculptor &t)  {
        vector<CutVoxel*> voxels;
        for (int i = x0; i<x1; i++){
            for (int j = y0; j<y1; j++){
                for (int k = z0; k<z1; k++){
                    voxels.push_back(new CutVoxel(i,j,k));
                }
            }
        }
        for (CutVoxel* voxel : voxels) {
            voxel->draw(t);
        }

        for (CutVoxel* voxel : voxels) {
            delete voxel;
        }
    }
};

int distanciaPontos(int x0,int x1,int y0,int y1,int z0,int z1){
    int distancia = std::sqrt(
        (x1 - x0) * (x1 - x0) +
        (y1 - y0) * (y1 - y0) +
        (z1 - z0) * (z1 - z0)
        );
    return distancia;
}

class PutSphere : public FiguraGeometrica {
private:
    int xcenter;
    int ycenter;
    int zcenter;
    int radius;
    float r;
    float g;
    float b;
    float a;
public:
    PutSphere(int _xcenter, int _ycenter, int _zcenter, int _radius, float _r, float _g, float _b, float _a) {
        xcenter = _xcenter;
        ycenter = _ycenter;
        zcenter = _zcenter;
        radius = _radius;
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }

    void draw(Sculptor &t)   {
        vector<PutVoxel*> voxels;
        for (int i = 0; i<t.nx; i++){
            for (int j = 0; j<t.ny; j++){
                for (int k = 0; k<t.nz; k++){
                    int distancia_raio = distanciaPontos(xcenter,i,ycenter,j,zcenter,k);
                    if ( distancia_raio <= radius){
                        voxels.push_back(new PutVoxel(i,j,k,r,g,b,a));
                    }
                }
            }
        }

        for (PutVoxel* voxel : voxels) {
            voxel->draw(t);
        }

        for (PutVoxel* voxel : voxels) {
            delete voxel;
        }

    }
};

class CutSphere : public FiguraGeometrica {
private:
    int xcenter;
    int ycenter;
    int zcenter;
    int radius;
public:
    CutSphere(int _xcenter, int _ycenter, int _zcenter, int _radius) {
        xcenter = _xcenter;
        ycenter = _ycenter;
        zcenter = _zcenter;
        radius = _radius;
    }

    void draw(Sculptor &t) {
        vector<CutVoxel*> voxels;
        for (int i = 0; i<t.nx; i++){
            for (int j = 0; j<t.ny; j++){
                for (int k = 0; k<t.nz; k++){
                    int distancia_raio = distanciaPontos(xcenter,i,ycenter,j,zcenter,k);
                    if ( distancia_raio <= radius){
                        voxels.push_back(new CutVoxel(i,j,k));
                    }
                }
            }
        }

        for (CutVoxel* voxel : voxels) {
            voxel->draw(t);
        }

        for (CutVoxel* voxel : voxels) {
            delete voxel;
        }
    }
};

class PutEllipsoid : public FiguraGeometrica {
private:
    int xcenter;
    int ycenter;
    int zcenter;
    int rx;
    int ry;
    int rz;
    float r;
    float g;
    float b;
    float a;
public:
    PutEllipsoid(int _xcenter, int _ycenter, int _zcenter, int _rx, int _ry, int _rz, int _r, int _g, int _b, int _a) {
        xcenter = _xcenter;
        ycenter = _ycenter;
        zcenter = _zcenter;
        rx = _rx;
        ry = _ry;
        rz = _rz;
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }

    void draw(Sculptor &t)  {
        vector<PutVoxel*> voxels;
        for(int i= xcenter-rx; i <= rx+xcenter; i++){
            for (int j= ycenter- ry; j <=ry+ycenter; j++){
                for (int k = zcenter - rz; k <= rz+zcenter; k++){
                    float distanciaX = pow((i - xcenter)/rx,2) ;
                    float distanciaY = pow((j - ycenter)/ry,2) ;
                    float distanciaZ = pow((k - zcenter)/rz,2) ;
                    float distancia = distanciaX + distanciaY + distanciaZ;
                    // Verifica se a distância está dentro da elipsoide
                    if (distancia < 1) {
                        voxels.push_back(new PutVoxel(i,j,k,r,g,b,a));
                    }
                }
            }
        }
        for (PutVoxel* voxel : voxels) {
            voxel->draw(t);
        }

        for (PutVoxel* voxel : voxels) {
            delete voxel;
        }
    }
};

class CutEllipsoid : public FiguraGeometrica {
private:
    int xcenter;
    int ycenter;
    int zcenter;
    int rx;
    int ry;
    int rz;
    float r;
    float g;
    float b;
    float a;
public:
    CutEllipsoid(int _xcenter, int _ycenter, int _zcenter, int _rx, int _ry, int _rz) {
        xcenter = _xcenter;
        ycenter = _ycenter;
        zcenter = _zcenter;
        rx = _rx;
        ry = _ry;
        rz = _rz;
    }

    void draw(Sculptor &t)  {
        vector<CutVoxel*> voxels;
        for(int i= xcenter-rx; i <= rx+xcenter; i++){
            for (int j= ycenter- ry; j <=ry+ycenter; j++){
                for (int k = zcenter - rz; k <= rz+zcenter; k++){
                    float distanciaX = pow((i - xcenter)/rx,2) ;
                    float distanciaY = pow((j - ycenter)/ry,2) ;
                    float distanciaZ = pow((k - zcenter)/rz,2) ;
                    float distancia = distanciaX + distanciaY + distanciaZ;
                    // Verifica se a distância está dentro da elipsoide
                    if (distancia < 1) {
                        voxels.push_back(new CutVoxel(i,j,k));
                    }
                }
            }
        }
        for (CutVoxel* voxel : voxels) {
            voxel->draw(t);
        }

        for (CutVoxel* voxel : voxels) {
            delete voxel;
        }
    }
};


#endif // FIGURAGEOMETRICA_H
