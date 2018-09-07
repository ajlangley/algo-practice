# Created by AJ Langley on 6 September, 2018
# Defines the Airport struct and the functions
# used to read a graph of Airport nodes

struct Airport
    city::String
    code::String
end

show(z::Airport) = println("$(z.code), $(z.city)")
