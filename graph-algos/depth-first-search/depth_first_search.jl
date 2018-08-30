# Created by AJ Langley on 28 August, 2018
# Displays a depth-first traversal of the input graph

include("./graph.jl")

using Main.Graph

struct Airport
    city::String
    code::String
end

show(z::Vertex) = show(z.item)
show(z::Airport) = println("$(z.code), $(z.city)")

function build_graph(filename::String)
    graph = Dict{String, Vertex{Airport}}()

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

function readkeys!(infile::IOStream, graph::Dict{String, Vertex{Airport}})
    for line in eachline(infile)
        buffer = IOBuffer(line)

        city = readuntil(buffer, ", ")
        code = readuntil(buffer, ", ")

        vertex = Vertex{Airport}(Airport(city, code))
        graph[code] = vertex
    end
end

function readedges!(infile::IOStream, graph::Dict{String, Vertex{Airport}})
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

function depth_first_search(graph::Dict{String, Vertex{Airport}}, start::String,
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


graph = build_graph(ARGS[1])
start = ARGS[2]
println("\nDepth-first traversal starting from $start:")
println("---------------------------------------\n")
depth_first_search(graph, start, show)
println()
