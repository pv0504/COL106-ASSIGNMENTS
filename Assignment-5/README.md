Expression Evaluator for E++ Language:

Supports fully parenthesized arithmetic infix expressions.
Uses custom UnlimitedInt and UnlimitedRational classes for handling arbitrary-sized integers and rational numbers.
Parser for Generating Parse Trees:

Parses expressions and generates unique parse trees.
Utilizes an unbalanced Binary Search Tree (BST) based symbol table to manage variables.
Expression Tree Creation:

Stores the parsed infix expression in a parse tree.
Memory Allocation:

Allocates memory for variables present in the parse tree using a min heap.
Opcode Generation:

Generates opcodes for the target language.
Compiler Completion:

Combines the expression tree creation, memory allocation, and opcode generation to complete the compiler.
