This took my much longer than I would have liked,

Had to implement a graph strcture and used DFS to backtrack through all possible paths.
I used a very janky way of keeping track of upercase caves, rather than building some type of 
hash table I just assigned each cave as their own segment of an array at a unique index, and made sure capital caves
were assigned values greater than 30 (LOL) so the candidate finder function could tell. 
