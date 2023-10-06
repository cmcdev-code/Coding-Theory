#include "code.hpp"
#include <iostream>

int main()
{

    std::vector<std::vector<bool>> t = {
        {0, 1, 1, 1, 1, 0, 0, 0},
        {1, 0, 1, 1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0, 0, 1, 0},
        {1, 1, 1, 0, 0, 0, 0, 1},
    };

    std::vector<bool> word = {0, 0, 0, 1, 1, 1, 0, 0};
    std::vector<int> p = {};

    Code a(t, word);

    while (!a.containsDuplicateState() && a.sumCheckNodeStates() != 0)
    {
        a.updateWord("u=s");
        a.debug();
    }
    a.debug();

    return 0;
}