#include "RedSocial.h"

using namespace std;

RedSocial::RedSocial(){
    _usuarios = map<int, Usuario>();
    _conjunto_ids = set<int>();
    _cantidad_amistades = 0;
    _usuario_mas_popular;
}

const set<int> & RedSocial::usuarios() const{
    return _conjunto_ids;
}

string RedSocial::obtener_alias(int id) const{
    return _usuarios.at(id)._alias; //O(logn)
}

const set<string> & RedSocial::obtener_amigos(int id) const{
    return _usuarios.at(id)._conjunto_amigos; //O(logn)
}

int RedSocial::cantidad_amistades() const{
    return _cantidad_amistades;
}

void RedSocial::registrar_usuario(string alias, int id){
    Usuario nuevo_usuario {id, alias, {}};
    _usuarios.insert({id, nuevo_usuario});
    // hace falta este set?
    _conjunto_ids.insert(id);
    if(_usuarios.size() == 1) {
        _usuario_mas_popular = _usuarios.begin();
    }
}

void RedSocial::eliminar_usuario(int id){
    auto it = obtener_amigos(id).begin();
    while(it != obtener_amigos(id).end()) {
        int id_amigo = obtener_id(*it);
        ++it;
        desamigar_usuarios(id, id_amigo);
    }
    // Lucas:
    // auto it = _usuarios.at(id)._conjunto_amigos.begin();
    // while( it != _usuarios.at(id)._conjunto_amigos.end()){
    //     int id_amigo = obtener_id(*it);
    //     desamigar_usuarios(id, id_amigo);
    //     it =_usuarios.at(id)._conjunto_amigos.begin();
    // }

    _usuarios.erase(id);
    _conjunto_ids.erase(id);
}

void RedSocial::amigar_usuarios(int id_A, int id_B){
    _usuarios.at(id_A)._conjunto_amigos.insert(obtener_alias(id_B));
    _usuarios.at(id_B)._conjunto_amigos.insert(obtener_alias(id_A));
    _cantidad_amistades++;

    // chequeamos usuario más popular
    /* este if es al peso pq como arriba se hace _cantidad_amistades++ nunca es 0
    if(_cantidad_amistades == 0) {
        //_usuario_mas_popular = _usuarios.at(id_A); 
        _usuario_mas_popular = _usuarios.find(id_A);
    }

    else { 
        */
        int cantidad_amigos_A = obtener_amigos(id_A).size();
        int cantidad_amigos_B = obtener_amigos(id_B).size();
        int cantidad_amigos_popular = (*_usuario_mas_popular).second._conjunto_amigos.size();

        if(cantidad_amigos_A > cantidad_amigos_popular){
            _usuario_mas_popular = _usuarios.find(id_A);
        } else if(cantidad_amigos_B > cantidad_amigos_popular){
            _usuario_mas_popular = _usuarios.find(id_B);
        }
    //}
}

void RedSocial::desamigar_usuarios(int id_A, int id_B){
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

int RedSocial::obtener_id(string alias) const{
    auto it = _usuarios.begin();
    while(alias != (*it).second._alias) {
        ++it;
    }

    return (*it).second._id;
}

const set<string> & RedSocial::amigos_del_usuario_mas_popular() const{
    return (*_usuario_mas_popular).second._conjunto_amigos;
}