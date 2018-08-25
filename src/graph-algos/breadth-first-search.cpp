// Created by Alexander Langley 25 August, 2018
// Gives the breadth first traversal of an input graph

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include "airport.h"
#include "vertex.h"

typedef std::map<std::string, Vertex<Airport*, std::string>*> Graph;
typedef Vertex<Airport*, std::string> AirportVertex;
typedef std::queue<AirportVertex*> AirportQueue;

void build_graph(std::string, Graph&);
void destruct_graph(Graph&);
void display_graph(Graph&);
void breadth_first_search(Graph&, std::string, AirportQueue*&,
    void (*visit)(AirportVertex*, int, AirportQueue*));
void visit(AirportVertex*, int, AirportQueue*);

int main()
{
    std::string filename = "input-files/airports.csv";
    Graph graph;
    AirportQueue *output_queue;

    build_graph(filename, graph);
    breadth_first_search(graph, graph.begin()->first, output_queue, visit);
    // destruct_graph(graph);

    return 0;
}

void build_graph(std::string filename, Graph &graph)
{
    int n_connections;
    std::string city_name, city_code, connection_code, n_conn_str;
    std::ifstream infile;
    AirportVertex *new_vertex;
    Airport *new_airport;

    infile.open(filename);
    // Remove the header from the csv file
    getline(infile, city_name);

    while (getline(infile, city_name, ','))
    {
        infile.get();
        getline(infile, city_code, ',');
        infile.get();
        getline(infile, n_conn_str, ',');
        n_connections = stoi(n_conn_str);

        new_airport = new Airport(city_name, city_code);
        new_vertex = new AirportVertex(new_airport);

        for (int j = 0; j < n_connections; j++)
        {
            getline(infile, city_name, '(');
            getline(infile, connection_code, ',');
            // All the connection weights are 1 because it's an unweighted graph
            new_vertex->add_connection(connection_code, 1);
        }

        graph[city_code] = new_vertex;

        getline(infile, city_name, '\n');
    }

    infile.close();
}

void display_graph(Graph &graph)
{
    AirportVertex *vertex_ptr;

    for (auto &vertex : graph)
    {
        vertex_ptr = vertex.second;
        std::cout << std::left << std::setw(6) << vertex_ptr->get_item()->get_code();

        for (auto &code : vertex_ptr->get_connections())
            std::cout << std::setw(6) << code;

        std::cout << std::endl;
    }
}

void breadth_first_search(Graph &graph, std::string start,
    AirportQueue *&output_queue, void (*visit)(AirportVertex*, int, AirportQueue*))
{
    int distance = 0;
    AirportVertex *vertex_ptr = graph[start];
    output_queue = new AirportQueue;

    for (auto &vertex : graph)
        if (vertex.first != start)
        {
            vertex.second->set_unvisited();
            vertex.second->set_distance(-1);
        }

    visit(vertex_ptr, distance, output_queue);

    while (output_queue->size())
    {
        vertex_ptr = output_queue->front();
        output_queue->pop();

        for (auto &connection : vertex_ptr->get_connections())
            if (!graph[connection]->is_visited())
                visit(graph[connection], vertex_ptr->get_distance() + 1,
                output_queue);

        vertex_ptr->set_visited();
    }
}

void visit(AirportVertex *vertex, int distance, AirportQueue *output_queue)
{
    vertex->set_visited();
    vertex->set_distance(distance);
    output_queue->push(vertex);

    std::cout << std::left << std::setw(6) << vertex->get_item()->get_code()
        << vertex->get_distance() << std::endl;
}
