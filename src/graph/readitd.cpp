#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>
#include <iostream>
#include "graph.hpp"
#include "../utils.hpp"

const char * FILE_NAME {"../../data/map1.itd"};

/**
 * Lit le fichier ITD
*/
std::pair<Graph::WeightedGraph, std::unordered_map<int, std::pair<int, int>>> read_ITD(std::string & map_name, std::vector<int> & in, std::vector<int> & out, std::vector<int> & path) {
    std::ifstream itd_file(FILE_NAME);

    Graph::WeightedGraph graph {};
    std::unordered_map<int, std::pair<int, int>> node_positions {};

    // On lit le fichier ITD
    if (itd_file) {

        std::string line {};
        std::vector<std::string> lines {};
        
        // Ajout de chaque ligne du fichier ITD dans un tableau (hors commentaires)
        while (std::getline(itd_file, line)) {
            if (line[0] != '#') {
                lines.push_back(line);
            }   
        }

        // Analyse et traitement des lignes récupérées
        std::vector<std::vector<int>> list_nodes {};
        int number_of_nodes {};
        for (int i=0; i<lines.size(); i++) {
            std::vector<std::string> vec_line { split_string(lines[i]) };

            // récupération du nom du fichier de la map
            if (vec_line[0] == "map") {
                map_name = vec_line[1];
            }

            // nombre de noeuds
            else if (vec_line[0] == "graph") {
                number_of_nodes = std::stoi(vec_line[1]);
            }

            // création des noeuds
            else if (vec_line[0] == "node") {
                std::vector<int> vec_tmp {};
                for (int j=1; j<vec_line.size(); j++) {
                    vec_tmp.push_back(std::stoi(vec_line[j]));
                }
                list_nodes.push_back(vec_tmp);
            }

            // récupération des couleurs de la map
            else if (vec_line[0] == "in") {
                in.push_back(std::stoi(vec_line[1]));
                in.push_back(std::stoi(vec_line[2]));
                in.push_back(std::stoi(vec_line[3]));
            }
            else if (vec_line[0] == "out") {
                out.push_back(std::stoi(vec_line[1]));
                out.push_back(std::stoi(vec_line[2]));
                out.push_back(std::stoi(vec_line[3]));
            }
            else if (vec_line[0] == "path") {
                path.push_back(std::stoi(vec_line[1]));
                path.push_back(std::stoi(vec_line[2]));
                path.push_back(std::stoi(vec_line[3]));
            }
        }

        // Création de la liste d'adjacence du graphe
        std::vector<std::vector<float>> adjacency_matrix { from_list_nodes_to_adjency_matrix(list_nodes, number_of_nodes) };
        graph = Graph::adjacency_list_from_adjacency_matrix(adjacency_matrix);

        for (int i = 0; i < list_nodes.size(); i++) {
            node_positions.insert({list_nodes[i][0], {list_nodes[i][1], list_nodes[i][2]}});
        }
        
    }
    
    // Le fichier ITD ne s'ouvre pas
    else {
        std::cout << "Impossible d'ouvrir le fichier ITD" << std::endl;
    }

    return {graph, node_positions};
}

/**
 * Transforme la liste de noeuds extraits du fichier ITD en matrice d'adjacence du graphe
 */
std::vector<std::vector<float>> from_list_nodes_to_adjency_matrix(std::vector<std::vector<int>> & list_nodes, int number_of_nodes) {
    std::vector<float> adjency_line {};
    std::vector<std::vector<float>> adjency_matrix {};

    // Initialisation de la matrice d'adjacence
    for (int i=0; i<number_of_nodes; i++) {
        adjency_line.push_back(0);
    }
    for (int i=0; i<number_of_nodes; i++) {
        adjency_matrix.push_back(adjency_line);
    }

    // Création des voisins
    for (int i=0; i<list_nodes.size(); i++) {
        if (list_nodes[i].size() > 3) {
            for (int j=3; j<list_nodes[i].size(); j++) {
                int ind = list_nodes[i][j];
                adjency_matrix[i][ind] = 1;
            }
        }
    }

    // Mise à jours des distances entre deux noeuds (en nombre de cases)
    for (int i=0; i<number_of_nodes; i++) {
        for (int j=0; j<number_of_nodes; j++) {
            if (adjency_matrix[i][j] == 1) {
                adjency_matrix[i][j] = abs(list_nodes[j][1] - list_nodes[i][1])  +  abs(list_nodes[j][2] - list_nodes[i][2]);
            }
        }
    }

    return adjency_matrix;
}

/**
 * @brief Remonte l'algorithme pour récupérer la suite des noeuds formant le chemin le plus court en les combinant vec leurs positions
 * 
 * @param dijkstra 
 * @param nodes_positions 
 * @return std::unordered_map<int, std::pair<int, int>> 
 */
std::unordered_map<int, std::pair<int, int>> find_path(Graph::WeightedGraph graph, std::unordered_map<int, std::pair<int, int>> nodes_positions, int const start, int const end) {
    auto shortest_paths = dijkstra(graph, start, end);
    std::unordered_map<int, std::pair<int, int>> path {};

    int current_node {end};

    while (current_node != start) {
        path.insert({current_node, {nodes_positions.at(current_node)}});

        current_node = shortest_paths.at(current_node).second;
    }
    
    path.insert({start, {nodes_positions.at(start)}});

    return path; 
}