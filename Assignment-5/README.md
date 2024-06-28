1. Now we will make an epp compiler.
 
Created an expression evaluator for the E++ language, supporting fully parenthesized 
arithmetic infix expressions with custom UnlimitedInt and UnlimitedRational classes 
to handle arbitrary-sized integers and rational numbers. Implemented a parser to 
generate unique parse trees and an unbalanced Binary Search Tree (BST) based 
symbol table to manage variables, facilitating accurate expression parsing and 
evaluation.

In epp compiler class we would create expression tree, for storing the expression
of infix, we will first parse the expression and store it in parse tree and then after
the memory for variables present in the parse tree are being allocated through min heap
.and finally we will generate opcodes which is target language and hence compiler is
completed





