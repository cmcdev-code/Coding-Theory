#pragma Once
#include <vector>
#include <iostream>
#include <string>

static int binaryToInt(std::vector<bool> input)
{
    int a = 0;
    for (int i = 0; i < input.size(); i++)
    {
        a += input.at(i) * 2 ^ i;
    }
    return a;
}
static std::string binToString(std::vector<bool> input)
{
    std::string str = "";

    for (auto itr : input)
    {
        str += itr ? "1" : "0";
    }
    return str;
}

#include <stack>
#include <sstream>

int type(char c)
{
    // if its a value in the range 0-9
    if (int(c) >= 48 && int(c) <= 57)
    {
        return int(c) - 48;
    }
    // the type of operator only accepts + - > < =
    if (int(c) == 43)
    {
        return 10;
    }
    if (int(c) == 45)
    {
        return 11;
    }
    if (int(c) == 62)
    {
        return 12;
    }
    if (int(c) == 60)
    {
        return 13;
    }
    if (int(c) == 61)
    {
        return 14;
    }
    return -1;
}

bool ShuntingYard(std::string str, int s, int u)
{

    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == 's')
        {
            str.erase(i, 1);
            str.insert(i, std::to_string(s));
            i += std::to_string(s).size() - 1;
        }
        else if (str[i] == 'u')
        {
            str.erase(i, 1);
            str.insert(i, std::to_string(u));
            i += std::to_string(u).size() - 1;
        }
    }

    // removing white space
    std::stringstream ss(str);
    std::string tok;
    std::string result;
    while (ss >> tok)
    {
        result += tok;
    }
    std::stack<int> numbers;
    std::stack<int> arithmeticOps;
    std::stack<int> logicOperators;
    for (int i = 0; i < result.size(); i++)
    {

        if (isdigit(result[i]))
        {
            std::string numString = "";
            while (i < result.size() && isdigit(result[i]))
            {
                numString += (std::to_string(type(result[i])));
                i += 1;
            }
            numbers.push(std::stoi(numString));
        }

        if (type(result[i]) == 11 && i + 1 < result.size() && isdigit(result[i + 1]))
        {
            std::string numString = "";
            while (i + 1 < result.size() && isdigit(result[i + 1]))
            {
                numString += (std::to_string(type(result[i])));
                i += 1;
            }
            int a = std::stoi(numString);
            a *= -1;
            numbers.push(a);
            i += 1;
        }

        if (type(result[i]) == 10)
        {
            arithmeticOps.push(type(result[i]));
        }
        if (type(result[i]) == 12 || type(result[i]) == 13 || type(result[i]) == 14)
        {
            logicOperators.push(type(result[i]));
        }
    }
    while (numbers.size() >= 3)
    {
        int b = numbers.top();
        numbers.pop();

        int a = numbers.top();
        numbers.pop();

        if (arithmeticOps.top() == 10)
        {
            arithmeticOps.pop();
            numbers.push(a + b);
        }
    }
    int valLogic = 1;

    while (logicOperators.size() > 0)
    {
        valLogic *= logicOperators.top();
        logicOperators.pop();
    }

    if (valLogic == 196 || valLogic == 14)
    {
        int a = numbers.top();
        numbers.pop();

        int b = numbers.top();

        numbers.pop();
        return a == b;
    }
    if (valLogic == 12)
    {
        int a = numbers.top();
        numbers.pop();

        int b = numbers.top();
        numbers.pop();

        return b > a;
    }

    if (valLogic == 168)
    {
        int a = numbers.top();
        numbers.pop();

        int b = numbers.top();
        numbers.pop();

        return b >= a;
    }
    if (valLogic == 13)
    {
        int a = numbers.top();
        numbers.pop();

        int b = numbers.top();
        numbers.pop();
        return b < a;
    }
    if (valLogic == 182)
    {
        int a = numbers.top();
        numbers.pop();

        int b = numbers.top();
        numbers.pop();
        return b <= a;
    }

    return false;
}

class Code
{

public:
    Code() : matrix(3, std::vector<bool>(3, 0)), previousWord(0), word(matrix.at(0).size(), 0) { whatFunction = "u>=s"; }

    Code(std::vector<std::vector<bool>> &matrix,
         std::vector<bool> &word,
         std::vector<int> previousWord = {}) : matrix(matrix), word(word), previousWord(previousWord) { whatFunction = "u>=s"; }

    std::string getWordAsString() const
    {
        std::string wordAsString;
        for (auto itr : this->word)
        {
            wordAsString += std::to_string(itr);
        }
        return wordAsString;
    }

    void debug()
    {

        std::cout << "Code Word is \n";

        for (auto itr : this->word)
        {
            std::cout << itr << " ";
        }

        std::cout << "\n previous code words \n";
        for (auto &itr : this->previousWord)
        {
            std::cout << itr << " ";
        }
    }
    std::string whatFunction;

    void updateWord()
    {
        // First to find the neighbor check nodes that are 0
        std::vector<bool> checkNodesState = this->stateOfCheckNodes();

        for (int i = 0; i < this->matrix.at(0).size(); i++)
        {
            int numberBadState = 0;
            for (int j = 0; j < this->matrix.size(); j++)
            {
                numberBadState += this->matrix.at(j).at(i) * checkNodesState.at(j);
            }
            if (ShuntingYard(whatFunction, numberBadState, this->matrix.size() - numberBadState))
            {
                this->word.at(i) = !this->word.at(i);
            }
        }
        this->previousWordString.push_back(binToString(this->word));
        this->previousWord.push_back(binaryToInt(this->word));
    }

    std::vector<bool> stateOfCheckNodes() const
    {
        std::vector<bool> checkNodesState;

        for (int i = 0; i < this->matrix.size(); i++)
        {
            int state = 0;
            for (int j = 0; j < this->matrix.at(0).size(); j++)
            {
                state += this->word.at(j) * this->matrix.at(i).at(j);
            }
            checkNodesState.push_back(state % 2);
        }

        return checkNodesState;
    }

    int sumCheckNodeStates() const
    {
        int sum = 0;
        std::vector<bool> checkNode = this->stateOfCheckNodes();
        for (auto itr : checkNode)
        {
            sum += itr;
        }
        return sum;
    }
    int sumOfMatrix() const
    {
        int sum = 0;
        for (auto &itr : this->matrix)
        {
            for (auto i : itr)
            {
                sum += i;
            }
        }
        return sum;
    }

    bool containsDuplicateState() const
    {
        for (int i = 0; i < this->previousWord.size(); i++)
        {
            for (int j = 0; j < this->previousWord.size(); j++)
            {
                if (i != j)
                {
                    if (previousWord.at(i) == previousWord.at(j))
                    {
                        return 1;
                    }
                }
            }
        }
        return 0;
    }

    void setMatrix(std::vector<std::vector<bool>> matrix)
    {
        this->matrix = matrix;
    }
    void setWord(std::vector<bool> word)
    {
        this->word = word;
    }
    void setPreviousWord(std::vector<int> previousWord)
    {
        this->previousWord = previousWord;
    }

    std::vector<std::vector<bool>> getMatrix() const
    {
        return this->matrix;
    }

    std::vector<bool> getWord() const
    {
        return this->word;
    }

    std::vector<int> getPreviousWord() const
    {
        return this->previousWord;
    }

    void setPreviousWordString(std::vector<std::string> &previousWordString)
    {
        this->previousWordString = previousWordString;
    }

    std::vector<std::string> getPreviousWordAsString() const
    {
        return this->previousWordString;
    }

    void operator=(const Code &c)
    {
        this->matrix = c.getMatrix();
        this->word = c.getWord();
        this->previousWord = c.getPreviousWord();
        this->previousWordString = c.getPreviousWordAsString();
    }

private:
    // matrix that will represent the tanner graph
    std::vector<std::vector<bool>> matrix;

    // the code word
    std::vector<bool> word;

    // the representation of the input is a binary number
    std::vector<int> previousWord;

    std::vector<std::string> previousWordString;
};
