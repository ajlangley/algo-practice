// Created by Alexander Langley 25 August, 2018
// Defines the Vertex class

#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

template <class T, class U>
class Vertex
{
private:
    bool visited;
    int discovery_time, finishing_time, distance;
    T item;
    std::vector<U> connections;
    std::vector<int> connection_weights;

public:
    Vertex(T item)
    {
        this->item = item;
        visited = false;
        distance = -1;
     }

    T get_item() { return item; }
    std::vector<U> get_connections() { return connections; }
    std::vector<int> get_connection_weights() { return connection_weights; }
    bool is_visited() { return visited; }
    int get_discovery_time() { return discovery_time; }
    int get_finishing_time() { return finishing_time; }
    int get_distance() { return distance; }


    void set_visited() { visited = true; }
    void set_unvisited() { visited = false; }
    void set_distance(int d) { distance = d; }
    void set_discovery_time(int t) { discovery_time = t; }
    void set_finishing_time(int t) { finishing_time = t; }
    void add_connection(U connection, int weight)
    {
        connections.push_back(connection);
        connection_weights.push_back(weight);
    }
};


#endif // VERTEX_H
