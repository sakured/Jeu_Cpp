#include <vector>
#include <unordered_map>
#include <utility>
#include <stack>
#include <queue>
#include <algorithm>
#pragma once

namespace Graph {
    struct WeightedGraphEdge {
        int to {};
        float weight {1.0f};

        bool operator==(WeightedGraphEdge const& other) const = default;
        bool operator!=(WeightedGraphEdge const& other) const = default;
    };

    struct WeightedGraph {
        std::unordered_map<int, std::vector<WeightedGraphEdge>> adjacency_list {};

        void add_vertex(int const id);

        // Fonction qui teste si un noeud est présent dans le graphe
        bool is_existing(int const id);

        void add_directed_edge(int const from, int const to, float const weight = 1.0f);
        void add_undirected_edge(int const from, int const to, float const weight = 1.0f);
        
        // Même fonctionnement que pour WeightedGraphEdge
        bool operator==(WeightedGraph const& other) const = default;
        bool operator!=(WeightedGraph const& other) const = default;

        void print_DFS(int const start) const;
        void print_BFS(int const start) const;

    };

    WeightedGraph adjacency_list_from_adjacency_matrix (std::vector<std::vector<float>> const& adjacency_matrix);

    std::unordered_map<int, std::pair<float, int>> dijkstra(WeightedGraph const & graph, int const start, int const end);
} // namespace

// bool is_in_stack(std::stack<int> stack, int target);
// bool is_in_queue(std::queue<int> queue, int target);

std::pair<Graph::WeightedGraph, std::unordered_map<int, std::pair<int, int>>> read_ITD(std::string & map_name, std::vector<int> & in, std::vector<int> & out, std::vector<int> & path);
std::vector<std::vector<float>> from_list_nodes_to_adjency_matrix(std::vector<std::vector<int>> & list_nodes, int number_of_nodes);
std::vector<std::pair<int, int>> find_path(Graph::WeightedGraph graph, std::unordered_map<int, std::pair<int, int>> nodes_positions, int const start, int const end);