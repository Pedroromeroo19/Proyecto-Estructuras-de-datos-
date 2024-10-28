#include <iostream>
#include <random>
#include <time.h>
//Colores para decorar //
#define BLACK   "\x1B[30m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1B[37m"
#define ORANGE  "\x1B[38;2;255;128;0m"
#define ROSE    "\x1B[38;2;255;151;203m"
#define LBLUE   "\x1B[38;2;53;149;240m"
#define LGREEN  "\x1B[38;2;17;245;120m"
#define GRAY    "\x1B[38;2;176;174;174m"
#define RESET   "\x1b[0m"
//===Color background code===/
#define BG_BLACK   "\x1B[40m"
#define BG_RED     "\x1B[41m"
#define BG_GREEN   "\x1B[42m"
#define BG_YELLOW  "\x1B[43m"
#define BG_BLUE    "\x1B[44m"
#define BG_MAGENTA "\x1B[45m"
#define BG_CYAN    "\x1B[46m"
#define BG_WHITE   "\x1B[47m"
#define BG_ORANGE  "\x1B[48;2;255;128;0m"
#define BG_LBLUE   "\x1B[48;2;53;149;240m"
#define BG_LGREEN  "\x1B[48;2;17;245;120m"
#define BG_GRAY    "\x1B[48;2;176;174;174m"
#define BG_ROSE    "\x1B[48;2;255;151;203m"


using namespace std;


// Elaborado por: Pedro Romero, Naim (noseescribirsuapellido) y Jhoselin Bello.                                  //


//                                       ESTRUCTURAS DE LOS DATOS                                                   //


//_______________________________________ Mapa _________________________________________________________________//
struct mapa{
    string Nombre;


};
//_______________________________________ Accesorios ___________________________________________________________//
struct Accesorios{
    string Nombre_del_accesorio;
    string Tipo;
    int Usos_Municion;
    int valor;


    Accesorios *siguiente;


};


//_____________________________________________ Mochila _____________________________________________________//
struct Mochila{
    string Nombre_del_soldado;
    int Capacidad;
    Accesorios *accesorios;
    Mochila *proxMochila;


};


//______________________________________________ Zombies ___________________________________________________________//


struct Ataque{
    string Nombre_del_ataque;
    int Daño;
    Ataque *proxAtaque;  
};


struct Zombie{
    string Nombre_del_zombie;
    int fortaleza;
    string nombre_de_ataque;
    int Danno;
    Zombie *siguiente;


};


//________________________________________ Soldado ________________________________________________________________//


struct Soldado{
    string nombre;
    int salud;
    Soldado *siguiente;
    Mochila *listaMochila;
};


//                                           FUNCIONES PRINCIPALES                                              //


//___________________________________________ Funciones de zombies _____________________________________________//
Zombie *CrearZombie(string  nom, int fort, string nombre_ataque, int danio){
    Zombie *nuevo_zombie = new Zombie;
    nuevo_zombie->Nombre_del_zombie= nom;
    nuevo_zombie->fortaleza= fort;
    nuevo_zombie->nombre_de_ataque= nombre_ataque;
    nuevo_zombie->Danno = danio;
    nuevo_zombie->siguiente = nullptr;
    return nuevo_zombie;
}


bool lista_vacia_zombie(Zombie*& punt_tope){
    return (punt_tope == NULL);
}


enum zombiestipo {zombierapidotipo = 0, zombietanquetipo = 1, zombieinteligentetipo = 2, zombiesconhongostipo = 3, zombieluminiscentetipo = 4};


void agregar_zombie(zombiestipo tipo, Zombie*& punt_tope){


    /*Caracteristicas ataque
    Zombie Rápido


        Arma: Cuchillas retráctiles en los brazos: Estas cuchillas permitirían al zombie infligir daño en ataques rápidos y certeros, aprovechando su velocidad.
        Poder: Dash: Un movimiento rápido que le permita cubrir grandes distancias en poco tiempo, sorprendiendo al jugador y dificultando su seguimiento.
        Poder: Adrenalina: Un aumento temporal de su velocidad y fuerza, permitiéndole realizar ataques más poderosos y esquives más rápidos.


    Zombie Tanque


        Arma: Puños reforzados con hueso: Sus puños, endurecidos y afilados, serían armas contundentes capaces de romper obstáculos y causar un daño considerable al jugador.
        Poder: Carga: Una carga poderosa que derribe al jugador y cause daño a su alrededor.
        Poder: Escudo óseo: Un escudo temporal que lo proteja de los ataques, permitiéndole acercarse al jugador sin recibir daño.


    Zombie Inteligente


        Arma: Proyectiles biológicos: Podría lanzar proyectiles venenosos o explosivos a distancia, utilizando su inteligencia para anticipar los movimientos del jugador.
        Poder: Mimetismo: La capacidad de camuflarse con el entorno, haciéndolo difícil de detectar hasta que sea demasiado tarde.
        Poder: Control mental: Podría intentar controlar al jugador o a otros zombies para distraerlo o atacarlo.


    Zombies con Hongos


        Arma: Esporas venenosas: Podría liberar esporas tóxicas que dañen al jugador a distancia o lo infecten con un efecto negativo.
        Poder: Crecimiento acelerado: Los hongos que cubren su cuerpo podrían crecer rápidamente, permitiéndole aumentar su tamaño y fuerza temporalmente.
        Poder: Control de hongos: Podría controlar otros hongos en el entorno para atacar al jugador o crear obstáculos.


    Zombie Luminiscente


        Arma: Rayos de energía: Podría disparar rayos de energía desde sus ojos o manos, causando daño y aturdiendo al jugador.
        Poder: Curación: Podría absorber la energía de su entorno para curar sus heridas o aumentar su fuerza.
        Poder: Ceguera: Podría emitir una luz cegadora que dificulte la visión del jugador, permitiéndole atacar por sorpresa.*/






    Zombie *nuevo_zombie = new Zombie ();        //Declaracion nodo


    //nombres ataques nombre armas


    string zombierapidonombre[] = {"Cuchillas retráctiles","Dash", "Adrenalina"};
    string zombietanquenombre[] = {"Puños reforzados con hueso", "Carga", "Escudo óseo"};
    string zombieinteligentenombre[] = {"Proyectiles biológicos","Mimetismo", "Control mental"};
    string zombieconhongosnombre[] = {"Esporas venenosas", "Crecimiento acelerado", "Control de hongos"};
    string nombresFarmaciasnombre[] = {"Rayos de energía","Curación", "Ceguera"};


    //valor por ataque en el mismo orden 


    int zombierapidodano[] = {-12, -15,-10};
    int zombietanquedano[] = {-10, -13, -11};
    int zombieinteligentedano[] = {-18,-5, -12};
    int zombieconhongosdano[] = {-3, -12, -10};
    int nombresFarmaciasdano[] = {-16,-15, -12};


    int randomnum = (rand() % 4);








    zombiestipo opciones = tipo;


    switch(opciones){


    case  zombierapidotipo:
        nuevo_zombie->Nombre_del_zombie = "zombie rapido";
        nuevo_zombie->Danno = zombierapidodano[randomnum];
        nuevo_zombie->nombre_de_ataque = zombierapidonombre[randomnum];
        nuevo_zombie->fortaleza=110;
    break;


    case zombietanquetipo:
        nuevo_zombie->Nombre_del_zombie="zombie tanque";
        nuevo_zombie->Danno = zombietanquedano[randomnum];
        nuevo_zombie->nombre_de_ataque = zombietanquenombre[randomnum];
        nuevo_zombie->fortaleza=150;
    break;


    case zombieinteligentetipo:
        nuevo_zombie->Nombre_del_zombie="zombie inteligente";
        nuevo_zombie->Danno = zombieinteligentedano[randomnum];
        nuevo_zombie->nombre_de_ataque = zombieinteligentenombre[randomnum];
        nuevo_zombie->fortaleza=80;
    break;


    case zombiesconhongostipo:
        nuevo_zombie->Nombre_del_zombie="zombies con hongos";
        nuevo_zombie->Danno = zombieconhongosdano[randomnum];
        nuevo_zombie->nombre_de_ataque = zombieconhongosnombre[randomnum];
        nuevo_zombie->fortaleza=90;
    break;


    case zombieluminiscentetipo:
        nuevo_zombie->Nombre_del_zombie="zombie luminiscente";
        nuevo_zombie->Danno = nombresFarmaciasdano[randomnum];
        nuevo_zombie->nombre_de_ataque = nombresFarmaciasnombre[randomnum];
        nuevo_zombie->fortaleza=120;
    break;
    }


    if (lista_vacia_zombie(punt_tope)) //agregar a lista vacia
    {
        nuevo_zombie->siguiente = NULL;
    }
    else                               //agregar a lista con mas datos
    {
        nuevo_zombie->siguiente = punt_tope; //apuntar al proximo
    }


    punt_tope = nuevo_zombie; //pasar puntero tope de el ultimo primero al proximo primero
    }
   


void eliminar_lista_zombie(Zombie*& punt_tope){
    if(!lista_vacia_zombie(punt_tope)){


        Zombie *ptrtemporal1 = punt_tope;
        Zombie *ptrtemporal2;


        while (punt_tope != NULL)
        {
            ptrtemporal2 = ptrtemporal1;
            ptrtemporal1 = ptrtemporal1->siguiente;
            delete ptrtemporal2;
        }
       
    }
}


void eliminar_un_zombie(string referencia, Zombie*& cabeza){
        Zombie *aux1;
        aux1 = cabeza;
        Zombie *aux2;
        while (aux1->siguiente != NULL){
            aux2 = aux1;
            if((aux1->siguiente)->Nombre_del_zombie == referencia){
                aux2 = aux2->siguiente;
                aux1->siguiente= aux2->siguiente;
                delete aux2;
            }


            aux1= aux1->siguiente;
        }
}


Zombie* CrearTropaZombie(int tama){
    Zombie *lista_zombie= NULL;


    for (int i = 0; i < tama; i++)
    {
        int randomnum = (rand() % 5);
        zombiestipo randomColor = static_cast<zombiestipo>(randomnum);


        agregar_zombie(randomColor,lista_zombie);
    }
    return lista_zombie;
}


void recorridozombies(Zombie *&cabeza) {
    Zombie *aux1 = cabeza;
    if(cabeza != nullptr){
        cout << "Caracteristicas de los Zombies:"<< endl;
        cout << "Nombre del zombie:"<< aux1->Nombre_del_zombie << endl;
        cout << "Nombre del ataque:" << aux1->nombre_de_ataque << endl;
        cout << "Numero de daño:"<<aux1->Danno << endl;
        cout<< endl;
        recorridozombies(aux1->siguiente);
    }
}




int mostrarnum(Zombie *& cabeza){
    Zombie *aux1;
    aux1 = cabeza;
    if(cabeza != nullptr){
        cout << aux1->Danno << endl;
        mostrarnum(aux1->siguiente);
    }
    return 0;
}


int calculadoradanno(Zombie *&cabeza){
    Zombie *aux1 = cabeza;
    if (cabeza != nullptr){
        cout << "Tipo : " << aux1->Nombre_del_zombie<< endl;
        cout << "Danio : " << aux1->Danno<< endl;
        calculadoradanno(aux1->siguiente);
    }
    return 0;


}


int calculador(Zombie *& cabeza){
    Zombie *aux1;
    aux1 = cabeza;
    int valor;
    while (aux1->siguiente != NULL){
            valor = valor + aux1->Danno;
            aux1= aux1->siguiente;
        }
    return valor;
    }


//___________________________________________ Funciones de Soldados __________________________________________//
Soldado *CrearSoldado(string nombre, int vida, Mochila *mochila){
    Soldado *nuevo_soldado = new Soldado;
    nuevo_soldado->nombre = nombre;
    nuevo_soldado->salud = vida;
    nuevo_soldado->siguiente = nullptr;
    nuevo_soldado->listaMochila = mochila;
    return nuevo_soldado;
}


bool listaVaciaSoldado(Soldado *listaDeSoldados){
    return listaDeSoldados == nullptr;
}


void insertarUltimoSoldado(Soldado **lista, string nombre, int salud , Mochila *mochila){
    Soldado *nuevoSoldado = CrearSoldado(nombre, salud, mochila );
                                             
   if (listaVaciaSoldado(*lista)) {
       *lista = nuevoSoldado;
    }
    else {
       Soldado *auxiliar = *lista;
       while (auxiliar->siguiente!= NULL) {
           auxiliar = auxiliar->siguiente;
       }
        auxiliar->siguiente = nuevoSoldado;
   }


}


Soldado *buscarSoldadoPorNombre(Soldado *cabeza, string nombre_jugador ){
    Soldado *temp= cabeza;
    while(temp!=nullptr){
        if(temp->nombre == nombre_jugador){
            return temp;
        }else{
            cout << " Jugador no encontrado..." << endl;
        }
        temp = temp->siguiente;


    }
    return nullptr;
}


void mostrarJugador(Soldado *lista){
    Soldado *mover = nullptr;


    if (!listaVaciaSoldado(lista)){
        mover = lista;
        cout << "Lista de jugadores" << endl;
        while(mover != nullptr){


            cout << GREEN << "Nombre: "<<       mover->nombre << RESET << endl;
            cout <<"Salud: "<<mover->salud <<endl;
            mover = mover->siguiente;  }
    }
}






//___________________________________________ Funciones de Accesorios __________________________________________//




Accesorios *CrearAccesorio(string nombre, string tipo, int uso_municion, int valor){
    Accesorios *nuevo_accesorio = new Accesorios;
    nuevo_accesorio->Nombre_del_accesorio = nombre;
    nuevo_accesorio->Tipo = tipo;
    nuevo_accesorio->Usos_Municion = uso_municion;
    nuevo_accesorio->valor= valor;  
    nuevo_accesorio->siguiente = nullptr;
    return nuevo_accesorio;
}


bool listaVaciaAccesorios(Accesorios *listaDeAccesorios){
    return listaDeAccesorios == nullptr;
}


void insertarAccesorioUltimo(Accesorios **acces, string nombre, string tipo, int muni_uso, int valor){
    Accesorios *nuevoAccesorio = CrearAccesorio(nombre, tipo, muni_uso, valor);
                                             
   if (listaVaciaAccesorios(*acces)) {
       *acces = nuevoAccesorio;
    }
    else {
       Accesorios *auxiliar = *acces;
       while (auxiliar->siguiente!= NULL) {
           auxiliar = auxiliar->siguiente;
       }
        auxiliar->siguiente = nuevoAccesorio;
   }


}


Accesorios *buscarAccesorioPorNombre(Accesorios *accesorios, string nombreAccesorio){
    Accesorios *temp= accesorios;
    while(temp!=nullptr){
        if(temp->Nombre_del_accesorio == nombreAccesorio){
            return temp;
        }
        temp = temp->siguiente;


    }
    return nullptr;
}


int generar_Accesorio_Aleatorio(int min, int max){
  static default_random_engine generador(time(nullptr));
  uniform_int_distribution<int> distribucion(min, max);
  return distribucion(generador);
}


void mostrarAccesorios(Accesorios *lista){
    Accesorios *mover;
   
    if (!listaVaciaAccesorios(lista)){
         mover = lista;
      cout <<"Lista de Accesorios: "<<endl;
        while (mover != NULL) {
   
            cout <<" Nombre: "<<mover->Nombre_del_accesorio <<endl;
            cout <<" Tipo de accesorio: "<<mover->Tipo <<endl;
            cout <<" Cantidad : "<<mover->Usos_Municion <<endl;
            cout <<" Uso o municion: " << mover->Usos_Municion <<endl;
            cout << "Valor: " << mover->valor << " ";
            mover = mover->siguiente;
      }


   }  
  else
     cout <<" ";
}


void eliminarAccesorios(Accesorios *cabeza, string nombre){
    Accesorios *actual = cabeza;
    Accesorios *anterior = nullptr;
    while (actual->siguiente != NULL){
        anterior = actual;
        if(nombre == (actual->siguiente)->Nombre_del_accesorio ){
            anterior = anterior->siguiente;
            actual->siguiente= anterior->siguiente;
            delete anterior;
        }
        actual= actual->siguiente;
    }
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
        }else
            return temp;
       
    }
    return nullptr;
}


void mostrarMochilas(Mochila *lista){
    Mochila *mover;
   
    if (!listaVaciaMochila(lista)){
         mover = lista;
      cout <<"Mochila: "<<endl;
        while (mover != NULL) {
   
            cout <<" Nombre del Soldado: "<<mover->Nombre_del_soldado <<endl;
            cout <<" Capacidad: "<<mover->Capacidad<<endl;
            if(mover->accesorios != nullptr){
                mostrarAccesorios(mover->accesorios);
            }else{
                cout << "Tu mochila esta vacia, busca objetos para meterlos a tu mochila!" << endl;
            }
            mover = mover->proxMochila;
      }


   }  
  else
     cout <<" ";
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


void mostrarUnaMochila(Mochila *lista, string nombre){
    Mochila *mover = nullptr;    
     if (!listaVaciaMochila(lista)){
        Mochila *mochila = buscarMochilaPorNombre(lista, nombre);
        mover = mochila;
       
        cout <<"Mochila: "<<endl;
        cout <<" Nombre del Soldado: "<<mover->Nombre_del_soldado <<endl;
        cout <<" Capacidad: "<<mover->Capacidad<<endl;
        if(mover->accesorios != nullptr){    
            while(mover->accesorios != nullptr){
                cout << "Acesorios que lleva: " << endl;
                cout <<" nombre : "<<mover->accesorios->Nombre_del_accesorio <<endl;
                cout <<" Tipo : "<<mover->accesorios->Tipo <<endl;
                cout <<" Uso o municion: " << mover->accesorios->Usos_Municion <<endl;
                cout << "Valor: " << mover->accesorios->valor << endl;
                mover->accesorios = mover->accesorios->siguiente;
            }
        }
        else{
            cout << RED << "Tu mochila esta vacia, busca objetos para meterlos a tu mochila!" << endl;
        }
    }  
    else
      cout <<" ";
 }
 
void MeterAccesorioEnMochilaDelJugador(Soldado *jugador, Mochila *lista,string nombre_del_jugador, string nombre_del_accesorio, string tipo, int uso, int valor){
    Mochila *mochila = buscarMochilaPorNombre(lista ,nombre_del_jugador);
    if(!mochila){
        cout << "El soldado no esta en el equipo, intenta crear un nuevo personaje con ese nombre" << endl;
        }else{
        if( jugador->listaMochila->Capacidad >= 20){
            cout << "El jugador : " << jugador->nombre<< " No posee espacio suficiente en la mochila!!" << endl;
            cout << "Intenta desaserte de alguno para ingresar uno nuevo" << endl;
            return;
        }
        else{
            Soldado *auxj = jugador;
            Accesorios *acc = CrearAccesorio(nombre_del_accesorio,tipo, uso, valor);
            if(auxj->listaMochila->accesorios == nullptr){
                auxj->listaMochila->accesorios = acc ;
            }else{
                Accesorios *actual = acc;
                while(actual->siguiente!=nullptr ){
                    if(auxj->listaMochila->accesorios->Tipo == "Supervivencia"){
                        if(auxj->listaMochila->accesorios->Nombre_del_accesorio == "Botiquín de Primeros Auxilios"){
                            auxj->listaMochila->accesorios->Usos_Municion = auxj->listaMochila->accesorios->Usos_Municion + acc->valor;
                        }
                        else if(auxj->listaMochila->accesorios->Nombre_del_accesorio == "Nutrichicha"){
                            auxj->listaMochila->accesorios->Usos_Municion = auxj->listaMochila->accesorios->Usos_Municion + acc->valor;
                        }
                        else if(auxj->listaMochila->accesorios->Nombre_del_accesorio == "Gasas desinfectadas"){
                            auxj->listaMochila->accesorios->Usos_Municion = auxj->listaMochila->accesorios->Usos_Municion + acc->valor;
                        }
                    }
                    else if(auxj->listaMochila->accesorios->Tipo == " Ataque"){
                        if(auxj->listaMochila->accesorios->Nombre_del_accesorio == "Bate de Béisbol Metálico"){
                            auxj->listaMochila->accesorios->Usos_Municion = auxj->listaMochila->accesorios->Usos_Municion + acc->valor;
                        }
                        else if(auxj->listaMochila->accesorios->Nombre_del_accesorio == "Cuchillo de Supervivencia"){
                            auxj->listaMochila->accesorios->Usos_Municion = auxj->listaMochila->accesorios->Usos_Municion + acc->valor;
                        }
                        else if(auxj->listaMochila->accesorios->Nombre_del_accesorio == "Ak-47"){
                            auxj->listaMochila->accesorios->Usos_Municion = auxj->listaMochila->accesorios->Usos_Municion + acc->valor;
                        }
                    }
                    else if(auxj->listaMochila->accesorios->Tipo == "Defensa"){
                        if(auxj->listaMochila->accesorios->Nombre_del_accesorio == "Armadura Casera (metal, cuero)"){
                            auxj->listaMochila->accesorios->Usos_Municion = auxj->listaMochila->accesorios->Usos_Municion + acc->valor;
                        }
                        else if(auxj->listaMochila->accesorios->Nombre_del_accesorio == "Casco Protector"){
                            auxj->listaMochila->accesorios->Usos_Municion = auxj->listaMochila->accesorios->Usos_Municion + acc->valor;
                        }
                        else if(auxj->listaMochila->accesorios->Nombre_del_accesorio == "Escudo Improvisado"){
                            auxj->listaMochila->accesorios->Usos_Municion = auxj->listaMochila->accesorios->Usos_Municion + acc->valor;
                        }
                    }
                    actual = actual->siguiente;
                }
                actual->siguiente = acc;


            }
           
            auxj->listaMochila->Capacidad+=1;
        }
    }
}

//_______________________________________________Funciones de estacion __________________________________________________//

struct estaciones{
    string Nombre_de_estacion; 
    int cantidadzombies;
    estaciones *siguiente;
}; 

bool lista_vacia_estaciones(estaciones*& punt_tope_estac){
    return (punt_tope_estac == NULL);
}

void agregar_estacion(string nombre,int cantidad_zombies, estaciones*& punt_tope_estac){
    estaciones *nueva_estacion = new estaciones ();
    nueva_estacion->Nombre_de_estacion= nombre;
    nueva_estacion->cantidadzombies = cantidad_zombies;

    if (lista_vacia_estaciones(punt_tope_estac)) //agregar a lista vacia
    {
        nueva_estacion->siguiente = NULL;
    }
    else                               //agregar a lista con mas datos
    {
        nueva_estacion->siguiente = punt_tope_estac; //apuntar al proximo 
    }
    punt_tope_estac = nueva_estacion;

}

void eliminar_lista_estaciones(estaciones*& punt_tope_estac){
    if(!lista_vacia_estaciones(punt_tope_estac)){

        estaciones *ptrtemporal1 = punt_tope_estac;
        estaciones *ptrtemporal2;

        while (ptrtemporal1 != NULL)
        {
            ptrtemporal2 = ptrtemporal1;
            ptrtemporal1 = ptrtemporal1->siguiente;
            delete ptrtemporal2;
        }
        
    }
}

void eliminar_una_estacion(string referencia, estaciones*& cabeza_estac){
        if (cabeza_estac == nullptr) {
        cout << "Lista esta vacia"<<endl;
        return;
        }

        estaciones *aux1;
        aux1 = cabeza_estac;
        estaciones *aux2;
        while (aux1->siguiente != NULL){
            aux2 = aux1;
            if((aux1->siguiente)->Nombre_de_estacion == referencia){
                aux2 = aux2->siguiente;
                aux1->siguiente= aux2->siguiente;
                delete aux2;
            }

            aux1= aux1->siguiente;
        }
}

void recorridoestaciones(estaciones *& cabeza_estac) {
    estaciones *aux1;
    aux1 = cabeza_estac;
    if(cabeza_estac != nullptr){
        cout << "Caracteristicas de las estaciones:"<< endl;
        cout << "Nombre de la estacion:"<< aux1->Nombre_de_estacion << endl;
        cout << "Cantidad de zombies en estacion:" << aux1->cantidadzombies << endl;
        cout<< endl;
        recorridoestaciones(aux1->siguiente);
    }
}

estaciones* CrearlistaEstacion(){
    estaciones *lista_estaciones= NULL;

    for (int i = 0; i < 3; i++)
    {
        agregar_estacion("plazavenezuela", 20 ,lista_estaciones);
    }
    return lista_estaciones;
}



//Opcion que desea cambiar
//El numero 1 para cambiar cantidad de zombies
//el numero 2 para cambiar nombre

//  editarestacion(NOMBRE DE REFERENCIA, LISTA A CAMBIAR, OPCION A ESCOGER A CAMBIAR, CANTIDAD DE ZOMBIES QUE DESEAS PONER, NUEVO NOMBRE QUE DESEAS PONER)

// si no quieres agregar nombre pones ""
// si no quieres agregar zombies pones NULL
// NO SE PUEDEN PONER LOS 2 AL MISMO TIEMPO

void editarestacion(string referencia, estaciones*& cabeza_estac, int var_cambio_opcion, int cantidad_zombie_acamb, string nombre_a_cambiar){
    estaciones*aux1 = cabeza_estac;

    if (var_cambio_opcion>0 && var_cambio_opcion<3){

        if (var_cambio_opcion == 1 && cantidad_zombie_acamb){

            while (aux1 != NULL){
            
            if(aux1->Nombre_de_estacion == referencia){
                aux1->cantidadzombies = cantidad_zombie_acamb;
            }
            aux1= aux1->siguiente;
        }
        }

        if (var_cambio_opcion == 2 && !nombre_a_cambiar.empty()){

            while (aux1 != NULL){
            if(aux1->Nombre_de_estacion == referencia){
                aux1->Nombre_de_estacion = nombre_a_cambiar;
            }
            aux1= aux1->siguiente;

        }
        }
    }
    else{
        cout << "indique una opcion valida valido" << endl;
    }
}







//____________________________________________ MENU _______________________________________//
void mostrarMenu(){
    cout<< RED << "Bienvenido a RUNNING DEAD [Demo] " << RESET << endl;
    cout<< BG_LGREEN << "======== MENU =========" << RESET << endl;
    cout << "1. Iniciar partida" <<endl;
    cout << "2. Crear "<< endl;
    cout << "3. Como jugar?" <<endl;
    cout << "4. Borrar datos." << endl;
    cout << "5. Salir" <<endl;
    cout << "-----------------------------------------" << endl;
}


// ---------------------------------------------- MAIN ------------------------------------ //
int main(){
    Soldado *primerSoldado = nullptr;
    Accesorios *primeraccesorio = nullptr;
    Mochila *primeraMochila = nullptr;
    estaciones *cabezaestacion= nullptr;
    Zombie *cabezazombie= nullptr;
   
    // insertarAccesorioUltimo(&primeraccesorio, "gasas", "Supervivencia", 1, 10);
    // insertarAccesorioUltimo(&primeraccesorio, "AK-47" , "ataque", 30, 10);
    // insertarAccesorioUltimo(&primeraccesorio, "escudo", "Defense ", 1, 10);
    // //mostrarAccesorios(primeraccesorio);


    // insertarUltimaMochila(&primeraMochila, "Juan", 0);
    // insertarUltimaMochila(&primeraMochila, "Roberto", 0);
    // insertarUltimaMochila(&primeraMochila, "Luis", 0);
    // //mostrarMochilas(primeraMochila);
   
    // insertarUltimoSoldado(&primerSoldado, "Juan",        100, primeraMochila);
    // insertarUltimoSoldado(&primerSoldado,  "Roberto",   0, primeraMochila);
    // insertarUltimoSoldado(&primerSoldado, "Luis",        0, primeraMochila);
    // mostrarJugador(primerSoldado);


    // MeterAccesorioEnMochilaDelJugador(primerSoldado, primeraMochila, "Juan", "gasa", "Supervivnecia ", 1, 10);
    // MeterAccesorioEnMochilaDelJugador(primerSoldado,primeraMochila,  "Roberto", "AK-47", "Ataque ", 1, 10);
    // MeterAccesorioEnMochilaDelJugador(primerSoldado,primeraMochila, "juan", "Escudo", "Defensa ", 1, 10);


   
    // mostrarUnaMochila(primeraMochila, "juan");


    // mostrarMochilas(primeraMochila);


    //srand(time(0));
    // Zombie* lista_zombie = CrearTropaZombie();
    // recorridozombies(lista_zombie);
    // cout << endl;
    // cout << calculador(lista_zombie) << endl;


    int opcion;
    do {
        mostrarMenu();
            cout<< "Selecciona una opcion: ";
            cin>> opcion;
            switch(opcion){
                case 1:
                    break;


                case 2:
                    {int opc3;
                    string name;
                    string weapon;
                    string estaciones_nombres;
                    int estaciones_cantidad_zombie;
                    int health;
                    int damage;
                    cout<< RED << "Bienvenido a RUNNING DEAD [Demo] " << RESET << endl;
                        cout<< BG_LGREEN << "======== ¿Que deseas crear? =========" << RESET << endl;
                        cout << "1. Soldado " <<endl;
                        cout << "2. Zombie caracteristicas"<< endl;
                        cout << "3. Accesorio" <<endl;
                        cout << "4. Estaciones" <<endl;
                        cout << "5. Salir" <<endl;
                        cout << "-----------------------------------------" << endl;
                        cin >> opc3;
                    switch(opc3){
                        case 1:
                            cout << "Indique como se llama el soldado:" << endl;
                            cin >> name;
                            fflush(stdin);
                            cout << "Indique la vida en números del soldado:" << endl;
                            cin >> health;
                            fflush(stdin);
                            if(health <50 || health > 100 ){
                                cout << "El numero de salud no esta en el rango aceptado." << endl;
                                cout << "Por favor ponle un numero entre 50 y 100: " << endl;
                                cin >> health;
                            }
                            insertarUltimoSoldado(&primerSoldado,name,health,primeraMochila);
                            cout << "Soldado creado con exito!! " << endl;
                            system("cls");
                            cout << "Regresando al menú principal." << endl;
                            system("cls");
                            break;
                        case 2:
                            cabezazombie = CrearTropaZombie(10);
                            cout << "caracteristicas 10 zombies" << endl;
                            recorridozombies(cabezazombie);
                            //nota falta conexion cantidad por estacion y crear tropa
                            break;
                        case 3:
                            break;
                        case 4:
                            cout << "Indique como se llama la estacion sin espacio:" << endl;
                            cin >> estaciones_nombres;
                            cout << "Indique la cantidad de zombies:" << endl;
                            cin >> estaciones_cantidad_zombie;
                            fflush(stdin);
                            agregar_estacion(estaciones_nombres,estaciones_cantidad_zombie, cabezaestacion);

                            cout << "sus estaciones son:" << endl;
                            recorridoestaciones(cabezaestacion);
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
                                break;
                            case 2:
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
                                break;
                            case 3:
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
                    cout << BG_LGREEN << "Vuelva pronto!!!" << RESET << endl;
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