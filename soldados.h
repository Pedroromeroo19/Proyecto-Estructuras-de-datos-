#include <iostream>
#include <fstream>
#include <sstream>
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

    void Agregar_Ultimo_especifico(string  nombre, int vida, soldado *& cabeza){
        soldado* nuevosoldado= new soldado;

        //Declaracion de datos
        nuevosoldado->Nombre_soldado= nombre;
        nuevosoldado->vida = vida;
        nuevosoldado->next = nullptr;

        if (estavaciasoldado(cabeza)){
            nuevosoldado->next= NULL;
        }
        if (!estavaciasoldado(cabeza)){
            nuevosoldado ->next= cabeza;
        }

        cabeza = nuevosoldado;
    } 


    void Agregar_Al_final_especifico(string  nombre, int vida, soldado *& cabeza){
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

    void Agregar_Medio_especifico(string  nombre, int vida ,int posicion, soldado *& cabeza,int tamano){
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

//__________________________________________Funcion para leer soldado______________________________________________________//
// no termina de funcionar revisar ********
    bool lecturasoldados(soldado **soldado){ 
        ifstream archivo("Soldado.zmb", ios::in);
        if (!archivo) {
            cout << "Error al abrir el archivo." << endl;
            system("pause");
            cout << endl;  
            return false;
        }else{
            string nombre, vida, aux; 
            int cantidad_soldados; 
            int cont = 0; 
            getline(archivo, aux);
            istringstream(aux)>>cantidad_soldados; 
            while(cont<cantidad_soldados){
                if(aux == "---");
                else{
                    getline(archivo, aux);
                    getline(archivo, nombre); 
                    getline(archivo, vida);
                    }
                // convierte variables que son strings en numeros
                int num_vida = stoi(vida); 
                Agregar_Ultimo_especifico(nombre, num_vida, *soldado); 
                cont++;
            }

        archivo.close(); // Cerramos archivo 
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
    
    void leerlist(){
        int size = 0;

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