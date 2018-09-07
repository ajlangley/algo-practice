module Graph

export Vertex, Edge, show

struct Edge
    # didn't asert Vertex{T} type because mutually recursive type definitions
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
end

end
