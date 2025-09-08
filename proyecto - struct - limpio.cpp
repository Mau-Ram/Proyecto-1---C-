#include <iostream>
#include <string>
using namespace std;

enum tipo_movimiento{INGRESO,GASTO};

const int TAM_FECHA = 3; // Variable constante que le asigna un valor de 3 a el arreglo fecha

// Cada movimiento financiero contiene lo siguiente:
struct Movimiento{
    int dia;
    int mes;
    int anio;
    string descripcion; 
    string categoria;   
    float monto;
    tipo_movimiento tipo;   //  Es un ingreso o un gasto
    Movimiento* sgte;   // Puntero al siguiente valor
};


int main(){

    return 0;
}