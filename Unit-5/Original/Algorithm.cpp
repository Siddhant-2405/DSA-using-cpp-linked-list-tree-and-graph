Algorithm:
 Start the program.
 Input the number of hospital equipment units and possible wiring connections.
 Assign a name or number to each equipment unit.
 Store each wiring connection with its source, destination, and cost.
 Sort all edges in ascending order of cost.
 Initialize each vertex as a separate set.
 Select the edge with the minimum cost.
 Check whether its endpoints belong to different sets:
  - If yes, select the edge and merge the two sets.
  - If no, reject the edge because it creates a cycle.
 Repeat until V - 1 edges have been selected or all edges have been processed.
 Display the selected edges and total wiring cost.
 Display the rejected edges that create cycles.
 Stop.
