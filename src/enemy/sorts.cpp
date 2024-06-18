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


/* Tri fusion */

// Étape de fusion
void merge_sort_merge(std::vector<enemy> & vec, size_t const left, size_t const middle, size_t const right) {
    size_t const left_size { middle - left + 1 };
    size_t const right_size = { right - middle };
    std::vector<enemy> left_vec(vec.begin() + left, vec.begin() + middle + 1);
    std::vector<enemy> right_vec(vec.begin() + middle + 1, vec.begin() + right + 1);

    size_t left_index {0};
    size_t right_index {0};

    size_t index {left};

     // Tant que nous avons pas parcouru tout les éléments d'au moins une des deux sous-parties
    while (left_index < left_size && right_index < right_size) {
        // On compare les éléments des deux sous-parties et on place le plus petit dans le vecteur original
        // on met à jour les index pour parcourir les sous-parties en conséquence
        if (left_vec[left_index].crossed_distance >= right_vec[right_index].crossed_distance) {
            vec[index] = left_vec[left_index];
            left_index ++;
        } else {
            vec[index] = right_vec[right_index];
            right_index ++;
        }
        index ++;
    }

    // S'il reste des éléments dans une des deux sous-parties, on les place dans le vecteur original
    while (left_index < left_size) {
        vec[index] = left_vec[left_index];
        left_index ++;
        index ++;
    }
    while (right_index < right_size) {
        vec[index] = right_vec[right_index];
        right_index ++;
        index ++;
    }
}

// Étape de merge
void merge_sort(std::vector<enemy> & vec, size_t const left, size_t const right) {
    if (left >= right) {
        return;
    }
    size_t const middle = (left + right) / 2;
    merge_sort(vec, left, middle);
    merge_sort(vec, middle + 1, right);
    merge_sort_merge(vec, left, middle, right);
}

void merge_sort(std::vector<enemy> & vec) {
    merge_sort(vec, 0, vec.size() - 1);
}