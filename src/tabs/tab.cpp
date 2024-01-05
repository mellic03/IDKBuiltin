#include "../EditorUI.hpp"
#include "EditorUI-tabs.hpp"
#include "../idkui_components.hpp"


void
EditorUI_Module::_tab( idk::EngineAPI &api )
{
    auto &engine = api.getEngine();
    auto &ren    = api.getRenderer();

    // ImGui::Begin("Editor UI");
    // ImGui::DockSpace(ImGui::GetID("Editor DockSpace"));

    this->_tab_scene_hierarchy(api);
    this->_tab_inspect(api, m_selected_object);

    if (engine.hasComponent<idk::Transform_CS>(m_selected_object))
    {
        idkg::ui::transform_component(
            engine, ren.getCamera(), engine.getCS<idk::Transform_CS>(), m_selected_object
        );
    }


    EditorTab::shader_programs(api);
    EditorTab::skybox(api);
    EditorTab::cameras(api);
    EditorTab::models(api);


    // ImGui::End();
}
