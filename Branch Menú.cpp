//Proyecto #1 Analisis y Diseño de Algoritmos 

//Integrantes: Mauricio Ramírez Benavidez e Isaac Esquivel Ocampo

//Profesor: Bryan Hernández


#include <iostream>
#include <string>
using namespace std;


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
                cout<<"REGISTRAR MOVIMIENTO";
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
                cout<<"Se ha salido del software correctamente, Gracias por preferirnos";
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


    menu();
    return 0;
}