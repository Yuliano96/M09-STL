/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 21:44:24 by yuliano           #+#    #+#             */
/*   Updated: 2026/04/30 21:48:17 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <string>

class EjemploMap 
{
	private:
    std::map<std::string, int> datos;

	public:
    // Constructor
    EjemploMap() 
	{
        std::cout << "Constructor\n";
    }

    // Destructor
    ~EjemploMap() 
	{
        std::cout << "Destructor\n";
    }

    // Constructor de copia
    EjemploMap(const EjemploMap& other) : datos(other.datos) 
	{
        std::cout << "Constructor de copia\n";
    }

    // Operador de asignación
    EjemploMap& operator=(const EjemploMap& other) 
	{
        if (this != &other) {
            datos = other.datos;
        }
        std::cout << "Asignación\n";
        return *this;
    }

    // Insertar elementos
    void insertar() 
	{
        datos.insert(std::make_pair("ana", 23));
        datos.insert(std::make_pair("juan", 30));

        // Otra forma (cuidado: sobreescribe)
        datos["luis"] = 27;
		datos.insert(std::make_pair("Merling", 29));
    }

    // Iterar
    void iterar() const {
        std::map<std::string, int>::const_iterator it;

        for (it = datos.begin(); it != datos.end(); ++it) {
            std::cout << it->first << " -> " << it->second << std::endl;
        }
    }

    // Buscar
    void buscar(const std::string& clave) const {
        std::map<std::string, int>::const_iterator it = datos.find(clave);

        if (it != datos.end()) {
            std::cout << "Encontrado: "
                      << it->first << " -> " << it->second << std::endl;
        } else {
            std::cout << "No encontrado\n";
        }
    }
};

int main() {
    EjemploMap ejemplo;

    ejemplo.insertar();

    std::cout << "\nIterar:\n";
    ejemplo.iterar();

    std::cout << "\nBuscar:\n";
    ejemplo.buscar("juan");
    ejemplo.buscar("pedro");

    return 0;
}