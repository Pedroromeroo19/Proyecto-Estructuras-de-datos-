#include <iostream>
#include "soldados.h"

using namespace std;

struct Equipos{
    string nombre; 
    int numero_de_soldados; 
    Soldados *listaJugadores; 
    Equipos *prox; 
}; 


//___________________________________________funcion para saber si esta vacia______________________________________________
bool listaVaciaEquipos(Equipos *equipo){
    return equipo == NULL;
}

Equipos *CrearEquipo(string nombre){
    Equipos *nuevo = new Equipos; 
    nuevo->nombre = nombre; 
    nuevo->numero_de_soldados = 0; 
    nuevo->listaJugadores = nullptr; 
    nuevo->prox = nullptr;
    return nuevo; 
}

Equipos *Buscar_Equipo(Equipos *lista, string nombre){
    Equipos *mover = lista; 
    bool encontrado = false; 
    if(listaVaciaEquipos(lista)){
        cout << "No hay equipos para llevar la cura!! Crea un equipo" << endl ; 
        return nullptr; 
    }else{
        while(mover != nullptr && encontrado == false){
            if(mover->nombre == nombre){
                encontrado = true; 
            }else{
                mover = mover->prox;
            }
        }
        return mover; 
    }
}

void agregarUltimoEquipo(Equipos **equipo_listas, string nombre_equipo){
    int cant = 2; 
    int cont = 0; 
    Equipos *NuevoEquipo = CrearEquipo(nombre_equipo); 
    while (cont < cant){
        if(listaVaciaEquipos(*equipo_listas)){
            (*equipo_listas) = NuevoEquipo; 
        }else{
            Equipos *actual = (*equipo_listas); 
            while(actual->prox != nullptr){
                actual = actual->prox; 
            }
            actual->prox =  NuevoEquipo; 
        }
    }

}

void EliminarEquipo(Equipos **lista, string nombre){
    Equipos *actual = (*lista); 
    Equipos *anterior = nullptr; 
    Soldados::soldado* eliminado = nullptr;

    if(listaVaciaEquipos(*lista)){
        cout << "No hay equipos formados! Crea un equipo para poder eliminarlo. " << endl; 
    }else{
        while(actual != nullptr && actual->nombre !=nombre){
            anterior = actual; 
            actual = actual->prox; 
        }
        if(actual==nullptr){
            cout << "No existe un equipo con ese nombre!" << endl; 
        }else{
            eliminado = actual->listaJugadores; 
            if(actual == (*lista)){
                (*lista) = (*lista)->prox;
            }else{
                anterior->prox = actual->prox; 
                Soldados::soldado *aux = eliminado;
                if(eliminado != nullptr){
                    while(aux != nullptr){
                        eliminado = eliminado->next; 
                        delete aux; 
                        aux = eliminado; 
                    }
                }
            }
        }
    }
    delete actual; 
}

void AgregarSoldadoEquipoPorNombre(Equipos **lista, string nombre, Soldados lista_jugadores){
    Equipos *actual = *lista; 
    actual = Buscar_Equipo(*lista, nombre);
    
    
    if(listaVaciaEquipos(actual)){
        cout << "Equipo no encontrado. Intenta con otro nombre!" << endl; 
    }else{
        int cant;
        cout << "Indique la cantidad de soldados que desea agregar: " << endl;
        cin >> cant; 
        for(int i = 0; i<cant; i++){
            string nombre_soldado; 

            lista_jugadores.agregar_soldados_por_zmb();
            lista_jugadores.agregar_espec_soldados(-1,lista_jugadores.nombreSoldado(), lista_jugadores.vida());
        }
        actual->numero_de_soldados = cant; 
    }
}

void asignarEstacionLlegadaAleatoria(vector<string>& estaciones, Equipos* listaEquipos) {
    if (listaVaciaEquipos(listaEquipos)) {
        cout << "No hay equipos disponibles para asignar estación de llegada." << endl;
        return;
    }

    srand(static_cast<unsigned>(time(nullptr))); // Inicializar generador aleatorio
    int indiceLlegada = rand() % estaciones.size();
    string estacionLlegada = estaciones[indiceLlegada];

    cout << "Estación de llegada asignada aleatoriamente: " << estacionLlegada << endl;

    Equipos* actual = listaEquipos;
    while (actual != nullptr) {
        cout << "Equipo " << actual->nombre << " tiene como estación de llegada: " << estacionLlegada << endl;
        actual = actual->prox;
    }
}
