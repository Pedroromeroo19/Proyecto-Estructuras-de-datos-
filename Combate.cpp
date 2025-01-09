#include "soldados_seguro.h"
#include "zombies.h"
#include "mochila.h"
#include <iostream>
#include <cmath>
using namespace std;

bool comparacion_accesorios_con_cantidad_de_soldados(mochila & accesorios, Soldados & equipo) {
    if (accesorios.size < equipo.size) {
        cout << "No hay suficientes accesorios para todos los soldados." << endl;
        return false;
    }
    return true;
}

mochila administrar_accesorios(mochila & accesorios, Soldados & equipo) {
    cout << "Accesorios a escoger por jugador:" << endl;
    accesorios.leer_lista_accesorios();
    cout << "Elija un accesorio para cada soldado:" << endl;

    mochila accesorios_en_uso;

    for (int i = 1; i <= equipo.size; i++) {
        string nombre_soldado = equipo.retornar_nombre_soldado(i);
        int nombreAccesorio;
        cout << "Indique el accesorio para " << nombre_soldado << " usando su numero: ";
        cin >> nombreAccesorio;
        accesorios_en_uso.agregar_espec_accesorio(-1, accesorios.retornar_nombre_accesorio(i), accesorios.retornar_tipo_accesorio(i), accesorios.retornar_danno_accesorio(i), accesorios.retornar_usos_accesorio(i));
    }

    return accesorios_en_uso;
}

void ataque_soldado(Soldados & equipo, zombies & hordaZombies, mochila & accesorios) {
    cout << "Los soldados atacan a los zombies:" << endl;
    cout << endl;

    for (int i = 1; i <= equipo.size; i++) {
        cout << "El soldado " << equipo.retornar_nombre_soldado(i) << " ataca al zombie " << hordaZombies.retornar_nombre_zombie(i) << " con el accesorio: " << accesorios.retornar_nombre_accesorio(i) << endl;

        if (accesorios.retornar_tipo_accesorio(i) == "Ataque") {
            int danno_soldado = accesorios.retornar_danno_accesorio(i);
            int vida_Zombie_nueva = hordaZombies.retornar_vida_zombie(i) - danno_soldado;
            hordaZombies.modificar_list_zombie(i, "", vida_Zombie_nueva, 0);
        }

        if (accesorios.retornar_tipo_accesorio(i) == "Supervivencia" || accesorios.retornar_tipo_accesorio(i) == "Defensa") {
            int vida_soldado_nueva = equipo.retornar_vida_soldado(i) + accesorios.retornar_danno_accesorio(i);
            equipo.modificar_list_soldado(i, "", vida_soldado_nueva);
        }

        if (hordaZombies.retornar_vida_zombie(i) <= 0) {
            hordaZombies.eliminar_zombie(i);
            i--; // Ajustar el índice después de eliminar un zombie
        }

        if (equipo.retornar_vida_soldado(i) <= 0) {
            equipo.eliminar_soldado(i);
            i--; // Ajustar el índice después de eliminar un soldado
        }

        if (hordaZombies.size == 0 || equipo.size == 0) {
            break;
        }
    }

    accesorios.actualizacion_de_usos();
    cout << endl;
}

void ataque_zombie(Soldados & equipo, zombies & hordaZombies, mochila & accesorios) {
    cout << "Los zombies atacan a los soldados:" << endl;

    for (int i = 1; i <= hordaZombies.size; i++) {
        cout << "El zombie " << hordaZombies.retornar_nombre_zombie(i) << " ataca al soldado " << equipo.retornar_nombre_soldado(i) << endl;

        int danno_zombie = hordaZombies.retornar_dano_zombie(i);
        int vida_soldado_nueva = equipo.retornar_vida_soldado(i) - danno_zombie;
        equipo.modificar_list_soldado(i, "", vida_soldado_nueva);

        if (equipo.retornar_vida_soldado(i) <= 0) {
            equipo.eliminar_soldado(i);
            i--; // Ajustar el índice después de eliminar un soldado
        }

        if (hordaZombies.retornar_vida_zombie(i) <= 0) {
            hordaZombies.eliminar_zombie(i);
            i--; // Ajustar el índice después de eliminar un zombie
        }

        if (hordaZombies.size == 0 || equipo.size == 0) {
            break;
        }
    }

    cout << endl;
}

int mostrar_estado_actual(Soldados & equipo, zombies & hordaZombies) {
    cout << "Estado actual:" << endl;
    cout << " - Zombies restantes: " << hordaZombies.size << endl;
    cout << " - Soldados vivos:" << equipo.size << endl;
    cout << endl;
    cout << "Indique 1 o 2 para ver la situacion actual de los zombies o soldados respectivamente:" << endl;
    cout << "Indique 3 para continuar el combate" << endl;
    cout << "Indique 4 para terminar el combate " << endl;
    int opcion;

    switch (opcion)
    {
    case 1:{
        hordaZombies.leer_lista_zombies();
        break;
    }
    case 2:{
        equipo.leer_lista_soldados();
        break;
    }
    case 3:{
        break;
    }
    case 4:{
        return 5;
        break;
    }
    default:
        break;
    }


    equipo.leer_lista_soldados();
    cout << endl;
}

void combate(Soldados& equipo, zombies& hordaZombies, mochila & accesorios) {
    cout << "Comienza el combate!" << endl;
    cout << "Zombies en la horda:" << endl;
    cout << endl;
    hordaZombies.leer_lista_zombies();
    cout << "Soldados en el equipo:" << endl;
    cout << endl;
    equipo.leer_lista_soldados();
    cout << endl;
    mochila accesorios_en_uso = administrar_accesorios(accesorios, equipo);
    int terminar;

    cout << endl;

    while (equipo.size > 0 && hordaZombies.size > 0 && terminar != 5) {
        ataque_soldado(equipo, hordaZombies, accesorios);
        ataque_zombie(equipo, hordaZombies, accesorios);

        terminar = mostrar_estado_actual(equipo, hordaZombies);

        if (equipo.size == 0) {
            cout << "Los zombies han ganado el combate." << endl;
            break;
        }
        if (hordaZombies.size == 0) {
            cout << "Los soldados han ganado el combate." << endl;
            break;
        }
    }
}

int main() {
    Soldados equipo;
    equipo.agregar_espec_soldados(-1, "Soldado A", 100);
    equipo.agregar_espec_soldados(-1, "Soldado B", 100);
    equipo.agregar_espec_soldados(-1, "Soldado C", 100);

    zombies hordaZombies;
    hordaZombies.agregar_espec_zombies(-1, "Zombie A", 50, 10);
    hordaZombies.agregar_espec_zombies(-1, "Zombie B", 60, 15);
    hordaZombies.agregar_espec_zombies(-1, "Zombie C", 70, 20);

    mochila accesorios;
    accesorios.agregar_espec_accesorio(-1, "Accesorio A", "Ataque", 1000, 5);
    accesorios.agregar_espec_accesorio(-1, "Accesorio B", "Ataque", 2000, 10);
    accesorios.agregar_espec_accesorio(-1, "Accesorio C", "Ataque", 3000, 15);

    combate(equipo, hordaZombies, accesorios);

    return 0;
}