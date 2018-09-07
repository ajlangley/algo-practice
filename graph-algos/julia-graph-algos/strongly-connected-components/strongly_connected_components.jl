include("../airportgraph.jl")
include("../depth-first-search/depthfirstsearch.jl")

function transpose(graph::AirportGraph)
    graphtranspose = AirportGraph()
    copykeys!(graph, graphtranspose)
    reverse_edges!(graph, graphtranspose)

    return graphtranspose
end

function copykeys!(graph::AirportGraph, graphtranspose::AirportGraph)
    for vertex in values(graph)
        vcopy = AirportVertex(vertex.item)
        vcopy.discoverytime = vertex.discoverytime
        vcopy.finishingtime = vertex.finishingtime
        graphtranspose[vcopy.item.code] = vcopy
    end
end

function reverse_edges!(graph::AirportGraph, graphtranspose::AirportGraph)
    for vertex in values(graph)
        for edge in vertex.connections
            reverse_edge = Edge(graphtranspose[vertex.item.code], edge.weight)
            push!(graphtranspose[edge.connection.item.code].connections,
                reverse_edge)
        end
    end
end

function strongly_connected_components(graph::AirportGraph)
    depthfirstsearch(graph, collect(keys(graph))[1], x->())
    graphtranspose = transpose(graph)
    sortedvertices = collect(values(graphtranspose))
    sort!(sortedvertices, by=v->(v.finishingtime), rev=true)
    foreach(v->(v.visited = false), sortedvertices)
    findscc(sortedvertices, show)
end

function findscc(sortedvertices::Array{AirportVertex}, processnode)
    n::Int32 = 1

    println("\n")

    for vertex in sortedvertices
        if vertex.visited == false
            println("Strongly Connected Component $n:")
            println("------------------------------")
            visitscc(vertex, show)
            println("\n")
            n += 1
        end
    end
end

function visitscc(vertex::AirportVertex, processnode)
    processnode(vertex)
    vertex.visited = true

    for edge in vertex.connections
        #println("\t", edge.connection.item.code)
        if edge.connection.visited == false
            visitscc(edge.connection, processnode)
        end
    end
end
