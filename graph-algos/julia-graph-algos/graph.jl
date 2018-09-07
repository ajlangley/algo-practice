# Created by AJ Langley on 28 August, 2018
# Defines the types used to create a graph

struct Edge
    # didn't assert Vertex{T} type because mutually recursive type definitions
    # are not supported as of v 1.0
    connection
    weight::Int32
end

mutable struct Vertex{T}
    item::T
    connections::Array{Edge, 1}
    visited::Bool
    discovery_time::Int32
    finishing_time::Int32
    distance::Int32
    Vertex{T}(my_item) where {T} = (x = new(); x.item = my_item;
        x.connections = Array{Edge, 1}(); return x)
    Vertex{Vertex{T}}(v) where {T} = (x = new(); x.item = v.item;
        x.connections = Array{Edge, 1}(); x.discovery_time = v.discovery_time;
        x.finishing_time = v.finishing_time)
end

show(z::Vertex) = show(z.item)
