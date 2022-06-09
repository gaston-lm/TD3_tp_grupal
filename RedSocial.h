#ifndef __REDSOCIAL_H__
#define __REDSOCIAL_H__

#include <string>
#include <set>

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
    /* completar */
};

#endif