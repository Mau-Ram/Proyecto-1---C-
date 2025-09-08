//Proyecto #1 Analisis y Diseño de Algoritmos 

//Integrantes: Mauricio Ramírez Benavidez e Isaac Esquivel Ocampo

//Profesor: Bryan Hernández


#include <iostream>
#include <string>
using namespace std;

int main (){
<<<<<<< Updated upstream
    cout << "Hola mundo";


    cout<<"polla";
    cout<<"polla voladora volando"
=======
    cout<<"BIENVENIDO A BANCO MAIS";
    cout<<"\n\n";

    while (true){ //se declara un while true para que el menú aparezca hasta que se salga de este
    int opcion;
    cout<<"MENU\n";
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

    switch (opcion) //se declara un switch para los caminos del menu
    {
    case 1:
        cout<<"REGISTRAR MOVIMIENTO";
        break;
    
    case 2:
        cout<<"CONSULTAR MOVIMIENTO";

        break;
    
    case 3:
        cout<<"MODIFICAR MOVIMIENTO";

        break;
        
    case 4:
        cout<<"ELIMINAR MOVIMIENTO";

        break;

    case 5:
        cout<<"REPORTES Y ESTADISTICAS";

        break;

    case 6:
        cout<<"SALIR DEL SOFTWARE";

        return;

    default: //si se ingresa otra opcion imprime este msj, y vuelve a preguntar
        cout<<"Ingrese una opcion valida";
        cout<<"\n\n";
        break;
    }
    }
>>>>>>> Stashed changes
    return 0;
    
}