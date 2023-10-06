#include "code.hpp"
#include <iostream>


int main(){

    std::vector<std::vector<bool>> t = { {1,1,0},
                                         {1,0,0},
                                         {1,1,0}};

    std::vector<bool> word= {0,0,0};
    std::vector<int> p= {};

    Code a(t,word );
    
    //a.debug();

    std::string f = "s<u+1+10+10";
    std::cout<<ShuntingYard(  f,100000+1+10+10,100000);


    return 0;
}