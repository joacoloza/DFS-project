#ifndef GRAFO_H_
#define GRAFO_H_
#include <list>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include "iostream"

using namespace std;

template <typename C> class Grafo
{
public:
	class Arco
	{
	public:
		Arco();
		Arco(int adyacente, const C & costo);
		int devolver_adyacente() const;
		const C & devolver_costo_arco() const;
	private:
		int vertice;
		C costo;
	}; // class Arco

public:
	// NOTA: Dependiendo de la implementación puede ser necesario incluir otras funciones constructuras
	Grafo();
	Grafo(const Grafo & otroGrafo);

	~Grafo();

	Grafo & operator = (const Grafo & otroGrafo);

	// Devuelve true si la cantidad de vértices es cero
	bool esta_vacio() const;//listo

	// Indica la cantidad de vértices del grafo
	int devolver_longitud() const;//listo

	bool existe_vertice(int vertice) const;//listo

	bool existe_arco(int origen, int destino) const;//listo

	// PRE CONDICION: existe_arco(origen, destino)
	const C & costo_arco(int origen, int destino) const;

	void devolver_vertices(list<int> & vertices) const;

	void devolver_adyacentes(int origen, list<Arco> & adyacentes) const;//listo

	void agregar_vertice(int vertice);//listo

	// POST CONDICION: Para todo vértice v != vertice: !existeArco(v, vertice) && !existeArco(vertice, v)
	void eliminar_vertice(int vertice);

	// PRE CONDICION: existeArco(origen, destino)
	void modificar_costo_arco(int origen, int destino, const C & costo);

	// PRE CONDICION: existeVertice(origen) && existeVertice(destino)
	// POST CONDICION: existeArco(origen, destino)
	void aggArco(int origen, int destino, const C & costo);

	// POST CONDICION: !existeArco(origen, destino)
	void eliminar_arco(int origen, int destino);
    void eliminar_all_arcos(int vertice);

	void vaciar();
    void mostrar_grafo();
    void dfs_forest(list<int> & orden_dfs) const;
    void dfs(int origen, set<int> & visitados, list<int> & orden_dfs) const;


private:
	/*
	 * Definir la estructura interna
	 */
	// map<int,list<Arco>>_grafo;
	 map<int,map<int,C>>_mapa;

}; // class Grafo


/*
 * Arco
 */

template <typename C> Grafo<C>::Arco::Arco()
{

}

template <typename C> Grafo<C>::Arco::Arco(int adyacente, const C & costo)
{
    this->vertice=adyacente;
    this->costo=costo;
}

template <typename C> int Grafo<C>::Arco::devolver_adyacente() const
{
    return this->vertice;

}

template <typename C> const C & Grafo<C>::Arco::devolver_costo_arco() const
{
    return this->costo;
}


/*
 * Grafo
 */

template <typename C> Grafo<C>::Grafo()
{
}

template <typename C> Grafo<C>::Grafo(const Grafo & otroGrafo)
{

}

template <typename C> Grafo<C>::~Grafo()
{

}

template <typename C> Grafo<C> & Grafo<C>::operator = (const Grafo & otroGrafo)
{

    return *this;
}

template <typename C> bool Grafo<C>::esta_vacio() const
{   /*//ml
    bool vacio=_grafo.empty();
    return vacio;*/
    //mm
    bool vacio=_mapa.empty();
    return vacio;
}

template <typename C> int Grafo<C>::devolver_longitud() const
{
    //con lista
    /*int longitud=0;
    list<Arco> lista;
    typename map<int,list<Arco>>:: const_iterator iterador=_grafo.begin();

    while (iterador != _grafo.end()){
        longitud++;
        iterador++;
    }
    return longitud;*/
    //tambien se puede hacer asi calculo y serviria para mapa de mapa y para lista de lista
    //int longitud=_grafo.size();
    int longitud = _mapa.size();
    return longitud;
}

template <typename C> void Grafo<C>::mostrar_grafo(){
    //ml
    /*if (this->esta_vacio()==false){
        typename map<int,list<Arco>>:: const_iterator iterador_map=_grafo.begin();
        typename list<Arco>:: const_iterator it=iterador_map->second.begin();
        int numero_vertice=1;

        while(iterador_map != _grafo.end()){

            typename list<Arco>:: const_iterator iterador_list=iterador_map->second.begin();
            std::cout<<"los adyacentes al vertice "<<numero_vertice<<":"<<endl;
            iterador_map;
            while(iterador_list != iterador_map->second.end()){
                std::cout<<"-->"<<iterador_list->devolver_adyacente()<<endl;
                iterador_list++;
            }
            cout<<"                                      "<<endl;
            iterador_map++;
            numero_vertice++;
        }
    }
    else cout<<"grafo vacio"<<endl;*/
    //mm
    if(this->esta_vacio()==false){
        list <int> vertices;
        devolver_vertices(vertices);
        auto v=vertices.begin();
        while(v!= vertices.end()){
            list <Arco> adyacentes;
            devolver_adyacentes(*v, adyacentes);
            auto a=adyacentes.begin();
            while (a!=adyacentes.end()){
                cout<<"("<<*v<<","<< a->devolver_adyacente()<<","<<a->devolver_costo_arco()<<")"<<endl;
                a++;
            }
            v++;
        }
    }
    else cout<<"el grafo no existe"<<endl;
}

template <typename C> bool Grafo<C>::existe_vertice(int vertice) const
{   //ml
    /*bool encontrado=false;
    //solucion para mapa de listas y para mapa de mapas
    if (_grafo.find(vertice)!=_grafo.end()){
        encontrado=true;
    }
    return encontrado;*/
    //mm
    bool existe=false;
    if(_mapa.find(vertice)!=_mapa.end()){existe=true;}
    return existe;
}

template <typename C> bool Grafo<C>::existe_arco(int origen, int destino) const
{
    //con lista
    /*bool encontrado=false;
    typename map<int,list<Arco>>:: const_iterator iterador=_grafo.find(origen);

    if(iterador!=_grafo.end()){
        typename list<Arco>:: const_iterator it=iterador->second.begin();
        while(!encontrado && it!=iterador->second.end()){
            if(it->devolver_adyacente()==destino){encontrado=true;}
            it++;
            }
    }
    return encontrado;*/

   //con mapa
    bool encontrado=false;
    typename map<int,map<int,C>>:: const_iterator iterador=_mapa.find(origen);
    if(iterador!=_mapa.end()){
        auto it=iterador->second.find(destino);
        if(it != iterador->second.end())encontrado=true;
    }
    return encontrado;
}

template <typename C> const C & Grafo<C>::costo_arco(int origen, int destino) const
{   //ml
    /*if(this->existe_arco(origen,destino)){
        std::cout<<"el costo del arco es"<<endl;
        bool encontrado=false;
        auto iterador_map=_grafo.find(origen);
        auto iterador_lista=iterador_map->second.begin();
        while(!encontrado && iterador_lista!=iterador_map->second.end()){
            iterador_lista++;
            if(iterador_lista->devolver_adyacente()==destino){encontrado=true;}
        }
        std::cout<<iterador_lista->devolver_costo_arco()<<endl;
    }*/
    //mm
    if(this->existe_arco(origen,destino)){
        cout<<"el costo del arco es"<<endl;
        auto it1=_mapa.find(origen);
        auto it2=it1->second.find(destino);
        cout<<it2->second<<endl;
    }
}

template <typename C> void Grafo<C>::devolver_vertices(list<int> & vertices) const
{
    //ml
    /*auto iterador_map=_grafo.begin();
    while(iterador_map != _grafo.end()){
        vertices.push_back(iterador_map->first);
        iterador_map++;
    }*/
    //mm
    auto it_map=_mapa.begin();
    while(it_map!=_mapa.end()){
        vertices.push_back(it_map->first);
        it_map++;
    }
}

template <typename C> void Grafo<C>::devolver_adyacentes(int origen , list<Arco> & adyacentes) const
{
    //con lista
    /*typename map<int,list<Arco>>:: const_iterator iterador=_grafo.find(origen);

    if(iterador != _grafo.end()){//te fijas si existe
        typename list<Arco>:: const_iterator it=iterador->second.begin();//te metes a la lista

        while (it!=iterador->second.end()){
            adyacentes.push_back(*it); //preguntar si esta bien pasar it
            it++;
        }
    }*/


    auto it = this->_mapa.find(origen);
    if(it != this->_mapa.end()){
        auto it2 = it->second.begin();
        while(it2 != it->second.end()){
            adyacentes.push_back(Arco(it2->first,it2->second));
            it2++;
        }
    }


}

template <typename C> void Grafo<C>::agregar_vertice(int vertice)
{
    //con mapa de lista
    /*list<Arco> lista;//creo lista

    if(_grafo.find(vertice)==_grafo.end()){
        _grafo.emplace(vertice,lista);//1
        _grafo[vertice]=lista;//2 preguntar si 1 o 2 estan bien
    }
    else{cout<<"ya existe elemento"<<endl;*/

    //con mapa de mapa
    map<int,C> mapa;
    _mapa.emplace(vertice,mapa);
}

template <typename C> void Grafo<C>::eliminar_all_arcos(int vertice)
{   //ml
    /*auto iterador_map=_grafo.begin();
    while(iterador_map != _grafo.end()){
        this->eliminar_arco(iterador_map->first,vertice);
       // vertice_origen++;
        iterador_map++;
    }*/
    //mm
    auto it_map=_mapa.begin();
    int vertice_origen;
    while(it_map != _mapa.end()){
        this->eliminar_arco(it_map->first,vertice);
        it_map++;
    }
}

template <typename C> void Grafo<C>::eliminar_vertice(int vertice)
{
    //ml
    /*if(this->existe_vertice(vertice)==true){
        this->eliminar_all_arcos(vertice);
        _grafo.erase(vertice);
    }*/
    //mm
    if(this->existe_vertice(vertice)==true){
        this->eliminar_all_arcos(vertice);
        _mapa.erase(vertice); //tendria todo eliminado bien ?
    }
}

template <typename C> void Grafo<C>::modificar_costo_arco(int origen, int destino, const C & costo)
{   //ml
    /*if(this->existe_arco(origen,destino)){
        auto iterador_map=_grafo.find(origen);
        auto iterador_list= iterador_map->second.begin();
        while (iterador_list->devolver_adyacente()!= destino){
            iterador_list++;
        }
        iterador_map->second.erase(iterador_list);
        this->agregar_arco(origen,destino,costo);
    }*/
    //mm
    if(this->existe_arco(origen,destino)){
        auto iterador_map=_mapa.find(origen);
        auto it2= iterador_map->second.find(destino);
        _mapa.find(origen)->second.erase(it2);
        this->agregar_arco(origen,destino,costo);

    }

}
template <typename C> void Grafo<C>::aggArco(int origen, int destino, const C & costo)
{
    //ml
    /*//compruebo que existan los vertices
    //if ((_grafo.find(origen)!=_grafo.end())&&(_grafo.find(destino)!=_grafo.end())){
    if ((this->existe_vertice(origen))&&(this->existe_vertice(destino))){
        if(!this->existe_arco(origen,destino)){
            typename map<int,list<Arco>>:: iterator iterador=_grafo.find(origen);
            typename list<Arco>:: iterator it=iterador->second.begin();//te metes a la lista
            Arco arco(destino,costo);
            _grafo.find(origen)->second.push_back(arco);
        }
    }*/
    //mm
    if((_mapa.find(origen)!=_mapa.end())&&(_mapa.find(destino)!=_mapa.end())){
        typename map<int,map<int,C>>:: iterator it_map=_mapa.find(origen);
        it_map->second.insert(pair<int,C>(destino,costo));
    }
}

template <typename C> void Grafo<C>::eliminar_arco(int origen, int destino){
    //ml
    /*if(this->existe_arco(origen,destino)){
        auto iterador_map=_grafo.find(origen);
        auto iterador_list= iterador_map->second.begin();
        while (iterador_list->devolver_adyacente()!= destino){
            iterador_list++;
        }
        _grafo.find(origen)->second.erase(iterador_list);
    }*/
    //mm
    if(this->existe_arco(origen,destino)){
        auto iterador_map=_mapa.find(origen);
        auto it2=iterador_map->second.find(destino);
       _mapa.find(origen)->second.erase(it2);
    }
}

template <typename C> void Grafo<C>::vaciar()
{   //ml
    /*auto it_map=_grafo.begin();
    int vertice=0;
    while(it_map!=_grafo.end()){
        this->eliminar_vertice(vertice);
        vertice++;
        it_map++;
    }
    cout<<"grafo eliminado con exito"<<endl;*/

    //mm
    auto it_map=_mapa.begin();
    while(it_map!=_mapa.end()){
        it_map->second.clear();
        it_map++;
    }
    _mapa.clear();
    cout<<"grafo eliminado con exito"<<endl;
}
template <typename C> void Grafo<C>::dfs_forest(list<int> & orden_dfs) const
{
    //ml
    /*set<int> visitados;
    auto it_map=_grafo.begin();
    while(it_map !=_grafo.end()){
        dfs(it_map->first,visitados,orden_dfs);
        orden_dfs.push_back(-1);
        it_map++;
    }*/
    //mm
    set<int> visitados;
    auto it_map=_mapa.begin();
    while(it_map != _mapa.end()){
        dfs(it_map->first,visitados,orden_dfs);
        orden_dfs.push_back(-1);
        it_map++;
    }
}

template <typename C> void Grafo<C>::dfs(int origen, set<int> & visitados, list<int> & orden_dfs) const
{   //ml
    /*visitados.insert(origen);
    orden_dfs.push_back(origen);
    list <Grafo::Arco> lista_ady;   //creo lista
    devolver_adyacentes(origen,lista_ady);//agarro los adyacentes
    auto it_list=lista_ady.begin();//iterador para poder recorrer
    while(it_list != lista_ady.end() ){ //for each
        if(visitados.find(it_list->devolver_adyacente()) == visitados.end()){ //si marca blanco
            dfs(it_list->devolver_adyacente(),visitados,orden_dfs);
        }
        it_list++;
    }*/
    //mm
    visitados.insert(origen);
    orden_dfs.push_back(origen);
    list <Arco> lista_ady;
    devolver_adyacentes(origen,lista_ady);
    auto it_list= lista_ady.begin();
    while (it_list != lista_ady.end()){
        if(visitados.find(it_list->devolver_adyacente())== visitados.end()){
            dfs(it_list->devolver_adyacente(),visitados,orden_dfs);
        }
        it_list++;
    }

}

/*Grafo(const Grafo & otroGrafo){
    //con mapa de lista
    typename map<int,list>:: iterator iterador=_grafo.find();
}*/
#endif /* GRAFO_H_ */
