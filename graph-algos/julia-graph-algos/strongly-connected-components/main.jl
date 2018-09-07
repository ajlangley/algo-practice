include("./strongly_connected_components.jl")

graph = buildgraph(ARGS[1])
strongly_connected_components(graph)
