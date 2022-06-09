#include "RedSocial.h"

using namespace std;

RedSocial::RedSocial(){
    /* completar */
}

const set<int> & RedSocial::usuarios() const{
    /* completar */
    return *(new set<int>);
}
string RedSocial::obtener_alias(int id) const{
    /* completar */
    return "";
}
const set<string> & RedSocial::obtener_amigos(int id) const{
    /* completar */
    return *(new set<string>);
}
int RedSocial::cantidad_amistades() const{
    /* completar */
    return 0;
}

void RedSocial::registrar_usuario(string alias, int id){
    /* completar */
}
void RedSocial::eliminar_usuario(int id){
    /* completar */
}

void RedSocial::amigar_usuarios(int id_A, int id_B){
    /* completar */
}
void RedSocial::desamigar_usuarios(int id_A, int id_B){
    /* completar */
}

int RedSocial::obtener_id(string alias) const{
    /* completar */
    return 0;
}
const set<string> & RedSocial::amigos_del_usuario_mas_popular() const{
    /* completar */
    return *(new set<string>);
}