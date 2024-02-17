/*

#include <iostream>
#include "TraversableStack.hpp"

int main() {


    TraversableStack stack;

    // Adding tokens to the stack
    Token token1(1, 0);
    token1.makeOpenTag("tag1");
    stack.addLast(token1);

    Token token2(2, 0);
    token2.makeOpenTag("tag2");
    stack.addLast(token2);

    Token token3(3, 0);
    token3.makeCloseTag("tag3");
    stack.addLast(token3);

    // Print the size of the stack
    std::cout << "Size of stack: " << stack.size() << std::endl;

    // Print the last token in the stack
    std::cout << "Last token in stack: ";
    stack.last().print();

    // Check if a tag is a member of the stack
    std::cout << "Is 'tag2' a member of the stack? ";
    if (stack.rmember("tag2")) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }

    // Remove a token from the stack
    std::cout << "Removing 'tag2' from the stack..." << std::endl;
    stack.rremove("tag2");

    std::cout << "Is 'tag2' a member of the stack? ";
    if (stack.rmember("tag2")) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }

    // Print the size of the stack after removal
    std::cout << "Size of stack after removal: " << stack.size() << std::endl;

    // Print tokens backward with indentation
    std::cout << "Printing tokens with tag 'tag1' backward with indentation:" << std::endl;
    stack.printBackwardUnit("tag1", false);

     */


#include <iostream>
#include "TagParser.hpp"

    int main() {
        TagParser parser;
        std::string inputFile = "phase2_input2.txt"; // Assuming you have an input HTML file named "input.html"

        std::cout << "Parsing tags from file: " << inputFile << std::endl;
        parser.parseTags(inputFile);

        return 0;
    }



