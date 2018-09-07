# Created by AJ Langley on 6 September, 2018
# Defines a type for a graph of airport and
# the functions used to build an airport graph
# from a file

include("./graph.jl")
include("./airport.jl")

AirportGraph = Dict{String, Vertex{Airport}}
AirportVertex = Vertex{Airport}

function buildgraph(filename::String)
    graph = AirportGraph()

    open(filename) do infile
        readline(infile)
        readkeys!(infile, graph)
        seekstart(infile)
        readline(infile)
        readedges!(infile, graph)
        close(infile)
    end

    return graph
end

function readkeys!(infile::IOStream, graph::AirportGraph)
    for line in eachline(infile)
        buffer = IOBuffer(line)

        city = readuntil(buffer, ", ")
        code = readuntil(buffer, ", ")

        vertex = Vertex{Airport}(Airport(city, code))
        graph[code] = vertex
    end
end

function readedges!(infile::IOStream, graph::AirportGraph)
    for line in eachline(infile)
        buffer = IOBuffer(line)
        readuntil(buffer, ", ")

        vertex = graph[readuntil(buffer, ", ")]

        for _ in 1:parse(Int32, readuntil(buffer, ", "))
            readuntil(buffer, "(")
            connection = readuntil(buffer, ", ")
            weight = parse(Int32, readuntil(buffer, ")"))
            edge = Edge(graph[connection], weight)
            push!(vertex.connections, edge)
        end
    end
end

function displaygraph(graph::AirportGraph)
    for vertex in values(graph)
        print(vertex.item.code)
        for edge in vertex.connections
            print(" ", edge.connection.item.code)
        end
        println("\n")
    end
end
