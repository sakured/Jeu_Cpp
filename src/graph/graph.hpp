#include <vector>
#include <unordered_map>
#include <utility>
#include <stack>
#include <queue>
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