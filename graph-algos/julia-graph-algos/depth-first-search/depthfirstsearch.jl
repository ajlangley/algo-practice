# Created by AJ Langley on 28 August, 2018
# Defines functions used to run depth-first
# traversal on an input graph

include("./../airportgraph.jl")

function depthfirstsearch(graph::AirportGraph, start::String,
    processnode)
    for vertex in values(graph)
        vertex.visited = false
    end

    # Need to figure out how to initialize a 0-dim array for this purpose
    time = Int32[0]
    graph[start].visited = true
    visit!(time, graph[start], processnode)

    # Iterate through the vertices and check if they've been visited, in
    # case of an unconnected graph
    for vertex in values(graph)
        if vertex.visited == false
            visit!(time, vertex, processnode)
        end
    end
end

function visit!(time::Array{Int32, 1}, vertex::Vertex{Airport}, processnode)
    time[1] += 1
    vertex.discovery_time = time[1]
    vertex.visited = true
    processnode(vertex)

    for edge in vertex.connections
        if edge.connection.visited == false
            visit!(time, edge.connection, processnode)
        end
    end

    vertex.finishing_time = time[1]
    time[1] += 1
end
