# Created by AJ Langley on 7 September, 2018
# Displays a depth-first traversal of the input graph

include("./depthfirstsearch.jl")

graph = buildgraph(ARGS[1])
start = ARGS[2]
println("\nDepth-first traversal starting from $start:")
println("---------------------------------------\n")
depthfirstsearch(graph, start, show)
println()
