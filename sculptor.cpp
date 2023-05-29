#include "sculptor.h"
#include <fstream>
#include <cmath>


Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
    std::cout << "construtor " << _nx << " " << _ny  << " " <<  _nz << std::endl ;
    nx = _nx;
    ny = _ny;
    nz = _nz;

//    v = (Voxel***)malloc(_nx * sizeof(Voxel**));
    v = new Voxel**[nx];
    for(int i=0; i< _nx; i++){
        v[i] = new Voxel*[ny];
        for (int j = 0; j< _ny; j++){
            v[i][j] =  new Voxel[nz];
        }
    }

    for (int i = 0; i< nx; i++){
        for (int j = 0; j< ny; j++){
            for (int k = 0; k< nz; k++){
                v[i][j][k].show = 0;
                v[i][j][k].a = 0;
                v[i][j][k].r = 0;
                v[i][j][k].g = 0;
                v[i][j][k].b = 0;
            }
        }
    }
    std::cout << "criada matriz \n";

}

Sculptor::~Sculptor()
{
    for (int i = 0; i<nx; i++) {
        for (int j = 0; j<ny; j++) {
            delete v[i][j];
        }
        delete v[i];
    }
    delete(v);
    std::cout << "destrutor" << std::endl ;
}

void Sculptor::setColor(float _r, float _g, float _b, float _a)
{
    r = _r;
    g = _g;
    b = _b;
    a = _a;
}

void Sculptor::putVoxel(int x, int y, int z)
{
    if (x < nx && y < ny && z <nz){
        v[x][y][z].show  = 1;
        v[x][y][z].r = r;
        v[x][y][z].g = g;
        v[x][y][z].b = b;
        v[x][y][z].a = a;
    }
}

void Sculptor::cutVoxel(int x, int y, int z)
{
    if (x < ny && y < nx && z < nz){
        v[x][y][z].show  = 0;
    }
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for (int i = x0; i<x1; i++){
        for (int j = y0; j<y1; j++){
            for (int k = z0; k<z1; k++){
                    putVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for (int i = x0; i<x1; i++){
        for (int j = y0; j<y1; j++){
            for (int k = z0; k<z1; k++){
                cutVoxel(i,j,k);
        }
    }
    }
}

int distancia(int x0,int x1,int y0,int y1,int z0,int z1){
    int distancia = std::sqrt(
        (x1 - x0) * (x1 - x0) +
        (y1 - y0) * (y1 - y0) +
        (z1 - z0) * (z1 - z0)
        );
    return distancia;
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    for (int i = 0; i<nx; i++){
        for (int j = 0; j<ny; j++){
            for (int k = 0; k<nz; k++){
                int distancia_raio = distancia(xcenter,i,ycenter,j,zcenter,k);
                if ( distancia_raio <= radius){
                    putVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    for (int i = 0; i<nx; i++){
        for (int j = 0; j<ny; j++){
            for (int k = 0; k<nz; k++){
                int distancia_raio = distancia(xcenter,i,ycenter,j,zcenter,k);
                if ( distancia_raio <= radius){
                    cutVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    for(int i= xcenter-rx; i <= rx+xcenter; i++){
        for (int j= ycenter- ry; j <=ry+ycenter; j++){
            for (int k = zcenter - rz; k <= rz+zcenter; k++){
                float distanciaX = pow((i - xcenter)/rx,2) ;
                float distanciaY = pow((j - ycenter)/ry,2) ;
                float distanciaZ = pow((k - zcenter)/rz,2) ;
                float distancia = distanciaX + distanciaY + distanciaZ;
                // Verifica se a distância está dentro da elipsoide
                if (distancia < 1) {
                    putVoxel(i,j,k);
                }
            }
        }
    }

}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    for(int i= xcenter-rx; i <= rx+xcenter; i++){
        for (int j= ycenter- ry; j <=ry+ycenter; j++){
            for (int k = zcenter - rz; k <= rz+zcenter; k++){
                float distanciaX = pow((i - xcenter)/rx,2) ;
                float distanciaY = pow((j - ycenter)/ry,2) ;
                float distanciaZ = pow((k - zcenter)/rz,2) ;
                float distancia = distanciaX + distanciaY + distanciaZ;
                // Verifica se a distância está dentro da elipsoide
                if (distancia < 1) {
                    cutVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::writeOFF(const char *filename)
{
    std::ofstream arquivo;

    arquivo.open(filename);

    if (!arquivo.is_open()){
        std::cout << "Não foi possível criar o arquivo "<< filename << std::endl;
    }
    std::cout << "Write OFF\n";

    arquivo << "OFF\n";
    int contador = 0;
    for(int i = 0; i<nx; i++) {
        for (int j = 0; j<ny; j++) {
            for (int k = 0; k< nx; k++) {

                if (v[i][j][k].show){
                    contador++;
                }
            }
        }
    }
    std::cout << contador << std::endl;

    for (int i = 0; i<nx; i++) {
        for (int j = 0; j<ny; j++) {
             for (int k = 0; k< nx; k++) {
                if (i == 0 && j == 0 & k == 0){
                    // Segunda linha do arquivo OFF [NVertices  NFaces  NArestas]
                    arquivo << contador * 8 << " " << contador * 6 << " " << 0 << "\n";
                    contador = 1;
                }
                if (v[i][j][k].show){
                    arquivo.precision(1);
                    arquivo << std::fixed;
                    arquivo << -0.5 + i <<" "<< 0.5 + j  <<" " << -0.5 + k<<"\n";
                    arquivo << -0.5 + i <<" "<< -0.5 + j <<" " <<-0.5 + k <<"\n";
                    arquivo << 0.5  + i <<" "<< -0.5 + j <<" " <<-0.5 + k <<"\n";
                    arquivo << 0.5  + i <<" "<< 0.5  + j <<" " <<-0.5 + k <<"\n";
                    arquivo << -0.5 + i <<" "<< 0.5  + j <<" " << 0.5 + k <<"\n";
                    arquivo << -0.5 + i <<" "<<-0.5  + j <<" " << 0.5 + k <<"\n";
                    arquivo << 0.5  + i <<" "<<-0.5  + j <<" " << 0.5 + k <<"\n";
                    arquivo << 0.5  + i <<" "<< 0.5  + j <<" " << 0.5 + k <<"\n";

                    contador++;
                }
             }
        }
    }
    contador = 0;
    for (int i = 0; i<nx; i++) {
        for (int j = 0; j<ny; j++) {
             for (int k = 0; k< nx; k++) {
                if (v[i][j][k].show){
                    float ca, cr, cg, cb;
                    ca = v[i][j][k].a;
                    cr = v[i][j][k].r;
                    cg = v[i][j][k].g;
                    cb = v[i][j][k].b;
                    arquivo.precision(1);
                    arquivo << std::fixed;
                    arquivo << 4 << "  "<< 0 + contador <<" "<< 3 + contador <<" "<< 2 + contador<<" "<< 1 + contador << " " << cr << " " << cg << " " << cb << " " << ca <<"\n";
                    arquivo << 4 << "  "<< 4 + contador <<" "<< 5 + contador <<" "<< 6 + contador<<" "<< 7 + contador << " " << cr << " " << cg << " " << cb << " " << ca <<"\n";
                    arquivo << 4 << "  "<< 0 + contador <<" "<< 1 + contador <<" "<< 5 + contador<<" "<< 4 + contador << " " << cr << " " << cg << " " << cb << " " << ca <<"\n";
                    arquivo << 4 << "  "<< 0 + contador <<" "<< 4 + contador <<" "<< 7 + contador<<" "<< 3 + contador << " " << cr << " " << cg << " " << cb << " " << ca <<"\n";
                    arquivo << 4 <<"  "<< 3 + contador <<" "<< 7 + contador <<" "<< 6 + contador<<" "<< 2 + contador << " " << cr << " " << cg << " " << cb << " " << ca <<"\n";
                    arquivo << 4 <<"  "<< 1 + contador <<" "<< 2 + contador <<" "<< 6 + contador<<" "<< 5 + contador << " " << cr << " " << cg << " " << cb << " " << ca <<"\n";

                    contador+= 8;
                }
            }
        }
    }
    arquivo.close();
}

