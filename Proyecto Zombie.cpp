#include <iostream>
#include <random>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <windows.h>
#include "Colores.h"

//Todo el manejo de zombies, soldado, accesorios y mapa
#include "soldados.h"
#include "zombies.h"
#include "Accesorios.h"


using namespace std;

// Elaborado por: Pedro Romero, Naim Chelhot y Jhoselin Bello.                                  //

//                                       ESTRUCTURAS DE LOS DATOS                                                   // 


//_______________________________________ Mapa _________________________________________________________________//
struct mapa{
    string Nombre;

};

//_____________________________________________ Mochila _____________________________________________________// 
struct Mochila{
    string Nombre_del_soldado;
    int Capacidad;
    accesorios *accesorios; 
    Mochila *proxMochila; 

};

//                                           FUNCIONES PRINCIPALES                                              //



//___________________________________________ Funciones de Accesorios __________________________________________//

int generar_Accesorio_Aleatorio(int min, int max){
  static default_random_engine generador(time(nullptr));
  uniform_int_distribution<int> distribucion(min, max);
  return distribucion(generador);
}


//__________________________________________ Funciones de Mochilas _____________________________________________//
Mochila *CrearMochila(string nombre, int capacidad){
    Mochila *nueva_mochila = new Mochila; 
    nueva_mochila->Nombre_del_soldado = nombre; 
    nueva_mochila->Capacidad = capacidad; 
    nueva_mochila->accesorios = nullptr;
    nueva_mochila->proxMochila = nullptr;  
    return nueva_mochila;
}

bool listaVaciaMochila(Mochila *listaDeMochilas){
    return listaDeMochilas == nullptr;
}

void insertarUltimaMochila(Mochila **mochila, string nombre, int capacidad){
    Mochila *nuevaMochila = CrearMochila(nombre, capacidad);
											 
   if (listaVaciaMochila(*mochila)) {
       *mochila = nuevaMochila;
    } 
    else {
       Mochila *auxiliar = *mochila;
       while (auxiliar->proxMochila!= NULL) {
           auxiliar = auxiliar->proxMochila;
       }
        auxiliar->proxMochila= nuevaMochila;
   }

}

Mochila *buscarMochilaPorNombre(Mochila *mochila, string nombreDelSoldado){ 
    Mochila *temp= mochila; 
    while(temp!=nullptr){
        if(temp->Nombre_del_soldado != nombreDelSoldado){
            temp = temp->proxMochila;
        }else{
            return temp; 
            cout << "Jugador encontrado"<< endl; 
        }
    } 
    return temp ; 
}

void eliminarMochilaPorNombreDelSoldado(Mochila *cabeza, string nombre){
    Mochila *actual = cabeza;
    Mochila *anterior = nullptr;
    while (actual->proxMochila != NULL){
        anterior = actual;
        if(nombre == (actual->proxMochila)->Nombre_del_soldado){
            anterior = anterior->proxMochila;
            actual->proxMochila= anterior->proxMochila;
            delete anterior;
        }
        actual= actual->proxMochila;
    }
}

// void mostrarUnaMochila(Mochila *lista, string nombre){
//     Mochila *mover = nullptr;     
//      if (!listaVaciaMochila(lista)){
//         Mochila *mochila = buscarMochilaPorNombre(lista, nombre);
//         mover = mochila;
        
//         cout <<"Mochila: "<<endl;
//  	    cout <<" Nombre del Soldado: "<<mover->Nombre_del_soldado <<endl;
//  	    cout <<" Capacidad: "<<mover->Capacidad<<endl;
//         if(mover->accesorios != nullptr){    
//             while(mover->accesorios != nullptr){ 
//                 cout << "Acesorios que lleva: " << endl; 
//                 cout <<" nombre : "<<mover->accesorios->Nombre_del_accesorio <<endl;
//                 cout <<" Tipo : "<<mover->accesorios->Tipo <<endl;
//                 cout <<" Uso o municion: " << mover->accesorios->Usos_Municion <<endl;
//                 cout << "Valor: " << mover->accesorios->valor << endl;
//  	            mover->accesorios = mover->accesorios->siguiente;
//             }
//         }
//         else{
//             cout << RED << "Tu mochila esta vacia, busca objetos para meterlos a tu mochila!" << endl; 
//         }
//     }  
//     else
//       cout <<" ";
//  }


//_________________________________________Lectura de archivos_______________________________________//


//____________________________________________ MENU _______________________________________//
void mostrarMenu(){
    cout<< RED << "Bienvenido a RUNNING DEAD [Demo] " << RESET << endl;
    cout<< BG_LGREEN << "======== MENU =========" << RESET << endl;
    cout << "1. Iniciar partida" <<endl;
    cout << "2. Crear datos "<< endl; 
    cout << "3. Como jugar?" <<endl;
    cout << "4. Borrar datos." << endl;
    cout << "5. Salir" <<endl;
    cout << "-----------------------------------------" << endl; 
}
 

// ---------------------------------------------- MAIN ------------------------------------ //
int main(){
    soldado **primerSoldado = nullptr; 
    lecturasoldados(&*primerSoldado);
    string equipo1; 
    string equipo2; 
    
    //srand(time(0));
    // Zombie* lista_zombie = CrearTropaZombie();
    // recorridozombies(lista_zombie);
    // cout << endl;
    // cout << calculador(lista_zombie) << endl;


    
    string personajes;
    string accaux; 
    int opcion;
    do {
        mostrarMenu();
                cout<< "Selecciona una opcionque desee: ";
                cin>> opcion;
                switch(opcion){
                    case 1:
                        cout<<""<<endl;
                        cout<<"Era Londres del 2024..."<<endl;
                        cout<<"Lo que comenzo como una serie de extranios sintomas en pequenias comunidades"<<endl;
                        cout<<"a lo largo y ancho del pais. "<<endl;
                        cout<<"Pronto se revelo como una pesadilla global, gracias a patogenos modificados a "<<endl;
                        cout<<"partir del covid-19 se habria dispersado en la atmosfera"<<endl;
                        cout<<""<<endl;

                        //system("pause");

                        cout<<"Ingrese el nombre del equipo 1:"<<endl;
                        getline(cin,equipo1);
                        cout<<""<<endl;

                        cout<<"Ingrese el nombre del equipo 2:"<<endl;
                        getline(cin,equipo2);
                        cout<<""<<endl;

                        //system("pause");

                        cout<<""<<endl;
                        cout<<"Gracias a la Dra. Emily Carter ha desarrollado una cura"<<endl;
                        cout<<"y eligio a los equipos militares " << YELLOW  << equipo1  << RESET << " y " << YELLOW << equipo2 << RESET <<endl;
                        cout<<"para distribuirla a traves de una red de tuneles del metro "<<endl;
                        cout<<""<<endl;

                        //system("pause");

                        cout<<""<<endl;
                        cout<< equipo1 <<" confiamos en usted para llevar la cura hasta su lugar de destino. Buena suerte!!"<<endl;
                        cout<<"Debe seleccionar con cuidado que soldados llevara a la disputa"<<endl;
                        // colocar opcion de elegir soldados en la batalla
                       
 
                    break;

                case 2:
                    {int opc3;
                    string name;
                    string weapon;
                    int type;
                    int health;
                    int damage;
                    int value;
                    cout<< RED << "Bienvenido a RUNNING DEAD [Demo] " << RESET << endl;
                        cout<< BG_LGREEN << "======== ¿Que deseas crear? =========" << RESET << endl;
                        cout << "1. Soldado " <<endl;
                        cout << "2. Zombie "<< endl; 
                        cout << "3. Accesorio" <<endl;
                        cout << "4. Accesorio" <<endl;
                        cout << "5. Salir" <<endl;
                        cout << "-----------------------------------------" << endl; 
                        cin >> opc3;
                    switch(opc3){
                        case 1:
                            
                            break;
                        case 2:
                                                  
                            
                            break;
                        case 3:
                            
                            break;
                        case 4:
                            break;
                        case 5:
                            system("cls");
                            cout << "Saliendo al menú principal." << endl;
                            system("cls");
                            break;
                        default:
                            system("cls");                                
                            cout << RED << "Opción invalida. Intentalo de nuevo." << RESET << endl;
                            system("cls");
                            break;
                        }
                    }
                    break;

                case 3:{
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
                            case 1:
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
                                break;
                            case 2:
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

                                break;
                            case 3:
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

                                break;                           
                            case 4:
                                system("cls");
                                cout << "Saliendo al menú principal." << endl;
                                system("cls");
                                break;
                            default:
                                system("cls");
                                cout << RED << "Opción invalida. Intentalo de nuevo." << RESET << endl;
                                system("cls");
                                break;
                        }  
                    }while(opc2 != 4);
                    break;
                }
                case 4:
                    break;
                
                case 5:
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
    
    return 0;
}