#include "code.hpp"
#include <iostream>

int main()
{

    std::vector<std::vector<bool>> t = {{1, 1, 0,1,0,0,0,0,0,1, 0, 0,0,1,0,0,0,0},
                                        {1, 0, 0,1,0,0,0,0,0,1, 0, 0,1,1,0,0,0,0},
                                        {1, 0, 0,0,1,0,1,0,0,0, 0, 0,1,1,1,0,1,0},
                                        {1, 1, 0,1,0,0,1,0,1,1, 0, 0,1,0,1,0,0,0}};

    std::vector<bool> word = {1,1, 1, 1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1};
    std::vector<int> p = {};

    Code a(t, word);

    while(!a.containsDuplicateState() && a.sumCheckNodeStates()!=0){
        a.updateWord("u>=s");
        a.debug();
    }

    return 0;
}