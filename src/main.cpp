#include "code.hpp"
#include <iostream>


int main(){

    std::vector<std::vector<bool>> t = { {1,1,0},
                                         {1,0,0},
                                         {1,1,0}};

    std::vector<bool> word= {0,0,0};
    std::vector<int> p= {};

    Code a(t,word );
    
    a.debug();

    std::string f = "s=u+1";
    std::cout<<ShuntingYard(  f,2,9);


    return 0;
}