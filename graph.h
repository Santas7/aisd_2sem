#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <limits>
#include <unordered_map>
#include <unordered_set>
// #include "Graphics.h"

// шаблонный класс графа
template<typename Vertex, typename Distance = double>
class Graph{
private:
    struct Edge {
        Vertex from; // откуда
        Vertex to; // куда
        Distance distance;
        Edge(int from, int to, Distance distance) : from(from), to(to), distance(distance) {}
        Edge() = default;
    };
    // вершины и список ребер
    std::unordered_map<Vertex, std::vector<Edge>> _data;
public:
    // проверка наличия вершины в графе
    bool has_vertex(const Vertex& v) const{
        return _data.count(v) > 0;
    }

    // добавление вершины
    void add_vertex(const Vertex& v){
        if (has_vertex(v))
            throw std::invalid_argument("Вершина уже существует!");
        _data[v] = std::vector<Edge>();
    }

    // удаление вершины
    bool remove_vertex(const Vertex& v){
        if (!has_vertex(v))
            return false;
        for (auto& pair : _data) {
            auto pred = [&](const auto& edge) {
                return edge.to == v;
            };

            auto vector_iter = std::find_if(pair.second.begin(), pair.second.end(), pred);

            while (vector_iter != pair.second.end()) {
                auto tmp_begin = pair.second.erase(vector_iter);

                vector_iter = std::find_if(tmp_begin, pair.second.end(), pred);
            }
        }
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
        if (!has_vertex(from))
            throw std::invalid_argument("Нет вершины from!");
        if (!has_vertex(to))
            throw std::invalid_argument("Нет вершины to!");
        _data[from].push_back(Edge(from, to, d));
    }

    // удаление ребра из графа
    bool remove_edge(const Vertex& from, const Vertex& to){
        if (!has_vertex(from) || !has_vertex(to))
            return false;
        auto pred = [&from, &to](const auto& edge) {
            return edge.from == from && edge.to == to;
        };

        bool is_removed = false;
        auto vector_iter = std::find_if(_data.at(from).begin(), _data.at(from).end(), pred);

        while (vector_iter != _data.at(from).end()) {
            auto tmp_begin = _data.at(from).erase(vector_iter);

            vector_iter = std::find_if(tmp_begin, _data.at(from).end(), pred);

            is_removed = true;
        }
        return is_removed;

        return false;
    }

    // удаление ребра из графа
    bool remove_edge(const Edge& e) {
        if (!has_vertex(e.from) || !has_vertex(e.to))
            return false;

        auto pred = [&e](const auto& edge) {
            return edge.from == e.from && edge.to == e.to;
        };

        bool is_removed = false;
        auto vector_iter = std::find_if(_data.at(e.from).begin(), _data.at(e.from).end(), pred);

        while (vector_iter != _data.at(e.from).end()) {
            auto tmp_begin = _data.at(e.from).erase(vector_iter);

            vector_iter = std::find_if(tmp_begin, _data.at(e.from).end(), pred);

            is_removed = true;
        }
        return is_removed;
    }

    // генерация случайного графа
    void generate_random_graph(size_t count){
        for (size_t i = 0; i < count; i++)
            add_vertex(i);
        for (size_t i = 0; i < count; i++){
            auto n = rand() % count;
            for (size_t j = 0; j < n; j++)
                if (i != j)
                    add_edge(i, j, rand() % 100);
        }
    }

    // вывод графа в консоль
    void print() const{
        // вершины
        std::cout << "Вершины: ";
        for (auto& item : _data)
            std::cout << item.first << " ";
        std::cout << std::endl;
        // ребра
        std::cout << "Ребра: " << std::endl;
        for (auto& item : _data)
            for (auto& item2 : item.second)
                std::cout << item2.from << " -> " << item2.to << " (" << item2.distance << ")" << std::endl;
    }

    // проверка наличия ребра в графе с учетом направления (from -> to)
    bool has_edge(const Vertex& from, const Vertex& to) const{
        if (!has_vertex(from))
            return false;
        if (!has_vertex(to))
            return false;
        for (auto& item : _data.at(from))
            if (item.to == to)
                return true;
        return false;
    }

    // проверка наличия ребра в графе
    bool has_edge(const Edge& e) const{
        if (!has_vertex(e.from) || !has_vertex(e.to))
            return false;
        for (auto& item : _data.at(e.from))
            if (item.to == e.to)
                return true;
        return false;
    }

    // получение всех ребер выходящих из вершины
    std::vector<Edge> edges(const Vertex& vertex) const{
        if (!has_vertex(vertex) || _data.at(vertex).empty())
            throw std::invalid_argument("Нет вершины vertex!");
        return _data.at(vertex);
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
    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to, Distance* dist=nullptr) const{
        if (!has_vertex(from) || !has_vertex(to))
            throw std::invalid_argument("Вершина не найдена!");

        // инициализация расстояний и предков для каждой вершины
        std::vector<Edge> result; // результирующий путь
        std::unordered_map<Vertex, Distance> distance; // расстояния
        std::unordered_map<Vertex, Edge> prev; // предки
        for (auto& item : _data){
            distance[item.first] = std::numeric_limits<Distance>::max(); // расстояние от from до всех остальных вершин - бесконечность
        }
        distance[from] = 0;

        // алгоритм Беллмана-Форда (поиск кратчайшего пути)
        // order() - количество вершин
        for (size_t i = 0; i < order() - 1; ++i) {
            for (const auto& pair : _data) {
                for (const auto& edge : pair.second) {
                    if (distance[edge.from] + edge.distance < distance[edge.to]) {
                        distance[edge.to] = distance[edge.from] + edge.distance;
                        prev[edge.to] = edge;
                    }
                }
            }
        }

        for (const auto& pair : _data)
            for (const auto& edge : pair.second)
                if (distance[edge.from] + edge.distance < distance[edge.to])
                    throw std::runtime_error("Граф имеет отрицательный цикл");

        if (distance[to] == std::numeric_limits<Distance>::max()) {
            throw std::invalid_argument("Ошибка! Эти вершины не связаны!");
        }
        // восстановление пути
        Vertex current = to; // текущая вершина - конечная

        while (current != from) {
            result.push_back(prev[current]);
            current = prev[current].from;
        }

        std::reverse(result.begin(), result.end()); // разворачиваем путь (т.к. мы восстанавливали его с конца)
        return result;
    }

    // Обход графа в глубину, начиная с вершины start_vertex
    std::vector<Vertex> walk(const Vertex& start_vertex) const {
        // Проверяем наличие стартовой вершины в графе
        if (!has_vertex(start_vertex))
            throw std::invalid_argument("Стартовая вершина не найдена!");

        // Список посещенных вершин
        std::vector<Vertex> visited;
        // Список вершин, которые нужно посетить
        std::stack<Vertex> stack;
        // Добавляем стартовую вершину в список посещенных
        visited.push_back(start_vertex);
        // Добавляем стартовую вершину в стек
        stack.push(start_vertex);

        // Пока стек не пуст
        while (!stack.empty()) {
            // Получаем вершину из стека
            Vertex current = stack.top();
            // Удаляем вершину из стека
            stack.pop();
            // Получаем список смежных вершин
            auto edges = this->edges(current);
            // Перебираем все смежные вершины
            for (auto& edge : edges) {
                // Если вершина еще не посещена
                if (std::find(visited.begin(), visited.end(), edge.to) == visited.end()) {
                    // Добавляем вершину в список посещенных
                    visited.push_back(edge.to);
                    // Добавляем вершину в стек
                    stack.push(edge.to);
                }
            }
        }
        return visited;
    }
};
