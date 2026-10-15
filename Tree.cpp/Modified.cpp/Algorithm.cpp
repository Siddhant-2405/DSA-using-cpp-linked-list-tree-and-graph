Algorithm

Start.
Create an empty AVL tree and an empty BST.
Read the number of elements.
Insert each element into both trees.
Maintain the AVL tree's balance using rotations.
Read the number of keys to search.
Read a search key.
Initialize the comparison counter and path length to zero.
Start searching from the root of the AVL tree.
Display each visited node and increment the comparison counter and path length.
If the key matches the current node, display "Key found".
If the key is smaller, move to the left child; otherwise, move to the right child.
Continue until the key is found or a NULL node is reached.
Display the search path, comparison count, and path length.
Repeat Steps 8–14 for the ordinary BST.
Repeat the search for all remaining keys.
Compare the results of the AVL tree and BST.
Stop.
