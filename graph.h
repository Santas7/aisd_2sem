//
// Created by ANDREY on 5/3/23.
//

#ifndef AISD_LABA_3_GRAPH_H
#define AISD_LABA_3_GRAPH_H
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <unordered_map>
#include <unordered_set>

// шаблонный класс графа
template<typename Vertex, typename Distance = double>
class Graph{
private:
    struct Edge{
        Vertex from; // откуда
        Vertex to; // куда
        Distance distance;
        Edge(int from, int to, Distance distance) : from(from), to(to), distance(distance) {}
    };
    // вершины и список ребер
    std::vector<std::pair<Vertex, std::list<Edge>>> _data;
public:
    // проверка наличия вершины в графе
    bool has_vertex(const Vertex& v) const{
        for (auto& item : _data)
            if (item.first == v)
                return true;
        return false;
    }

    // добавление вершины
    void add_vertex(const Vertex& v){
        if (has_vertex(v))
            throw std::invalid_argument("Вершина уже существует");
        _data.push_back(std::make_pair(v, std::list<Edge>()));
        //_data.push_back({v, std::list<Edge>()});
    }

    // удаление вершины
    bool remove_vertex(const Vertex& v){
        if (!has_vertex(v))
            return false;
        for (auto& item : _data)
            if (item.first == v)
                _data.erase(item);
        return true;
    }

    // получение всех вершин графа
    std::vector<Vertex> vertices() const{
        std::vector<Vertex> result;
        for (auto& item : _data)
            result.push_back(item.first);
        return result;
    }


    // добавление ребра в граф
    void add_edge(const Vertex& from, const Vertex& to, const Distance& d){
        if (!has_vertex(from) || !has_vertex(to))
            throw std::invalid_argument("Вершина не найдена!");
        for (auto& item : _data)
            if (item.first == from)
                item.second.push_back(Edge(from, to, d));
    }

    // удаление ребра из графа с учетом направления (from -> to)
    bool remove_edge(const Vertex& from, const Vertex& to){
        if (!has_vertex(from) || !has_vertex(to))
            return false; // вершины не найдены
        for (auto& item : _data)
            if (item.first == from)
                for (auto& item2 : item.second)
                    if (item2.to == to)
                        item.second.erase(item2);
        return true;
    }

    // удаление ребра из графа
    bool remove_edge(const Edge& e){
        if (!has_vertex(e.from) || !has_vertex(e.to))
            return false;
        for (auto& item : _data)
            if (item.first == e.from)
                for (auto& item2 : item.second)
                    if (item2.to == e.to)
                        item.second.erase(item2);
        return true;
    }

    // проверка наличия ребра в графе с учетом направления (from -> to)
    bool has_edge(const Vertex& from, const Vertex& to) const {
        if (!has_vertex(from) || !has_vertex(to))
            return false; // вершины не найдены
        for (auto& item : _data)
            if (item.first == from)
                for (auto& item2 : item.second)
                    if (item2.to == to)
                        return true;
        return false;
    }

    // проверка наличия ребра в графе
    bool has_edge (const Edge& e){
        if (!has_vertex(e.from) || !has_vertex(e.to))
            return false;
        for (auto& item : _data)
            if (item.first == e.from)
                for (auto& item2 : item.second)
                    if (item2.to == e.to)
                        return true;
        return false;
    }

    // получение всех ребер, выходящих из вершины (все ребра, у которых from == vertex)
    std::vector<Edge> edges(const Vertex& vertex) const{
        if (!has_vertex(vertex))
            throw std::invalid_argument("Vertex not found");
        std::vector<Edge> result;
        for (auto& item : _data)
            if (item.first == vertex)
                for (auto& item2 : item.second)
                    result.push_back(item2);
        return result;
    }

    // получение порядка графа (количество вершин)
    size_t order() const{
        return _data.size();
    }

    // степень графа (количество ребер)
    size_t degree() const{
        size_t result = 0;
        for (auto& item : _data)
            result += item.second.size(); // item.second - список ребер
        return result;
    }

    // поиск кратчайшего пути по алгоритму Беллмана-Форда
    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const{
        if (!has_vertex(from) || !has_vertex(to))
            throw std::invalid_argument("Вершины не найдены!");

        std::vector<Edge> result;
        // Инициализация вектора расстояний и предшественников
        std::unordered_map<Vertex, Distance> distance;
        std::unordered_map<Vertex, Vertex> prev;

        for (const auto& item : _data) {
            distance[item.first] = std::numeric_limits<Distance>::max();
            prev[item.first] = from;
        }
        distance[from] = 0;

        // Релаксация всех ребер графа |V| - 1 раз
        for (size_t i = 1; i < _data.size(); ++i) {
            for (const auto& item : _data) {
                Vertex u = item.first;
                const auto& edges = item.second;
                for (const Edge& edge : edges) {
                    Vertex v = edge.to;
                    Distance new_dist = distance[u] + edge.distance;
                    if (distance[u] != std::numeric_limits<Distance>::max() && new_dist < distance[v]) {
                        distance[v] = new_dist;
                        distance[v] = u;
                    }
                }
            }
        }

        // Проверка наличия циклов отрицательного веса
        for (const auto& item : _data) {
            Vertex u = item.first;
            for (const Edge& edge : item.second) {
                Vertex v = edge.to;
                Distance new_dist = distance[u] + edge.distance;
                if (distance[u] != std::numeric_limits<Distance>::max() && new_dist < distance[v]) {
                    throw std::runtime_error("Граф содержит отрицательный цикл!");
                }
            }
        }

        // Восстановление пути
        if (distance[to] != std::numeric_limits<Distance>::max()) {
            Vertex current = to;
            while (current != from) {
                Vertex prev_vertex = prev[current];
                result.push_back(Edge(prev_vertex, current, distance[current] - distance[prev_vertex]));
                current = prev_vertex;
            }
            std::reverse(result.begin(), result.end());
        }

        return result;
    }

    // Обход графа в глубину, начиная с вершины start_vertex
    std::vector<Vertex> walk(const Vertex& start_vertex) const {
        // Проверяем наличие стартовой вершины в графе
        if (!has_vertex(start_vertex)) {
            throw std::invalid_argument("Стартовая вершина не найдена!");
        }

        // Инициализация структур данных для обхода
        std::vector<Vertex> visited; // Вектор для хранения посещенных вершин
        std::unordered_set<Vertex> visited_set; // Множество для проверки, была ли вершина уже посещена
        std::stack<Vertex> stack; // Стек для хранения вершин, ожидающих обработки
        stack.push(start_vertex);

        while (!stack.empty()) {
            Vertex current_vertex = stack.top();
            stack.pop(); // Удаляем вершину из стека

            // Если вершина еще не была посещена, обрабатываем ее
            if (visited_set.find(current_vertex) == visited_set.end()) {
                visited.push_back(current_vertex); // Добавляем вершину в список посещенных
                visited_set.insert(current_vertex); // Добавляем вершину в множество посещенных
                // Добавляем соседей текущей вершины в стек для дальнейшего обхода
                std::vector<Edge> adjacent_edges = edges(current_vertex);
                for (const Edge& edge : adjacent_edges) {
                    Vertex neighbor = edge.to;
                    if (visited_set.find(neighbor) == visited_set.end()) {
                        stack.push(neighbor);
                    }
                }
            }
        }
        return visited;
    }

};

#endif //AISD_LABA_3_GRAPH_H
