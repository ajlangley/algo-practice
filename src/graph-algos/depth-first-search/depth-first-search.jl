#=iter = [4, 5, 6]
next = iterate(iter)

while next !== nothing
    (i, state) = next
    println(i, " ", state)
    global next = iterate(iter, state)
end
=#

struct Airport
    city::string
    code::string

mutable struct Edge{T, Int32}
    connection::T
    weight::Int32

EdgeArray = Array{Edge, 1}

mutable struct Vertex{T}
    item::T
    connections::EdgeArray
    visited::bool
    discovery_time::Int32
    finishing_time::Int32
    distance::Int32
    Vertex(my_item) = new(my_item, EdgeArray(), false, -1, -1, -1)


function build_graph!(filename::string, )
