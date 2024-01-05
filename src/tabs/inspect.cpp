#include "../EditorUI.hpp"
#include "EditorUI-tabs.hpp"

#include "../idkui_components.hpp"


static void
tab_inspect_CS( idk::RenderEngine &ren, idk::Transform_CS &CS, int object_id )
{
    glm::mat4 &model = CS.getModelMatrix(object_id);

    float matrixTranslation[3], matrixRotation[3], matrixScale[3];
    ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(model), matrixTranslation, matrixRotation, matrixScale);
    ImGui::InputFloat3("Tr", matrixTranslation, "%.3f");
    ImGui::InputFloat3("Rt", matrixRotation, "%.3f");
    ImGui::InputFloat3("Sc", matrixScale, "%.3f");
    ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, glm::value_ptr(model));

}



static void
tab_inspect_CS( idk::RenderEngine &ren, idk::Model_CS &CS, int object_id )
{
    idk::Model &model = CS.getModel(ren, object_id);

    for (auto &mesh: model.meshes)
    {
        ImGui::Text(IDK_ICON_EYE " Mesh %d", mesh.material_id);
        ImGui::Text(IDK_ICON_PERSON " Mesh %d", mesh.material_id);
        ImGui::Text(IDK_ICON_EYE_CLOSED " Mesh %d", mesh.material_id);
    }
}


// static void
// tab_inspect_CS( idk::RenderEngine &ren, idkg::Terrain_CS &CS, int object_id )
// {
//     auto &model   = CS.getModel(ren, object_id);
//     auto &terrain = ren.modelSystem().getModel_Terrain(model.terrain_id);

//     ImGui::DragFloat("Height scale", &terrain.height_scale);
// }


static void
tab_inspect_CS( idk::RenderEngine &ren, idk::Icon_CS &CS, int object_id )
{
    static const std::vector<std::string> icons = {
        IDK_ICON_FILE,
        IDK_ICON_FOLDER,
        IDK_ICON_FOLDER_OPENED,
        IDK_ICON_PERSON,
        IDK_ICON_EYE,
        IDK_ICON_EYE_CLOSED,
        IDK_ICON_CAMERA,
        IDK_ICON_TRASH,
        IDK_ICON_PLUS,
        IDK_ICON_BOX,
        IDK_ICON_BOX_OPEN,
        IDK_ICON_FOLDER_TREE,
        IDK_ICON_GLOBE
    };

    std::string &icon = CS.getIcon(object_id);

    for (int i=0; i<icons.size(); i++)
    {
        bool selected = icon == icons[i];

        if (ImGui::Selectable(icons[i].c_str(), &selected))
        {
            icon = icons[i];
        }
    }

}



static void
tab_inspect_component( idk::EngineAPI &api, int object_id, idk::ComponentSystem *CS )
{
    if (CS == nullptr)
    {
        return;
    }

    std::string label = CS->name() + " component";
    ImGui::BeginChild(label.c_str());

    auto &engine = api.getEngine();
    auto &ren    = api.getRenderer();


    if (CS == &engine.getCS<idk::Transform_CS>())
    {
        tab_inspect_CS(ren, *dynamic_cast<idk::Transform_CS *>(CS), object_id);
    }

    if (CS == &engine.getCS<idk::Model_CS>())
    {
        tab_inspect_CS(ren, *dynamic_cast<idk::Model_CS *>(CS), object_id);
    }

    if (CS == &engine.getCS<idk::Icon_CS>())
    {
        tab_inspect_CS(ren, *dynamic_cast<idk::Icon_CS *>(CS), object_id);
    }


    ImGui::EndChild();
}



void
EditorUI_Module::_tab_inspect( idk::EngineAPI &api, int object_id )
{
    ImGui::Begin("Inspect");

    if (object_id == -1)
    {
        ImGui::End();
        return;
    }

    auto &engine = api.getEngine();
    auto &ren    = api.getRenderer();

    std::string label = "Object ID: " + std::to_string(object_id);
    ImGui::Text(label.c_str());

    static idk::ComponentSystem *CS_ptr = nullptr;
    static int stored_id = 0;

    int cs_id = (CS_ptr) ? CS_ptr->ID() : -1;

    if (object_id != stored_id)
    {
        stored_id = object_id;
    
        if (CS_ptr && engine.hasComponent(object_id, CS_ptr->ID()) == false)
        {
            CS_ptr = nullptr;
        }
    }


    if (EditorUI::splitWindow_begin("Inspect Component"))
    {
        for (auto &CS: engine.getComponentSystems())
        {
            const std::string &name = CS->name();
            const int CS_id = CS->ID();

            if (engine.hasComponent(object_id, CS_id))
            {
                if (ImGui::MenuItem(name.c_str()))
                {
                    CS_ptr = CS;
                }
            }
        }

        EditorUI::splitWindow_split();
        tab_inspect_component(api, object_id, CS_ptr);
        EditorUI::splitWindow_end();
    }



    ImGui::End();
}

