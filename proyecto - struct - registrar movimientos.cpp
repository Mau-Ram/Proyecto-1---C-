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

// función para convertir strings en mayúsculas
string Mayuscula(string texto){
    for (int i=0; i < texto.length(); i++){
        texto[i] = toupper(texto[i]);   // Recorre cada letra del string y la convierte en mayúscula
    }
    return texto;
}

// Función para imprimir lista enlazada
void Imprimir_ListaEnlazada(Movimiento* cabeza){
    Movimiento* actual = cabeza;
    cout << "[ ";
    while(actual != nullptr){
        cout << "(";
        cout << actual->dia ;
        cout << "/";
        cout << actual->mes ;
        cout << "/";
        cout << actual->anio ;
        cout << ")";
        cout << endl;
        cout << actual->descripcion ;
        cout << endl;
        cout << actual->categoria ;
        cout << endl;
        cout << actual->monto ;
        cout << endl;
        if (actual -> tipo == INGRESO){
            cout << "Se hizo un ingreso \n";
        }else if (actual -> tipo == GASTO){
            cout << "Se hizo un gasto \n";
        }
        
        actual = actual->sgte;
    }
    cout << " ]";
}


// Función para crear un nuevo movimiento ya sea un ingreso o un gasto
void CrearMovimiento(Movimiento*& cabeza){
    Movimiento* nuevo_movimiento = new Movimiento();    // Creamos la lista vacia
    nuevo_movimiento -> sgte = nullptr;                 // Establecemos que este es el último valor de la lista

    // ALGUNAS VARIABLES
    string mov;
    int monto_temp;
    string descripcion_temp;
    string categoria_temp;

   
    cout << "\nREGISTRO DE MOVIMIENTOS\n" ;
    cout<<"------------------------------------------\n";   

    // Repetimos el ciclo hasta que se de una respuesta correcta
    while (true){
        cout << "1.) Tipo de Movimiento\n\n" ;     // Ingresar tipo de movimiento
        cout << "Escriba el tipo de movimiento que desea realizar ('INGRESO' / 'GASTO' ). \n";
        cout << "MOVIMIENTO:";
        cin >> mov;
        Mayuscula(mov);    // Convertimos el string en un texto completamente en mayúscula
        cout << mov;
        if (mov == "INGRESO"){
            nuevo_movimiento -> tipo = INGRESO;
            break;
        } else if (mov == "GASTO") {
            nuevo_movimiento -> tipo = GASTO;
            break;
        } else {
            cerr << "   *** ERROR **    \n Solo se permite los movimientos: 'INGRESO' / 'GASTO' ";
            cout << endl << endl;
        }
        
    }
    cout << endl << endl;

    while (true){
        cout << "2.) Monto\n\n" ;     // Ingresar categoría
        cout << "Ingrese el monto de su 'INGRESO' / 'GASTO'. Solo se permiten valores positivos \n";
        cout << "Monto:";
        cin >> monto_temp;
        if (monto_temp>0){
            if (nuevo_movimiento -> tipo == INGRESO){
                nuevo_movimiento ->monto = monto_temp;  
                break;                 // Si el tipo de monto es un ingreso el monto se queda igual que como lo ingreso el usuario. Sino pasa a ser la misma cantidad pero negativa
            }else{
                nuevo_movimiento -> monto = -monto_temp; 
                break; 
            }
        } else {
            cerr << "   *** ERROR **    \n Solo se permiten numeros positivos";
            cout << endl << endl;
        }
    }
    
    cout << "3.) Categoria\n\n" ;     // Ingresar categoría
    cout << "Ingrese la categoria en la que se encuentra su movimiento. \n";
    cout << "Categoria:";
    cin >> categoria_temp;
    Mayuscula(categoria_temp);    // Convertimos la categoria en mayúscula así nos aseguramos que siempre las categorías son maýusculas
    nuevo_movimiento ->categoria = categoria_temp;
    cout << endl << endl;


    cout << "4.) Descripcion\n\n" ;     // Ingresar descripción
    cout << "Ingrese una descripcion para este retiro. \n";
    cout << "Descripcion del movimiento:";
    getline(cin,descripcion_temp);  // Utilizamos un getline para que se puedan ingresar un texto que permita ingresar espacios.
    nuevo_movimiento ->descripcion = descripcion_temp;
    cout << endl << endl;

    cout << "5.) Fecha\n\n" ;     // Ingresar Fecha
    cout << "Ingrese la fecha de este movimiento (dia/mes/anio): \n";
    cout << "Dia: ";
    cin >> nuevo_movimiento -> dia;
    cout << "\nMes: ";
    cin >> nuevo_movimiento -> mes;
    cout << "\nanio: ";
    cin >> nuevo_movimiento -> anio;
    cout << endl << endl;
    /*
        ESTE ESPACIO ES PARA LAS VERIFICACIONES DE LA FECHA
        
    */
    cout<<"------------------------------------\n";
    // La lista esta vacia:
    if (cabeza ==  nullptr){
        cabeza = nuevo_movimiento;
    } else{                             // Lista no esta vacia
        Movimiento* actual = cabeza;
        while(actual->sgte != nullptr){             // Mientras que el nodo no apunte a null continue el ciclo y modifique actual
            actual = actual ->sgte;
        }
        actual ->sgte = nuevo_movimiento;
    }
    
    
}

int main(){
    Movimiento* lista = nullptr;
    CrearMovimiento(lista);
    Imprimir_ListaEnlazada(lista);
    return 0;
}