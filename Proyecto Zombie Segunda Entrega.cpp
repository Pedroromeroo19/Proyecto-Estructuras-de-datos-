#include <iostream>
#include <random>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <windows.h>
#include "Colores.h"

//Todo el manejo de zombies, soldado, accesorios , mapa, etc. 
#include "soldados.h"
#include "zombies.h"
#include "Accesorios.h"
#include "listamochila.h"
#include "Equipos.h"
#include "Bitacora.h"

using namespace std;

// Elaborado por: Pedro Romero, Naim Chelhot y Jhoselin Bello.                                  //

//                                       ESTRUCTURAS DE LOS DATOS                                                   // 


//____________________________________________ MENU _______________________________________//
void mostrarMenu(){
    cout<< RED << "Bienvenido a RUNNING DEAD " << RESET << endl;
    cout<< BG_LGREEN << "======== MENU =========" << RESET << endl;
    cout << "1. Iniciar partida" <<endl;
    cout << "2. Configuracion "<< endl; 
    cout << "3. Como jugar?" <<endl;
    cout << "4. Salir" <<endl;
    cout << "-----------------------------------------" << endl; 
}
 

//___________________________________________ Combate _________________________________________//
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

// ---------------------------------------------- MAIN ------------------------------------ //
int main(){
    //srand(time(0));
    // Zombie* lista_zombie = CrearTropaZombie();
    // recorridozombies(lista_zombie);
    // cout << endl;
    // cout << calculador(lista_zombie) << endl;

    //Declaracion lista soldados 
    Bitacora *bitacora;
    Soldados primerSoldado; 
    string equipo1; 
    string equipo2; 
    zombies lista_zombies;
    mochila lista_accesorios_principal; 
    Equipos *primerequipo; 
    listamochilas lista_mochilas;
    // Esto es una lista de accesorios que describe todo los accesorios en el juego y por funcionalidas 
    // para el manejo de la lista de mochilas se usa el nombre mochila

    team1.agregar_soldados_por_zmb();
    lista_zombies.agregar_zombies_por_zmb();
    lista_accesorios_principal.agregar_accesorios_por_zmb();
    
    string personajes;
    string accaux; 
    int opcion;


    do {
        mostrarMenu();
        cout<< "Selecciona una opcionque desee: ";
        cin>> opcion;

        switch(opcion){
            case 1:
            
            {

                cout<<""<<endl;
                cout<<"Era Londres del 2024..."<<endl;
                cout<<"Lo que comenzo como una serie de extranios sintomas en pequenias comunidades"<<endl;
                cout<<"a lo largo y ancho del pais. "<<endl;
                cout<<"Pronto se revelo como una pesadilla global, gracias a que patogenos modificados a "<<endl;
                cout<<"partir del covid-19 se habrian dispersado en la atmosfera"<<endl;
                cout<<""<<endl;

                //system("pause");

                cout<<"Ingrese el nombre del equipo 1:"<<endl;
                getline(cin,equipo1);
                cout<<""<<endl;
                agregarUltimoEquipo(&primerequipo,equipo1);

                cout<<"Ingrese el nombre del equipo 2:"<<endl;
                getline(cin,equipo2);
                cout<<""<<endl;
                agregarUltimoEquipo(&primerequipo, equipo2); 

                //system("pause");

                cout<<""<<endl;
                cout<<"Gracias a la Dra. Emily Carter, se desarrollo una cura"<<endl;
                cout<<"y eligio a los equipos militares " << YELLOW  << equipo1  << RESET << " y " << YELLOW << equipo2 << RESET <<endl;
                cout<<"para distribuirla a traves de una red de tuneles de metro... "<<endl;
                cout<<""<<endl;

                //system("pause");
                        
                cout<<""<<endl;
                cout<< equipo1 << "!! y" << equipo2 <<"!! confiamos en ustedes para llevar la cura hasta su lugar de destino. Buena suerte!!"<<endl;
                cout<<"Debe seleccionar con cuidado que soldados llevara a la disputa"<<endl;
                // colocar opcion de elegir soldados en la batalla

                cout << "Equipo " << equipo1 << "es hora de elegir los soldados que te acompaniaran en tu aventura" << endl; 
                AgregarSoldadoEquipoPorNombre(&primerequipo, equipo1, primerSoldado); 

                cout << "Equipo" << equipo2 << "es hora de elegir los soldados que te acompaniaran en esta aventura!" << endl; 
                AgregarSoldadoEquipoPorNombre(&primerequipo, equipo2, primerSoldado); 
                                      
             
                 //comenzar misiones, batalla etc 

 
                    break;
            }

            case 2:
            
            {

                int opcion_configuracion; 

                int opcionsoldados;

                int opcionzombies;

                int opcionmochila;

                int opcionaccesorios;

                string name;
                string weapon;


                cout<< RED << "Bienvenido a RUNNING DEAD [Demo] " << RESET << endl;
                cout<< BG_LGREEN << "======== ¿Que deseas configurar? =========" << RESET << endl;
                cout << "1. Manejo de Soldado " <<endl;
                cout << "2. Manejo de Zombie "<< endl; 
                cout << "3. Manejo de mochila" <<endl;
                cout << "4. Manejo de Accesorio" <<endl;
                cout << "5. Subir documentos con datos predeterminados"<< endl;
                cout << "6. Salir" <<endl;
                cout << "-----------------------------------------" << endl; 
                cin >> opcion_configuracion;


                switch(opcion_configuracion)
                
                {

                    case 1:
                    
                    {
                        cout<< BG_LGREEN << "======== ¿Que deseas configurar? =========" << RESET << endl;
                        cout << "1. Agregar Soldados " <<endl;
                        cout << "2. Mostrar Soldados "<< endl;
                        cout << "3. Modificar Soldados "<< endl;
                        cout << "4. Eliminar Soldados" <<endl;
                        cout << "5. Salir" <<endl;
                        cout << "-----------------------------------------" << endl;
                        cin >> opcionsoldados;

                        string nombre_soldado;
                        int vida_soldado;
                        int posicion_soldado;

                        switch (opcionsoldados)
                                
                            {
                                    case 1:
                                            
                                    {

                                        cout << "Ingrese el nombre del soldado o ponga salir para salir: ";
                                        cin >> nombre_soldado;
                                        cout << "Ingrese el arma del soldado o ponga 0 para salir o un numero menor a 0: ";
                                        cin >> vida_soldado;
                                        cout << "Ingrese la posicion que desea usar";
                                        cin >> posicion_soldado;

                                        if ( nombre_soldado == "salir")
                                        {
                                            break;
                                        }
                                        if ( vida_soldado <= 0)
                                        {
                                            break;
                                        }

                                        team1.agregar_espec_soldados(-1, nombre_soldado, vida_soldado);

                                        break;
                                            
                                    }

                                    case 2:
                                            
                                    {

                                        cout << "Mostrando soldados" << endl;
                                        team1.leer_lista_soldados();

                                        break;
                                                    
                                    }

                                    case 3:
                                            
                                    {

                                        int modificar_soldado;

                                        cout << "Para modificar soldado indique que desea modificar:" << endl;
                                        cout << "1. Modificar nombre " <<endl;
                                        cout << "2. Modificar vida"<< endl;
                                        cout << "3. Mostrar Soldados"<< endl;
                                        cout << "4. Salir " << endl;
                                        cin >> modificar_soldado;

                                        switch(modificar_soldado)
                                                    
                                            {

                                                case 1:
                                                    {

                                                    int posicion_soldado_modificado;
                                                    string nombre_soldado_modificado;
                                                    cout << "Indique que Soldado desea modificar por su numero de posicion" << endl;
                                                    cin >> posicion_soldado_modificado;
                                                    cout << "Indique el nombre que desea utilizar" << endl;
                                                    cin >> nombre_soldado_modificado;

                                                    team1.modificar_list_soldado(posicion_soldado_modificado,nombre_soldado_modificado, 0);
                                                    break;
                                                            
                                                    }
                                                case 2:
                                                    {
                                                    int posicion_soldado_modificado;
                                                    int vida_soldado_modificado;
                                                    cout << "Indique que Soldado desea modificar por su numero de posicion" << endl;
                                                    cin >> posicion_soldado_modificado;
                                                    cout << "Indique la vida que desea utilizar" << endl;
                                                    cin >> vida_soldado_modificado;

                                                    team1.modificar_list_soldado(posicion_soldado_modificado,"", vida_soldado_modificado);                                                               
                                                    break;
                                                    }
                    
                                            }
                                        break;
                                    }

                                    case 4:
                                            
                                    {
                                        int posicion_soldado;
                                        cout << "Eliminando soldados" << endl;
                                        cout << "Indique que Soldado desea eliminar por su numero de posicion:" << endl;
                                        cin >> posicion_soldado;
                                        team1.eliminarlistpos(posicion_soldado);

                                        break;
                                                    
                                    }
                                            
                                    case 5:
                                            
                                    {

                                        cout << "Saliendo al menú principal." << endl;
                                        break;
                                            
                                    }

                                    default:
                                            
                                    {

                                        cout << "Opción invalida. Intentalo de nuevo." << endl;
                                        break;
                                            
                                    }

                            }
                        break;
                                
                    }
                            
                    case 2:
                    
                    {
                        cout<< BG_LGREEN << "======== ¿Que deseas configurar? =========" << RESET << endl;
                        cout << "1. Agregar Zombies " <<endl;
                        cout << "2. Mostrar Zombies "<< endl;
                        cout << "3. Modificar Zombies "<< endl;
                        cout << "4. Eliminar Zombies" <<endl;
                        cout << "5. Salir" <<endl;
                        cout << "-----------------------------------------" << endl;
                        cin >> opcionzombies;

                        string nombre_zombie;
                        int fortaleza_zombie;
                        int danno_zombie;
                        int posicion_zombie;

                        switch (opcionzombies)
                        
                        {

                            case 1:
                                {
                                    cout << "Ingrese el nombre del zombie o ponga salir para salir: ";
                                    cin >> nombre_zombie;
                                    cout << "Ingrese el daño del zombie o ponga 0 para salir o un numero menor a 0: ";
                                    cin >> danno_zombie;
                                    cout << "Ingrese la fortaleza del zombie o ponga 0 para salir o un numero menor a 0: ";
                                    cin >> fortaleza_zombie;
                                    cout << "Ingrese la posicion que desea usar";
                                    cout << "siendo -1 para agregar de ultimo y el tamaño de la lista igual a " << lista_zombies.size;
                                    cin >> posicion_zombie;

                                    if ( nombre_zombie == "salir")
                                    {
                                        break;
                                    }

                                    if ( fortaleza_zombie <= 0)
                                    {
                                        break;
                                    }

                                    lista_zombies.agregar_espec_zombies(posicion_zombie, nombre_zombie, danno_zombie, fortaleza_zombie);

                                    break;
                                }

                            case 2:
                                {
                                    cout << "Mostrando zombies" << endl;
                                    lista_zombies.leer_lista_zombies();
                                    break;
                                }

                            case 3:

                                {
                                    int modificar_zombie;

                                    cout << "Para modificar zombie indique que desea modificar:" << endl;
                                    cout << "1. Modificar nombre " <<endl;
                                    cout << "2. Modificar fortaleza"<< endl;
                                    cout << "3. Modificar Daño"<< endl;
                                    cout << "4. Mostrar Zombies"<< endl;
                                    cout << "5. Salir " << endl;
                                    cin >> modificar_zombie;

                                    switch(modificar_zombie)
                                    {
                                        case 1:
                                            {
                                                int posicion_zombie_modificado;
                                                string nombre_zombie_modificado;
                                                cout << "Indique que Zombie desea modificar por su numero de posicion" << endl;
                                                cin >> posicion_zombie_modificado;
                                                cout << "Indique el nombre que desea utilizar" << endl;
                                                cin >> nombre_zombie_modificado;

                                                lista_zombies.modificar_list_zombie(posicion_zombie_modificado,nombre_zombie_modificado, 0, 0);
                                                break;
                                            }
                                        case 2:
                                            {
                                                int posicion_zombie_modificado;
                                                int fortaleza_zombie_modificado;
                                                cout << "Indique que Zombie desea modificar por su numero de posicion" << endl;
                                                cin >> posicion_zombie_modificado;
                                                cout << "Indique la" << RED << " fortaleza " << RESET << "que desea utilizar" << endl;

                                                lista_zombies.modificar_list_zombie(posicion_zombie_modificado,"", fortaleza_zombie_modificado, 0);
                                                break;
                                            }
                                        case 3:
                                            {
                                                int posicion_zombie_modificado;
                                                int danno_zombie_modificado;
                                                cout << "Indique que Zombie desea modificar por su numero de posicion" << endl;
                                                cin >> posicion_zombie_modificado;
                                                cout << "Indique el" << RED << " daño " << RESET << "que desea utilizar" << endl;

                                                lista_zombies.modificar_list_zombie(posicion_zombie_modificado,"", 0, danno_zombie_modificado);
                                                break;
                                            }
                                        case 4:
                                            {
                                                cout << "Mostrando zombies" << endl;
                                                lista_zombies.leer_lista_zombies();
                                                break;
                                            }
                                        case 5:
                                            {
                                                cout << "Saliendo al menú de configuracion" << endl;
                                                break;
                                            }
                                        default:
                                            {
                                                cout << "Opción invalida. Intentalo de nuevo." << endl;
                                                break;
                                            }
                                    }
                                    break;
                                }
                            case 4:
                                {
                                    int posicion_zombie;
                                    cout << "Eliminando zombies" << endl;
                                    cout << "Indique que Zombie desea eliminar por su numero de posicion:" << endl;
                                    cin >> posicion_zombie;
                                    lista_zombies.eliminarlistpos(posicion_zombie);

                                    break;
                                }
                            case 5:
                                {
                                        system("cls");
                                        cout << "Saliendo al menú principal." << endl;
                                        system("cls");
                                        break;
                                }
                            default:
                                {
                                        system("cls");                                
                                        cout << RED << "Opción invalida. Intentalo de nuevo." << RESET << endl;
                                        system("cls");
                                        break;
                                }
                        }
                        break;
                    }
                    case 3:
                    {
                        cout<< BG_LGREEN << "======== ¿Que deseas configurar? =========" << RESET << endl;
                        cout << "1. Agregar Mochila " <<endl;
                        cout << "2. Mostrar Mochila "<< endl;
                        cout << "3. Modificar Mochila "<< endl;
                        cout << "4. Eliminar Mochila" << endl;
                        cout << "-----------------------------------------" << endl;
                        cout << "5. Rellenar Mochila con Accesorios" << endl;
                        cout << "6. Mostrar Mochila con Accesorios" << endl;
                        cout << "7. Modificar Accesorios de Mochila"<< endl;
                        cout << "8. Eliminar Accesorios de Accesorios" << endl;
                        cout << "9. Salir" <<endl;
                        cout << "-----------------------------------------" << endl;
                        cin >> opcionmochila;

                        string nombre_mochila;

                        switch(opcionmochila)
                        {
                            case 1:
                            {
                                cout << "Ingrese el nombre de la mochila o ponga salir para salir: ";
                                cin >> nombre_mochila;

                                if ( nombre_mochila == "salir")
                                {
                                    break;
                                }

                                lista_mochilas.agregar_espec_lista_mochilas(-1, nombre_mochila);

                                break;
                            }
                            case 2:
                            {
                                cout << "Mostrando mochilas" << endl;
                                lista_mochilas.leer_lista_mochilas();
                                break;
                            }
                            case 3:
                            {
                                int modificar_mochila;

                                cout << "Para modificar mochila indique que desea modificar:" << endl;
                                cout << "1. Modificar nombre " <<endl;
                                cout << "2. Mostrar mochilas"<< endl;
                                cout << "3. Salir " << endl;
                                cin >> modificar_mochila;

                                switch(modificar_mochila)
                                {
                                    case 1:
                                    {
                                        int posicion_mochila_modificado;
                                        string nombre_mochila_modificado;
                                        cout << "Indique que Mochila desea modificar por su numero de posicion" << endl;
                                        cin >> posicion_mochila_modificado;
                                        cout << "Indique el nombre que desea utilizar" << endl;
                                        cin >> nombre_mochila_modificado;

                                        lista_mochilas.modificar_lista_mochilas(posicion_mochila_modificado,nombre_mochila_modificado, "", 0, 0);
                                        break;
                                    }
                                    case 2:
                                    {
                                        cout << "Mostrando mochilas" << endl;
                                        lista_mochilas.leer_mochilas();
                                        break;
                                    }
                                    case 3:
                                    {
                                        cout << "Saliendo al menú de configuracion" << endl;
                                        break;
                                    }
                                }
                                break;
                            }
                            case 4:
                            {
                                int posicion_mochila;
                                cout << "Eliminando mochilas" << endl;
                                cout << "Indique que Mochila desea eliminar por su numero de posicion:" << endl;
                                cin >> posicion_mochila;
                                lista_mochilas.eliminar_mochila_pos(posicion_mochila);

                                break;
                            }
                            case 5:
                            {
                                int posicion_mochila;
                                cout << "Rellenando mochilas con accesorios" << endl;
                                cout << "Indique que Mochila desea rellenar por su numero de posicion:" << endl;
                                cin >> posicion_mochila;

                                string nombre_accesorio;
                                string tipo_accesorio;
                                int usos_accesorio;
                                int valor_accesorio;

                                cout << "Ingrese el nombre del accesorio o ponga salir para salir: ";
                                cin >> nombre_accesorio;
                                cout << "Ingrese el tipo del accesorio o ponga salir para salir: ";
                                cin >> tipo_accesorio;
                                cout << "Ingrese los usos del accesorio o ponga 0 para salir o un numero menor a 0: ";
                                cin >> usos_accesorio;
                                cout << "Ingrese el valor del accesorio o ponga 0 para salir o un numero menor a 0: ";
                                cin >> valor_accesorio;

                                if ( nombre_accesorio == "salir")
                                {
                                    break;
                                }

                                if ( tipo_accesorio == "salir")
                                {
                                    break;
                                }

                                if ( usos_accesorio <= 0)
                                {
                                    break;
                                }

                                if ( valor_accesorio <= 0)
                                {
                                    break;
                                }

                                lista_mochilas.rellenar_mochila(posicion_mochila, nombre_accesorio, tipo_accesorio, usos_accesorio, valor_accesorio);
                            }
                            case 6:
                            {
                                cout << "Mostrando mochilas con accesorios:" << endl;
                                lista_mochilas.leer_lista_mochilas_con_accesorios();
                                break;
                            }
                            case 7:
                            {
                                int modificar_accesorio_mochila;
                                int posicion_mochila_modificar;
                                int posicion_accesorio_modificar;

                                cout << "Indique que Mochila desea modificar por su numero de posicion" << endl;
                                cin >> posicion_mochila_modificar;
                                cout << "Indique que Accesorio desea modificar por su numero de posicion" << endl;
                                cin >> posicion_accesorio_modificar;

                                int modificar_accesorio;

                                cout << "Para modificar accesorio indique que desea modificar:" << endl;
                                cout << "1. Modificar nombre " <<endl;
                                cout << "2. Modificar tipo de accesorio"<< endl;
                                cout << "3. Modificar usos"<< endl;
                                cout << "4. Modificar valor"<< endl;
                                cout << "5. Mostrar accesorios"<< endl;
                                cout << "6. Salir " << endl;
                                cin >> modificar_accesorio_mochila;

                                switch(modificar_accesorio_mochila)
                                {
                                    case 1:
                                    {
                                        string nombre_accesorio_modificado;
                                        cout << "Indique el nombre que desea utilizar" << endl;
                                        cin >> nombre_accesorio_modificado;

                                        lista_mochilas.modificar_mochila(posicion_mochila_modificar, posicion_accesorio_modificar, nombre_accesorio_modificado, "", 0, 0);
                                        break;
                                    }
                                    case 2:
                                    {
                                        string tipo_accesorio_modificado;
                                        cout << "Indique el tipo de accesorio que desea utilizar" << endl;
                                        cin >> tipo_accesorio_modificado;

                                        lista_mochilas.modificar_mochila(posicion_mochila_modificar, posicion_accesorio_modificar, "", tipo_accesorio_modificado, 0, 0);
                                        break;
                                    }
                                    case 3:
                                    {
                                        int usos_accesorio_modificado;
                                        cout << "Indique los usos que desea utilizar" << endl;
                                        cin >> usos_accesorio_modificado;

                                        lista_mochilas.modificar_mochila(posicion_mochila_modificar, posicion_accesorio_modificar, "", "", usos_accesorio_modificado, 0);
                                        break;
                                    }
                                    case 4:
                                    {
                                        int valor_accesorio_modificado;
                                        cout << "Indique el valor que desea utilizar" << endl;
                                        cin >> valor_accesorio_modificado;

                                        lista_mochilas.modificar_mochila(posicion_mochila_modificar, posicion_accesorio_modificar, "", "", 0, valor_accesorio_modificado);
                                        break;
                                    }
                                    case 5:
                                    {
                                        cout << "Mostrando accesorios" << endl;
                                        lista_mochilas.leer_mochilas();
                                        break;
                                    }
                                    case 6:
                                    {
                                        cout << "Saliendo al menú de configuracion" << endl;
                                        break;
                                    }
                                }
                                break;
                            }
                            case 8:
                            {
                                int posicion_accesorio;
                                int posicion_mochila;
                                cout << "Eliminando accesorios" << endl;
                                cout << "Indique que Accesorio desea eliminar por su numero de posicion:" << endl;
                                cin >> posicion_accesorio;
                                cout << "Indique que Mochila desea eliminar por su numero de posicion:" << endl;
                                cin >> posicion_mochila;
                                lista_mochilas.eliminar_accesorio_posicion_mochila(posicion_mochila, posicion_accesorio);

                                break;
                            }
                            case 9:
                            {
                                cout << "Saliendo al menú principal." << endl;
                                break;
                            }
                            default:
                            {
                                cout << "Opción invalida. Intentalo de nuevo." << endl;
                                break;
                            }
                        }
                        break;
                    }
                    case 4:
                    {
                        cout<< BG_LGREEN << "======== ¿Que deseas configurar? =========" << RESET << endl;
                        cout << "1. Agregar accesorios " <<endl;
                        cout << "2. Mostrar accesorios "<< endl;
                        cout << "3. Modificar accesorios "<< endl;
                        cout << "4. Eliminar accesorios" <<endl;
                        cout << "5. Salir" <<endl;
                        cout << "-----------------------------------------" << endl;
                        cin >> opcionaccesorios;

                        string nombredelaccesorio;
                        string tipodeaccesorio;
                        int usosdelaccesorio;
                        int valordelaccesorio;

                        switch(opcionaccesorios){
                            case 1:
                            {
                                cout << "Ingrese el nombre del accesorio o ponga salir para salir: ";
                                cin >> nombredelaccesorio;
                                cout << "Ingrese el tipo del accesorio o ponga 0 para salir o un numero menor a 0: ";
                                cin >> tipodeaccesorio;
                                cout << "Ingrese los usos del accesorio o ponga 0 para salir o un numero menor a 0: ";
                                cin >> usosdelaccesorio;
                                cout << "Ingrese el valor del accesorio o ponga 0 para salir o un numero menor a 0: ";
                                cin >> valordelaccesorio;

                                if ( nombredelaccesorio == "salir")
                                {
                                    break;
                                }

                                if ( tipodeaccesorio == "salir")
                                {
                                    break;
                                }

                                if ( usosdelaccesorio <= 0)
                                {
                                    break;
                                }

                                if ( valordelaccesorio <= 0)
                                {
                                    break;
                                }

                                lista_accesorios_principal.agregar_espec_accesorio(-1, nombredelaccesorio, tipodeaccesorio, usosdelaccesorio, valordelaccesorio);

                                break;

                            }
                            case 2:
                            {
                                cout << "Mostrando accesorios" << endl;
                                lista_accesorios_principal.leer_lista_accesorios();
                                break;

                            }
                            case 3:
                            {
                                int modificar_accesorio;

                                cout << "Para modificar accesorio indique que desea modificar:" << endl;
                                cout << "1. Modificar nombre " <<endl;
                                cout << "2. Modificar tipo de accesorio"<< endl;
                                cout << "3. Modificar usos"<< endl;
                                cout << "4. Modificar valor"<< endl;
                                cout << "5. Mostrar accesorios"<< endl;
                                cout << "6. Salir " << endl;
                                cin >> modificar_accesorio;

                                switch(modificar_accesorio)
                                {
                                    case 1:
                                    {
                                        int posicion_accesorio_modificado;
                                        string nombre_accesorio_modificado;
                                        cout << "Indique que Accesorio desea modificar por su numero de posicion" << endl;
                                        cin >> posicion_accesorio_modificado;
                                        cout << "Indique el nombre que desea utilizar" << endl;
                                        cin >> nombre_accesorio_modificado;

                                        lista_accesorios_principal.modificar_accesorio(posicion_accesorio_modificado,nombre_accesorio_modificado, "", 0, 0);
                                        break;
                                    }
                                    case 2:
                                    {
                                        int posicion_accesorio_modificado;
                                        string tipo_accesorio_modificado;
                                        cout << "Indique que Accesorio desea modificar por su numero de posicion" << endl;
                                        cin >> posicion_accesorio_modificado;
                                        cout << "Indique el tipo de accesorio que desea utilizar" << endl;
                                        cin >> tipo_accesorio_modificado;

                                        lista_accesorios_principal.modificar_accesorio(posicion_accesorio_modificado,"", tipo_accesorio_modificado, 0, 0);
                                        break;
                                    }
                                    case 3:
                                    {
                                        int posicion_accesorio_modificado;
                                        int usos_accesorio_modificado;
                                        cout << "Indique que Accesorio desea modificar por su numero de posicion" << endl;
                                        cin >> posicion_accesorio_modificado;
                                        cout << "Indique los usos que desea utilizar" << endl;
                                        cin >> usos_accesorio_modificado;

                                        lista_accesorios_principal.modificar_accesorio(posicion_accesorio_modificado,"", "", usos_accesorio_modificado, 0);
                                        break;
                                    }
                                    case 4:
                                    {
                                        int posicion_accesorio_modificado;
                                        int valor_accesorio_modificado;
                                        cout << "Indique que Accesorio desea modificar por su numero de posicion" << endl;
                                        cin >> posicion_accesorio_modificado;
                                        cout << "Indique el valor que desea utilizar" << endl;
                                        cin >> valor_accesorio_modificado;

                                        lista_accesorios_principal.modificar_accesorio(posicion_accesorio_modificado,"", "", 0, valor_accesorio_modificado);
                                        break;
                                    }
                                    case 5:
                                    {
                                        cout << "Mostrando accesorios" << endl;
                                        lista_accesorios_principal.leer_lista_accesorios();
                                        break;
                                    }
                                    case 6:
                                    {
                                        cout << "Saliendo al menú de configuracion" << endl;
                                        break;
                                    }
                                }

                            }
                            case 4:
                            {
                                int posicion_accesorio;
                                cout << "Eliminando accesorios" << endl;
                                cout << "Indique que Accesorio desea eliminar por su numero de posicion:" << endl;
                                cin >> posicion_accesorio;
                                lista_accesorios_principal.eliminar_accesorio_pos(posicion_accesorio);

                                break;
                            }
                            case 5:
                            {
                                cout << "Saliendo al menú principal." << endl;
                                break;
                            }
                        }
                        break;
                    }
                    case 5:
                    {
                        cout << "Subiendo documentos Predeterminados" << endl;
                        team1.agregar_soldados_por_zmb();
                        lista_zombies.agregar_zombies_por_zmb();
                        lista_accesorios_principal.agregar_accesorios_por_zmb();
                        break;
                    }
                    case 6:
                    {
                        cout << "Saliendo al menú principal." << endl;
                        break;
                    }
                }
                break;
            }

            case 3:
            {
                    int opc2;

                    do{
                        system("cls");
                        cout << MAGENTA << "=== ¿COMO JUGAR? ===" << RESET <<endl;
                        cout <<BLUE << "1. Historia." << RESET <<endl;
                        cout <<BLUE<< "2. Enemigos." << RESET << endl;
                        cout <<BLUE<< "3. Trata de salvar el planeta con estrategias." << RESET << endl;
                        cout <<BLUE<< "4. Salir." << RESET << endl;
                        cout <<GREEN << "Indica que quieres saber soldado?" << RESET << endl;                            cin >> opc2;
                        switch(opc2){
                            case 1:{
                                system("cls");

                                cout << MAGENTA << "Londres, 2024. " << RESET << "Lo que comenzó como una serie de extraños síntomas en pequeñas" << endl;
                                cout << "comunidades a lo largo y ancho del país, pronto se reveló como una pesadilla global." << endl;
                                cout << "Investigaciones preliminares apuntan a un incidente aéreo en el Canal de la Mancha, donde un" << endl;
                                cout << "cargamento altamente confidencial de patógenos modificados a partir del COVID-19 se habría" << endl;
                                cout << "dispersado en la atmósfera. La comunidad internacional se encuentra al borde del pánico," << endl;
                                cout << "mientras expertos en salud pública y gobiernos intentan contener lo que parece ser una " << RED << "guerra" << endl;
                                cout << RED << "biológica " << RESET << "desatada accidentalmente." << endl << endl;

                                cout << "La " << LBLUE << "Dra. Emily Carter " << RESET << "se encontraba en su laboratorio cuando recibió la llamada. Un nuevo" << endl;
                                cout << "virus, mucho más agresivo que cualquier otro conocido, estaba diezmando poblaciones enteras." << endl;
                                cout << "Como viróloga experta, sabía que solo había una explicación: una fuga en uno de los laboratorios" << endl;
                                cout << "secretos que habían estado desarrollando armas biológicas. Sin embargo, cuando comenzó a" << endl;
                                cout << "investigar, se encontró con una conspiración mucho más profunda de lo que jamás había" << endl;
                                cout << "imaginado. Las grandes potencias habían estado jugando con fuego, y ahora " << RED << "el mundo entero" << endl;
                                cout << "estaba pagando las consecuencias." << endl;
                                system("pause");
                                system("cls");
                                break;}
                            case 2:{
                                system("cls");

                                cout << BG_GREEN << "· Zombies rápidos y ágiles" << RESET <<": Estos zombies son extremadamente rápidos y ágiles, capaces de" << endl;
                                cout << "perseguir a sus presas a altas velocidades. Podrían ser el resultado de una mutación que aceleró su" << endl;
                                cout << "metabolismo." << endl << endl;

                                cout << BG_RED << "· Zombies tanques" << RESET <<": Grandes y lentos, estos zombies son casi indestructibles. Su fuerza bruta los" << endl;
                                cout << "convierte en una amenaza formidable, capaces de derribar puertas y paredes, su debilidad es las" << endl;
                                cout << "luces , las cuales no puede soportar." << endl << endl;

                                cout << BG_LBLUE << "· Zombies inteligentes" << RESET <<": Estos zombies han conservado parte de su inteligencia, lo que les permite" << endl;
                                cout << "planificar emboscadas y utilizar herramientas. Podrían ser una evolución de los zombies, o el" << endl;
                                cout << "resultado de una infección en individuos con un coeficiente intelectual alto. Pero son frágiles y" << endl;
                                cout << "lentos." << endl << endl;

                                cout << BG_ORANGE << "· Zombies infectados por hongos" << RESET <<": Estos zombies presentan características fúngicas, como esporas" << endl;
                                cout << "que se propagan por el aire y la capacidad de controlar a otros organismos." << endl << endl;
                                
                                cout << BG_YELLOW << "· Zombies bioluminiscentes" << RESET <<": Estos zombies emiten una luz bioluminiscente, lo que los hace" << endl;
                                cout << "fácilmente visibles en la oscuridad. Esta característica podría ser un efecto secundario de la" << endl;
                                cout << "mutación o una adaptación para comunicarse entre ellos." << endl;
                                 system("pause");
                                system("cls");

                                break;}
                            case 3:{
                                system("cls");

                                cout << GREEN << "Consejos adicionales:" << endl;
                                cout << "· Combina diferentes tipos de armas: Utilizar una combinación de armas a distancia y cuerpo a cuerpo te permitirá" << endl;
                                cout << "adaptarte a diferentes situaciones." << endl;
                                cout << "· Aprende a fabricar armas: En un apocalipsis zombie, los recursos pueden ser escasos, por lo que aprender a" << endl;
                                cout << "fabricar tus propias armas puede ser vital." << endl;
                                cout << "· Entrena regularmente: Practica con tus armas para mejorar tu puntería y velocidad." << endl;
                                cout << "· Sé creativo: En un mundo post-apocalíptico, cualquier objeto puede convertirse en un arma." << endl << endl;

                                cout << "La " << LBLUE << "Dra. Emily Carter " << RESET << "ha desarrollado una " << LGREEN << "cura " << RESET << "para el virus zombie, pero necesita" << endl;
                                cout << "encontrar una forma segura de distribuirla. Decide utilizar la red de túneles del metro como un" << endl;
                                cout << "sistema de distribución, para ello se va a enviar a uno o varios equipos de militares, que" << endl;
                                cout << "cada ciudad grande del planeta tiene un sistema de redes diferentes y puede o no contener" << endl;
                                cout << RED << "grupos de zombies " << RESET << "diferentes en cada estación" << endl;
                                system("pause");
                                system("cls");

                                break;}                           
                            case 4:{
                                system("cls");
                                cout << "Saliendo al menú principal." << endl;
                                system("cls");
                                break;}
                            default:{
                                system("cls");
                                cout << RED << "Opción invalida. Intentalo de nuevo." << RESET << endl;
                                system("cls");
                                break;}
                        }  
                        }while(opc2 != 4);
                        break;
                    }
            case 4:
                    system("cls");
                    cout << MAGENTA << "Cerrando programa" << endl;
                    cout << BG_LGREEN << "Vuelve pronto soldado !!!" << RESET << endl;
                    break;

                default:
                    system("cls");
                    cout << RED << "Opción invalida. Intentalo de nuevo." << RESET << endl;
                    system("cls");
                    break;
            }
    }while (opcion != 5);   

    // liberar memoria  
    // delete; 
    // delete; 
    // delete; 
    
    return 0;
}
