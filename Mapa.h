#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>   
#include <algorithm>
#include <fstream>
#include <sstream>
#include "zombies.h"
#include  "Equipos.h"

using namespace std;

// Nombres de las estaciones 
vector<string> estaciones= {};

// Estructura para representar una arista
struct Arista {
    int destino; // Índice de la estación destino
    int peso;    // Peso (cantidad de zombies)
};

Arista *ady = NULL; 
// Estructura para representar el grafo
struct Grafo {
    int V; // Número de estaciones
    vector<Arista> *adj; // Lista de adyacencias
    zombies *listazombies;  

    // Constructor
    Grafo(vector<string> &estaciones) {
        this->V = estaciones.size();
        adj = new vector<Arista>[V];
    }

    Grafo *cabezaGrafos = NULL; 
    // Agregar una arista
    void agregarArista(int u, int v) {
        if (u < 0 || u >= V || v < 0 || v >= V) {
            cout << "Índice de estación no válido. Verifique los valores ingresados." << endl;
            return;
        }
        Arista nuevaArista = {v, rand() % 10 + 1}; // Peso aleatorio entre 1 y 10 (cantidad de zombies)
        adj[u].push_back(nuevaArista);
        cout << "Arista agregada de " << estaciones[u] << " a " << estaciones[v] << "." << endl;
    }

    // Eliminar una arista
    void eliminarArista(int u, int v) {
        if (u < 0 || u >= V) {
            cout << "Índice de estación no válido.\n";
            return;
        }
        auto &aristas = adj[u];
        auto it = remove_if(aristas.begin(), aristas.end(), [v](const Arista &arista) {
            return arista.destino == v;
        });
        if (it != aristas.end()) {
            aristas.erase(it, aristas.end());
            cout << "Arista eliminada de " << estaciones[u] << " a " << estaciones[v] << "." << endl;
        } else {
            cout << "No se encontró la arista especificada." << endl;
        }
    }

    // Mostrar el grafo
    void mostrarGrafo() {
        for (int i = 0; i < V; i++) {
            cout << "Estación " << i + 1 << " (" << estaciones[i] << "): ";
            for (const auto &arista : adj[i]) {
                cout << "-> (Estación " << arista.destino + 1 << " - " << estaciones[arista.destino] << ", Zombies: " << arista.peso << ") ";
            }
            cout << endl;
        }
    }

    // Agregar una estación
    void agregarEstacion(string &nombre) {
        estaciones.push_back(nombre);
        vector<Arista> *nuevaAdj = new vector<Arista>[V + 1];
        for (int i = 0; i < V; i++) {
            nuevaAdj[i] = adj[i];
        }
        delete[] adj;
        adj = nuevaAdj;
        V++;
        cout << "Nueva estación '" << nombre << "' agregada."<< endl;
    }

    // Eliminar una estación
    void eliminarEstacion(int u) {
        if (u < 0 || u >= V) {
            cout << "Índice de estación no válido." << endl;
            return;
        }

        string nombreEliminado = estaciones[u];
        estaciones.erase(estaciones.begin() + u);

        // Actualizar la lista de adyacencias
        vector<Arista> *nuevaAdj = new vector<Arista>[V - 1];
        for (int i = 0, k = 0; i < V; i++) {
            if (i == u) continue;
            nuevaAdj[k++] = adj[i];
        }
        delete[] adj;
        adj = nuevaAdj;
        V--;

        // Eliminar referencias a la estación eliminada
        for (int i = 0; i < V; i++) {
            adj[i].erase(remove_if(adj[i].begin(), adj[i].end(), [u](Arista &arista) {
                return arista.destino == u;
            }), adj[i].end());

            for (auto &arista : adj[i]) {
                if (arista.destino > u) {
                    arista.destino--;
                }
            }
        }

        cout << "Estación '" << nombreEliminado << "' eliminada." << endl;
    }

    void agregar_mapa_por_zmb(zombies listazombies){
        lecturaMapa(cabezaGrafos, ady, listazombies);
    }

    bool lecturaMapa(Grafo *&listagrafos, Arista *&listaAdy, zombies listaZombies){ 
        ifstream archivo("Mapa.zmb", ios::in);
        //Grafo *grafo = *listagrafos; 
        if (!archivo) {
            cout << "Error al abrir el archivo." << endl;
            system("pause");
            cout << endl;  
            return false;
        }else{
            string nombreEstacion ,nombreZombie, numeroZombie, NodoAdyacencia, distancia ,aux;  
            int numeroAdy; 
            int cantidad_de_estaciones; 
            archivo >> cantidad_de_estaciones; 

            while(getline(archivo, aux)){
                stringstream token(aux);
                if(aux == "---"){
                    archivo >> numeroAdy;  
                    getline(token, nombreEstacion); 
                    agregarEstacion(nombreEstacion); 
                    if(aux == "-"){
                        getline(token, numeroZombie, '|') ; 
                        getline(token, nombreZombie);
                        int num_zom = stoi(numeroZombie); 
                        listagrafos->listazombies->replicador_de_zombies(nombreZombie, num_zom, listaZombies); 
                        if(aux == "--"){
                            getline(token, NodoAdyacencia, ':') ; 
                            getline(token, distancia,  '|') ; 
                            int nodo_ady = stoi(NodoAdyacencia); 
                            int dist = stoi(distancia); 
                            agregarArista(nodo_ady, dist); 
                        }
                    }
                }
            }

        archivo.close(); // Cerramos archivo 
        cout << " Mapa cargado con exito !!" << endl; 
        
        return true; 
        }
    }

    

};

void inicializarEstacionEquipoAleatoria(vector<string> &estaciones, string &estacionInicial) {
    if (estaciones.empty()) {
        cout << "No hay estaciones disponibles para seleccionar." << endl;
        return;
    }

    srand(static_cast<unsigned>(time(nullptr))); // Inicializar generador aleatorio
    int indiceAleatorio = rand() % estaciones.size(); // Seleccionar índice aleatorio
    estacionInicial = estaciones[indiceAleatorio];

    cout << "La estación inicial asignada al equipo es: " << estacionInicial << endl;
}

void inicializarEstacionesEquipos(vector<string>& estaciones, Equipos* listaEquipos) {
    if (listaVaciaEquipos(listaEquipos)) {
        cout << "No hay equipos para asignar estaciones." << endl;
        return;
    }

    srand(static_cast<unsigned>(time(nullptr))); // Inicializar generador aleatorio
    vector<bool> estacionesOcupadas(estaciones.size(), false);

    Equipos* actual = listaEquipos;
    while (actual != nullptr) {
        int indice;
        do {
            indice = rand() % estaciones.size();
        } while (estacionesOcupadas[indice]);

        estacionesOcupadas[indice] = true;
        cout << "Estación inicial para " << actual->nombre << ": " << estaciones[indice] << endl;

        actual = actual->prox;
    }
}