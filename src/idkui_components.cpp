#include "idkui_components.hpp"

#include <IDKGameEngine/IDKengine.hpp>
#include <IDKBuiltinCS/IDKBuiltinCS.hpp>

#include <idk_imgui/imgui.hpp>
#include <idk_imgui/imguizmo.hpp>


void
idkg::ui::transform_component( idk::Engine &engine, idk::Camera &camera, idk::Transform_CS &CS, int obj_id )
{
    ImGuizmo::SetOrthographic(false);

    auto &io = ImGui::GetIO();
    float x = ImGui::GetWindowPos().x;
    float y = ImGui::GetWindowPos().y;
    float w = io.DisplaySize.x; // ImGui::GetWindowWidth();
    float h = io.DisplaySize.y; // ImGui::GetWindowHeight();
    ImGuizmo::SetRect(0, 0, w, h);

    glm::mat4 view     = camera.view();
    glm::mat4 proj     = camera.projection();
    glm::mat4 inv_view = glm::inverse(view);
    glm::mat4 inv_proj = glm::inverse(proj);


    glm::mat4 &model    = CS.getModelMatrix(obj_id);
    glm::mat4 transform = CS.getModelMatrixParented(obj_id);
    glm::mat4 parent    = CS.getParentModelMatrix(obj_id);

    ImGuizmo::MODE mode = ImGuizmo::MODE::LOCAL;

    if (engine.eventManager().keylog().keyDown(idk::Keycode::LSHIFT))
    {
        mode = ImGuizmo::MODE::WORLD;
    }


    ImGuizmo::Manipulate(
        glm::value_ptr(view),
        glm::value_ptr(proj),
        ImGuizmo::OPERATION::TRANSLATE,
        mode,
        glm::value_ptr(transform)
    );

    ImGuizmo::Manipulate(
        glm::value_ptr(view),
        glm::value_ptr(proj),
        ImGuizmo::OPERATION::ROTATE,
        mode,
        glm::value_ptr(transform)
    );

    model = glm::inverse(parent) * transform;

}

