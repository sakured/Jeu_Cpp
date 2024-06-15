#include "utils.hpp"

#include <iostream>

/**
 * Crée un chemin absolu vers un fichier
 */
std::filesystem::path make_absolute_path(std::filesystem::path const& path, bool check_path_exists)
{
    auto const res {path.is_relative() ? CMAKE_SOURCE_DIR / path : path };

    if (check_path_exists && !std::filesystem::exists(res))
    {
        using namespace std::literals;
        auto const msg { "Path \""s + res.string() + "\" does not exist. Make sure you didn't misspell it or made it relative to the wrong folder. All relative paths will be relative to the directory containing your CMakeLists.txt file." };
        std::cerr << msg << '\n';
        throw std::runtime_error{msg};
    }

    return res;
}

auto const is_space = [](char letter){ return letter == ' '; };

/**
 * Sépare les mots d'une chaine de caractères dans un tableau
 */
std::vector<std::string> split_string(std::string const& str) {
    std::vector<std::string> vec {};
    auto it_begin { str.begin() };
    while (it_begin != str.end()) {
        std::string word {};
        auto it_space = std::find_if(it_begin, str.end(), is_space);
        int distance = std::distance(it_begin, it_space);
        for (auto it = it_begin; it != it_space; it++) {
            word += *it;
        }
        vec.push_back(word);
        (it_space != str.end()) ? it_begin = it_space + 1 : it_begin = str.end();
    }
    return vec;
}