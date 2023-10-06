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
    int shapeDimensions;
    float circleShapeAlignment;
    float squareShapeAlignment;

    std::vector<sf::Shape> shapes;

    SfWindow()
    {
        this->window.create(sf::VideoMode(1280, 720), "Iterative Decoding");
        this->shapeDimensions = 20;
        circleShapeAlignment = 20.0f;
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

    int getShapeDim() const
    {
        return this->shapeDimensions;
    }

    int setShapeDim(int shapeDimensions)
    {
        this->shapeDimensions = shapeDimensions;
    }

    SfWindow(Code &code, int shapeDimensions = 20, float shapeAliment = 20.0f)
    {
        this->window.create(sf::VideoMode(1280, 720), "Iterative Decoding");
        this->code = code;
        this->shapeDimensions = shapeDimensions;
        this->circleShapeAlignment = circleShapeAlignment;
    }

    void initializeShapes()
    {
        std::vector<std::vector<bool>> matrix = this->code.getMatrix();
        std::vector<bool> word = this->code.getWord();

        for (int i = 0; i < word.size(); i++)
        {
            if (word.at(i))
            {
                sf::CircleShape shape(this->getShapeDim());
                shape.setPosition(sf::Vector2f(this->getCircleShapeAlignment(), this->getShapeDim() * i));
                shape.setFillColor(sf::Color::Green);
                this->shapes.push_back(shape);
            }
            else if (!word.at(i))
            {
                sf::CircleShape shape(this->getShapeDim());
                shape.setPosition(sf::Vector2f(this->getCircleShapeAlignment(), this->getShapeDim() * i));
                shape.setFillColor(sf::Color::Red);
                this->shapes.push_back(shape);
            }
        }

        std::vector<bool> stateOfCheckNodes = this->code.stateOfCheckNodes();
        for (int i = 0; i < stateOfCheckNodes.size(); i++)
        {
            if (stateOfCheckNodes.at(i))
            {
                sf::RectangleShape shape(sf::Vector2f(this->getShapeDim(), this->getShapeDim()));
                shape.setPosition(sf::Vector2f(this->getSquareShapeAlignment(), this->getShapeDim() * i));
                shape.setFillColor(sf::Color::Blue);
            }
        }
    }
};