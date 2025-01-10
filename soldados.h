#include <iostream>
#include <fstream>
#include <sstream>
#include "Colores.h"
#include "Bitacora.h"
using namespace std;

struct Soldados{   

    struct soldado{
        string Nombre_soldado; 
        int vida;
        soldado *next;
    };

    soldado* cabeza = NULL;
    int size = 0;
    
    void agregar_espec_soldados(int posicion, string  nombre, int vida){
        if (posicion>size){
            cout << "Error : Se puso una posicion mayor al tamaño de la lista" << endl;
            return;
        }
        if ((posicion == -1)or(posicion==size)){ //caso agregar ultimo
            Agregar_Ultimo_especifico(nombre, vida,  cabeza);
            size = size + 1 ;
        }
        if (posicion == 0){ //caso agregar primero
            Agregar_Al_final_especifico(nombre, vida , cabeza);
            size = size + 1 ;
        }
        if (posicion>0 && posicion<size){ //caso agregar en el medio
            Agregar_Medio_especifico(nombre,  vida, posicion , cabeza, size);
            size = size + 1 ;
        }
    }
    
    int vida(){
        int vida = 0; 
        cout  <<"Indique la cantidad de vida que tiene el soldado de la lista" << endl; 
        cin >> vida; 
        return vida; 
    }

    string nombreSoldado(){
        string nombresoldado; 
        cout << "Indique el nombre del soldado que esta en la lista" << endl; 
        cin >>nombresoldado; 
        return nombresoldado;
    }

    void leer_lista_soldados(){
        soldado* aux1 = cabeza;
        int valor_pos = size;
        while (aux1 != NULL){
            cout << "Posicion: "<< valor_pos << endl;
            valor_pos=valor_pos-1;
            cout << "Caracteristicas de los Zombies:"<< endl;
            cout << "Nombre del soldado: "<< aux1->Nombre_soldado << endl;
            cout << "Vida del soldado: "<< aux1->vida << endl;
            cout << endl;
            aux1= aux1->next;
        }
    }
    
    void agregar_soldados_por_zmb(){
        lecturasoldados(cabeza);
    }


    void modificar_list_soldado(int posicion, string  nombre, int vida){        
        if (posicion>size){
            cout << "Error : Se puso una posicion mayor al tamaño de la lista" << endl;
            return;
        }
        if (nombre != ""){
            modificar_nombre(nombre,posicion,cabeza, size);
        }
        if (vida != 0){
            modificar_vida(vida, posicion, cabeza, size);
        }
        if (posicion<0){
            cout << "Error : Se puso una posicion menor a 0" << endl;
            return;
        }

    }

    void eliminar_soldado(int position){
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
   
    void eliminar_lista_zombie(soldado *& cabeza){
    if(!estavacia(cabeza)){

        soldado *aux1 = cabeza;
        soldado *aux2;

        while (cabeza != NULL)
        {
            aux2 = aux1;
            aux1 = aux1->next;
            delete aux2;
        }
        
    }}

    string retornar_nombre_soldado(int posicion){
        return retornar_nombre_soldados(cabeza, posicion);
    }

    int retornar_vida_soldado(int posicion){
        return retornar_vida_soldados(cabeza, posicion);
    }

    int actualizacion_de_vida(int posicion, int vida){
        soldado *aux1 = cabeza;
        int avanze= size - posicion;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
        }
        aux1->vida = aux1->vida - vida;
        return aux1->vida;
    }

    

    private:

//_______________________________________________________Agregar Especifico_______________________________________________________

    void Agregar_Ultimo_especifico(string  nombre, int vida, soldado *& cabeza){
        soldado* nuevosoldado= new soldado();

        //Declaracion de datos
        nuevosoldado->Nombre_soldado= nombre;
        nuevosoldado->vida = vida;
    
        if (estavacia(cabeza)){
            nuevosoldado->next= NULL;
        }

        if (!estavacia(cabeza)){
            nuevosoldado ->next= cabeza;
        }

        cabeza = nuevosoldado;
    }

    void Agregar_Al_final_especifico(string  nombre, int vida, soldado *& cabeza){
        soldado* nuevosoldado = new soldado();

        //Declaracion de datos
        nuevosoldado->Nombre_soldado = nombre;
        nuevosoldado->vida = vida;

        soldado *aux1= cabeza->next;
        soldado *aux2= cabeza;
        while (aux1 != NULL){
            aux1= aux1->next;
            aux2= aux2->next;
            if (aux1 == NULL){
                nuevosoldado->next= aux1;
                aux2->next=nuevosoldado;
            }
        }
    }

    void Agregar_Medio_especifico(string  nombre, int vida ,int posicion, soldado *& cabeza,int tamano){
        soldado* nuevosoldado = new soldado;

        //Declaracion de datos
        nuevosoldado->Nombre_soldado = nombre;
        nuevosoldado->vida = vida;

        soldado *aux1= cabeza->next;
        soldado *aux2= cabeza;
        int avanze= tamano - posicion;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
            aux2= aux2->next;
        }
        nuevosoldado->next = aux1;
        aux2->next= nuevosoldado;
    }



//_______________________________________________________funciones eliminar________________________________________________
    void Eliminar_Ultimo(soldado *& cabeza){
        soldado *aux1 = cabeza->next;
        soldado *aux2 = cabeza;
        cabeza= aux1;
        delete aux2;
    }

    void eliminar_medio(int posicion, soldado *& cabeza, int tamano){
        soldado *aux1 = cabeza->next;
        soldado *aux2 = cabeza;
        int avanze= tamano - posicion - 1;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
            aux2= aux2->next;
        }
        aux2->next = aux1->next;
        delete aux1;
    }

    void eliminar_al_final(soldado *& cabeza){
        soldado *aux1= cabeza->next;
        soldado *aux2= cabeza;
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
    void modificar_nombre(string  nombre,int posicion, soldado *& cabeza, int tamano){
        soldado *aux1 = cabeza;
        int avanze= tamano - posicion;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
        }
        aux1->Nombre_soldado= nombre;
    }


    void modificar_vida(int  vida,int posicion, soldado *& cabeza, int tamano){
        soldado *aux1 = cabeza;
        int avanze= tamano - posicion;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
        }
        aux1->vida = vida;
    }

//___________________________________________funcion para saber si esta vacia______________________________________________
    bool estavacia(soldado *& p){
        return p == nullptr;
    }
    
//____________________________________________Funcion para leer soldado___________________________________________________

    bool lecturasoldados(soldado *& cabeza){ 
        ifstream archivo("Soldado.zmb", ios::in);
        if (!archivo) {
            cout << "Error al abrir el archivo." << endl;
            system("pause");
            cout << endl;  
            return false;
        }else{
            string nombre, aux; 
            int vida; 
            int cantidad_soldados; 
            archivo >> cantidad_soldados; 
            archivo.ignore();
            int cont = 0; 
            while(cont<cantidad_soldados){
                getline(archivo, aux);
                if(aux == "---"){
                    getline(archivo, nombre);  
                    archivo >> vida; 
                    //cout <<"nombre antes de meterlo en la lista " << nombre << endl ; 
                    //cout <<"nombre antes de meterlo en la lista " << vida << endl; 
                    cont++;
                    //cout << cont << endl; 
                    agregar_espec_soldados(-1, nombre, vida);
                    //cout << "aqui termins" <<(cabeza)->Nombre_soldado << endl ;
                }
            // convierte variables que son strings en numeros
            //int num_vida = stoi(vida); 
            }

        archivo.close(); // Cerramos archivo 
        //cout << "Los jugadores se han cargado con exito !!" << endl; 
        
        return true; 
        }
    }

    //_______________________________________________Funciones retornar datos____________________________________________________

    string retornar_nombre_soldados(soldado *& cabeza, int posicion) {
        if (posicion < 0 || posicion >= size) {
            cout << "Error: Posición fuera de rango." << endl;
            return ""; // O cualquier valor que indique un error
        }

        soldado *aux1 = cabeza;
        int avanze = size - posicion;

        for (int i = 0; i < avanze; i++) {
            if (aux1 == nullptr) {
                cout << "Error: Nodo no encontrado." << endl;
                return ""; // O cualquier valor que indique un error
            }
            aux1 = aux1->next;
        }

        return aux1->Nombre_soldado;
    }

    int retornar_vida_soldados(soldado *& cabeza, int posicion) {
        if (posicion < 0 || posicion >= size) {
            cout << "Error: Posición fuera de rango." << endl;
            return -1; // O cualquier valor que indique un error
        }

        soldado *aux1 = cabeza;
        int avanze = size - posicion - 1;

        for (int i = 0; i < avanze; i++) {
            if (aux1 == nullptr) {
                cout << "Error: Nodo no encontrado." << endl;
                return -1; // O cualquier valor que indique un error
            }
            aux1 = aux1->next;
        }

    return aux1->vida;
}

void eliminar_soldado(Bitacora* bitacora, int position) {
        if (position >= size || position < 0) {
            cout << "Error: Posición inválida." << endl;
            return;
        }

        soldado* current = cabeza;
        soldado* prev = nullptr;

        int i = 0;
        while (i < position) {
            prev = current;
            current = current->next;
            i++;
        }

        if (prev == nullptr) {
            cabeza = current->next;
        } else {
            prev->next = current->next;
        }

        registrarSoldadoCaido(bitacora, current->Nombre_soldado);
        delete current;
        size--;
    }

    void agregar_soldado(Bitacora* bitacora, const string& nombre, int vida) {
        soldado* nuevo = new soldado{nombre, vida, cabeza};
        cabeza = nuevo;
        size++;
        registrarEvento(bitacora, "Soldado agregado: " + nombre);
    }

};
