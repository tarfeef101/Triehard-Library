# Triehard-Library
A simple library for Triehards, a variation on a compressed binary trie.

Compared to Patricia Tries, these tries do not store "compressed" substrings as the full length of the non-shared part. These take an entirely different approach. Since patricia tries take non-shared substrings and just store them in one node, they reduce the number of nodes, but not storage space. This also means searching them takes, one average, log (m) (where m is height of the tree) plus k, where k is the length of the string since a full comparison still occurs.

On the other hand, triehards compress by reducing the actual amount of data being stored. Each node has a pointer to its children (as usual), a flag to indicate if a stored value ends there (as usual), and a magnitude. This magnitude represents the amount of repeat digits represented by this node. So, if we have a string 11011110, there are 4 nodes, of magnitudes 2, 1, 4, and 1, respectively. This allows for compression based on repeat digits, without increasing the size (each node is of constant size, and there are less nodes than the total length of all strings when compression is possible). This makes the storage overhead lower than O(n) where n is the length of all strings.

As for searching, these retain the same efficiency as a standard trie O(k), compared to the longer search times of patricia tries. Since the compression is based on repeat digits instead of unshared substrings, this allows for standard searching to still occur.
