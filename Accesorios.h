#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


    struct accesorios{
        string Nombre_del_Accesorio; 
        string tipo_de_accesorio;
        int valor;
        int usos; 
        accesorios *next;
    };

    accesorios* cabeza_acc = NULL;

    //___________________________________________funcion para saber si esta vacia______________________________________________
    bool estavacia_acc(accesorios *& p){
        return p == nullptr;
    }

    //_______________________________________________________Agregar Especifico_______________________________________________________

    void Agregar_Ultimo_especifico_acc(string  nombre, string tipoAcc, int valor , int usos , accesorios *& cabeza){
        accesorios* nuevoAcc= new accesorios();

        //Declaracion de datos
        nuevoAcc->Nombre_del_Accesorio = nombre;
        nuevoAcc->tipo_de_accesorio = tipoAcc;
        nuevoAcc->valor = valor;
        nuevoAcc->usos = usos;

        if (estavacia_acc(cabeza)){
            nuevoAcc->next= NULL;
        }

        if (!estavacia_acc(cabeza)){
            nuevoAcc->next= cabeza;
        }

        cabeza = nuevoAcc;
    }

    void Agregar_Al_final_especifico_acc(string  nombre, string tipoAcc, int valor, int usos ,accesorios *& cabeza){
        accesorios* nuevoAcc = new accesorios();

        //Declaracion de datos
        nuevoAcc->Nombre_del_Accesorio = nombre;
        nuevoAcc->tipo_de_accesorio = tipoAcc;
        nuevoAcc->valor = valor;
        nuevoAcc->usos = usos;

        accesorios *aux1= cabeza->next;
        accesorios *aux2= cabeza;
        while (aux1 != NULL){
            aux1= aux1->next;
            aux2= aux2->next;
            if (aux1 == NULL){
                nuevoAcc->next= aux1;
                aux2->next=nuevoAcc;
            }
        }
    }

    void Agregar_Medio_especifico_acc(string  nombre, int uso, string tipo, int valor,int posicion, accesorios *& cabeza,int tamano){
        accesorios* nuevoacc = new accesorios();

        //Declaracion de datos
        nuevoacc->Nombre_del_Accesorio= nombre;
        nuevoacc->tipo_de_accesorio = tipo;
        nuevoacc->usos = uso;
        nuevoacc->valor = valor;

        accesorios *aux1= cabeza->next;
        accesorios *aux2= cabeza;
        int avanze = tamano - posicion;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
            aux2= aux2->next;
        }
        nuevoacc->next = aux1;
        aux2->next= nuevoacc;
    }



//_______________________________________________________funciones eliminar________________________________________________
    void Eliminar_Ultimo_acc(accesorios *& cabeza){
        accesorios *aux1 = cabeza->next;
        accesorios *aux2 = cabeza;
        cabeza= aux1;
        delete aux2;
    }

    void eliminar_medio_acc(int posicion, accesorios *& cabeza, int tamano){
        accesorios *aux1 = cabeza->next;
        accesorios *aux2 = cabeza;
        int avanze= tamano - posicion - 1;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
            aux2= aux2->next;
        }
        aux2->next = aux1->next;
        delete aux1;
    }

    void eliminar_al_final_acc(accesorios *& cabeza){
        accesorios *aux1= cabeza->next;
        accesorios *aux2= cabeza;
        while (aux1 != nullptr){
            aux1 = aux1->next;
            aux2 = aux2->next;
            if (aux1->next == nullptr){
                aux2->next = nullptr;
                delete aux1;
                break;
            }
        }
    }


//___________________________________________________funciones modificar lista___________________________________________

    void modificar_nombre_acc(string  nombre,int posicion, accesorios *& cabeza, int tamano){
        accesorios *aux1 = cabeza;
        int avanze= tamano - posicion;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
        }
        aux1->Nombre_del_Accesorio = nombre;
    }

    void modificar_tipo_de_acc(string  nombre,int posicion, accesorios *& cabeza, int tamano){
        accesorios *aux1 = cabeza;
        int avanze= tamano - posicion;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
        }
        aux1->tipo_de_accesorio = nombre;
    }

    void modificar_usos(int  usos,int posicion, accesorios *& cabeza, int tamano){
        accesorios *aux1 = cabeza;
        int avanze= tamano - posicion;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
        }
        aux1->usos = usos;
    }

    void modificar_valor(int  valor,int posicion, accesorios *& cabeza, int tamano){
        accesorios *aux1 = cabeza;
        int avanze= tamano - posicion;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
        }
        aux1->valor = valor;
    }
    
    void agregar_espec_acc(int posicion, string  nombre, string tipo_acc, int valor, int usos ){
        int size = 0;

        if (posicion>size){
            cout << "Error : Se puso una posicion mayor al tamaño de la lista" << endl;
            return;
        }
        if ((posicion == -1)or(posicion==size)){ //caso agregar ultimo
            Agregar_Ultimo_especifico_acc(nombre,tipo_acc, valor, usos, cabeza_acc);
            size = size + 1 ;
        }
        if (posicion == 0){ //caso agregar primero
            Agregar_Al_final_especifico_acc(nombre, tipo_acc, valor, usos, cabeza_acc);
            size = size + 1 ;
        }
        if (posicion>0 && posicion<size){ //caso agregar en el medio
            Agregar_Medio_especifico_acc(nombre,usos, tipo_acc,valor, posicion , cabeza_acc, size);
            size = size + 1 ;
        }
    }
    
    void leerlistacc(){
        int size = 0;

        accesorios* aux1 = cabeza_acc;
        int valor_pos = size;
        while (aux1 != NULL){
            cout << "Posicion: "<< valor_pos << endl;
            valor_pos=valor_pos-1;
            cout << "Caracteristicas de los accesorios:"<< endl;
            cout << "Nombre: "<< aux1->Nombre_del_Accesorio << endl;
            cout << "Tipo: " << aux1->tipo_de_accesorio << endl;
            cout << "Usos: "<< aux1->valor << endl;
            cout << "Valor: " << aux1->usos << endl;
            cout << endl;
            aux1= aux1->next;
        }
    }

    void modificarlistacc(int posicion, string  nombre, string tipo_acc, int valor, int usos){ 
        int size = 0;

        if (posicion>size){
            cout << "Error : Se puso una posicion mayor al tamaño de la lista" << endl;
            return;
        }
        if (nombre != ""){
            modificar_nombre_acc(nombre,posicion,cabeza_acc, size);
        }
        if (tipo_acc != ""){
            modificar_tipo_de_acc(tipo_acc,posicion,cabeza_acc, size);
        }
        if (valor != 0){
            modificar_valor(valor,posicion,cabeza_acc, size);
        }
        if (usos != 0){
            modificar_usos(usos, posicion, cabeza_acc, size);
        }

    }

    void eliminarlistposacc(int position){
        int size = 0;

        if (position>size){
            cout << "Error : Se puso una posicion mayor al tamaño de la lista" << endl;
            return;
        }
        if ((position == -1)or(position==size)){ //caso eliminar ultimo
            Eliminar_Ultimo_acc(cabeza_acc);
            size = size - 1 ;
        }
        if (position == 0){ //caso eliminar primero
            eliminar_al_final_acc(cabeza_acc);
            size = size - 1 ;
        }
        if (position>0 && position<size){ //caso agregar en el medio
            eliminar_medio_acc(position, cabeza_acc, size);
            size = size - 1 ;
        }
    }

    void eliminar_lista_accesorios(accesorios*& cabeza){
        if(!estavacia_acc(cabeza)){

            accesorios *aux1 = cabeza;
            accesorios *aux2;

            while (cabeza != NULL)
            {
                aux2 = aux1;
                aux1 = aux1->next;
                delete aux2;
            }
        
        }
    }

// __________________________________________________Lectura de archivos __________________________________________________// 
    bool lecturaAcc(accesorios **accesorios){ 
        ifstream archivo("Accesorio.zmb", ios::in);
        if (!archivo) {
            cout << "Error al abrir el archivo." << endl;
            system("pause");
            cout << endl;  
            return false;
        }else{
            string nombre, tipo,  aux; 
            int valor, usos, pos; 
            int cantidad_acc; 
            archivo >> cantidad_acc; 
            archivo.ignore();
            int cont = 0;
            while(cont<cantidad_acc){
                getline(archivo, aux);
                if(aux == "---"){
                    archivo >> pos; 
                    getline(archivo, nombre); 
                    getline(archivo,tipo );  
                    archivo >> valor; 
                    archivo >> usos; 
                    cont++;
                    agregar_espec_acc(pos, nombre, tipo,valor, usos );
                }
            // convierte variables que son strings en numeros
            //int num_vida = stoi(vida); 
            }

        archivo.close(); // Cerramos archivo 
        cout << "Los jugadores se han cargado con exito !!" << endl; 
        leerlistacc(); 
        return true; 
        }
    }

