//Proyecto #1 Analisis y Diseño de Algoritmos 

//Integrantes: Mauricio Ramírez Benavidez e Isaac Esquivel Ocampo

//Profesor: Bryan Hernández

//INCLUSIONES
//-------------------------------------------------------------------------------------------------------------------------------
#include <iostream> //para usar cout y cin
#include <string> //usar string
#include <fstream> //manejo de archivos
#include <cmath> //funciones matematicas (abs)
#include <windows.h> //se incuye windows.h para permitir entrada y salida de ñ, tildes y emojis
#include <iomanip> //para usar el setprecision

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
    long double monto;
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

//FUNCION QUE INTERCAMBIA LOS ESPACIOS POR  "_"
//-------------------------------------------------------------------------------------------------------------------------------
string EliminarEspacios(string texto){
    for (int i=0; i<texto.length(); i++){
        if (texto[i] == ' '){
            texto[i] = '_';
        }
    }
    return texto;
}
//-------------------------------------------------------------------------------------------------------------------------------

//FUNCION QUE INTERCAMBIA LOS "_" POR ESPACIOS
//-------------------------------------------------------------------------------------------------------------------------------
string Espaciado(string texto){
    for (int i=0; i<texto.length(); i++){
        if (texto[i] == '_'){
            texto[i] = ' ';
        }
    }
    return texto;
}
//-------------------------------------------------------------------------------------------------------------------------------

//FUNCION PARA DETERMINAR SI UN STRING ESTA VACIO 
//-------------------------------------------------------------------------------------------------------------------------------
bool esVacio(string texto){
    if (texto.empty()){
        return true;        // Si está vacío
    } else {
        for (char letra : texto){    // Recorre el texto letra por letra
            if (!isspace(letra)){   // Si hay al menos una letra que no sea espacio significa que no esta vacía
                return false;
            }
        }
    }
   return true;    // Se recorrieron todas las letras de la palabra y todas eran espacios entonces esta vacía
}
//-------------------------------------------------------------------------------------------------------------------------------


//FUNCIONES PERMANENCIA DE ARCHIVOS

//-------------------------------------------------------------------------------------------------------------------------------
void AbrirTXT(Movimiento*& cabeza){
    // Abrir el archivo con los datos ADMIN en modo lectura
    ifstream fin_admin ("datos.txt");

    if (!fin_admin){
    
        return; 
    }   

    // Variables
    string diaTemp, mesTemp,aniosTemp,categoriaTemp,descripcionTemp;
    int tipoTemp;
    long double montoTemp;

    while (fin_admin >> diaTemp >> mesTemp >> aniosTemp >> tipoTemp >> montoTemp >> categoriaTemp >>descripcionTemp){
        Movimiento* nuevo = new Movimiento();   // Reservamos memoria para un nuevo nodo
        nuevo->sgte = nullptr; // es el último elemento de la lista
        // Agregar campos de fecha
        nuevo->diaString = diaTemp;
        nuevo->mesString = mesTemp;
        nuevo->anioString = aniosTemp;
        // Agregar tipo de dato
        if (tipoTemp == 0){
            nuevo->tipo = INGRESO;
            // Agregar monto
            nuevo->monto = abs(montoTemp);
        } else if(tipoTemp == 1){
            nuevo->tipo = GASTO;
            montoTemp = abs(montoTemp);    // lo pasamos primero a positivo
            // Agregar monto
            nuevo ->monto = -montoTemp;
        }
        // agregar categoría
        nuevo->categoria = Espaciado(categoriaTemp);
        //agregar descripción
        nuevo->descripcion = Espaciado(descripcionTemp);

        if (cabeza ==  nullptr){
            cabeza = nuevo;
        } else {                              // Lista no esta vacia
            Movimiento* actual = cabeza;
            while(actual->sgte != nullptr){             // Mientras que el nodo no apunte a null continue el ciclo y modifique actual
                actual = actual ->sgte;
            }
            actual ->sgte = nuevo; // se apunta al nuevo nodo
        }
    }
    fin_admin.close();
    
}
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
int GuardarTXT(Movimiento*& cabeza){
    // Se abren / crean los archivo en modo escritura
    ofstream fout_usuario ("movimientos.txt");   // texto con formato
    ofstream fout_admin ("datos.txt");          // texto con puros datos nada más


    // Verificar que se abrieron correctamente
    if (!fout_usuario){
    
        return 1; // codigo error
    } else if (!fout_admin){
     
        return 1;
    } else{         // Ambos archivos abrieron

        if (cabeza == nullptr){
            
            return 1;
        } else {
            Movimiento* actual = cabeza;


            // Agregar datos al txt del ADMIN
            while (actual!=nullptr){
                // Agregar al txt la fecha
                fout_admin << actual->diaString <<" ";
                fout_admin << actual->mesString<<" ";;
                fout_admin << actual->anioString<<" ";;

                //Agregar al txt El tipo de movimiento
                fout_admin << actual ->tipo <<" ";;

                // Agregar al txt el monto
                fout_admin << actual -> monto <<" ";;
                // Agregar Categoria
                fout_admin << EliminarEspacios(actual -> categoria)<<" ";;
                // Agregar descripción
                fout_admin << EliminarEspacios(actual -> descripcion)<<"  ";
                fout_admin << "\n";


                actual = actual->sgte; // avanzar en la lista
            }
            // Cerrar el archivo con información ADMIN
            fout_admin.close();

            // Agregar datos al txt del usuario
            actual = cabeza;    // Restablecemos el valor actual
            int contador = 1;
            while(actual != nullptr){
            fout_usuario << "\n---------------------------------------------------------------------------------------\n\n";
            // Imprimir el # de movimiento que es
            fout_usuario << "Moviemiento #" << contador << "\n\n";
            
            // Imprimir Fecha
            fout_usuario << "Fecha: " << actual->diaString << "/" << actual->mesString << "/" << actual->anioString <<"\n\n";
        
            // Tipo de Movimiento
            fout_usuario << "Tipo de Movimiento: ";
            if (actual -> tipo == INGRESO){
                fout_usuario << "Ingreso\n\n";
            }else if (actual -> tipo == GASTO){
                fout_usuario << "Gasto\n\n";
            }
            // Monto
            fout_usuario << "Monto: " << fixed << actual->monto ; //el fixed para evitar imprimir con notacion cientifica
            fout_usuario << "\n\n";
            // Categoría
            fout_usuario << "Categoría: "<< actual->categoria ;
            fout_usuario << "\n\n";
            // Descripción
            fout_usuario << "Descripción: "<< actual->descripcion ;
            fout_usuario << "\n\n";
            // Fin
            fout_usuario << "\n---------------------------------------------------------------------------------------\n\n";
            
            actual = actual->sgte;  // Avanzar en la lista
            contador++;
            }

            fout_usuario.close(); //cerramos el archivo dirigido al usuario
            return 0; // Se ejecuto todo correctamente.
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------------------


//FUNCIONES ANEXAS DE GENERAR REPORTES

//Calcular el Balance General en un mes y año específicos 
//-------------------------------------------------------------------------------------------------------------------------------
long double CalcularBalanceGeneral(Movimiento*& cabeza,string mes,string anio){
    if (cabeza == nullptr){
        return 0;                 // Lista vacía
    } else {
        // Algunas variables
        Movimiento* actual = cabeza;
        long double ingreso_total=0.0, gasto_total=0.0, balance_General;

        while (actual != nullptr){
            if (actual -> mesString == mes){    // Se toma en cuenta solamente los valores que incluyan el mes y año seleccionados por el usuario
                if (actual ->anioString == anio ){          
                    if (actual -> tipo == INGRESO){
                        ingreso_total += actual ->monto;    // Se suma al ingreso total lo que haya en monto
                    } else if (actual -> tipo == GASTO) {
                        gasto_total += fabs(actual -> monto );                   // se le suma el valor absoluto del monto al gasto total
                    }                    
                }   
            }
            actual=actual->sgte; // Avanzar al siguiente nodo
        }

        // actual = nullptr : Se llego al final de la lista

        balance_General = ingreso_total - gasto_total;

        return balance_General;

    }
}
//-------------------------------------------------------------------------------------------------------------------------------

//Determinar si existe cierto mes en el txt de la base de datos
//-------------------------------------------------------------------------------------------------------------------------------
bool ExisteElMes(Movimiento* cabeza,string mes){
    // Imprimir solo los años que existen en ese mes
    Movimiento* actual = cabeza;        // variable que recorre la lista enlazada
    if (cabeza == nullptr){
        return false;                 // La lista esta vaciía - mes no existe
    } else {
        while (actual != nullptr){
            if (actual -> mesString == mes){
                return true;      // si existe el movimiento en ese mes en nuestra lista enlazada
            }
            actual=actual->sgte; // Recorrer lista
        }
    }
    // actual == nullptr y no se encontro el mes
    return false;
}
//-------------------------------------------------------------------------------------------------------------------------------


//Determinar si existe cierto año en el txt de la base de datos
//-------------------------------------------------------------------------------------------------------------------------------
bool ExisteELAnio(Movimiento* cabeza, string mes, string anio){
    Movimiento* actual = cabeza;        // variable que recorre la lista enlazada
    if (cabeza == nullptr){
        return false;                 // La lista esta vaciía
    } else {
        while (actual != nullptr){
            if (actual -> mesString == mes){    // Si el mes coincide:
                if (actual ->anioString == anio ){          // Verificar si el año del parametro existe en la lista enlazada
                    return true;                        // El año si existe en nuestra lista enlazada entonces si se puede utilizar 
                }   
            }
            actual=actual->sgte;
        }
    }
    return false; // el año no existe en ese mes
}
//-------------------------------------------------------------------------------------------------------------------------------

//Funcion para ingresar el año correspondiente a cierto mes para luego hacer el reporte de ese mes y año
//-------------------------------------------------------------------------------------------------------------------------------
string IngresarAnio(string mes){
    string anio_temp;
    while (true) {
        cout << "¿De que año desea generar el reporte para el mes seleccionado? ❓: ";
        cin >> anio_temp;

        // Validaciones
        if (anio_temp[0] == '-') { //se valida que el año no sea negativo
            cout << "\n\nEl año no puede ser negativo ❌\n\n";
            continue;
            }

            if (anio_temp.size() != 4) { //validacion que el año sea de cuatro digitos
                cout << "\n\nEl año tiene que ser en formato (AAAA) ❗\n\n";
                continue;
            }

            int anioInt = stoi(anio_temp); // stoi, convierte un string a int
            if (anioInt <1 || anioInt > 2025) {
                cout << "\n\nEl año debe estar entre 0001 y 2025 ❗\n\n"; //se valida que el año no sea 0 o negativo, ni sobrepase el año actual
            } else {
                // Verificar que le año exista en el mes específico que deseamos

                if (ExisteELAnio(lista,mes,anio_temp)){     // El año si existe en el mes
                    break;
                } else {
                    cout << "\n\nEl año que ingresaste no tiene movimientos relacionados al mes # " << mes << " ❌ \n\n";
                }

    
            }
    }
    return anio_temp;       // Significa que el año si es valido Y lo devolvemos para trabajar con ese dato
}
//-------------------------------------------------------------------------------------------------------------------------------

//Funcion para guardar el reporte
//-------------------------------------------------------------------------------------------------------------------------------
void GuardarReporteTXT(Movimiento*& cabeza, string mes, string anio){
    // Pasar el mes a int 
    int mesInt = stoi(mes);
    string mes_letras;          // Variable que va a contener pero en letras en lugar de numero
    switch (mesInt)
    {
    case 1:
        mes_letras="ENERO";
        break;
    case 2:
        mes_letras="FEBRERO";
        break;
    case 3:
        mes_letras="MARZO";
        break;
    case 4:
        mes_letras="ABRIL";
        break;
    case 5:
        mes_letras="MAYO";
        break;
    case 6:
        mes_letras="JUNIO";
        break;
    case 7:
        mes_letras="JULIO";
        break;
    case 8:
        mes_letras="AGOSTO";
        break;
    case 9:
        mes_letras="SEPTIEMBRE";
        break;
    case 10:
        mes_letras="OCTUBRE";
        break;
    case 11:
        mes_letras="NOVIEMBRE";
        break;
    case 12:
        mes_letras="DICIEMBRE";
        break;
    default:
        break;
    }
    
    // Crear el txt del Reporte
    ofstream fout_reporte ("REPORTE "+mes_letras+"-"+anio+".txt");

    if (!fout_reporte){ // validar que se pueda abrir el archivo
        return;
    } else {

        if (cabeza == nullptr){
            return;                 // Lista vacía

        } else{
            // Algunas Variables
            int  contador_categoria=1;
            long double balance_general= CalcularBalanceGeneral(lista,mes,anio), ahorro_neto=0;
            Movimiento* actual = cabeza;


            //Impresiones
            fout_reporte << "---------------------------------------------------------------------------------------\n\n";
            fout_reporte << "REPORTE " << mes_letras << "/"<< anio<< "\n\n";
            fout_reporte << "*****************     Gastos     *****************\n";

            while (actual != nullptr){
                if (actual -> mesString == mes){    // Se toma en cuenta solamente los nodos que incluyan el mes y año seleccionados por el usuario
                    if (actual ->anioString == anio ){        
                        if (actual -> tipo == GASTO){  
                            fout_reporte << "Categoría #"<< contador_categoria << ": "<< actual->categoria << "\n\n";
                            fout_reporte << "Monto: "<< actual->monto << "\n\n";
                            // Se incrementan el contador
                            contador_categoria++;
                        }
                    }   
                }
                

                actual=actual->sgte; // Avanzar al siguiente nodo
            }
            fout_reporte << "\n**************************************************\n\n";

            fout_reporte << "Balance General: " << balance_general << "\n\n";;
            if (balance_general>0){
                ahorro_neto+=balance_general;   // Aumentamos el ahorro neto solamente si el balance general no es negativo
            }
            fout_reporte << "Ahorro neto: " << ahorro_neto << "\n\n";
            fout_reporte << "\n---------------------------------------------------------------------------------------\n\n";
            
        }
        fout_reporte.close();   // Cerrar el archivo una vez creado
    }
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
        cout<<"\n\nNo se encuentra ningun movimiento registrado en esta categoría ❗";  
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
    long double monto_temp;
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
        cin.ignore(); //limpia el buffer despues de un cin

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
        cout << "2.) Monto\n\n";     
        cout << "Ingrese el monto del movimiento. (no puede ser 0) \n";
        cout << "Monto: ";
        cin >> monto_temp;
        cin.ignore();

        if (monto_temp == 0){
            cerr << "ERROR ⚠️. El monto no puede ser 0\n\n";
            continue; // vuelve al principio del while true y pide el monto nuevamente
        }

        // Se asignará el monto correctamente según si es INGRESO o GASTO

        if (nuevo_movimiento->tipo == INGRESO){
            nuevo_movimiento->monto = abs(monto_temp);
        } else {
            nuevo_movimiento->monto = -abs(monto_temp);
        }

        break; // cuando el monto sea válido, saldrá del while true
    }

    cout <<"\n\n";
    while (true){
        cout <<"\n\n";
        cout << "3.) Categoria\n\n" ;     // Ingresar categoría
        cout << "Ingrese la categoria en la que se encuentra su movimiento\n";
        cout << "Categoria: ";
        getline(cin, categoria_temp);


        if (esVacio(categoria_temp)){
            cout << "\nERROR ⚠️. La categoría no puede quedar vacía\n";
        } else{
            categoria_temp= Mayuscula(categoria_temp);    // Convertimos la categoria en mayúscula así nos aseguramos que siempre las categorías son maýusculas
            nuevo_movimiento ->categoria = categoria_temp;
            cout<<"\n\n";
            break;

        }
        
    }

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

        if (nuevo_movimiento->anioString[0] == '-') { //se valida que el año no sea negativo (se pregunta por el indice [0] del string)
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
                cout<<"Ingrese una opcion valida ❗";
                cout<<"\n\n";
                break;
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------------------


//FUNCION MODIFICAR MOVIMIENTO
//-------------------------------------------------------------------------------------------------------------------------------
bool modificarMovimiento(Movimiento*& cabeza) {
    int numMov, contador = 1, total = 0;

    if (cabeza == nullptr) {
        cout << "La base de datos se encuentra vacía. No hay ningún movimiento a modificar ❗\n";
        return false;
    }

    imprimirTodosLosMovimientos(cabeza);

    cout << "Ingrese el número de movimiento que desea modificar 🔢: ";
    cin >> numMov;

    // contar total
    Movimiento* tmp = cabeza;
    while (tmp != nullptr) {
        total++;
        tmp = tmp->sgte;
    }

    if (numMov < 1 || numMov > total) {
        cout << "\n\nERROR ⚠️. El movimiento #"<< numMov<< " no existe (rango válido: 1 - " << total << ")\n\n";
        return false;
    }

    // buscar nodo
    Movimiento* actual = cabeza;
    while (contador < numMov && actual != nullptr) {
        actual = actual->sgte;
        contador++;
    }

    Movimiento* aModificar = actual;

    // menú de modificación
    while (true) {
        int opcion;
        cout << "\n¿Qué desea modificar de este movimiento? 🔀\n";
        cout << "------------------------------------------\n";
        cout << "1.) Modificar monto 🪙\n";
        cout << "2.) Modificar categoría 🔠\n";
        cout << "3.) Modificar descripción 📖\n";
        cout << "4.) Devolverse al menú principal 🔙\n";
        cout << "------------------------------------------\n";
        cout << "Ingrese una opción: ";
        cin >> opcion;
        cin.ignore();
        cout << "\n";

        switch (opcion) {
            case 1: {
                long double nuevoMonto;

                while (true) {
                    cout << "Monto actual: " << aModificar->monto << "\n";
                    cout << "Ingrese el nuevo monto (no puede ser 0): ";
                    cin >> nuevoMonto;
                        cout<<"\n\n";

                    if (nuevoMonto == 0) {
                        cout << "ERROR ⚠️. El monto no puede ser 0. Intente de nuevo\n\n";
                    } else {
                        // Se asignará el monto correctamente según si es INGRESO o GASTO

                        if (aModificar->tipo == INGRESO){
                            aModificar->monto = abs(nuevoMonto);
                        } else {
                            aModificar->monto = -abs(nuevoMonto);
                        }
                        cout << "Monto modificado correctamente ✅\n\n";
                        break; // cuando el monto sea válido, saldrá del while true   
                    }

                }
                break;
            }

            case 2: {
                string nuevaCategoria;
                while (true){
                    cout << "Categoría actual: " << aModificar->categoria << "\n";
                    cout << "Ingrese la nueva categoría: ";
                    getline(cin, nuevaCategoria);

                    if (esVacio(nuevaCategoria)){
                        cout << "\nERROR ⚠️. La categoría no puede quedar vacía\n\n";
                        continue;
                    }else{
                        aModificar->categoria = Mayuscula(nuevaCategoria);
                        cout << "\nCategoría modificada correctamente ✅\n";
                        break;
                    }
                }
                break;
            }  

            case 3: {
                string nuevaDescripcion;
                cout << "Descripción actual: " << aModificar->descripcion << "\n";
                cout << "Ingrese la nueva descripción: ";
                getline(cin, nuevaDescripcion);
                bool vacio = true; //se define la variable vacio en true

                for (char c : nuevaDescripcion){ //se recorre cada char del string
                    if (c != ' ') {  // si alguno de los caracteres no está vacio 
                    vacio = false; //pasa la condicion a false, es decir, no está vacío
                    break;
                }
                }
                
                if (nuevaDescripcion.empty() || vacio == true){ //si se tocó solo enter o hay solo espacios
                    aModificar->descripcion = "No hay descripcción para este movimiento";
                    cout<<"\n\n";
                }else{
                    aModificar->descripcion = nuevaDescripcion; //si si hay algo, se asigna lo que haya en descripcion temporal a la descripcion
                    cout<<"\n\n";
                }

                cout << "\nDescripción modificada correctamente ✅\n";
                break;
            }
            case 4:
                cout << "Volviendo al menú principal...\n";
                return true;

            default:
                cout << "Ingrese una opción válida ❗\n";
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
    cout<<"\n\n¿Está seguro que desea eliminar este movimiento?. (S / N) ❗: ";
    cin>>confirmacion;
    confirmacion = toupper(confirmacion);

    while (true){
        if (confirmacion == 'N'){
            cout<<"Se ha cancelado la eliminación del movimiento seleccionado ✅";
            return false;

        }else if (confirmacion == 'S'){
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

        }else{
            cout<<"\n\n";
            cout<<"Debe ingresar unicamente (S / N) ⚠️";
            cout<<"\n\n¿Está seguro que desea eliminar este movimiento?. (S / N) ❗: ";
            cin>>confirmacion;
            confirmacion = toupper(confirmacion);
            continue;
        }

    }

}
//-------------------------------------------------------------------------------------------------------------------------------

//FUNCION CREAR REPORTES
//-------------------------------------------------------------------------------------------------------------------------------
void Reportes(Movimiento*& cabeza){

    // Variables Temporales
    string anio_temp;

    while(true){
        int opcion;
        cout<<"Seleccione el mes 📆\n";
        cout<<"------------------------------------------\n";
        cout<<"1.) ENERO 🌻\n";
        cout<<"2.) FEBRERO 💘\n";
        cout<<"3.) MARZO 🍀\n";
        cout<<"4.) ABRIL ☔\n";
        cout<<"5.) MAYO 🌹\n";
        cout<<"6.) JUNIO 🩴\n";
        cout<<"7.) JULIO 🏐\n";
        cout<<"8.) AGOSTO 🦩\n";
        cout<<"9.) SEPTIEMBRE 🍎\n";
        cout<<"10.) OCTUBRE 🎃\n";
        cout<<"11.) NOVIEMBRE 🍁\n";
        cout<<"12.) DICIEMBRE ⛄\n";
        cout<<"13.) Devolverse al menú principal 🔙\n";
        cout<<"------------------------------------------\n";
        cout<<"\n\n";
        cout<<"Ingrese una opcion: ";
        cin>>opcion;
        cout<<"\n\n";

        switch (opcion){ //se declara un switch para los caminos del menu
            
            // Reporte de Enero
            case 1:
                if (!ExisteElMes(lista,"01")){
                    cout << "\nNo existe ningún movimiento en el mes de ENERO ❌\n\n";
                    break;
                } else {
                    
                    // Ingresar el año que desea 
                    anio_temp= IngresarAnio("01");

                    GuardarReporteTXT(lista,"01",anio_temp);    // Generar un reporte de este mes y año específicos
                    cout<<"\n Se generó el reporte correctamente ✅ \n\n";
                    break;
                }
                
            // Reporte de Febrero
            case 2:
                if (!ExisteElMes(lista,"02")){
                    cout << "\nNo existe ningún movimiento en el mes de FEBRERO ❌\n\n";
                    break;
                } else {
                    
                    anio_temp= IngresarAnio("02");


                    GuardarReporteTXT(lista,"02",anio_temp);    // Generar un reporte de este mes y año específicos
                    cout<<"\n Se generó el reporte correctamente ✅ \n\n";

                    break;
                }
            // Reporte de Marzo
            case 3:
               if (!ExisteElMes(lista,"03")){
                    cout << "\nNo existe ningún movimiento en el mes de Marzo ❌\n\n";
                    break;
                } else {

                    anio_temp= IngresarAnio("03");

                    GuardarReporteTXT(lista,"03",anio_temp);    // Generar un reporte de este mes y año específicos
                    cout<<"\n Se generó el reporte correctamente ✅ \n\n";
                    break;
                }
            // Reporte de Abril    
            case 4:
                if (!ExisteElMes(lista,"04")){
                        cout << "\nNo existe ningún movimiento en el mes de Abril ❌\n\n";
                        break;
                    } else {

                        anio_temp= IngresarAnio("04");

                        GuardarReporteTXT(lista,"04",anio_temp);    // Generar un reporte de este mes y año específicos
                        cout<<"\n Se generó el reporte correctamente ✅ \n\n";
                        break;
                    }
            // Reporte de Mayo 
            case 5:
                if (!ExisteElMes(lista,"05")){
                    cout << "\nNo existe ningún movimiento en el mes de Mayo ❌\n\n";
                    break;
                } else {

                    anio_temp= IngresarAnio("05");


                    GuardarReporteTXT(lista,"05",anio_temp);    // Generar un reporte de este mes y año específicos
                    cout<<"\n Se generó el reporte correctamente ✅ \n\n";
                    break;
                }
            // Reporte de Junio 
            case 6:
                if (!ExisteElMes(lista,"06")){
                    cout << "\nNo existe ningún movimiento en el mes de Junio ❌\n\n";
                    break;
                } else {

                    // Codigo faltante
                    anio_temp= IngresarAnio("06");

                    GuardarReporteTXT(lista,"06",anio_temp);    // Generar un reporte de este mes y año específicos
                    cout<<"\n Se generó el reporte correctamente ✅ \n\n";
                    break;
                }
            // Reporte de Julio 
            case 7:
                if (!ExisteElMes(lista,"07")){
                    cout << "\nNo existe ningún movimiento en el mes de Julio ❌\n\n";
                    break;
                } else {

                    // Codigo faltante
                    anio_temp= IngresarAnio("07");

                    GuardarReporteTXT(lista,"07",anio_temp);    // Generar un reporte de este mes y año específicos
                    cout<<"\n Se generó el reporte correctamente ✅ \n\n";
                    break;
                }
            // Reporte de Agosto 
            case 8:
                if (!ExisteElMes(lista,"08")){
                    cout << "\nNo existe ningún movimiento en el mes de Agosto ❌\n\n";
                    break;
                } else {

                    anio_temp= IngresarAnio("08");

                    GuardarReporteTXT(lista,"08",anio_temp);    // Generar un reporte de este mes y año específicos
                    cout<<"\n Se generó el reporte correctamente ✅ \n\n";
                    break;
                }
            // Reporte de Septiembre 
            case 9:
                if (!ExisteElMes(lista,"09")){
                    cout << "\nNo existe ningún movimiento en el mes de Septiembre ❌\n\n";
                    break;
                } else {

                    anio_temp= IngresarAnio("09");

                    GuardarReporteTXT(lista,"09",anio_temp);    // Generar un reporte de este mes y año específicos
                    cout<<"\n Se generó el reporte correctamente ✅ \n\n";
                    break;
                }

            // Reporte de Octubre 
            case 10:
                if (!ExisteElMes(lista,"10")){
                    cout << "\nNo existe ningún movimiento en el mes de Octubre ❌\n\n";
                    break;
                } else {

                    anio_temp= IngresarAnio("10");

                    GuardarReporteTXT(lista,"10",anio_temp);    // Generar un reporte de este mes y año específicos
                    cout<<"\n Se generó el reporte correctamente ✅ \n\n";
                    break;
                }

            // Reporte de Noviembre 
            case 11:
                if (!ExisteElMes(lista,"11")){
                    cout << "\nNo existe ningún movimiento en el mes de Noviembre ❌\n\n";
                    break;
                } else {

                    anio_temp= IngresarAnio("11");

                    GuardarReporteTXT(lista,"11",anio_temp);    // Generar un reporte de este mes y año específicos
                    cout<<"\n Se generó el reporte correctamente ✅ \n\n";
                    break;
                }
            // Reporte de Diciembre 
            case 12:
                if (!ExisteElMes(lista,"12")){
                    cout << "\nNo existe ningún movimiento en el mes de Diciembre ❌\n\n";
                    break;
                } else {

                    anio_temp= IngresarAnio("12");

                    GuardarReporteTXT(lista,"12",anio_temp);    // Generar un reporte de este mes y año específicos
                    cout<<"\n Se generó el reporte correctamente ✅ \n\n";
                    break;
                }

            //Salir
            case 13:
                cout<<"Volviendo al menu principal...";
                cout<<"\n";
                return;


            default: //si se ingresa otra opcion imprime este msj, y vuelve a preguntar
                cout<<"Ingrese una opcion valida ❗";
                cout<<"\n\n";
                break;
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------------------


//MENU PRINCIPAL
//-------------------------------------------------------------------------------------------------------------------------------
void menu (){
    AbrirTXT(lista);
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
                GuardarTXT(lista);

                cout<<"\n\n";
                break;
            
            case 2:
                consultarMovimiento();
                cout<<"\n\n";
                break;
            
            case 3:
                if(modificarMovimiento(lista) == true){
                    cout<<"\n\nSe ha modificado correctamente el movimiento seleccionado ✅\n\n";

                    GuardarTXT(lista);
                }
                break;
                
            case 4:
                if(eliminarMovimiento(lista) == true){
                    cout<<"\n\nSe ha eliminado correctamente el movimiento seleccionado ✅";
                    cout<<"\n\n\nNOTA: Se reorganizaron los numeros de movimientos ⚠️";

                    GuardarTXT(lista);
                }
                cout<<"\n\n";
                break;

            case 5:
                if (lista == nullptr) {
                    cout<<"La base de datos se encuentra vacía. No se puede generar ningún reporte ❗\n\n";
                }else{
                    Reportes(lista);
                    cout<<"\n\n";
                }
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

    cout << fixed << setprecision(2); //se arregla el formato de notación científica y se asigna la precision de decimales en 2
    SetConsoleOutputCP(CP_UTF8); //para que se puedan moestrar ñ y tildes en la consola
    SetConsoleCP(CP_UTF8); //para poder recibir ñ y tildes por cin
    menu();
    return 0;
}
//-------------------------------------------------------------------------------------------------------------------------------