#include <iostream>
#include <fstream>
#include <sstream>
#include "Colores.h"
using namespace std;

struct Soldados
{   

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
        cout  <<"Indique la cantidad de vida que tiene el jugador de la lista" << endl; 
        cin >> vida; 
        return vida; 
}

    string nombreSoldado(){
        string nombresoldado; 
        cout << "Indique el nombre del soldado que esta en la lista" << endl; 
        cin >>nombresoldado; 
        return nombresoldado;
    }

    void agregar_soldados_por_zmb(){
        lecturasoldados(cabeza);
    }

   void leerlistsoldado(soldado *lista){
        soldado *mover;
        int cont = 1; 
        while (!estavaciasoldado(lista)){
            mover = lista;
            cout <<"Lista de Jugadores: "<<endl;
            cout << "Soldado: " << cont << ")" << GREEN << "Nombre: "<<		mover->Nombre_soldado<< RESET << endl;
            cout <<"Vida: "<<mover->vida<<endl;
            cout << "" << endl; 
            mover = mover->next;
        }  
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

    }

    void eliminarlistpos(int position){
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



    private:

//_______________________________________________________Agregar Especifico_______________________________________________________

    void Agregar_Ultimo_especifico(string  nombre, int vida, soldado *& cabeza){
        soldado* nuevosoldado= new soldado;

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
        //leerlist(*soldado);
        return true; 
        }
    }
};
