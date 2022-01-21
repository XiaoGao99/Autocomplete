# Overview 

Use a Binary Search Tree to store key-value pairs where the values represent the frequency of keys (cities, words, movie names, etc)

Traverse the BST to find all entries that match the given prefix. Sort them by weight

### File format 

- The first line of the file must be an int which indicates number of lines of the file.
- Each line of the file must follow this format: text(string) \t weight(int)

### Compile 

`g++ *.cpp`

### To run 

- For Windows: `./a.exe filename keyword`
- For Linux: `./a.out filename keyword`
- Note: Keyword is case sensetive 

### Example outputs

`./a.exe cities.txt Seat` 

Seattle, Washington, United States      608660\
Seaton, South Australia, Australia      9704\
Seaton Delaval, United Kingdom  7219\
Seaton, United Kingdom  5240\
Seat Pleasant, Maryland, United States  4542

### cpp files

- bstmap.h/cpp: Binary Search Tree header and implementation
- bstmapprinter.cpp: Functions for printing BST on screen
- autocomple.h/cpp: Autocomplete
- testbst.cpp: Testing BST functions
- testac.cpp: Testing Autocomplete functions
- main.cpp: Accepts inputs to return strings sorted by their frequency


### Text files for testing

- small.txt Short list of words
- wiktionary.txt Large list of words
- cities.txt Cities





