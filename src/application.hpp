#pragma Once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include "sfWindow.hpp"

namespace myApp
{

    void RenderUI(SfWindow &win)
    {

        ImGui::Begin("Options");

        char inputBuffer[256];
        strcpy(inputBuffer, win.code.whatFunction.c_str());

        if (ImGui::InputText("Update rule: enter as u >= s + k", inputBuffer, sizeof(inputBuffer), ImGuiInputTextFlags_EnterReturnsTrue))
        {
            std::string enteredText(inputBuffer);
            win.code.whatFunction = enteredText;
        }

        std::string inputBufferWord = win.code.getWordAsString();

        if (ImGui::InputText("Word", &inputBufferWord[0], inputBufferWord.size() + 1, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            // 'inputBufferWord' will be automatically updated with the text entered by the user.
            // You can access the updated text using 'inputBufferWord'.

            // Now, you can parse and process the entered text here.
            std::vector<bool> word;
            for (int i = 0; i < inputBufferWord.size(); i++)
            {
                if (isdigit(inputBufferWord.at(i)))
                {
                    word.push_back((inputBufferWord.at(i) - '0') % 2);
                }
            }
            if (word.size() < win.code.getWordAsString().size())
            {
                for (int i = word.size(); i < win.code.getWordAsString().size(); i++)
                {
                    word.push_back(0);
                }
            }

            // Update the 'word' in your SfWindow instance.
            win.code.setWord(word);
        }

        if (ImGui::Button("Update Word"))
        {
            win.code.updateWord();
        }

        if (ImGui::TreeNode("Settings"))
        {
            ImGui::DragFloat("Offset Vertical", &win.offset);

            ImGui::DragFloat("Horizontal Alignment Variable Nodes", &win.circleShapeAlignment);
            ImGui::DragFloat("Horizontal Alignment Check Nodes", &win.squareShapeAlignment);
            ImGui::DragFloat("Spacing", &win.spacing);
            ImGui::DragFloat("Shape Dimensions", &win.shapeDimensions);
            ImGui::TreePop();
        }

        ImGui::End();
    }

}