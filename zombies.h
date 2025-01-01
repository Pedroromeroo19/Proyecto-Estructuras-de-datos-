#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct zombies
{   
    //Nodo con datos de zombie
    struct Zombie{
        string Nombre_del_zombie; 
        int fortaleza;
        int Danno; 
        Zombie *next;
    };

    //Lista interna dentro de el struct zombie que esta hecho de nodos de zombie
    Zombie* cabeza = NULL;

    //Manejo del tamaño de la lista
    int size = 0;

    // Completando el crud se presentan las siguientes funciones

    //___________________________________________________Funcion agregar (Create)_________________________________________________
    void Agregar_Random(int posicion){
        if (posicion>size){
            cout << "Error : Se puso una posicion mayor al tamaño de la lista" << endl;
            return;
        }
        if ((posicion == -1)or(posicion==size)){ //caso agregar ultimo
            Agregar_Ultimo(cabeza); // Parametro puntero cabeza de lista interna
            size = size + 1 ; // Al agregar nodo incrementa el tamaño de lista
        }
        if (posicion == 0){ //caso agregar primero
            Agregar_Al_final(cabeza); // Parametro puntero cabeza de lista interna
            size = size + 1 ;
        }
        if (posicion>0 && posicion<size){ //caso agregar en el medio
            Agregar_Medio(posicion , cabeza, size); // Parametro puntero cabeza de lista interna, posicion especifica y tamaño de lista
            size = size + 1 ;
        }
    }
    
    void agregar_espec_zombies(int posicion, string  nombre, int fortaleza, int danio ){
        if (posicion>size){
            cout << "Error : Se puso una posicion mayor al tamaño de la lista" << endl;
            return;
        }
        if ((posicion == -1)or(posicion==size)){ //caso agregar ultimo
            Agregar_Ultimo_especifico(nombre,fortaleza, danio, cabeza);
            size = size + 1 ;
        }
        if (posicion == 0){ //caso agregar primero
            Agregar_Al_final_especifico(nombre,fortaleza, danio, cabeza);
            size = size + 1 ;
        }
        if (posicion>0 && posicion<size){ //caso agregar en el medio
            Agregar_Medio_especifico(nombre,fortaleza, danio, posicion , cabeza, size);
            size = size + 1 ;
        }
    }
    
    //Por hacer
    void agregarlistref(){

    }

    //_________________________________________________________Funcion lear (read)________________________________________________
    void leer_lista_zombies(){
        Zombie* aux1 = cabeza;
        int valor_pos = size;
        while (aux1 != NULL){
            cout << "Posicion: "<< valor_pos << endl;
            valor_pos=valor_pos-1;
            cout << "Caracteristicas de los Zombies:"<< endl;
            cout << "Nombre del zombie: "<< aux1->Nombre_del_zombie << endl;
            cout << "Numero de daño: "<< aux1->Danno << endl;
            cout << "fortaleza: " << aux1->fortaleza << endl;
            cout << endl;
            aux1= aux1->next;
        }
    }

    //_____________________________________________________Funcion modificar (Update)___________________________________________________
    void modificar_list_zombie(int posicion, string  nombre, int fortaleza, int danio){        
        if (posicion>size){
            cout << "Error : Se puso una posicion mayor al tamaño de la lista" << endl;
            return;
        }
        if (nombre != ""){
            modificar_nombre(nombre,posicion,cabeza, size);
        }
        if (fortaleza != 0){
            modificar_fortaleza(fortaleza,posicion,cabeza, size);
        }
        if (danio != 0){
            modificar_danio(danio, posicion, cabeza, size);
        }

    }

    //_____________________________________________________Funcion eliminar (Delete)_____________________________________________
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


    //Por hacer
    void eliminarlistref(){

    }

    void eliminar_lista_zombie(Zombie*& cabeza){
    if(!estavacia(cabeza)){

        Zombie *aux1 = cabeza;
        Zombie *aux2;

        while (cabeza != NULL)
        {
            aux2 = aux1;
            aux1 = aux1->next;
            delete aux2;
        }
        
    }

    /*Zombie* CrearTropaZombie(){
    Zombie *lista_zombie= NULL;

    for (int i = 0; i < 10; i++)
    {
        int randomnum = (rand() % 5);
        zombiestipo randomColor = static_cast<zombiestipo>(randomnum);

        agregar_zombie(randomColor,lista_zombie);
    }
    return lista_zombie;
}*/

  /*int calculador(Zombie *& cabeza){
    Zombie *aux1;
    aux1 = cabeza;
    int valor;
    while (aux1->siguiente != NULL){
            valor = valor + aux1->Danno;
            aux1= aux1->siguiente;
        }
    return valor;
    }*/
}

    // Se Usa el private para las subfunciones en cada caso y para crear una capa de abstraccion entre las funciones principales y las subfunciones para casos especificos 
    private:

    enum zombiestipo {zombierapidotipo = 0, zombietanquetipo = 1, zombieinteligentetipo = 2, zombiesconhongostipo = 3, zombieluminiscentetipo = 4};

//_______________________________________________Funciones Agregar random___________________________________________________________
    Zombie* declararennodo(zombiestipo tipo,Zombie *& nodo){

        string zombierapidonombre[] = {"Cuchillas retráctiles","Dash", "Adrenalina"};
        string zombietanquenombre[] = {"Puños reforzados con hueso", "Carga", "Escudo óseo"};
        string zombieinteligentenombre[] = {"Proyectiles biológicos","Mimetismo", "Control mental"};
        string zombieconhongosnombre[] = {"Esporas venenosas", "Crecimiento acelerado", "Control de hongos"};
        string nombresFarmaciasnombre[] = {"Rayos de energía","Curación", "Ceguera"};

        //valor por ataque en el mismo orden (si es positivo suma la vida al zombie), si es negativo resta vida.

        int zombierapidodano[] = {-12, -15,-10};
        int zombietanquedano[] = {-10, -13, -11};
        int zombieinteligentedano[] = {-18,-5, -12};
        int zombieconhongosdano[] = {-3, -12, -10};
        int nombresFarmaciasdano[] = {-16,-15, -12};

            int randomnum = (rand() % 3);

        zombiestipo opciones = tipo;

        switch(opciones){

        case  zombierapidotipo:
            nodo->Nombre_del_zombie = "zombie rapido";
            nodo->Danno = zombierapidodano[randomnum];
            nodo->fortaleza=110;
            return nodo;
        break;

        case zombietanquetipo:
            nodo->Nombre_del_zombie="zombie tanque";
            nodo->Danno = zombietanquedano[randomnum];
            nodo->fortaleza=150;
            return nodo;
        break;

        case zombieinteligentetipo:
            nodo->Nombre_del_zombie="zombie inteligente";
            nodo->Danno = zombieinteligentedano[randomnum];
            nodo->fortaleza=80;
            return nodo;
        break;

        case zombiesconhongostipo:
            nodo->Nombre_del_zombie="zombies con hongos";
            nodo->Danno = zombieconhongosdano[randomnum];
            nodo->fortaleza=90;
            return nodo;
        break;

        case zombieluminiscentetipo:
            nodo->Nombre_del_zombie="zombie luminiscente";
            nodo->Danno = nombresFarmaciasdano[randomnum];
            nodo->fortaleza=120;
            return nodo;
        break;


        }
        return 0;
    }

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

    void Agregar_Ultimo(Zombie *& cabeza){
        //Nodo que entra en la funcion random 
        Zombie* primernodo = new Zombie();

        // Creacion tipo de zombie random
        int randomnum = (rand() % 5);
        zombiestipo zombierandom = static_cast<zombiestipo>(randomnum);

        //Funcion que declara los datos de el nodo
        Zombie* nuevoZombie = declararennodo(zombierandom,primernodo);


        if (estavacia(cabeza)){
            nuevoZombie->next= NULL;
        }

        if (!estavacia(cabeza)){
            nuevoZombie->next= cabeza;
        }

        cabeza = nuevoZombie;
    }

    void Agregar_Al_final(Zombie *& cabeza){
        //Nodo que entra en la funcion random 
        Zombie* primernodo = new Zombie();

        // Creacion tipo de zombie random
        int randomnum = (rand() % 5);
        zombiestipo zombierandom = static_cast<zombiestipo>(randomnum);

        //Funcion que declara los datos de el nodo
        Zombie* nuevoZombie = declararennodo(zombierandom,primernodo);

        Zombie *aux1= cabeza->next;
        Zombie *aux2= cabeza;
        while (aux1 != NULL){
            aux1= aux1->next;
            aux2= aux2->next;
            if (aux1 == NULL){
                nuevoZombie->next= aux1;
                aux2->next=nuevoZombie;
            }
        }
    }

    void Agregar_Medio(int posicion,Zombie *& cabeza,int tamano){
        //Nodo que entra en la funcion random 
        Zombie* primernodo = new Zombie();

        // Creacion tipo de zombie random
        int randomnum = (rand() % 5);
        zombiestipo zombierandom = static_cast<zombiestipo>(randomnum);

        //Funcion que declara los datos de el nodo
        Zombie* nuevoZombie = declararennodo(zombierandom,primernodo);
        
        Zombie *aux1= cabeza->next;
        Zombie *aux2= cabeza;

        int avanze= tamano - posicion;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
            aux2= aux2->next;
        }
        nuevoZombie->next = aux1;
        aux2->next= nuevoZombie;
    }

//_______________________________________________________Agregar Especifico_______________________________________________________

    void Agregar_Ultimo_especifico(string  nombre, int fortaleza, int danio,Zombie *& cabeza){
        Zombie* nuevoZombie = new Zombie();

        //Declaracion de datos
        nuevoZombie->Nombre_del_zombie = nombre;
        nuevoZombie->Danno = danio;
        nuevoZombie->fortaleza = fortaleza;

        if (estavacia(cabeza)){
            nuevoZombie->next= NULL;
        }

        if (!estavacia(cabeza)){
            nuevoZombie->next= cabeza;
        }

        cabeza = nuevoZombie;
    }

    void Agregar_Al_final_especifico(string  nombre, int fortaleza, int danio,Zombie *& cabeza){
        Zombie* nuevoZombie = new Zombie();

        //Declaracion de datos
        nuevoZombie->Nombre_del_zombie = nombre;
        nuevoZombie->Danno = danio;
        nuevoZombie->fortaleza = fortaleza;

        Zombie *aux1= cabeza->next;
        Zombie *aux2= cabeza;
        while (aux1 != NULL){
            aux1= aux1->next;
            aux2= aux2->next;
            if (aux1 == NULL){
                nuevoZombie->next= aux1;
                aux2->next=nuevoZombie;
            }
        }
    }

    void Agregar_Medio_especifico(string  nombre, int fortaleza, int danio,int posicion,Zombie *& cabeza,int tamano){
        Zombie* nuevoZombie = new Zombie();

        //Declaracion de datos
        nuevoZombie->Nombre_del_zombie = nombre;
        nuevoZombie->Danno = danio;
        nuevoZombie->fortaleza = fortaleza;

        Zombie *aux1= cabeza->next;
        Zombie *aux2= cabeza;
        int avanze= tamano - posicion;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
            aux2= aux2->next;
        }
        nuevoZombie->next = aux1;
        aux2->next= nuevoZombie;
    }



//_______________________________________________________funciones eliminar________________________________________________
    void Eliminar_Ultimo(Zombie *& cabeza){
        Zombie *aux1 = cabeza->next;
        Zombie *aux2 = cabeza;
        cabeza= aux1;
        delete aux2;
    }

    void eliminar_medio(int posicion, Zombie *& cabeza, int tamano){
        Zombie *aux1 = cabeza->next;
        Zombie *aux2 = cabeza;
        int avanze= tamano - posicion - 1;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
            aux2= aux2->next;
        }
        aux2->next = aux1->next;
        delete aux1;
    }

    void eliminar_al_final(Zombie *& cabeza){
        Zombie *aux1= cabeza->next;
        Zombie *aux2= cabeza;
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

    void modificar_nombre(string  nombre,int posicion, Zombie *& cabeza, int tamano){
        Zombie *aux1 = cabeza;
        int avanze= tamano - posicion;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
        }
        aux1->Nombre_del_zombie = nombre;
    }

    void modificar_fortaleza(int  fortaleza,int posicion, Zombie *& cabeza, int tamano){
        Zombie *aux1 = cabeza;
        int avanze= tamano - posicion;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
        }
        aux1->fortaleza = fortaleza;
    }

    void modificar_danio(int  Danio,int posicion, Zombie *& cabeza, int tamano){
        Zombie *aux1 = cabeza;
        int avanze= tamano - posicion;
        for (int i=0;i<avanze;i++){
            aux1= aux1->next;
        }
        aux1->Danno = Danio;
    }

//___________________________________________funcion para saber si esta vacia______________________________________________
    bool estavacia(Zombie *& p){
        return p == nullptr;
    }
};
