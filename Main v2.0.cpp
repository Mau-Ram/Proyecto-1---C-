//Proyecto #1 Analisis y Diseño de Algoritmos 

//Integrantes: Mauricio Ramírez Benavidez e Isaac Esquivel Ocampo

//Profesor: Bryan Hernández

//INCLUSIONES
//-------------------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <windows.h> //se incuye windows.h para permitir entrada y salida de ñ, tildes y emojis
using namespace std;
//-------------------------------------------------------------------------------------------------------------------------------


//ESTRUCTURA DE LOS NODOS
//-------------------------------------------------------------------------------------------------------------------------------
enum tipo_movimiento{INGRESO,GASTO}; //el tipo de movimiento se trabajara como un enum de solo 2 opciones

struct Movimiento{
    string diaString; //el dia, mes y año se recibiran como string, para validar formato de fecha
    string mesString; //luego se convertiran a int para validar rangos y validez de la fecha
    string anioString;
    string descripcion; 
    string categoria;   
    float monto;
    tipo_movimiento tipo;   //  Es un ingreso o un gasto (la variable tipo va a ser de tipo enum)
    Movimiento* sgte;   // Puntero al siguiente valor
};

Movimiento* lista = nullptr; //se inicializa el puntero lista que apuntará a null (este será el puntero cabeza que se pasa por parametro a las funciones)
//-------------------------------------------------------------------------------------------------------------------------------


//FUNCION PARA TRABAJAR TODO EN UPPER
//-------------------------------------------------------------------------------------------------------------------------------
string Mayuscula(string texto){
    for (int i=0; i < texto.length(); i++){
        texto[i] = toupper(texto[i]);   // Recorre cada letra del string y la convierte en mayúscula
    }
    return texto; //devuelve el texto todo en mayuscula
}
//-------------------------------------------------------------------------------------------------------------------------------


//LAS 4 FUNCIONES DE IMPRESION: TODOS, INGRESOS, GASTOS, CATEGORIA

//-------------------------------------------------------------------------------------------------------------------------------
void imprimirTodosLosMovimientos(Movimiento* cabeza){
    
    if (cabeza == nullptr){
        cout<<"No hay ningun movimiento registrado en la base de datos ❗";         // Observación si la lista está vacía podría agregar al txt esto.
        cout<<"\n\n";
        return;
    }
    // Algunas variables
    Movimiento* actual = cabeza;
    int contador = 1;

    // Impresiones

    while(actual != nullptr){
        cout << "\n---------------------------------------------------------------------------------------\n\n";
        // Imprimir el # de movimiento que es
        cout << "Moviemiento #" << contador << "\n\n";
        
        // Imprimir Fecha
        cout << "Fecha: " << actual->diaString << "/" << actual->mesString << "/" << actual->anioString <<"\n\n";
    
        // Tipo de Movimiento
        cout << "Tipo de Movimiento: ";
        if (actual -> tipo == INGRESO){
            cout << "Ingreso\n\n";
        }else if (actual -> tipo == GASTO){
            cout << "Gasto\n\n";
        }
        // Monto
        cout << "Monto: " << actual->monto ;
        cout << "\n\n";
        // Categoría
        cout << "Categoría: "<< actual->categoria ;
        cout << "\n\n";
        // Descripción
        cout << "Descripción: "<< actual->descripcion ;
        cout << "\n";
        // Fin
        cout << "\n---------------------------------------------------------------------------------------\n\n";
        
        actual = actual->sgte;  // Avanzar en la lista
        contador++;
    }
}
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
void imprimirSoloIngresos(Movimiento* cabeza){
    
    if (cabeza == nullptr){
        cout<<"No hay ningun movimiento registrado en la base de datos ❗";  // Observación si la lista está vacía podría agregar al txt esto.
        cout<<"\n\n";
        return;
    }
    // Algunas variables
    Movimiento* actual = cabeza;
    int contador = 1;
    bool encontrado = false;
    // Impresiones

    while(actual != nullptr){ //se recorre toda la lista
 
        if (actual->tipo == INGRESO){ //si hay por lo menos un movimiento de tipo INGRESO entra el if

            encontrado = true; //y pasa la condición encontrado a true

            cout << "\n---------------------------------------------------------------------------------------\n\n";
            // Imprimir el # de movimiento que es
            cout << "Moviemiento #" << contador << "\n\n";
            
            // Imprimir Fecha
            cout << "Fecha: " << actual->diaString << "/" << actual->mesString << "/" << actual->anioString <<"\n\n";
        
            // Tipo de Movimiento
            cout << "Tipo de Movimiento: ";
            if (actual -> tipo == INGRESO){
                cout << "Ingreso\n\n";
            }else if (actual -> tipo == GASTO){
                cout << "Gasto\n\n";
            }
            // Monto
            cout << "Monto: " << actual->monto ;
            cout << "\n\n";
            // Categoría
            cout << "Categoría: "<< actual->categoria ;
            cout << "\n\n";
            // Descripción
            cout << "Descripción: "<< actual->descripcion ;
            cout << "\n";
            // Fin
            cout << "\n---------------------------------------------------------------------------------------\n\n";
             
        }
        actual = actual->sgte;  // Avanzar en la lista
        contador++;
    }

    if (encontrado == false){ //si no encuentra ningun movimiento de tipo INGRESO entra a este if, el cual mostrará el msj
        cout<<"No se encuentra ningun ingreso registrado ❗"; 
    }
}
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
void imprimirSoloGastos(Movimiento* cabeza){
    
    if (cabeza == nullptr){
        cout<<"No hay ningun movimiento registrado en la base de datos ❗";  // Observación si la lista está vacía podría agregar al txt esto.
        cout<<"\n\n";
        return;
    }
    // Algunas variables
    Movimiento* actual = cabeza;
    int contador = 1;
    bool encontrado = false;

    // Impresiones

    while(actual != nullptr){

        if (actual->tipo == GASTO){

            encontrado = true;

            cout << "\n---------------------------------------------------------------------------------------\n\n";
            // Imprimir el # de movimiento que es
            cout << "Moviemiento #" << contador << "\n\n";
            
            // Imprimir Fecha
            cout << "Fecha: " << actual->diaString << "/" << actual->mesString << "/" << actual->anioString <<"\n\n";
        
            // Tipo de Movimiento
            cout << "Tipo de Movimiento: ";
            if (actual -> tipo == INGRESO){
                cout << "Ingreso\n\n";
            }else if (actual -> tipo == GASTO){
                cout << "Gasto\n\n";
            }
            // Monto
            cout << "Monto: " << actual->monto ;
            cout << "\n\n";
            // Categoría
            cout << "Categoría: "<< actual->categoria ;
            cout << "\n\n";
            // Descripción
            cout << "Descripción: "<< actual->descripcion ;
            cout << "\n";
            // Fin
            cout << "\n---------------------------------------------------------------------------------------\n\n";
             
        }
        actual = actual->sgte;  // Avanzar en la lista
        contador++;
    }

    if (encontrado == false){
        cout<<"No se encuentra ningun gasto registrado ❗";  
    }
}
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
void imprimirPorCategoria(Movimiento* cabeza){
    
    if (cabeza == nullptr){
        cout<<"No hay ningun movimiento registrado en la base de datos ❗";  // Observación si la lista está vacía podría agregar al txt esto.
        cout<<"\n\n";
        return;
    }
    // Algunas variables
    Movimiento* actual = cabeza;
    int contador = 1;
    string categoria;
    bool encontrado = false;
    // Impresiones

    cout<<"Ingrese la categoría por la cual desea filtrar 🔠: ";
    cin.ignore();
    getline(cin, categoria);
    categoria = Mayuscula(categoria);
    
    while(actual != nullptr){

        if (actual->categoria == categoria){

            encontrado = true;

            cout << "\n---------------------------------------------------------------------------------------\n\n";
            // Imprimir el # de movimiento que es
            cout << "Moviemiento #" << contador << "\n\n";
            
            // Imprimir Fecha
            cout << "Fecha: " << actual->diaString << "/" << actual->mesString << "/" << actual->anioString <<"\n\n";
        
            // Tipo de Movimiento
            cout << "Tipo de Movimiento: ";
            if (actual -> tipo == INGRESO){
                cout << "Ingreso\n\n";
            }else if (actual -> tipo == GASTO){
                cout << "Gasto\n\n";
            }
            // Monto
            cout << "Monto: " << actual->monto ;
            cout << "\n\n";
            // Categoría
            cout << "Categoría: "<< actual->categoria ;
            cout << "\n\n";
            // Descripción
            cout << "Descripción: "<< actual->descripcion ;
            cout << "\n";
            // Fin
            cout << "\n---------------------------------------------------------------------------------------\n\n";
            
        }
        actual = actual->sgte;  // Avanzar en la lista
        contador++;
    }

    if (encontrado == false){
        cout<<"No se encuentra ningun movimiento en esta categoría registrado ❗";  
    }
}
//-------------------------------------------------------------------------------------------------------------------------------

//FUNCION CREAR MOVIMIENTO (CORAZON DEL PROGRAMA)
//-------------------------------------------------------------------------------------------------------------------------------
void CrearMovimiento(Movimiento*& cabeza){
    Movimiento* nuevo_movimiento = new Movimiento();    // Creamos la lista vacia
    nuevo_movimiento -> sgte = nullptr;                 // Establecemos que este es el último valor de la lista

    // ALGUNAS VARIABLES
    string mov;
    float monto_temp;
    string descripcion_temp;
    string categoria_temp;

   
    cout << "\nREGISTRAR MOVIMIENTO 📝\n" ;
    cout<<"---------------------------------------------------------------------------------\n";   

    // Repetimos el ciclo hasta que se de una respuesta correcta
    while (true){
        cout << "1.) Tipo de Movimiento\n\n" ;     // Ingresar tipo de movimiento
        cout << "Escriba el tipo de movimiento que desea realizar (INGRESO / GASTO)\n";
        cout << "Tipo: ";
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
            cerr << "ERROR ⚠️. Solo se permite los movimientos (INGRESO / GASTO)";
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
            cerr << "ERROR ⚠️. Solo se permiten numeros positivos";
            cout <<"\n\n";
        }
    }
    cout <<"\n\n";
    cout << "3.) Categoria\n\n" ;     // Ingresar categoría
    cout << "Ingrese la categoria en la que se encuentra su movimiento\n";
    cout << "Categoria: ";
    cin.ignore();
    getline(cin, categoria_temp);
    categoria_temp= Mayuscula(categoria_temp);    // Convertimos la categoria en mayúscula así nos aseguramos que siempre las categorías son maýusculas
    nuevo_movimiento ->categoria = categoria_temp;
    cout<<"\n\n";


    cout << "4.) Descripcion\n\n" ;     // Ingresar descripción
    cout << "Ingrese una descripcion para este movimiento (toque ENTER si no desea ingresar descripción)\n";
    cout << "Descripcion del movimiento: ";
    getline(cin,descripcion_temp);  // Utilizamos un getline para que se puedan ingresar un texto que permita ingresar espacios.

    bool vacio = true; //se define la variable vacio en true

    for (char c : descripcion_temp){ //se recorre cada char del string
        if (c != ' ') {  // si alguno de los caracteres no está vacio 
        vacio = false; //pasa la condicion a false, es decir, no está vacío
        break;
    }
    }
    
    if (descripcion_temp.empty() || vacio == true){ //si se tocó solo enter o hay solo espacios
        nuevo_movimiento->descripcion = "No hay descripcción para este movimiento";
        cout<<"\n\n";
    }else{
        nuevo_movimiento ->descripcion = descripcion_temp; //si si hay algo, se asigna lo que haya en descripcion temporal a la descripcion
        cout<<"\n\n";
    }
    
    cout << "5.) Fecha\n\n" ;     // Ingresar Fecha
    cout << "Ingrese la fecha de este movimiento (DD/MM/AAAA) \n";


    //Estos 3 while true hacen las validaciones de las fechas
    while (true){
        cout<<"-----------\n";
        cout << "Dia: ";
        cin >> nuevo_movimiento->diaString;
        cout<<"-----------\n";

        if (nuevo_movimiento->diaString[0] == '-') { //se valida que el dia no sea negativo (se pregunta por el indice 0 porque es la primera posicion del string)
        cout << "\nEl dia no puede ser negativo ❌ \n\n";
        continue;
        }

        if (nuevo_movimiento->diaString.size() != 2) { //validacion que el dia sea de dos digitos
            cout << "\nEl día tiene que ser en formato (DD) ❗\n\n";
            continue;
        }

        int diaInt = stoi(nuevo_movimiento->diaString); // stoi, convierte un string a int
        if (diaInt < 1 || diaInt > 30) {
            cout << "\nEl día debe estar entre 01 y 30 ❗\n\n"; //se valida que el dia no sea 0, ni sobrepase el 30
        } else {
            break;
        }
    }

    while (true){
        cout<<"-----------\n";
        cout<<"Dia: "<<nuevo_movimiento->diaString<<"\n";
        cout << "Mes: ";
        cin >> nuevo_movimiento->mesString;
        cout<<"-----------\n";

        if (nuevo_movimiento->mesString[0] == '-') { //se valida que el mes no sea negativo
        cout << "\nEl mes no puede ser negativo ❌\n\n";
        continue;
        }

        if (nuevo_movimiento->mesString.size() != 2) { //validacion que el mes sea de dos digitos
            cout << "\nEl mes tiene que ser en formato (MM) ❗\n\n";
            continue;
        }

        int mesInt = stoi(nuevo_movimiento->mesString); // stoi, convierte un string a int
        if (mesInt < 1 || mesInt > 12) {
            cout << "\nEl mes debe estar entre 01 y 12 ❗\n\n"; //se valida que el mes no sea 0, ni sobrepase el 30
        } else {
            break;
        }
    }

    while (true){

        cout<<"-----------\n";
        cout<<"Dia: "<<nuevo_movimiento->diaString<<"\n";
        cout<<"Mes: "<<nuevo_movimiento->mesString<<"\n";
        cout << "Año: ";
        cin >> nuevo_movimiento->anioString;
        cout<<"-----------";

        if (nuevo_movimiento->anioString[0] == '-') { //se valida que el año no sea negativo
        cout << "\n\nEl año no puede ser negativo ❌\n\n";
        continue;
        }

        if (nuevo_movimiento->anioString.size() != 4) { //validacion que el año sea de cuatro digitos
            cout << "\n\nEl año tiene que ser en formato (AAAA) ❗\n\n";
            continue;
        }

        int anioInt = stoi(nuevo_movimiento->anioString); // stoi, convierte un string a int
        if (anioInt <1 || anioInt > 2025) {
            cout << "\n\nEl año debe estar entre 0001 y 2025 ❗\n\n"; //se valida que el año no sea 0 o negativo, ni sobrepase el año actual
        } else {
            break;
        }
    }
    
    cout <<"\n\n";
    cout<<"Movimiento registrado correctamente en la base de datos ✅";
    cout <<"\n\n";
    
    cout<<"---------------------------------------------------------------------------------\n"; 

    // Si la lista está vacía, el nuevo movimiento va a ser la cabeza de la lista
    if (cabeza ==  nullptr){
        cabeza = nuevo_movimiento;
    } else{                             //Si la lista no está vacía, se pondrá el nuevo movimiento al final
        Movimiento* actual = cabeza;
        while(actual->sgte != nullptr){             // Mientras que el nodo no apunte a null continue el ciclo y modifique actual
            actual = actual ->sgte;
        }
        actual ->sgte = nuevo_movimiento;
    }
    
    
}
//-------------------------------------------------------------------------------------------------------------------------------


//MENU INTERNO (CONSULTAR)
//-------------------------------------------------------------------------------------------------------------------------------

void consultarMovimiento(){
    while(true){
        int opcion;
        cout<<"Tipos de movimientos a mostrar 🏧\n";
        cout<<"------------------------------------------\n";
        cout<<"1.) Todos los movimientos ✉️\n";
        cout<<"2.) Solo ingresos 💰\n";
        cout<<"3.) Solo gastos 💸\n";
        cout<<"4.) Filtrar por categoria especifica 🔠\n";
        cout<<"5.) Devolverse al menu principal 🔙\n";
        cout<<"------------------------------------------\n";
        cout<<"\n\n";
        cout<<"Ingrese una opcion: ";
        cin>>opcion;
        cout<<"\n\n";

        switch (opcion){ //se declara un switch para los caminos del menu
        
            case 1:
                imprimirTodosLosMovimientos(lista);
                cout<<"\n\n";
                break;
            
            case 2:
                imprimirSoloIngresos(lista);
                cout<<"\n\n";
                break;
            
            case 3:
                imprimirSoloGastos(lista);
                cout<<"\n\n";
                break;
                
            case 4:
                imprimirPorCategoria(lista);
                cout<<"\n\n";
                break;

            case 5:
                cout<<"Volviendo al menu principal......";
                cout<<"\n";
                return;


            default: //si se ingresa otra opcion imprime este msj, y vuelve a preguntar
                cout<<"Ingrese una opcion valida ";
                cout<<"\n\n";
                break;
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------------------

//FUNCION ELIMINAR
//-------------------------------------------------------------------------------------------------------------------------------
bool eliminarMovimiento(Movimiento*& cabeza){

    int numMov, contador = 1, total = 0;
    char confirmacion;

    if (cabeza == nullptr) {
        cout<<"La base de datos se encuentra vacía. No hay nada que eliminar ❗";
        return false; // lista vacía, nada que eliminar
    }

    imprimirTodosLosMovimientos(lista);

    cout<<"Ingrese el numero de movimiento que desea borrar 🔢: ";
    cin>>numMov;


    //se pregunta si el usuario está seguro de eliminar el movimiento que seleccionó 
    cout<<"\n\n¿Está seguro que desea eliminar este movimiento?. (S = eliminar, Otra tecla = cancelar eliminación) ❗: ";
    cin>>confirmacion;
    confirmacion = toupper(confirmacion);

    if (confirmacion != 'S'){
        cout<<"Se ha cancelado la eliminación del movimiento seleccionado ✅";
        return false;
    }

    Movimiento* tmp = cabeza; //se apunta el nodo temporal a la cabeza

    while (tmp != nullptr) { //se recorre la lista hasta el ultimo nodo y se incrementa el valor de total
        total++;             //para conocer la longitud de la lista (cantidad de nodos) (cantidad de movimientos)
        tmp = tmp->sgte;
    }

    if (numMov < 1 || numMov > total) { //se valida que el movimiento que se desea eliminar esté en rango 
        cout<<"\n\n";
        cout << "ERROR ⚠️. El movimiento #" << numMov << " no existe (rango válido: 1 - " << total << ")\n";
        return false;
        
}
    // Caso especial: el nodo a eliminar es la cabeza
    if (contador == numMov) {
        Movimiento* aBorrar = cabeza;
        cabeza = cabeza->sgte;   // mueve la cabeza al segundo nodo
        delete aBorrar;                      // libera el nodo eliminado
        return true;
    }
    

    // Para eliminar un nodo intermedio o la cola
    Movimiento* actual = cabeza;
    Movimiento* anterior = nullptr;
    
    while (cabeza != nullptr && contador < numMov){
        anterior = actual;
        actual = actual->sgte;
        contador++;
    }

    Movimiento* aBorrar = actual;
    anterior->sgte = actual->sgte;
    delete aBorrar;
    return true; 
}
//-------------------------------------------------------------------------------------------------------------------------------

//MENU PRINCIPAL
//-------------------------------------------------------------------------------------------------------------------------------
void menu (){
    cout<<"\n\n";
    cout<<"BIENVENIDO A BANCO MAIS 🌽";
    cout<<"\n\n";

    while (true){ //se declara un while true para que el menú aparezca hasta que se salga de este
        int opcion;
        cout<<"MENU PRINCIPAL 📍\n";
        cout<<"------------------------------------------\n";
        cout<<"1.) Registrar un nuevo movimiento 📝\n";
        cout<<"2.) Consultar movimientos existentes 🏧\n";
        cout<<"3.) Modificar un movimiento 🔀\n";
        cout<<"4.) Eliminar un movimiento 🗑️\n";
        cout<<"5.) Generar reporte 📄\n";
        cout<<"6.) Salir del programa 👋\n";
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
                if(eliminarMovimiento(lista) == true){
                    cout<<"\n\nSe ha eliminado correctamente el movimiento seleccionado ✅";
                    cout<<"\n\n\nNOTA: Se reorganizaron los numeros de movimientos ⚠️";
                }
                cout<<"\n\n";
                break;

            case 5:
                cout<<"REPORTES Y ESTADISTICAS";
                cout<<"\n\n";
                break;

            case 6:
                cout<<"Se ha salido del software correctamente. Gracias por preferirnos 👋";
                cout<<"\n\n";
                return;

            default: //si se ingresa otra opcion imprime este msj, y vuelve a preguntar
                cout<<"Ingrese una opcion valida ❗";
                cout<<"\n\n";
                break;
        }
    }

}
//-------------------------------------------------------------------------------------------------------------------------------


//MAIN (ORQUESTADOR)
//-------------------------------------------------------------------------------------------------------------------------------
int main(){

    SetConsoleOutputCP(CP_UTF8); //para que se puedan moestrar ñ y tildes en la consola
    SetConsoleCP(CP_UTF8); //para poder recibir ñ y tildes por cin
    menu();
    return 0;
}
//-------------------------------------------------------------------------------------------------------------------------------