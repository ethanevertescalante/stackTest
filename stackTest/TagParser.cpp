//
// Created by Ethan on 2/12/2024.
//

#include "TagParser.hpp"
#include "Token.hpp"
#include <iomanip>
#include <iostream>

TagParser::TagParser(): stack{TraversableStack()}, openTag(0,0), closeTag(0,0){


}



void TagParser::parseTags(std::string nameOfInputFile) {
    Tokenizer tokenizer(nameOfInputFile);

    Token token = tokenizer.getToken();
    while (!token.endOfFile()) {
        if( token.isOpenTag() )
            handleOpenTag(tokenizer, token);
        else if( token.isCloseTag() )
            handleCloseTag(tokenizer, token);
        else if(token.isCloseStandAloneTag())
            handleStandAloneCloseTag(token);
        else if(token.isCloseAngleBracket() || token.isOpenAngleBracket()) {
            token.print();
            std::cout << (token.isCloseAngleBracket() ? " ignoring random close angle-bracket."
                                                      : " ignoring random open angle-bracket.") << std::endl;
        } else {
            token.print();
            std::cout << " unknown token."  << std::endl;
        }
        token = tokenizer.getToken(); //get next token
    }
// tokens have finished, but you want to determine if
// there are any open tags that have not been matched.

    while(!stack.empty()){
        Token noMatchingCloseTag = stack.last();
        noMatchingCloseTag.print();
        std:: cout << " doesn't have a matching close tag. Will discard it." << std::endl;
        stack.popLast();
    }

    printWellFormedTags();

}

void TagParser::handleOpenTag(Tokenizer &tokenizer, Token &token) {
    std::string tName = token.tagName();
    stack.addLast(token);
    token = tokenizer.getToken();
    if(!token.isCloseAngleBracket())
    {
        stack.popLast();
    }

}

void TagParser::handleCloseTag(Tokenizer &tokenizer, Token &token) {
    std::string nameTag = token.tagName();

    stack.addLast(token);
    token = tokenizer.getToken();
    if(!token.isCloseAngleBracket())
    {
        stack.popLast();
    }

    pairTokens(nameTag);





}

void TagParser::handleStandAloneCloseTag(Token &token) {
    std::string tagName = token.tagName();
    std::pair<Token, Token> pairOfTags = {openTag, closeTag};
    openTag = stack.last();
    closeTag = token;

    tagLocations.push_back(pairOfTags);
    mapPair(tagName,pairOfTags);


}

void TagParser::pairTokens(std::string tagName) {

    std::pair<Token, Token> pairOfTags = {openTag, closeTag};

    while(stack.rmember(tagName))
    {

        if(stack.last().isOpenTag())
        {
            openTag = stack.last();
            pairOfTags.first = openTag;
            stack.popLast();

        }else if(stack.last().isCloseTag())
        {
            closeTag = stack.last();
            pairOfTags.second = closeTag;
            stack.popLast();

        }



    }



    tagLocations.push_back(pairOfTags);

    mapPair(tagName, pairOfTags);


}


void TagParser::mapPair(std::string tagName, std::pair<Token, Token> pairTags) {


        allTagLocations[tagName] = std::vector<std::pair< Token, Token>>();
        allTagLocations[tagName].push_back(pairTags);

}





void TagParser::printWellFormedTags() {
    std::cout << "The following is a list of well-formed HTML tags." << std::endl;
    std::cout << std::endl;
    for (auto mapIter = allTagLocations.begin(); mapIter != allTagLocations.end(); ++mapIter) {
        // our map, pairs an array of Tokens with tag-name strings.
        std::cout << mapIter->first << " appeared in the following " << mapIter->first.size() << " location(s)." << std::endl;
        std::vector<std::pair<Token, Token>> locations = mapIter->second;
        for(auto vIter = locations.begin(); vIter != locations.end(); ++vIter) {
            // Each element in the vector is a pair of tokens.
            std::cout << "\t";
            vIter->first.print();
            std::cout << std::setw(3) << "--" << std::setw(2);
            vIter->second.print();
            std::cout << std::endl;
        }

        std::cout << std::endl;

    }
}