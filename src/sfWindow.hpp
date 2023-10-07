#pragma Once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "code.hpp"

class SfWindow
{

public:
    sf::RenderWindow window;
    Code code;
    float shapeDimensions;
    float spacing;
    float circleShapeAlignment;
    float squareShapeAlignment;
    float offset;

    sf::Color colorOfCircleTrue;
    sf::Color colorOfCircleFalse;
    sf::Color colorOfSquareTrue;
    sf::Color colorOfSquareFalse;
    sf::Color backgroundColor;

    std::vector<sf::RectangleShape> shapeR;
    std::vector<sf::CircleShape> shapeC;

    sf::VertexArray line;

    SfWindow()
    {
        this->window.create(sf::VideoMode(1280, 720), "Iterative Decoding");
        this->shapeDimensions = 20;
        this->circleShapeAlignment = 20.0f;
        this->spacing = 3;
        this->offset = 30;
        this->colorOfCircleFalse = sf::Color::Red;
        this->colorOfCircleTrue = sf::Color::Green;
        this->colorOfSquareTrue = sf::Color::Yellow;
        this->colorOfSquareFalse = sf::Color::Blue;
        this->backgroundColor= sf::Color(45,54,59);

    }
    float getOffset() const
    {
        return this->offset;
    }
    void setOffset(float offset)
    {
        this->offset = offset;
    }

    float getSquareShapeAlignment() const
    {
        return this->squareShapeAlignment;
    }
    void setSquareShapeAlignment(float squareShapeAlignment)
    {
        this->squareShapeAlignment = squareShapeAlignment;
    }

    float getCircleShapeAlignment() const
    {
        return this->circleShapeAlignment;
    }
    void setCircleShapeAlignment(float circleShapeALignment)
    {
        this->circleShapeAlignment = circleShapeALignment;
    }

    float getShapeDim() const
    {
        return this->shapeDimensions;
    }

    void setShapeDim(float shapeDimensions)
    {
        this->shapeDimensions = shapeDimensions;
        this->line.setPrimitiveType(sf::Lines);
    }

    SfWindow(Code &code, int shapeDimensions = 20,
             float shapeAliment = 20.0f,
             int spacing = 3,
             int offset = 30,
             sf::Color colorOfCircleFalse = sf::Color::Red,
             sf::Color colorOfCircleTrue = sf::Color::Green,
             sf::Color colorOfSquareTrue = sf::Color::Yellow,
             sf::Color colorOfSquareFalse = sf::Color::Blue,
             sf::Color backgroundColor = sf::Color(45, 54, 59))
    {
        this->window.create(sf::VideoMode(1280, 800), "Iterative Decoding");
        this->code = code;
        this->shapeDimensions = shapeDimensions;
        this->circleShapeAlignment = circleShapeAlignment;
        this->line.setPrimitiveType(sf::Lines);
        this->spacing = spacing;
        this->offset = offset;
        this->colorOfCircleFalse = sf::Color::Red;
        this->colorOfCircleTrue = sf::Color::Green;
        this->colorOfSquareTrue = sf::Color::Yellow;
        this->colorOfSquareFalse = sf::Color::Blue;
        this->backgroundColor=backgroundColor;
    }
    float getSpacing() const
    {
        return this->spacing;
    }

    void setSpacing(float spacing)
    {
        this->spacing = spacing;
    }

    void initializeShapes()
    {
        std::vector<std::vector<bool>> matrix = this->code.getMatrix();
        std::vector<bool> word = this->code.getWord();

        for (int i = 0; i < word.size(); i++)
        {
            sf::CircleShape shape(this->getShapeDim() / 2);
            shape.setPosition(sf::Vector2f(this->getCircleShapeAlignment(), this->getShapeDim() * this->getSpacing() * i + this->getOffset()));
            shape.setFillColor(word.at(i) ? this->colorOfCircleTrue : this->colorOfCircleFalse);
            this->shapeC.push_back(shape);
        }

        std::vector<bool> stateOfCheckNodes = this->code.stateOfCheckNodes();
        for (int i = 0; i < stateOfCheckNodes.size(); i++)
        {
            sf::RectangleShape shape(sf::Vector2f(this->getShapeDim(), this->getShapeDim()));
            shape.setPosition(sf::Vector2f(this->getSquareShapeAlignment(), this->getShapeDim() * this->getSpacing() * i + this->getOffset()));
            shape.setFillColor(!stateOfCheckNodes.at(i) ? this->colorOfSquareFalse : this->colorOfSquareTrue);
            shapeR.push_back(shape);
        }

        for (int i = 0; i < matrix.size(); i++ /*columns*/)
        {
            for (int j = 0; j < matrix.at(0).size(); j++ /*rows*/)
            {
                if (matrix.at(i).at(j))
                {
                    this->line.append(sf::Vertex(this->shapeR.at(i).getPosition(), this->shapeR.at(i).getFillColor()));
                    this->line.append(sf::Vertex(this->shapeC.at(j).getPosition(), this->shapeC.at(j).getFillColor()));
                }
            }
        }
    }
    void updateShapesColor()
    {
        std::vector<bool> word = this->code.getWord();
        for (int i = 0; i < word.size(); i++)
        {
            // this->shapeC.at(i).setFillColor()
        }
    }

    void updateShapes()
    {

        std::vector<bool> word = this->code.getWord();
        for (int i = 0; i < word.size(); i++)
        {   
            
            this->shapeC.at(i).setFillColor(word.at(i) ? this->colorOfCircleTrue : this->colorOfCircleFalse);
            this->shapeC.at(i).setPosition(sf::Vector2f(this->getCircleShapeAlignment(), this->getShapeDim() * this->getSpacing() * i + this->getOffset()));
            this->shapeC.at(i).setRadius(this->getShapeDim() / 2);
        }

        std::vector<bool> checkNodeStates = this->code.stateOfCheckNodes();
        for (int i = 0; i < checkNodeStates.size(); i++)
        {   
            this->shapeR.at(i).setFillColor(!checkNodeStates.at(i) ? this->colorOfSquareFalse : this->colorOfSquareTrue);
            this->shapeR.at(i).setPosition(sf::Vector2f(this->getSquareShapeAlignment(), this->getShapeDim() * this->getSpacing() * i + this->getOffset()));
            this->shapeR.at(i).setSize(sf::Vector2f(this->getShapeDim(), this->getShapeDim()));
        }

        std::vector<std::vector<bool>> matrix = this->code.getMatrix();
        int numberOfLines = 0;
        for (int i = 0; i < matrix.size(); i++ /*columns*/)
        {
            for (int j = 0; j < matrix.at(0).size(); j++ /*rows*/)
            {
                if (matrix.at(i).at(j))
                {
                    this->line[numberOfLines] = sf::Vertex(this->shapeR.at(i).getPosition(), this->shapeR.at(i).getFillColor());
                    numberOfLines += 1;
                    this->line[numberOfLines] = sf::Vertex(this->shapeC.at(j).getPosition(), this->shapeC.at(j).getFillColor());
                    numberOfLines += 1;
                }
            }
        }
    }
};