#pragma Once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include "sfWindow.hpp"

namespace myApp
{
    static void HelpMarker(const char *desc)
    {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }

    void RenderUI(SfWindow &win)
    {
        ImGui::Begin("Options");

        char inputBuffer[256];
        strcpy(inputBuffer, win.code.whatFunction.c_str());

        ImGui::Text("Update rule: enter as u>= s + k");
        ImGui::SameLine();
        HelpMarker("enter an equation of the form\n"
                   "u>= s+k where k is an int\n");
        if (ImGui::InputText("", inputBuffer, sizeof(inputBuffer), ImGuiInputTextFlags_EnterReturnsTrue))
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
            if (ImGui::TreeNode("Position"))
            {
                ImGui::DragFloat("Offset Vertical", &win.offset);

                ImGui::DragFloat("Horizontal Alignment Variable Nodes", &win.circleShapeAlignment);
                ImGui::DragFloat("Horizontal Alignment Check Nodes", &win.squareShapeAlignment);
                ImGui::DragFloat("Spacing", &win.spacing);
                ImGui::DragFloat("Shape Dimensions", &win.shapeDimensions);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Colors of Nodes"))
            {

                static ImVec4 colorTrueVariableNode = ImVec4(win.colorOfCircleTrue.r / 255.0f,
                                                             win.colorOfCircleTrue.g / 255.0f,
                                                             win.colorOfCircleTrue.b / 255.0f,
                                                             win.colorOfCircleTrue.a / 255.0f);

                static ImVec4 colorOfFalseVariableNode = ImVec4(win.colorOfCircleFalse.r / 255.0f,
                                                                win.colorOfCircleFalse.g / 255.0f,
                                                                win.colorOfCircleFalse.b / 255.0f,
                                                                win.colorOfCircleFalse.a / 255.0f);

                static ImVec4 colorOfTrueCheckNodes = ImVec4(win.colorOfSquareTrue.r / 255.0f,
                                                             win.colorOfSquareTrue.g / 255.0f,
                                                             win.colorOfSquareTrue.b / 255.0f,
                                                             win.colorOfSquareTrue.a / 255.0f);

                static ImVec4 colorOfFalseCheckNodes = ImVec4(win.colorOfSquareFalse.r / 255.0f,
                                                              win.colorOfSquareFalse.g / 255.0f,
                                                              win.colorOfSquareFalse.b / 255.0f,
                                                              win.colorOfSquareFalse.a / 255.0f);
                static ImVec4 backGroundColor = ImVec4(win.backgroundColor.r / 255.0f,
                                                       win.backgroundColor.g / 255.0f,
                                                       win.backgroundColor.b / 255.0f,
                                                       win.backgroundColor.a / 255.0f);

                static bool alpha_preview = false;
                static bool alpha_half_preview = false;
                static bool drag_and_drop = true;
                static bool options_menu = true;
                static bool hdr = false;

                ImGuiColorEditFlags misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);
                ImGui::Text("Color of Variable Node when true");
                ImGui::SameLine();
                HelpMarker(
                    "Click on the color square to open a color picker.\n"
                    "CTRL+click on individual component to input value.\n");
                ImGui::ColorEdit4("MyColor##1", (float *)&colorTrueVariableNode, misc_flags);
                win.colorOfCircleTrue = sf::Color(colorTrueVariableNode.x * 255,
                                                  colorTrueVariableNode.y * 255,
                                                  colorTrueVariableNode.z * 255,
                                                  colorTrueVariableNode.w * 255);

                ImGui::Text("Color of Variable Node when false");
                ImGui::SameLine();
                HelpMarker(
                    "Click on the color square to open a color picker.\n"
                    "CTRL+click on individual component to input value.\n");
                ImGui::ColorEdit4("MyColor##2", (float *)&colorOfFalseVariableNode, misc_flags);
                win.colorOfCircleFalse = sf::Color(colorOfFalseVariableNode.x * 255,
                                                   colorOfFalseVariableNode.y * 255,
                                                   colorOfFalseVariableNode.z * 255,
                                                   colorOfFalseVariableNode.w * 255);

                ImGui::Text("Color of Check Node when true");
                ImGui::SameLine();
                HelpMarker(
                    "Click on the color square to open a color picker.\n"
                    "CTRL+click on individual component to input value.\n");
                ImGui::ColorEdit4("MyColor##3", (float *)&colorOfTrueCheckNodes, misc_flags);
                win.colorOfSquareTrue = sf::Color(colorOfTrueCheckNodes.x * 255,
                                                  colorOfTrueCheckNodes.y * 255,
                                                  colorOfTrueCheckNodes.z * 255,
                                                  colorOfTrueCheckNodes.w * 255);

                ImGui::Text("Color of Check Node when false");
                ImGui::SameLine();
                HelpMarker(
                    "Click on the color square to open a color picker.\n"
                    "CTRL+click on individual component to input value.\n");
                ImGui::ColorEdit4("MyColor##4", (float *)&colorOfFalseCheckNodes, misc_flags);
                win.colorOfSquareFalse = sf::Color(colorOfFalseCheckNodes.x * 255,
                                                   colorOfFalseCheckNodes.y * 255,
                                                   colorOfFalseCheckNodes.z * 255,
                                                   colorOfFalseCheckNodes.w * 255);

                ImGui::Text("Background Color");
                ImGui::SameLine();
                HelpMarker(
                    "Click on the color square to open a color picker.\n"
                    "CTRL+click on individual component to input value.\n");
                ImGui::ColorEdit4("MyColor##5", (float *)&backGroundColor, misc_flags);
                win.backgroundColor = sf::Color(backGroundColor.x * 255,
                                                backGroundColor.y * 255,
                                                backGroundColor.z * 255,
                                                backGroundColor.w * 255);
                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
        // ImGui::ShowDemoWindow();

        ImGui::End();
    }

}