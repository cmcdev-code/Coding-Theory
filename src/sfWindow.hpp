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
    int spacing;
    float circleShapeAlignment;
    float squareShapeAlignment;

    std::vector<sf::RectangleShape> shapeR;
    std::vector<sf::CircleShape> shapeC;

    sf::VertexArray line;

    SfWindow()
    {
        this->window.create(sf::VideoMode(1280, 720), "Iterative Decoding");
        this->shapeDimensions = 20;
        this->circleShapeAlignment = 20.0f;
        this->spacing = 3;
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

    void setShapeDim(int shapeDimensions)
    {
        this->shapeDimensions = shapeDimensions;
        this->line.setPrimitiveType(sf::Lines);
    }

    SfWindow(Code &code, int shapeDimensions = 20, float shapeAliment = 20.0f, int spacing = 3)
    {
        this->window.create(sf::VideoMode(1280, 720), "Iterative Decoding");
        this->code = code;
        this->shapeDimensions = shapeDimensions;
        this->circleShapeAlignment = circleShapeAlignment;
        this->line.setPrimitiveType(sf::Lines);
        this->spacing = spacing;
    }
    int getSpacing() const
    {
        return this->spacing;
    }

    void setSpacing(int spacing)
    {
        this->spacing = spacing;
    }

    void initializeShapes()
    {
        std::vector<std::vector<bool>> matrix = this->code.getMatrix();
        std::vector<bool> word = this->code.getWord();

        for (int i = 0; i < word.size(); i++)
        {
            sf::CircleShape shape(this->getShapeDim());
            shape.setPosition(sf::Vector2f(this->getCircleShapeAlignment(), this->getShapeDim() * this->getSpacing() * i + 30));
            shape.setFillColor(word.at(i) ? sf::Color::Green : sf::Color::Red);
            this->shapeC.push_back(shape);
        }

        std::vector<bool> stateOfCheckNodes = this->code.stateOfCheckNodes();
        for (int i = 0; i < stateOfCheckNodes.size(); i++)
        {
            sf::RectangleShape shape(sf::Vector2f(this->getShapeDim(), this->getShapeDim()));
            shape.setPosition(sf::Vector2f(this->getSquareShapeAlignment(), this->getShapeDim() * this->getSpacing() * i + 30));
            shape.setFillColor(stateOfCheckNodes.at(i) ? sf::Color::Blue : sf::Color::Yellow);
            shapeR.push_back(shape);
        }

        for (int i = 0; i < matrix.size(); i++ /*columns*/)
        {
            for (int j = 0; j < matrix.at(0).size(); j++ /*rows*/)
            {
                if (matrix.at(i).at(j))
                {
                    line.append(sf::Vertex(this->shapeR.at(i).getPosition(), this->shapeR.at(i).getFillColor()));
                    line.append(sf::Vertex(this->shapeC.at(j).getPosition(), this->shapeC.at(j).getFillColor()));
                }
            }
        }
    }
};