#include <iostream>
#include "Accesorios.h"
using namespace std;

struct listamochilas
{  

    mochila* cabe = NULL; // al declarar esto estas declarando una lista de accesorios interna dentro de cada nodo
    int tama = 0;
    
    //__________________________________________________Agregar______________________________________________
    void agregar_espec_lista_mochilas(int posicion, string  nombre){
        if (posicion>tama){
            cout << "Error : Se puso una posicion mayor al tamaño de la lista" << endl;
            return;
        }
        if ((posicion == -1)or(posicion==tama)){ //caso agregar ultimo
            Agregar_Ultimo_especifico(nombre, cabe);
            tama = tama + 1 ;
        }
        if (posicion == 0){ //caso agregar primero
            Agregar_Al_final_especifico(nombre,cabe);
            tama = tama + 1 ;
        }
        if (posicion>0 && posicion<tama){ //caso agregar en el medio
            Agregar_Medio_especifico(nombre, posicion , cabe, tama);
            tama = tama + 1 ;
        }
    }

    //__________________________________________________Agregar Accesorio en Mochila______________________________________________
    void rellenar_mochila(int posicion_en_mochila, string  nombre, string tipo_acc, int valor, int usos){
        mochila* aux1 = cabe->siguiente_mochila;
        mochila* aux2 = cabe;
        int avanze = tama - posicion_en_mochila;

        for (int i=0;i<avanze;i++){
                aux1= aux1->siguiente_mochila;
                aux2= aux2->siguiente_mochila;
            }

        if( (aux2->size + 1) > 3){
            cout << "Error: no se puede tener mas de 3 accesorios por mochila " << endl;
            return;
        }
        else{
            aux2->agregar_espec_accesorio(-1, nombre, tipo_acc, valor, usos);
        }
    }


    //__________________________________________________Mostrar______________________________________________
    void leer_mochilas(){
        mochila* aux1 = cabe;
        while (aux1 != NULL){
            aux1->leer_lista_accesorios();
            cout << endl;
            aux1= aux1->siguiente_mochila;
        }
    }

    void leer_lista_mochilas(){
        mochila* aux1 = cabe;
        while (aux1 != NULL){
            cout << "Caracteristicas de la mochila:"<< endl;
            cout << "Nombre dueño:" << aux1->nombredueno << endl;
        }
    }

    void leer_lista_mochilas_con_accesorios(){
        mochila* aux1 = cabe;
        int valor_pos = tama;
        while (aux1 != NULL){
            cout << "Posicion: "<< valor_pos << endl;
            valor_pos=valor_pos-1;
            cout << "Caracteristicas de la mochila:"<< endl;
            cout << "Nombre dueño:" << aux1->nombredueno << endl;
            cout << endl;
            aux1->leer_lista_accesorios();
            cout << endl;
            aux1= aux1->siguiente_mochila;
        }
    }


    //__________________________________________________Modificar______________________________________________
    void modificar_lista_mochilas(int posicion, string  nombre, string tipo_acc, int valor, int usos){       
        if (posicion>tama){
            cout << "Error : Se puso una posicion mayor al tamaño de la lista" << endl;
            return;
        }
        if (nombre != ""){
            modificar_nombre(nombre,posicion,cabe, tama);
        }
    }

    //__________________________________________________Modificar Accesorio en mochila______________________________________________
    void modificar_mochila(int posicion_lista_mochila,int posicion_mochila, string  nombre, string tipo_acc, int valor, int usos){
        mochila* aux1 = cabe->siguiente_mochila;
        mochila* aux2 = cabe;
        int avanze = tama - posicion_lista_mochila;

        for (int i=0;i<avanze;i++){
                aux1= aux1->siguiente_mochila;
                aux2= aux2->siguiente_mochila;
            }

        if (nombre != ""){
            aux2->modificar_accesorio(posicion_mochila, nombre, tipo_acc, valor, usos);
        }
    }

    //__________________________________________________Eliminar______________________________________________
    void eliminar_mochila_pos(int position){
        if (position>tama){
            cout << "Error : Se puso una posicion mayor al tamaño de la lista" << endl;
            return;
        }
        if ((position == -1)or(position==tama)){ //caso eliminar ultimo
            Eliminar_Ultimo(cabe);
            tama = tama - 1 ;
        }
        if (position == 0){ //caso eliminar primero
            eliminar_al_final(cabe);
            tama = tama - 1 ;
        }
        if (position>0 && position<tama){ //caso agregar en el medio
            eliminar_medio(position, cabe, tama);
            tama = tama - 1 ;
        }
    }

    //__________________________________________________Eliminar Accesorio en mochila______________________________________________
    void eliminar_accesorio_pos(int posicion_en_mochila, int posicion_en_accesorio){
        mochila* aux1 = cabe->siguiente_mochila;
        mochila* aux2 = cabe;
        int avanze = tama - posicion_en_mochila;

        for (int i=0;i<avanze;i++){
                aux1= aux1->siguiente_mochila;
                aux2= aux2->siguiente_mochila;
            }

        aux2->eliminar_accesorio_pos(posicion_en_accesorio);
    }

    void eliminar_lista_mochila(mochila*& cabe){
        if(!estavacia(cabe)){

            mochila *aux1 = cabe;
            mochila *aux2;

            while (cabe != NULL)
            {
                aux2 = aux1;
                aux1 = aux1->siguiente_mochila;
                delete aux2;
            }
        
        }
    }


    private:

//_______________________________________________________Agregar Especifico_______________________________________________________

    void Agregar_Ultimo_especifico(string nombre, mochila *& cabe){
        mochila* nodo_mochila= new mochila();

        nodo_mochila->nombredueno= nombre;

        if (estavacia(cabe)){
            nodo_mochila->siguiente_mochila= NULL;
        }

        if (!estavacia(cabe)){
            nodo_mochila->siguiente_mochila= cabe;
        }

        cabe = nodo_mochila;
    }

    void Agregar_Al_final_especifico(string nombre, mochila *& cabe){
        mochila* nodo_mochila = new mochila();

        nodo_mochila->nombredueno= nombre;

        mochila *aux1= cabe->siguiente_mochila;
        mochila *aux2= cabe;
        while (aux1 != NULL){
            aux1= aux1->siguiente_mochila;
            aux2= aux2->siguiente_mochila;
            if (aux1 == NULL){
                nodo_mochila->siguiente_mochila= aux1;
                aux2->siguiente_mochila=nodo_mochila;
            }
        }
    }

    void Agregar_Medio_especifico(string nombre,int posicion, mochila *& cabe,int tamano){
        mochila* nodo_mochila = new mochila();

        nodo_mochila->nombredueno= nombre;

        mochila *aux1= cabe->siguiente_mochila;
        mochila *aux2= cabe;
        int avanze = tamano - posicion;
        for (int i=0;i<avanze;i++){
            aux1= aux1->siguiente_mochila;
            aux2= aux2->siguiente_mochila;
        }
        nodo_mochila->siguiente_mochila = aux1;
        aux2->siguiente_mochila= nodo_mochila;
    }



//_______________________________________________________funciones eliminar________________________________________________
    void Eliminar_Ultimo(mochila *& cabe){
        mochila *aux1 = cabe->siguiente_mochila;
        mochila *aux2 = cabe;
        cabe= aux1;
        delete aux2;
    }

    void eliminar_medio(int posicion, mochila *& cabe, int tamano){
        mochila *aux1 = cabe->siguiente_mochila;
        mochila *aux2 = cabe;
        int avanze= tamano - posicion - 1;
        for (int i=0;i<avanze;i++){
            aux1= aux1->siguiente_mochila;
            aux2= aux2->siguiente_mochila;
        }
        aux2->siguiente_mochila = aux1->siguiente_mochila;
        delete aux1;
    }

    void eliminar_al_final(mochila *& cabe){
        mochila *aux1= cabe->siguiente_mochila;
        mochila *aux2= cabe;
        while (aux1 != nullptr){
            aux1 = aux1->siguiente_mochila;
            aux2 = aux2->siguiente_mochila;
            if (aux1->siguiente_mochila == nullptr){
                aux2->siguiente_mochila = nullptr;
                delete aux1;
                break;
            }
        }
    }


//___________________________________________________funciones modificar lista___________________________________________

    void modificar_nombre(string  nombre,int posicion, mochila *& cabe, int tamano){
        mochila *aux1 = cabe;
        int avanze= tamano - posicion;
        for (int i=0;i<avanze;i++){
            aux1= aux1->siguiente_mochila;
        }
        aux1->nombredueno = nombre;
    }

//___________________________________________funcion para saber si esta vacia______________________________________________
    bool estavacia(mochila *& p){
        return p == nullptr;
    }
};
