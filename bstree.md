#  Antworten

- When would you use a sorted binary tree over a linked list?  
When I have a dataset, which I have to search trough regularily.
- What would you change if the tree had to support not just integers, but any
  type of data?  
I would implement a generic compare method, which compares the node value.
- Why do we use modules instead of putting everything a single file?  
So we can have different implementations, which are easily swappable. Also we want to split the logic, to keep it clean.
- Is the development cycle (i.e. changing a source file, recompiling and
  running tests) faster when using modules? Explain your answer.  
It doesn't matter in my opinion.
- What is a _header guard_ and why is it needed?  
It checks wether another module already included a specific library and only includes ith, when it is not already included. Avoids multiple includes of the same library.
- Why is `bstree` not _defined_ in the header file? What are the
  implications?  
It allows different implementations of the struct.
- Explain the `const` in the parameter list of `bstree_print`, is it required?  
It is not required, but is considered clean programming style. It makes the parameter immutable.
- Explain memory leaks. Why are memory leaks bad? You should know how to use `valgrind` to check your program for memory leaks.  
Memory leaks are ressources from the heap, which are allocated from the program, but never returned. When the program runs for a long time it will run out of memory.
valgrind --tool=memcheck
- What is the reason behind writing _everything_ in English?
So everybody can understand the code
- Why should you use `static` for _non-exported_ functions?
So they are only accessable inside the class
- Why should we comment our source code? Is it always needed? What should the
  comment state? What is _self-documenting code_?  
  Obvious code, which is self eexplaining trough function name and control flow, some opinions say that when you have to comment your code, you should refactor your code (especially in business logic application)
- Why should the module not output debug messages?
Because it would confuse somebody, who uses the module in combination with another module/code. If you really want to comment your code, there are often options which let you set a debug level for comments and disable them on production.
- Why and when should you use `assert`?
To add diagnostic debugging to your c file.
- What are the benefits of using `make` over calling the compiler by hand?
Compile chain for more complex compilations
- Imagine it was your job to design the interface for the bstree module
  (writing `bstree.h`). What would you have done differently, and why?  
node structure and and generic compare function, but overall it seems okay