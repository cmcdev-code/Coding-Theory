#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>
#include "application.hpp"


int main()
{
    std::vector<std::vector<bool>> t = { {1, 0, 1},
                                         {1, 0, 1},
                                         {1, 0, 1} };
    std::vector<bool> word= {1,1,1};
    Code c(t,word);
    SfWindow win(c);
    
    
    win.window.setFramerateLimit(60);
    ImGui::SFML::Init(win.window);

    sf::Clock deltaClock;
    while (win.window.isOpen())
    {
        sf::Event event;
        while (win.window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
            {
                win.window.close();
            }
        }

        ImGui::SFML::Update(win.window, deltaClock.restart());

        myApp::RenderUI(c);
        win.window.clear();
        ImGui::SFML::Render(win.window);
        win.window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}