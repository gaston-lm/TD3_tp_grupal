#include "RedSocial.h"

using namespace std;

RedSocial::RedSocial(){
    _usuarios = map<int, Usuario>();
    _conjunto_ids = set<int>();
    _cantidad_amistades = 0;
    _usuario_mas_popular = _usuarios.begin();
    //_amigos_del_mas_popular = (*_usuario_mas_popular).second._conjunto_amigos;
}

const set<int> & RedSocial::usuarios() const{
    /* completar */
    return _conjunto_ids;
}
string RedSocial::obtener_alias(int id) const{
    /* completar */
    auto it = _usuarios.find(id);
    return (*it).second._alias;
}
const set<string> & RedSocial::obtener_amigos(int id) const{
    /* completar */
    auto it = _usuarios.find(id); // log n
    return (*it).second._conjunto_amigos;
}
int RedSocial::cantidad_amistades() const{
    /* completar */
    return _cantidad_amistades;
}

void RedSocial::registrar_usuario(string alias, int id){
    /* completar */
    Usuario nuevo_usuario {id, alias, {}};
    _usuarios.insert({id, nuevo_usuario});
}
void RedSocial::eliminar_usuario(int id){
    /* completar */
    set<string> aux = obtener_amigos(id);
    auto it = aux.begin();
    for(it; it != aux.end(); ++it) {
        int id_amigo = obtener_id(*it);
        desamigar_usuarios(id, id_amigo);
    }
    /*
    auto it_usuario = _usuarios.find(id);
    if(it_usuario == _usuario_mas_popular) {
        auto it = obtener_amigos(id).begin();
        ++it;
        int cant_mas_popular = obtener_amigos(id).size();
        for(it; it != obtener_amigos(id).end(); ++it) {
            int id_de_usuario = obtener_id((*it));
            int cantidad_a_comparar = _usuarios.find(id_de_usuario);
            if(cant_mas_popular < )
        }
    }
    */
    auto it_usuario = _usuarios.find(id);
    _usuarios.erase(it_usuario);
}

void RedSocial::amigar_usuarios(int id_A, int id_B){
    /* completar */
    auto a = obtener_amigos(id_A);
    a.insert(obtener_alias(id_B));
    auto itA = _usuarios.find(id_A); 
    (*itA).second._conjunto_amigos = a;

    auto b = obtener_amigos(id_B);
    b.insert(obtener_alias(id_A));
    auto itB = _usuarios.find(id_B); 
    (*itB).second._conjunto_amigos = b;

    _cantidad_amistades++;
    // chequeamos usuario más popular
    int cantidad_amigos_A = obtener_amigos(id_A).size();
    int cantidad_amigos_B = obtener_amigos(id_B).size();
    int cantidad_amigos_mas_popular = (*_usuario_mas_popular).second._conjunto_amigos.size();
    if(cantidad_amigos_A >= cantidad_amigos_B) {
        if (cantidad_amigos_A > cantidad_amigos_mas_popular) {
            _usuario_mas_popular = _usuarios.find(id_A);
            //_amigos_del_mas_popular = obtener_amigos(id_A);
        }
    } else {
        if (cantidad_amigos_B > cantidad_amigos_mas_popular) {
            _usuario_mas_popular = _usuarios.find(id_B);
            //_amigos_del_mas_popular = obtener_amigos(id_B);
        }
    }
    
}
void RedSocial::desamigar_usuarios(int id_A, int id_B){
    /* completar */
    auto a = obtener_amigos(id_A);
    a.erase(obtener_alias(id_B));
    auto itA = _usuarios.find(id_A); 
    (*itA).second._conjunto_amigos = a;

    auto b = obtener_amigos(id_B);
    b.erase(obtener_alias(id_A));
    auto itB = _usuarios.find(id_B); 
    (*itB).second._conjunto_amigos = b;
    
    _cantidad_amistades--;
}

int RedSocial::obtener_id(string alias) const{
    /* completar */
    int res = 0;
    auto it = _usuarios.begin();
    for(it; it != _usuarios.end(); ++it) {
        string alias_de_it = (*it).second._alias;
        if(alias == alias_de_it) {
            res = (*it).second._id;
            break;
        }
    }
    return res;
}
const set<string> & RedSocial::amigos_del_usuario_mas_popular() const{
    /* completar */
    return *(new set<string>);
}