#include "RedSocial.h"

using namespace std;

RedSocial::RedSocial(){ // O(1)
    _usuarios = map<int, Usuario>();
    _conjunto_ids = set<int>();
    _cantidad_amistades = 0;
    _usuario_mas_popular;
}

const set<int> & RedSocial::usuarios() const{ // O(1)
    return _conjunto_ids;
}

string RedSocial::obtener_alias(int id) const{ //O(logn)
    return _usuarios.at(id)._alias; 
}

const set<string> & RedSocial::obtener_amigos(int id) const{ //O(logn)
    return _usuarios.at(id)._conjunto_amigos; 
}

int RedSocial::cantidad_amistades() const{ // O(1)
    return _cantidad_amistades;
}

void RedSocial::registrar_usuario(string alias, int id){ // O(log n)
    Usuario nuevo_usuario {alias, {}};
    _usuarios.insert({id, nuevo_usuario});
    _conjunto_ids.insert(id);

    // si hay un único usuario, ese es el más popular
    if(_usuarios.size() == 1) {
        _usuario_mas_popular = _usuarios.begin();
    }
}

void RedSocial::eliminar_usuario(int id){ // O(n) con n = cantidad de amigos de usuario a eliminar
    auto it = obtener_amigos(id).begin();
    while(it != obtener_amigos(id).end()) {
        int id_amigo = obtener_id(*it);
        ++it;
        desamigar_usuarios(id, id_amigo);
    }

    _usuarios.erase(id);
    _conjunto_ids.erase(id);
}

void RedSocial::amigar_usuarios(int id_A, int id_B){ // O(log n)
    _usuarios.at(id_A)._conjunto_amigos.insert(obtener_alias(id_B));
    _usuarios.at(id_B)._conjunto_amigos.insert(obtener_alias(id_A));
    _cantidad_amistades++;

    int cantidad_amigos_A = obtener_amigos(id_A).size();
    int cantidad_amigos_B = obtener_amigos(id_B).size();
    int cantidad_amigos_popular = (*_usuario_mas_popular).second._conjunto_amigos.size();

    if(cantidad_amigos_A > cantidad_amigos_popular){
        _usuario_mas_popular = _usuarios.find(id_A);
    } else if(cantidad_amigos_B > cantidad_amigos_popular){
        _usuario_mas_popular = _usuarios.find(id_B);
    }
}

void RedSocial::desamigar_usuarios(int id_A, int id_B){  // O(n) con n = cantidad de usuarios
    _usuarios.at(id_A)._conjunto_amigos.erase(obtener_alias(id_B));
    _usuarios.at(id_B)._conjunto_amigos.erase(obtener_alias(id_A));
    _cantidad_amistades--;

    if(id_A == (*_usuario_mas_popular).first || id_B == (*_usuario_mas_popular).first) {
        auto mas_popular = _usuarios.begin();
        for(auto it = mas_popular++; it != _usuarios.end(); it++) {
            if((*it).second._conjunto_amigos.size() > (*mas_popular).second._conjunto_amigos.size()){
                mas_popular = it;
            }
        }

        _usuario_mas_popular = mas_popular;
    }
}

int RedSocial::obtener_id(string alias) const{ // O(n) con n = cantidad de usuarios
    auto it = _usuarios.begin();
    while(alias != (*it).second._alias) {
        ++it;
    }

    return (*it).first;
}

const set<string> & RedSocial::amigos_del_usuario_mas_popular() const{ // O(1)
    return (*_usuario_mas_popular).second._conjunto_amigos;
}