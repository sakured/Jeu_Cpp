#include "enemy.hpp"

/* BUBBLE SORT */

void bubble_sort(std::vector<float> & vec) {
    for (unsigned int i = 0; i < vec.size()-1; i++) {
        for (unsigned int j = 0; j < vec.size()-i-1; j++) {   
            if (vec[j] > vec[j+1]) {
                std::swap(vec[j], vec[j+1]);
            }
        }
    }
}

/* QUICK SORT */

// l'idée de cette fonction est de prendre le vecteur sur lequel on va travailler en paramètre et de prendre deux index (left et right) qui indiquent la partie du tableau pour laquelle on va répartir les valeurs (inférieur au pivot à gauche supérieur à droite du pivot réciproquement à droite) et la valeur du pivot

size_t quick_sort_partition(std::vector<enemy> & vec, size_t const left, size_t const right) {
    enemy pivot_value { vec[right] };

    size_t first_bigger_element_index { left };

    for (size_t i {left}; i < right ;i++) {
        if (vec[i].crossed_distance < pivot_value.crossed_distance) {
            std::swap(vec[first_bigger_element_index], vec[i]);

            first_bigger_element_index++;
        }
    }

    // on échange le pivot (qui est positionné à la fin) pour qu'il soit positionné ente les deux sous partitions (des éléments plus petits et plus grand que le pivot)
    std::swap(vec[first_bigger_element_index], vec[right]);

    // on retourne l'index du pivot
    return first_bigger_element_index;
}

void quick_sort(std::vector<enemy> & vec, size_t const left, size_t const right) {
    if (left < right) {
        size_t pivot = quick_sort_partition(vec, left, right);
        
        if (pivot != right) quick_sort(vec, pivot+1, right);

        if (pivot != left) quick_sort(vec, left, pivot+1);
    }
}

// Surcharge de la fonction qui permet d'appeler la fonction en passant seulement le vecteur et définir les index left et right pour cibler la totalité du tableau à trier automatiquement
void quick_sort(std::vector<enemy> & vec) {
    quick_sort(vec, 0, vec.size()-1);
}