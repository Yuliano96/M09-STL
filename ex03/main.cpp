/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:20:16 by yuliano           #+#    #+#             */
/*   Updated: 2026/05/19 19:53:45 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>



std::vector<int>arr = {10, 2, 5, 1, 9, 7};

int jacobs[] = {1, 3, 5, 11};

typedef std::vector<int>		vect;
typedef vect::iterator			vectIt ;

typedef std::vector<vect>		groupVec;
typedef groupVec::iterator		groupVecIt;

/*void group_couple(groupVec &group)
{
    std::vector<int>temp = group[0];
    size_t clouples = temp.size() / 2;
	size_t k = 0;
	group.clear();
	
	for(size_t i = 0; i < clouples; ++i)
	{
		group.push_back(vect());
		for(size_t j = 0; j < 2; ++j)
		{
			group[i].push_back(temp[k]);
			k++;
		}
	}
	if (k < temp.size())
	{
		group.push_back(vect());
		group[clouples].push_back(temp[k]);
	}
}*/

bool is_less(int a, int b)
{
    if (a < b)
        return true;
    return false;
}

void swap(int &a, int &b)
{
    int temp;
    
    temp = a;
    a = b;
    b = temp;
}

void sort_pairs(groupVec &group)
{
    //size_t size = group.size() % 2 == 0 ? group.size():(group.size() - 1);
    
    // for(size_t i = 0; i < size; ++i)
    // {
        
    //     if(!is_less(group[i][0], group[i][1]))
    //         swap(group[i][0], group[i][1]);
    // }
	
    for (groupVecIt it = group.begin(); it != group.end() && (it + 1) != group.end(); ++it)
    {
        if(!is_less(*it->begin(),*(it->begin() + 1)))
        {
            swap(*it->begin(),*(it->begin() + 1));
        }
    }
}

void Main_chain(groupVec &group, vect &winner, vect &losers)
{
    groupVec temp = group;
    group.clear();
	group.push_back(vect());
	group.push_back(vect());

	size_t i = 0;
    for (; i < temp.size(); i++)
    {
		if (temp[i].size() == 1)
		{
			group[0].push_back(temp[i][0]);
			break;
		}
		group[0].push_back(temp[i][1]);
		group[1].push_back(temp[i][0]); //Main chain
    }
	
	winner = group[1]; 
	losers = group[0];
}

void group_couple(groupVec &group)
{
    vect temp = group[0];
    group.clear();
    
    //  Usamos iteradores para avanzar por 'temp'
    vectIt it = temp.begin();
    
    // Mientras queden al menos 2 elementos disponibles...
    while (it != temp.end() && (temp.end() - it) >= 2)
    {
        // El truco de eficiencia: Creamos el Group pasándole el rango [it, it + 2)
        // Esto copia los 2 elementos de golpe en memoria, sin push_backs individuales.
        group.push_back(vect(it, it + 2));
        
        it += 2; // Avanzamos el iterador de dos en dos
    }
    
    // 3. Manejo del elemento impar (si sobra uno)
    if (it != temp.end())
    {
        // Creamos una fila con el único elemento que queda hasta el final
        group.push_back(vect(it, temp.end()));
    }
}

void print_pairs(groupVec &group)
{
    for (groupVecIt itFila = group.begin(); itFila != group.end(); ++itFila) {
        
        // El bucle interno recorre los enteros de esa fila (Group)
        // Usamos '*itFila' para obtener el Group actual donde apunta el iterador
        for (vectIt itCol = itFila->begin(); itCol != itFila->end(); ++itCol) {
            std::cout << *itCol << " ";
        }
        std::cout << std::endl; // Salto de línea al terminar cada fila
    }
}

void Ford_jhoson(vect &Winner, vect &losers)
{
	groupVec group;
	
	if (Winner.size() == 1)
		return ;
	group.push_back(Winner);
	group.push_back(losers);
	group_couple(group);
	print_pairs(group);
	Main_chain(group, Winner, losers);
	Ford_jhoson(Winner, losers);
}

int main()
{
    vect losers;
    Ford_jhoson(arr, losers);
    
    
    
    return (0);
}

