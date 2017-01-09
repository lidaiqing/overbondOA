# Overbond Coding Challenge
## How to execute
###

Git clone this project to your local repository. Use make command to compile the program.

Solution1 is the solution for challenge1. Pass two parameters into the program. The first one is the path to the input file .csv, and the second one is the path to the output file also end with .csv

Solution2 is the solution for challenge2. Its input format is the same as Solution1.

## Technical Reasoning
###

Both solutions follow OOP design. All data structure, input, output and helper functions are wraped into a single class.

For solution1, it stores each rows from input into two vectors by its type. The key idea is to find the closest term of government bond for each corporate bond. Time complexity O(nm).

For solution2, it also stores rows from input into two vectors by its type. The key idea is to find the right range formed by two government bond for each corporate bond. I sort government bond first by its term and use binary search for each corporate bond to find the correct range. Sorting cost O(nlogn), finding range cost O(logn) for each corporate bond. After finding the correct range, use two endings G1, G2 to find the slop of this line. With simple math, we can get the vertical distance from corporate bond C to the line.
