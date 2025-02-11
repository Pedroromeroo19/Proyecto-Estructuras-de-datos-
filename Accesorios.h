#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#ifndef MOCHILA_H
#define MOCHILA_H

struct mochila
{   
    // Datos mochila
    int size = 0;
    string nombredueno;
    mochila* siguiente_mochila;
    
    //nodo accesorios 
    struct accesorios{
        string Nombre_del_Accesorio; 
        string tipo_de_accesorio;
        int valor;
        int usos; 
        accesorios *next;
    };
    accesorios* cabeza = NULL;
    
    //agregar4
    void agregar_espec_accesorio(int posicion, string  nombre, string tipo_acc, int valor, int usos ){
        if (posicion>size){
            cout << "Error : Se puso una posicion mayor al tamaño de la lista" << endl;
            return;
        }
        if ((posicion == -1)or(posicion==size)){ //caso agregar ultimo
            Agregar_Ultimo_especifico(nombre,tipo_acc, valor, usos, cabeza);
            size = size + 1 ;
        }
        if (posicion == 0){ //caso agregar primero
            Agregar_Al_final_especifico(nombre, tipo_acc, valor, usos, cabeza);
            size = size + 1 ;
        }
        if (posicion>0 && posicion<size){ //caso agregar en el medio
            Agregar_Medio_especifico(nombre,usos, tipo_acc,valor, posicion , cabeza, size);
            size = size + 1 ;
        }
    }

    void agregar_accesorios_por_zmb(){
        lectura_accesorios(cabeza);
    }
    
    void leer_lista_accesorios(){
        accesorios* aux1 = cabeza;
        int valor_pos = size;
        while (aux1 != NULL){
            cout << "   Caracteristicas del accesorio numero: "<< valor_pos << endl;
            valor_pos=valor_pos-1;
            cout << "   Nombre: "<< aux1->Nombre_del_Accesorio << endl;
            cout << "   Tipo: " << aux1->tipo_de_accesorio << endl;
            cout << "   Usos: "<< aux1->valor << endl;
            cout << "   Valor: " << aux1->usos << endl;
            cout << endl;
            aux1= aux1->next;
        }
    }

    void modificar_accesorio(int posicion, string  nombre, string tipo_acc, int valor, int usos){        
        if (posicion>size){
            cout << "Error : Se puso una posicion mayor al tamaño de la lista" << endl;
            return;
        }
        if (nombre != ""){
            modificar_nombre(nombre,posicion,cabeza, size);
        }
        if (tipo_acc != ""){
            modificar_tipo_de_acc(tipo_acc,posicion,cabeza, size);
        }
        if (valor != 0){
            modificar_valor(valor,posicion,cabeza, size);
        }
        if (usos != 0){
            modificar_usos(usos, posicion, cabeza, size);
        }
    }

    void eliminar_accesorio_pos(int position){
        if (position>size){
            cout << "Error : Se puso una posicion mayor al tamaño de la lista" << endl;
            return;
        }
        if ((position == -1)or(position==size)){ //caso eliminar ultimo
            Eliminar_Ultimo(cabeza);
            size = size - 1 ;
        }
        if (position == 0){ //caso eliminar primero
            eliminar_al_final(cabeza);
            size = size - 1 ;
        }
        if (position>0 && position<size){ //caso agregar en el medio
            eliminar_medio(position, cabeza, size);
            size = size - 1 ;
        }
    }

    void eliminar_lista_accesorios(accesorios*& cabeza){
        if(!estavacia(cabeza)){

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

    string retornar_nombre_accesorio(int posicion){
        return retornar_Nombre_del_Accesorio(cabeza, posicion);
    }

    string retornar_tipo_accesorio(int posicion){
        return retornar_tipo_de_accesorio(cabeza, posicion);
    }

    int retornar_danno_accesorio(int posicion){
        return retornar_valor(cabeza, posicion);
    }

    int retornar_usos_accesorio(int posicion){
        return retornar_usos(cabeza, posicion);
    }

    int danno_total(){
        accesorios* aux1 = cabeza;
        int danno_total = 0;
        while (aux1 != NULL){
            danno_total = danno_total + aux1->valor;
            aux1 = aux1->next;
        }
        return danno_total;
    };

    void actualizacion_de_usos() {
    accesorios* aux1 = cabeza;
    accesorios* prev = nullptr;
    int contador = 0; // Inicializar contador

    while (aux1 != NULL) {
        aux1->usos = aux1->usos - 1;
        if (aux1->usos < 0) {
            if (prev == nullptr) {
                // Eliminar el primer nodo
                cabeza = aux1->next;
                delete aux1;
                aux1 = cabeza;
            } else {
                // Eliminar un nodo en el medio o al final
                prev->next = aux1->next;
                delete aux1;
                aux1 = prev->next;
            }
            contador--; // Ajustar el contador después de eliminar un accesorio
        } else {
            prev = aux1;
            aux1 = aux1->next;
        }
        contador++;
        }
    }

    private:

//_______________________________________________________Agregar Especifico_______________________________________________________

    void Agregar_Ultimo_especifico(string  nombre, string tipoAcc, int valor , int usos , accesorios *& cabeza){
        accesorios* nuevoAcc= new accesorios();

        //Declaracion de datos
        nuevoAcc->Nombre_del_Accesorio = nombre;
        nuevoAcc->tipo_de_accesorio = tipoAcc;
        nuevoAcc->valor = valor;
        nuevoAcc->usos = usos;

        if (estavacia(cabeza)){
            nuevoAcc->next= NULL;
        }

        if (!estavacia(cabeza)){
            nuevoAcc->next= cabeza;
        }

        cabeza = nuevoAcc;
    }

    void Agregar_Al_final_especifico(string  nombre, string tipoAcc, int valor, int usos ,accesorios *& cabeza){
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

    void Agregar_Medio_especifico(string  nombre, int uso, string tipo, int valor,int posicion, accesorios *& cabeza,int tamano){
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
    void Eliminar_Ultimo(accesorios *& cabeza){
        accesorios *aux1 = cabeza->next;
        accesorios *aux2 = cabeza;
        cabeza= aux1;
        delete aux2;
    }

    void eliminar_medio(int posicion, accesorios *& cabeza, int tamano){
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

    void eliminar_al_final(accesorios *& cabeza){
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

    void modificar_nombre(string  nombre,int posicion, accesorios *& cabeza, int tamano){
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

//___________________________________________funcion para saber si esta vacia______________________________________________
    bool estavacia(accesorios *& p){
        return p == nullptr;
    }

//___________________________ Lectura de archivos _______________________
    bool lectura_accesorios(accesorios *& mochila){ 
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
                    agregar_espec_accesorio(-1, nombre, tipo,valor, usos );
                }
            // convierte variables que son strings en numeros
            //int num_vida = stoi(vida); 
            }

        archivo.close(); // Cerramos archivo 
        //cout << "Los jugadores se han cargado con exito !!" << endl; 
        //leerlistacc(); 
        return true; 
        }
    }

    string retornar_Nombre_del_Accesorio(accesorios *& cabeza, int posicion){
        accesorios *aux1 = cabeza;
        int avanze= size - posicion;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
        }
        return aux1->Nombre_del_Accesorio;

    }
    
    string retornar_tipo_de_accesorio(accesorios *& cabeza, int posicion){
        accesorios *aux1 = cabeza;
        int avanze= size - posicion;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
        }
        return aux1->tipo_de_accesorio;
    }

    int retornar_valor(accesorios *& cabeza, int posicion){
        accesorios *aux1 = cabeza;
        int avanze= size - posicion;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
        }
        return aux1->valor;
    }

    int retornar_usos(accesorios *& cabeza, int posicion){
        accesorios *aux1 = cabeza;
        int avanze= size - posicion;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
        }
        return aux1->usos;
    } 
};

#endif
