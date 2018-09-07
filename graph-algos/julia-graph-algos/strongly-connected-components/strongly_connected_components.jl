include("../airportgraph.jl")
include("../depth-first-search/depthfirstsearch.jl")

function transpose(graph::AirportGraph)
    graph_transpose = AirportGraph()
    copykeys!(graph, graph_transpose)
    reverse_edges(graph, graph_transpose)

    return graph_transpose
end

function copykeys!(graph::AirportGraph, graph_transpose::AirportGraph)
    for vertex in values(graph)
        println(typeof(vertex))
        v_copy = Vertex{Vertex{Airport}}(vertex)
        graph_transpose[v_copy.item.code] = v_copy
    end
end

function reverse_edges!(graph::AirportGraph, graph_transpose::AirportGraph)
    for vertex in values(graph)
        for edge in vertex.connections
            reverse_edge = Edge(vertex, edge.weight)
            push!(graph_transpose[edge.connection.item.code].connections,
                reverse_edge)
        end
    end
end

function strongly_connected_components(graph::AirportGraph)
    graph_transpose = transpose(graph)
    depth_first_search(graph_transpose, values(graph_transpose)[1], x->())
    sortedvertices = values(graph_transpose)
    sort!(sortedvertices, by=v->(v.finishing_time), rev=true)

    for vertex in sortedvertices
        vertex.visited = false
    end

    findscc(sortedvertices, show)
end

function findscc(sortedvertices::Array{Vertex{Airport}}, processnode)
    n::Int32 = 1

    for vertex in sortedvertices
        println("Strongly Connected Component $n:")
        println("--------------------------------")
        visitscc(vertex, show)
        println("\n")
    end
end

function visitscc(vertex::Vertex{Airport}, processnode)
    vertex.visited = true

    for connection in vertex.connections
        if vertex.visited == false
            visitscc(connection)
        end
    end
end
