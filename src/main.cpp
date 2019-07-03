#include "betaReducer.hpp"

int main(int argc, char * argv[])
{ const bool printDebug = (argc > 1)? true : false;
  std::cout<<"- Type exit to quit program.\n";
  while(true)
  { // input string that stores line that is read in
    std::string in;
    std::cout<<"\n input: ";
    getline(std::cin,in);
    if(in == "exit")
      break;

    if(printDebug) std::cout<<"\n------------------------\n\n";
    if(printDebug) std::cout<<"Lexical Analizer Output:\n\n";

    // string vector that stores the result of the lexical analizer
    std::vector<std::string> tokens;

    // perform the lexical analysis
    lexicalAnalyser(in, tokens);

    // print the output
    if(printDebug)
    { for(int i = 0; i < tokens.size(); i++)
        std::cout<<tokens[i]<<std::endl; }

    if(printDebug) std::cout<<"\n------------------------\n\n";
    if(printDebug) std::cout<<"Parser Output:\n\n";
    // parse the data using the string tokens
    Lambda * ptr = parser(tokens);

    // print the result
    if(printDebug) printSimple(ptr);

    if(printDebug) std::cout<<"\n------------------------\n\n";
    if(printDebug) std::cout<<"Beta Reduction Output:\n\n";

    // perform the recursive beta reduction
    Lambda * result = betaReducer(ptr);
    std::cout<<"output: ";
    printSimple(result);
    std::cout<<"\n";
    if(printDebug) std::cout<<"------------------------\n\n";

    // clean up to avoid memory leaks
    delete ptr;
    delete result;
    tokens.clear();
    in.clear(); }
  return 0; }
