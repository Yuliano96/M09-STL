/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:20:16 by yuliano           #+#    #+#             */
/*   Updated: 2026/05/21 13:07:11 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>     // Para std::cout
#include <vector>       // Para std::vector
#include <algorithm>    // Para std::lower_bound

typedef std::vector<int>        vect;       // Alias para vector de int
typedef vect::iterator          vectIt;     // Alias para iterador de vector<int>
typedef std::vector<vect>       groupVec;   // Alias para vector de vectores
typedef groupVec::iterator      groupVecIt; // Alias para iterador de groupVec

bool is_less(int a, int b)                  // Compara si a es menor que b
{
    return (a < b);                         // Devuelve true si a < b
}

void swap_values(int &a, int &b)            // Intercambia dos enteros por referencia
{
    int temp;                               // Variable temporal

    temp = a;                               // Guarda a
    a = b;                                  // Copia b en a
    b = temp;                               // Copia temp en b
}

void sort_pairs(groupVec &group)            // Ordena internamente cada par
{
    groupVecIt it;                          // Iterador para recorrer grupos

    it = group.begin();                     // Empieza en el primer grupo
    while (it != group.end())               // Recorre todos los grupos
    {
        if (it->size() == 2)                // Solo ordena si el grupo tiene 2 elementos
        {
            if (!is_less((*it)[0], (*it)[1])) // Si el primero no es menor que el segundo
                swap_values((*it)[0], (*it)[1]); // Intercambia para dejar menor, mayor
        }
        ++it;                               // Avanza al siguiente grupo
    }
}

/* Convierte group[0] en pares */
void group_pairs(groupVec &group)           
{
    vect temp;                              // Guarda la secuencia original
    vectIt it;                              // Iterador para recorrer temp

    temp = group[0];                        // Copia la secuencia actual
    group.clear();                          // Limpia group para guardar solo pares
    it = temp.begin();                      // Empieza desde el primer número

    while (it != temp.end() && temp.end() - it >= 2) // Mientras queden al menos 2 elementos
    {
        group.push_back(vect(it, it + 2));  // Crea un par con esos 2 elementos
        it += 2;                            // Avanza de dos en dos
    }

    if (it != temp.end())                   // Si sobra un elemento impar
        group.push_back(vect(it, temp.end())); // Lo guarda como grupo de tamaño 1
}

/* Separa ganadores y pendientes*/
void make_main_chain(groupVec &group)       
{
    groupVec temp;                          // Copia temporal de los pares
    size_t i;                               // Índice para recorrer temp

    temp = group;                           // Guarda los pares actuales
    group.clear();                          // Limpia group
    group.push_back(vect());                // group[0] será la main chain
    group.push_back(vect());                // group[1] serán los pendientes

    i = 0;                                  // Empieza en el primer par
    while (i < temp.size())                 // Recorre todos los pares
    {
        if (temp[i].size() == 1)            // Si es un número suelto
            group[1].push_back(temp[i][0]); // Se guarda como pendiente
        else                                // Si es un par normal
        {
            group[0].push_back(temp[i][1]); // El mayor va a la main chain
            group[1].push_back(temp[i][0]); // El menor va a pendientes
        }
        ++i;                                // Avanza al siguiente grupo
    }
}

void insert_pending(vect &main_chain, vect &pending) // Inserta pendientes en orden
{
    vectIt it;                              // Iterador para recorrer pending
    vectIt pos;                             // Posición donde insertar

    it = pending.begin();                   // Empieza en el primer pendiente
    while (it != pending.end())             // Recorre todos los pendientes
    {
        pos = std::lower_bound(main_chain.begin(), main_chain.end(), *it); // Busca posición ordenada
        main_chain.insert(pos, *it);        // Inserta el pendiente en su sitio
        ++it;                               // Avanza al siguiente pendiente
    }
}

groupVec Ford_johnson(groupVec group)       // Ordena usando recursividad
{
    groupVec recursive_group;               // Grupo que se enviará a la recursión
    groupVec result;                        // Resultado devuelto por la recursión
    vect main_chain;                        // Main chain ordenada
    vect pending;                           // Pendientes del nivel actual

    if (group[0].size() <= 1)               // Caso base: 0 o 1 elementos
        return (group);                     // Ya está ordenado

    group_pairs(group);                     // Crea pares desde group[0]
    sort_pairs(group);                      // Ordena cada par internamente
    make_main_chain(group);                 // Separa main chain y pendientes

    pending = group[1];                     // Guarda pendientes de ESTE nivel

    recursive_group.push_back(group[0]);    // La recursión solo ordena la main chain
    result = Ford_johnson(recursive_group); // Ordena recursivamente la main chain

    main_chain = result[0];                 // Recupera la main chain ya ordenada
    insert_pending(main_chain, pending);    // Inserta los pendientes de ESTE nivel

    group.clear();                          // Limpia group para devolver resultado final
    group.push_back(main_chain);            // Guarda la secuencia ordenada en group[0]

    return (group);                         // Devuelve el grupo ordenado
}

void print_vector(vect &v)                  // Imprime un vector
{
    vectIt it;                              // Iterador

    it = v.begin();                         // Empieza al inicio
    while (it != v.end())                   // Recorre hasta el final
    {
        std::cout << *it << " ";            // Imprime el valor actual
        ++it;                               // Avanza
    }
    std::cout << std::endl;                 // Salto de línea
}

int main(void)                              // Función principal
{
    vect arr = {10, 2, 5, 1, 9, 7};                               // Vector inicial
    groupVec group;                         // Grupo principal
    groupVec result;                        // Resultado final


    group.push_back(arr);                   // group[0] contiene la secuencia inicial
    result = Ford_johnson(group);           // Ordena la secuencia

    print_vector(result[0]);                // Imprime resultado ordenado

    return (0);                             // Fin correcto
}