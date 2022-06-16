#ifndef __REDSOCIAL_H__
#define __REDSOCIAL_H__

#include <string>
#include <set>
#include <map>

class RedSocial{
  public:
    RedSocial();

    const std::set<int> & usuarios() const; // O(1)
    std::string obtener_alias(int id) const; // O(log n)
    const std::set<std::string> & obtener_amigos(int id) const; // O(log n)
    int cantidad_amistades() const; // O(1)

    void registrar_usuario(std::string alias, int id); // O(log n)
    void eliminar_usuario(int id); // sin requerimiento
    void amigar_usuarios(int id_A, int id_B); // sin requerimiento
    void desamigar_usuarios(int id_A, int id_B); // sin requerimiento
    
    int obtener_id(std::string alias) const; // sin requerimiento
    const std::set<std::string> & amigos_del_usuario_mas_popular() const; // O(1)

  private:
    struct Usuario {
      std::string _alias;
      std::set<std::string> _conjunto_amigos; 
    };
    std::map<int, Usuario> _usuarios;
    std::set<int> _conjunto_ids;
    int _cantidad_amistades;
    std::map<int, Usuario>::iterator _usuario_mas_popular;
};

/*

Invariante de representación:

    - El diccionario _usuarios tiene como clave ids (irrepetibles) que tienen asociados
      un struct Usuario que almacena el _alias (irrepetible) y su _conjunto_amigos 
      (contiene alias de los usuarios de los que es amigo). A su vez el alias de un Usuario debe estar 
      asociada a un único id, y viceversa.
    - El conjunto _conjunto_ids son todas las claves del diccionario _usuarios.
    - El valor _cantidad_amistades es la cantidad total de relaciones de amistad actualmente en la red.
    - El puntero _usuario_mas_popular apunta al usuario cuyo _conjunto_amigos es el de mayor tamaño de la red.
      En caso de que haya un único usuario en la red este será el más popular. En caso de haber 2 usuarios con la misma
      cantidad de amigos, el usuario_mas_popular no cambia.

*/

#endif