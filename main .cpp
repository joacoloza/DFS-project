#include <iostream>
#include <list>
#include <set>
#include <map>
#include <stack>
#include "grafo.h"
#include "arco.h"
#include "auxiliares.h"

bool existeCaminoDfs(grafo<int> & g,int origen,int destino,std::list<int> & camino,std::set <int> & visitados,std::map<int,int> & colores){ //modificacion de un dfs con condicionales extra

    if(colores.at(origen) == rojo) return false; //importante!: no cambiar el orden de estas verificaciones o da true cuando el destino es rojo!!
    if(origen == destino){ camino.push_front(origen);return true;}

    //clear lista ady cuando implemente lo otro
    std::list<arco<int>> ady; //pasar una lista vacia desde afuera asi usa la misma en la recursividad y no crea una por cada llamado
    int siguiente;
    visitados.insert(origen);
    g.adyacentesA(origen,ady);
    auto it = ady.begin();

    while(it != ady.end()){
        siguiente = it->adyacente();
        if(visitados.find(siguiente) == visitados.end()){ //si el sig no está visitado recorro
            if(existeCaminoDfs(g,siguiente,destino,camino,visitados,colores)){
                camino.push_front(origen);
                return true;
            }
        }
        it++;
    }
    return false;
}

bool existeCaminoDfsIterativo(grafo<int> & g,int origen,int destino,std::list<int> & camino,std::set <int> & visitados,std::map<int,int> & colores){ //modificacion de un dfs con condicionales extra
    if (colores.at(origen) == rojo) return false;
    std::stack<int> pila;
    std::map<int, int> padres;
    pila.push(origen);
    padres[origen] = -1;
    while (!pila.empty()) {
        int actual = pila.top();
        pila.pop();
        visitados.insert(actual);
        if (actual == destino) {
            camino.push_front(destino);
            while (padres[destino] != -1) { // backtracking - aca se puede usar el mismo recuperar camino que arme para el bfs
                camino.push_front(padres[destino]);
                destino = padres[destino];
            }
            return true;
        }
        std::list<arco<int>> ady; // get ady
        g.adyacentesA(actual, ady);
        for (auto it = ady.begin(); it != ady.end(); ++it) {
            int siguiente = it->adyacente();
            if (visitados.find(siguiente) == visitados.end() && colores.at(siguiente) != rojo) {
                pila.push(siguiente);
                padres[siguiente] = actual;
            }
        }
    }
    return false;
}


void recuperarCaminoBfs(std::list<int> & camino,std::map<int,int> & padres, int n, int origen){
    camino.clear();
    camino.push_front(n);
    while(n != origen){
        n = padres[n];
        camino.push_front(n);
    }

}

bool existeCaminoBfs(grafo<int> & g,int origen,int destino,std::list<int> & camino,std::map<int,int> & colores){

    if(colores.at(origen) == rojo) return false;
    if(origen == destino){camino.push_front(origen); return true;}

    std::set <int> visitados;
    std::list<arco<int>> ady;
    std::map<int,int> padres;
    bool buscando = true; //para cortar si lo encuentra ya que solo interesa saber si hay un camino no encontrar todos ni el mejor
    int inicial = origen;
    camino.push_back(origen);
    visitados.insert(origen);

    while(!camino.empty() && buscando){
        origen = camino.front();
        camino.pop_front();
        ady.clear();
        g.adyacentesA(origen,ady);
        auto it = ady.begin();
        while(it != ady.end() && buscando){
            if(visitados.find(it->adyacente()) == visitados.end() && colores.at(it->adyacente()) != rojo){
                visitados.insert(it->adyacente());
                camino.push_back(it->adyacente());
                padres[it->adyacente()]=origen;
                if(it->adyacente() == destino){
                    buscando = false;
                }
            }
            //agregar else if == a destino y ademas rojo que corte, como funciona ahroa si es rojo no lo analiza y por ahi sigue buscando sin sentido
            //buscando = (!(colores.at(it->adyacente()) != rojo && it->adyacente() == destino))
            it++;
        }
    }
    //dejar el clear aca?? para que si no encontró devuelva un camino vacio
    //se puede manejar desde afuera ya q retorna un boolean pero quizá seria mejor tambien hacerlo acá
    if(!buscando) recuperarCaminoBfs(camino,padres,destino,inicial);
    return !buscando;
}

bool existeCamino(grafo<int> & g, int origen, int destino,std::list<int> & camino,std::map<int,int> & colorinches){ //agregar opcion para elegir dfs o bfs?

    //si se extiende la clase grafo para soportar colores esto se podria hacer adentro
    if(colorinches.find(destino) == colorinches.end()){
        std::cout<<"      Verificar que exista destino."<<std::endl;
        return false;
    } else if(colorinches.find(origen) == colorinches.end()){
        std::cout<<"      Verificar que exista origen."<<std::endl;
        return false;
    }

    std::set<int> visitados;
    bool dfs = existeCaminoDfs(g,origen,destino,camino,visitados,colorinches);
    std::cout<<"   |Por Dfs: "<<std::endl;
    if(dfs){
        printLista(camino);
    } else{
        std::cout<<"   |   No se encontró camino"<<std::endl;
    }

    camino.clear();
    visitados.clear();
    bool dfsIt = existeCaminoDfsIterativo(g,origen,destino,camino,visitados,colorinches);
    std::cout<<"   |Por Dfs Iterativo: "<<std::endl;
    if(dfsIt){
        printLista(camino);
    } else{
        std::cout<<"   |   No se encontró camino"<<std::endl;
    }

    camino.clear();
    bool bfs = existeCaminoBfs(g,origen,destino,camino,colorinches);
    std::cout<<"   |Por Bfs: "<<std::endl;
    if(bfs){
        printLista(camino);
    } else{
        std::cout<<"   |   No se encontró camino"<<std::endl;
    }
    camino.clear();

    return bfs&&dfs;
}

void pruebaPreCargada(){

    int origen = 1;
    int destino = 11;

    grafo<int> test;
    std::map<int,int> colorinches;
    std::list<int> camino;

    cargarVertices(test,1,13);
    cargarArcos(test);

    std::cout<<"================================================================================"<<std::endl;
    std::cout<<" Caso 0: existen origen["<<origen<<"] y destino["<<destino<<"], existe camino (no hay rojos)"<<std::endl;
    cargarColores(colorinches);
    existeCamino(test,origen,destino,camino,colorinches);

    std::cout<<"================================================================================"<<std::endl;
    std::cout<<" Caso 1: existen origen[1] y destino[13], no existe camino (no hay rojos)"<<std::endl; // no se si es posible con este grafo despues buscar
    existeCamino(test,1,13,camino,colorinches);

    std::cout<<"================================================================================"<<std::endl;
    std::cout<<" Caso 2: existen origen["<<origen<<"] y destino["<<destino<<"], existe camino, destino es rojo"<<std::endl;
    colorinches[destino] = rojo;
    existeCamino(test,origen,destino,camino,colorinches);
    colorinches[destino] = blanco;

    std::cout<<"================================================================================"<<std::endl;
    std::cout<<" Caso 3: existen origen["<<origen<<"] y destino["<<destino<<"], origen es rojo"<<std::endl;
    colorinches[origen] = rojo;
    existeCamino(test,origen,destino,camino,colorinches);
    colorinches[origen] = blanco;

    std::cout<<"================================================================================"<<std::endl;
    std::cout<<" Caso 4: existen origen["<<origen<<"] y destino["<<destino<<"], existe camino"<<std::endl;
    std::cout<<"   |---: mod de 0) uno de ese camino se marcó rojo [4-Bfs,7-Dfs]"<<std::endl;
    colorinches[4] = rojo;
    colorinches[7] = rojo;
    existeCamino(test,origen,destino,camino,colorinches);
    cargarColores(colorinches);

    std::cout<<"================================================================================"<<std::endl;
    std::cout<<" Caso 5: existen origen["<<origen<<"] y destino["<<destino<<"], no existe camino (a causa de rojos)"<<std::endl;
    aislarVertice(origen,colorinches,test);
    existeCamino(test,origen,destino,camino,colorinches);
    cargarColores(colorinches);

    std::cout<<"================================================================================"<<std::endl;
    std::cout<<" Caso 6: no existe origen[25]"<<std::endl;
    existeCamino(test,25,destino,camino,colorinches);

    std::cout<<"================================================================================"<<std::endl;
    std::cout<<" Caso 7: no existe destino[50]"<<std::endl;
    existeCamino(test,origen,50,camino,colorinches);
}

void ejercicio(){
    int opcion = 0;
    while(opcion != 2){
        std::cout<<"================================================================================"<<std::endl;
        std::cout<<"   0) Probar casos pre-cargados mostrados en el informe"<<std::endl;
        std::cout<<"   1) Crear un grafo desde 0"<<std::endl; //aca hay que preguntar lo de si se puede hacer un return de bool en algunos metodos asi no tirar el assert
        std::cout<<"   2) Salir"<<std::endl;
        std::cout<<"   Ingrese Opcion: ";
        std::cin>>opcion;
        if(opcion == 0) pruebaPreCargada();
        else if(opcion == 1) std::cout<<"op1- hacer"<<std::endl;
    }
}

int main(){

    ejercicio();
    return 0;
}
