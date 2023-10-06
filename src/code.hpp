#pragma Once
#include <vector>
#include <iostream>
#include <string>


class Code{

    public:
    Code(): matrix(3, std::vector<bool>(3,0)), previousWord(0), word(matrix.at(0).size(),0){}

    Code(std::vector<std::vector<bool>>  & matrix,
        std::vector<bool> & word,
         std::vector<int>  previousWord={}
         ) :
         matrix(matrix) ,word(word), previousWord(previousWord){}

    void debug(){

    for(auto & itr :  this->matrix){
        
        for( auto i : itr){
            std::cout<<i<<" ";
        }
        std::cout<<"\n";
        }
    }

    void setMatrix(std::vector<std::vector<bool>> matrix){
        this->matrix=matrix;
    }
    void setWord(std::vector<bool> word){
        this->word=word;
    }
    void setPreviousWord(std::vector<int> previousWord){
        this->previousWord=previousWord;
    }
    
    std::vector<std::vector<bool>> getMatrix() const{
        return this->matrix;
    }

    std::vector<bool> getWord() const{
        return this->word;
    }
    
    std::vector<int> getPreviousWord(){
        return this->previousWord;
    }
    
    private:
    
    //matrix that will represent the tanner graph 
    std::vector<std::vector<bool>> matrix;
    
    //the code word 
    std::vector<bool> word;

    //the representation of the input is a binary number 
    std::vector<int> previousWord;
};

#include <stack>
#include <sstream>
 


int type(char c){
    //if its a value in the range 0-9
    if( int(c) >= 48 && int(c)<=57){
        return int(c)-48;
    }
    //the type of operator only accepts + - > < = 
    if( int(c)== 43){
        return 10;
    }
    if( int(c) == 45){
        return 11;
    }
    if(int(c)== 62){
        return 12;
    }
    if(int(c)== 60){
        return 13;
    }
    if( int(c)== 61){
        return 14;
    }
    return -1;
}

bool ShuntingYard(std::string str, int s ,int u){


    for (int i = 0; i < str.size(); i++) {
        if (str[i] == 's') {
            str.erase(i, 1); 
            str.insert(i, std::to_string(s)); 
            i += std::to_string(s).size() - 1;
        }
        else if (str[i] == 'u') {
            str.erase(i, 1);
            str.insert(i, std::to_string(u));
            i += std::to_string(u).size() - 1;
        }
    }
    
    //removing white space
    std::stringstream ss(str);
    std::string tok;
    std::string result;
    while(ss>>tok){
        result+=tok;
    }
    std::stack<int> numbers;
    std::stack<int> arithmeticOps;
    std::stack<int> logicOperators;
    for(int i =0 ; i< result.size();i++){

        if( isdigit(result[i])){
            std::string numString="";
            while(i < result.size() && isdigit(result[i]) ){
                numString+=(std::to_string(type(result[i])));
                i+=1;
            }
            numbers.push(std::stoi(numString));
        }


        if(type(result[i])==11 && i+ 1 < result.size() && type(result[i+1]>=0 && type(result[i+1]<= 9))){
            numbers.push(-1 * type(result[i+1]));
            i+=1;
            
        }

        if(type(result[i])== 10){
            arithmeticOps.push(type(result[i]));
        }
        if(type(result[i])== 12 || type(result[i])== 13 || type(result[i])== 14){
            logicOperators.push(type(result[i]));
        }
    }
    while(numbers.size()>=3){
        int b= numbers.top();
        numbers.pop();

        int a = numbers.top();
        numbers.pop();
            
       
        if(arithmeticOps.top()==10){
            arithmeticOps.pop();
            numbers.push(a+b);
        
        }
    }
    int valLogic=1;

  
    while(logicOperators.size()>0){
        valLogic*=logicOperators.top();
        logicOperators.pop();

    }

    if(valLogic== 196 || valLogic== 14){
        int a= numbers.top();
        numbers.pop();

        int b= numbers.top();
       
        numbers.pop();
        return a ==b;
    }
    if(valLogic == 12){
        int a= numbers.top();
        numbers.pop();

        int b= numbers.top();
        numbers.pop();

        return b > a;
    }

    if(valLogic== 168){
          int a= numbers.top();
        numbers.pop();

        int b= numbers.top();
        numbers.pop();

        return b >=a ;
    }
    if( valLogic == 13){
          int a= numbers.top();
        numbers.pop();

        int b= numbers.top();
        numbers.pop();
        return b < a;
    }
    if (valLogic == 182){
        int a= numbers.top();
        numbers.pop();

        int b= numbers.top();
        numbers.pop();
        return b <= a;
    }
    
    return false;
}