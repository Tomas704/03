#include "turtle.hpp"

#include <imgui/imgui.h>

#include <stdexcept>

namespace turtlepreter
{

    Turtle::Turtle(const std::string &imgPath) : m_transformation(),
                                                 m_image(friimgui::Image::createImage(imgPath))
    {
    }

    Turtle::Turtle(const std::string &imgPath, float centerX, float centerY) : Turtle(imgPath)
    {
        m_transformation.translation.setValue({centerX, centerY});
    }

    void Turtle::draw(const friimgui::Region &region)
    {
        const float thickness = 1;
        const ImColor color = ImColor(ImVec4({0, 1, 0, 1}));
        ImDrawList *drawList = ImGui::GetWindowDrawList();
        const ImVec2 p0 = region.getP0();

        for (const ImVec4 &segment : m_path)
        {
            ImVec2 startPoint = {segment.x, segment.y};
            ImVec2 endPoint = {segment.z, segment.w};
            drawList->AddLine(startPoint, endPoint, color, thickness);
        }
        m_image.draw(region, m_transformation);
    }

    void Turtle::reset()
    {
        m_path.clear();
        m_transformation.reset();
    }

    void Turtle::move(float distance)
    {
        (void)distance;
        // Dobrovoľná úloha na doma.
        throw std::logic_error("Not implemented yet!");
    }

    void Turtle::jump(float x, float y)
    {
        const ImVec2 pos = m_transformation.translation.getValueOrDef();
        const ImVec2 dest(x, y);
        m_path.push_back(ImVec4{pos.x, pos.y, dest.x, dest.y});
        m_transformation.translation.setValue(dest);
    }

    void Turtle::rotate(float angleRad)
    {
        m_transformation.rotation.setValue(angleRad);
    }

} // namespace turtlepreter
