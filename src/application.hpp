#pragma Once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include "sfWindow.hpp"



namespace myApp{

    void RenderUI(Code & code){

        ImGui::Begin("Hello world");
        ImGui::Button("Hello");

        static float value=0.0f;
        ImGui::DragFloat(" Value",& value);
        ImGui::End();

    }

}