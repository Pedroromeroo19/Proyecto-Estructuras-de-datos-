#include <iostream>
using namespace std; 

struct Evento {
    string descripcion;
    Evento *siguiente;
};

struct Bitacora {
    int soldadosCaidos;
    int zombiesEliminados;
    int accGastados;
    Evento *eventos;
};

// Inicializar la bitácora

Bitacora *CrearBitacora(){
    Bitacora *nueva = new Bitacora; 
    nueva->soldadosCaidos= 0; 
    nueva->zombiesEliminados = 0; 
    nueva->accGastados = 0; 
    nueva->eventos = nullptr; 
    return nueva; 
};

void registrarEvento(Bitacora *bitacora, string descripcion){
    Evento* nuevoEvento = new Evento;
    nuevoEvento->descripcion = descripcion;
    nuevoEvento->siguiente = bitacora->eventos;
    bitacora->eventos = nuevoEvento;
}

void registrarSoldadoCaido(Bitacora* bitacora, string nombreSoldado) {
    bitacora->soldadosCaidos++;
    registrarEvento(bitacora, "Soldado caído: " + nombreSoldado);
}

// Registrar zombie eliminado
void registrarZombieEliminado(Bitacora* bitacora, string tipoZombie) {
    bitacora->zombiesEliminados++;
    registrarEvento(bitacora, "Zombie eliminado: " + tipoZombie);
}

// Registrar arma gastada
void registrarArmaGastada(Bitacora* bitacora, string nombreArma) {
    bitacora->accGastados++;
    registrarEvento(bitacora, "Arma gastada: " + nombreArma);
}

void mostrarResumen(Bitacora* bitacora) {
    cout << "--- Resumen de la partida ---" << endl ;
    cout << "Soldados caídos: " << bitacora->soldadosCaidos << endl;
    cout << "Zombies eliminados: " << bitacora->zombiesEliminados << endl;
    cout << "Accesorios gastados: " << bitacora->accGastados << endl;
}

void mostrarEventos(Bitacora* bitacora) {
    cout << "--- Eventos registrados ---" << endl;
    Evento* actual = bitacora->eventos;
    while (actual != nullptr) {
        cout << actual->descripcion << endl;
        actual = actual->siguiente;
    }
}

void liberarBitacora(Bitacora* bitacora) {
    Evento* actual = bitacora->eventos;
    Evento* siguiente;
    while (actual != nullptr) {
        siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    delete bitacora;
}
