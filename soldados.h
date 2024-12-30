#include <iostream>
#include <fstream>
#include <sstream>
#include "Colores.h"
using namespace std;

    struct soldado{
        string Nombre_soldado; 
        int vida;
        soldado *next;
    };

    soldado* cabeza = NULL;
    
    //___________________________________________funcion para saber si esta vacia______________________________________________
    bool estavaciasoldado(soldado *& p){
        return p == nullptr;
    }


    //_______________________________________________________Agregar Especifico_______________________________________________________

    void Agregar_Ultimo_especifico_Soldado(string  nombre, int vida, soldado ** cabeza){
        soldado* nuevosoldado= new soldado;

        //Declaracion de datos
        nuevosoldado->Nombre_soldado= nombre;
        nuevosoldado->vida = vida;
        nuevosoldado->next = nullptr;

        if (estavaciasoldado(*cabeza)){
            *cabeza = nuevosoldado;
        }
        else{
            soldado *aux = *cabeza; 
            while(aux->next != nullptr){
                 aux = aux->next; 
            }
            aux->next = nuevosoldado;
        }
    } 


    void Agregar_Al_final_especifico_Soldado(string  nombre, int vida, soldado *& cabeza){
        soldado* nuevosoldado = new soldado();

        //Declaracion de datos
        nuevosoldado->Nombre_soldado = nombre;
        nuevosoldado->vida = vida;
        nuevosoldado->next = nullptr; 

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

    void Agregar_Medio_especifico_Soldado(string  nombre, int vida ,int posicion, soldado *& cabeza,int tamano){
        soldado* nuevosoldado = new soldado;

        //Declaracion de datos
        nuevosoldado->Nombre_soldado = nombre;
        nuevosoldado->vida = vida;
        nuevosoldado->next = nullptr; 

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


    void leerlist(soldado *lista){
        soldado *mover;

        while (!estavaciasoldado(lista)){
            mover = lista;
            cout <<"Lista de Jugadores: "<<endl;
            cout << GREEN << "Name: "<<		mover->Nombre_soldado<< RESET << endl;
            cout <<"Vida: "<<mover->vida<<endl;
            cout << "" << endl; 
            mover = mover->next;
        }  
    }
//__________________________________________Funcion para leer soldado______________________________________________________//
    bool lecturasoldados(soldado **soldado){ 
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
                    cout <<"nombre antes de meterlo en la lista " << nombre << endl ; 
                    cout <<"nombre antes de meterlo en la lista " << vida << endl; 
                    cont++;
                    cout << cont << endl; 
                    Agregar_Ultimo_especifico_Soldado(nombre, vida, &*soldado);
                    cout << "aqui termins" <<(*soldado)->Nombre_soldado << endl ;
                }
            // convierte variables que son strings en numeros
            //int num_vida = stoi(vida); 
            }

        archivo.close(); // Cerramos archivo 
        cout << "Los jugadores se han cargado con exito !!" << endl; 
        leerlist(*soldado); 
        return true; 
        }
    }


//_______________________________________________________funciones eliminar________________________________________________
    void Eliminar_Ultimo_soldado(soldado *& cabeza){
        soldado *aux1 = cabeza->next;
        soldado *aux2 = cabeza;
        cabeza= aux1;
        delete aux2;
    }

    void eliminar_medio_soldado(int posicion, soldado *& cabeza, int tamano){
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

    void eliminar_al_final_soldado(soldado *& cabeza){
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

    void agregarespec(int posicion, string  nombre, int vida){
        int size = 0;

        if (posicion>size){
            cout << "Error : Se puso una posicion mayor al tamaño de la lista" << endl;
            return;
        }
        if ((posicion == -1)or(posicion==size)){ //caso agregar ultimo
            Agregar_Ultimo_especifico_Soldado(nombre, vida,  &cabeza);
            size = size + 1 ;
        }
        if (posicion == 0){ //caso agregar primero
            Agregar_Al_final_especifico_Soldado(nombre, vida , cabeza);
            size = size + 1 ;
        }
        if (posicion>0 && posicion<size){ //caso agregar en el medio
            Agregar_Medio_especifico_Soldado(nombre,  vida, posicion , cabeza, size);
            size = size + 1 ;
        }
    }
    
    

    void modificarlist(int posicion, string  nombre, int vida){        
        int size = 0;

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

    }

    void eliminarlistpos(int position){
        int size = 0;

        if (position>size){
            cout << "Error : Se puso una posicion mayor al tamaño de la lista" << endl;
            return;
        }
        if ((position == -1)or(position==size)){ //caso eliminar ultimo
            Eliminar_Ultimo_soldado(cabeza);
            size = size - 1 ;
        }
        if (position == 0){ //caso eliminar primero
            eliminar_al_final_soldado(cabeza);
            size = size - 1 ;
        }
        if (position>0 && position<size){ //caso agregar en el medio
            eliminar_medio_soldado(position, cabeza, size);
            size = size - 1 ;
        }
    }

    void eliminar_lista_soldado(soldado *& cabeza){
    if(!estavaciasoldado(cabeza)){

        soldado *aux1 = cabeza;
        soldado *aux2;

        while (cabeza != NULL)
        {
            aux2 = aux1;
            aux1 = aux1->next;
            delete aux2;
        }
        
    }

    
}
