//Proyecto #1 Analisis y Diseño de Algoritmos 

//Integrantes: Mauricio Ramírez Benavidez e Isaac Esquivel Ocampo

//Profesor: Bryan Hernández


#include <iostream>
#include <string>
#include <windows.h>
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
    tipo_movimiento tipo;   //  Es un ingreso o un gasto (la variable tipo va a ser de tipo enum)
    Movimiento* sgte;   // Puntero al siguiente valor
};

Movimiento* lista = nullptr; //se inicializa el puntero lista que apuntará a null (este será el puntero cabeza que se pasa por parametro a las funciones)

// función para convertir strings en mayúsculas
string Mayuscula(string texto){
    for (int i=0; i < texto.length(); i++){
        texto[i] = toupper(texto[i]);   // Recorre cada letra del string y la convierte en mayúscula
    }
    return texto; //devuelve el texto todo en mayuscula
}

// Función para imprimir lista enlazada
void Imprimir_ListaEnlazada(Movimiento* cabeza){
    if (cabeza == nullptr){
        cout<<"No se encuentra ningun movimiento registrado";
        cout<<"\n\n";
    }
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
        cout << "\n";
        cout << actual->descripcion ;
        cout << "\n";
        cout << actual->categoria ;
        cout << "\n";
        cout << actual->monto ;
        cout << "\n";
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

   
    cout << "\nREGISTRAR MOVIMIENTO\n" ;
    cout<<"---------------------------------------------------------------------------------\n";   

    // Repetimos el ciclo hasta que se de una respuesta correcta
    while (true){
        cout << "1.) Tipo de Movimiento\n\n" ;     // Ingresar tipo de movimiento
        cout << "Escriba el tipo de movimiento que desea realizar (INGRESO / GASTO)\n";
        cout << "tipo: ";
        cin >> mov;
        mov=Mayuscula(mov);    // Convertimos el string en un texto completamente en mayúscula
        if (mov == "INGRESO"){
            nuevo_movimiento -> tipo = INGRESO;
            break;
        } else if (mov == "GASTO") {
            nuevo_movimiento -> tipo = GASTO;
            break;
        } else {
            cout <<"\n\n";
            cerr << "ERROR. Solo se permite los movimientos (INGRESO / GASTO)";
            cout <<"\n\n";
        }
        
    }
    cout <<"\n\n";

    while (true){
        cout << "2.) Monto\n\n" ;     // Ingresar categoría
        cout << "Ingrese el monto del movimiento. Solo se permiten valores positivos (no se puede ingresar 0) \n";
        cout << "Monto: ";
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
            cerr << "ERROR. Solo se permiten numeros positivos";
            cout <<"\n\n";
        }
    }
    cout <<"\n\n";
    cout << "3.) Categoria\n\n" ;     // Ingresar categoría
    cout << "Ingrese la categoria en la que se encuentra su movimiento\n";
    cout << "Categoria: ";
    cin >> categoria_temp;
    categoria_temp= Mayuscula(categoria_temp);    // Convertimos la categoria en mayúscula así nos aseguramos que siempre las categorías son maýusculas
    nuevo_movimiento ->categoria = categoria_temp;
    cout<<"\n\n";


    cout << "4.) Descripcion\n\n" ;     // Ingresar descripción
    cout << "Ingrese una descripcion para este movimiento\n";
    cout << "Descripcion del movimiento: ";
    cin.ignore(); // Ignora el salto de línea que no permite que se complete el getline
    getline(cin,descripcion_temp);  // Utilizamos un getline para que se puedan ingresar un texto que permita ingresar espacios.
    nuevo_movimiento ->descripcion = descripcion_temp;
    cout<<"\n\n";

    
    cout << "5.) Fecha\n\n" ;     // Ingresar Fecha
    cout << "Ingrese la fecha de este movimiento (DD/MM/AAAA) \n";


    //Estos 3 while true hacen las validaciones de las fechas
    while (true){
        cout << "Dia: ";
        cin >> nuevo_movimiento->dia;
        if (nuevo_movimiento->dia > 30){
            cout<<"\n\n";
            cout<<"El dia no puede ser mayor a 30\n\n";
            
        } else if (nuevo_movimiento ->dia <= 0){
            cout<<"\n\n";
            cout<<"El dia no puede ser 0, ni tampoco ser negativo\n\n";   
        }else{
            break;
        }
    }


    while (true){
        cout << "Mes: ";
        cin >> nuevo_movimiento->mes;

        if (nuevo_movimiento->mes > 12){
            cout<<"\n\n";
            cout<<"El mes no puede ser mayor a 12\n\n";
            
        } else if (nuevo_movimiento->mes <= 0){
            cout<<"\n\n";
            cout<<"El mes no puede ser 0, ni tampoco ser negativo\n\n";
            
        }else{
            break;
        }
    }

    while (true){
        cout << "Año: ";
        cin >> nuevo_movimiento->anio;

        if (nuevo_movimiento->anio > 2025){
            cout<<"\n\n";
            cout<<"El año no puede ser mayor al año actual 2025\n\n";
            
        } else if (nuevo_movimiento ->anio <= 0){
            cout<<"\n\n";
            cout<<"El año no puede ser 0, ni tampoco ser negativo\n\n";
            

        }else{
            break;
        }
    }
        

        

    cout <<"\n\n";
    cout<<"Movimiento registrado correctamente en la base de datos";
    cout <<"\n\n";
    
    cout<<"---------------------------------------------------------------------------------\n";   
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

void consultarMovimiento(){
    while(true){
        int opcion;
        cout<<"Tipos de movimientos a mostrar\n";
        cout<<"------------------------------------------\n";
        cout<<"1.) Todos los movimientos\n";
        cout<<"2.) Solo ingresos\n";
        cout<<"3.) Solo gastos\n";
        cout<<"4.) Filtrar por categoria especifica\n";
        cout<<"5.) Devolverse al menu principal\n";
        cout<<"------------------------------------------\n";
        cout<<"\n\n";
        cout<<"Ingrese una opcion: ";
        cin>>opcion;
        cout<<"\n\n";

        switch (opcion){ //se declara un switch para los caminos del menu
        
            case 1:
                cout<<"a";
                cout<<"\n\n";
                break;
            
            case 2:
                cout<<"b";
                cout<<"\n\n";
                break;
            
            case 3:
                cout<<"c";
                cout<<"\n\n";
                break;
                
            case 4:
                cout<<"d";
                cout<<"\n\n";
                break;

            case 5:
                cout<<"Volviendo al menu principal......";
                cout<<"\n";
                return;


            default: //si se ingresa otra opcion imprime este msj, y vuelve a preguntar
                cout<<"Ingrese una opcion valida";
                cout<<"\n\n";
                break;
        }
    }
}

void menu (){
    cout<<"BIENVENIDO A BANCO MAIS";
    cout<<"\n\n";

    while (true){ //se declara un while true para que el menú aparezca hasta que se salga de este
        int opcion;
        cout<<"MENU PRINCIPAL\n";
        cout<<"------------------------------------------\n";
        cout<<"1.) Registrar un nuevo movimiento\n";
        cout<<"2.) Consultar movimientos existentes\n";
        cout<<"3.) Modificar un movimiento\n";
        cout<<"4.) Eliminar un movimiento\n";
        cout<<"5.) Generar reporte\n";
        cout<<"6.) Salir del programa\n";
        cout<<"------------------------------------------\n";
        cout<<"\n\n";
        cout<<"Ingrese una opcion: ";
        cin>>opcion;
        cout<<"\n\n";

        switch (opcion){ //se declara un switch para los caminos del menu
        
            case 1:
                CrearMovimiento(lista);
                cout<<"\n\n";
                break;
            
            case 2:
                consultarMovimiento();
                cout<<"\n\n";
                break;
            
            case 3:
                cout<<"MODIFICAR MOVIMIENTO";
                cout<<"\n\n";
                break;
                
            case 4:
                cout<<"ELIMINAR MOVIMIENTO";
                cout<<"\n\n";
                break;

            case 5:
                cout<<"REPORTES Y ESTADISTICAS";
                cout<<"\n\n";
                break;

            case 6:
                cout<<"Se ha salido del software correctamente. Gracias por preferirnos";
                cout<<"\n\n";
                return;

            default: //si se ingresa otra opcion imprime este msj, y vuelve a preguntar
                cout<<"Ingrese una opcion valida";
                cout<<"\n\n";
                break;
        }
    }

}

int main(){

    SetConsoleOutputCP(CP_UTF8); //para que se puedan moestrar ñ y tildes en la consola
    menu();
    return 0;
}