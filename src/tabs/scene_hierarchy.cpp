#include "../EditorUI.hpp"
#include "EditorUI-tabs.hpp"



static void
idk_scene_treenode_drag_drop( int id, idk::Transform_CS &tCS )
{
    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
    {
        ImGui::SetDragDropPayload("SCENE_HIERARCHY", reinterpret_cast<const void *>(&id), sizeof(int));
        ImGui::EndDragDropSource();
    }

    if (ImGui::BeginDragDropTarget())
    {
        ImGui::BeginTooltip();
        ImGui::TextColored({255, 0, 0, 255}, "Parent");
        ImGui::EndTooltip();

        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SCENE_HIERARCHY"))
        {
            IM_ASSERT(payload->DataSize == sizeof(int));
            int child_id = *reinterpret_cast<int *>(payload->Data);
            tCS.giveChild(id, child_id);
        }
        ImGui::EndDragDropTarget();
    }
}



static void
idk_scene_treenode( idk::Engine &engine, std::string *&text, int id, int &selected,
                    idk::Name_CS &nCS, idk::Icon_CS &iCS, idk::Transform_CS &tCS )
{
    if (id == -1)
    {
        return;
    }

    std::string &name = nCS.getName(id);
    std::string label = iCS.getIcon(id) + std::string(" ") + name;
    int flags  = ImGuiTreeNodeFlags_DefaultOpen;
        flags |= ImGuiTreeNodeFlags_OpenOnArrow;
        flags |= ImGuiTreeNodeFlags_SpanFullWidth;

    if (tCS.getChildren(id).size() == 0)
    {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }

    if (id == selected)
    {
        flags |= ImGuiTreeNodeFlags_Selected;
    }


    ImGui::PushID(id);

    if (ImGui::TreeNodeEx(label.c_str(), flags))
    {
        if (ImGui::IsItemClicked())
        {
            selected = id;
            text = &name;
        }



        if (ImGui::BeginPopupContextWindow("Ree Component"))
        {
            ImGui::Text(name.c_str());
            ImGui::Separator();

            if (ImGui::MenuItem("Copy"))
            {
                engine.copyGameObject(selected, name);
            }

            if (ImGui::MenuItem("Delete"))
            {
                engine.deleteGameObject(selected);
            }


            ImGui::EndPopup();
        }



        idk_scene_treenode_drag_drop(id, tCS);

        for (int child_id: tCS.getChildren(id))
        {
            if (child_id == 0)
            {
                continue;
            }
    
            idk_scene_treenode(engine, text, child_id, selected, nCS, iCS, tCS);
        }

        ImGui::TreePop();
    }

    ImGui::PopID();
}


void rightwindow( idk::Engine &engine, int selected )
{
    if (ImGui::Button("Add Component"))
    {
        ImGui::OpenPopup("Add Component");
    }

    if (ImGui::BeginPopup("Add Component"))
    {
        ImGui::Text("Add Component");
        ImGui::Separator();

        for (int i=0; i<5; i++)
        {
            std::string label = engine.getCS(i)->name();

            if (ImGui::MenuItem(label.c_str()))
            {
                engine.giveComponent(selected, i);
            }
        }

        ImGui::EndPopup();
    }
}


void
EditorUI_Module::_tab_scene_hierarchy( idk::EngineAPI &api )
{
    auto &engine = api.getEngine();
    auto &ren    = api.getRenderer();

    auto &nCS     = engine.getCS<idk::Name_CS>();
    auto &iCS     = engine.getCS<idk::Icon_CS>();
    auto &tCS     = engine.getCS<idk::Transform_CS>();
    auto &objects = engine.gameObjects();
    int  obj_id   = 0; // root object

    static std::string *text = nullptr;

    ImGui::Begin("Scene Hierarchy");
    ImGui::BeginChild("split-window", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));

    if (EditorUI::splitWindow_begin("Game Objects"))
    {
        idk_scene_treenode(engine, text, obj_id, m_selected_object, nCS, iCS, tCS);

        EditorUI::splitWindow_split();

        if (text != nullptr)
        {
            ImGui::InputText("Name: ", text);
        }

        if (m_selected_object != -1)
            rightwindow(engine, m_selected_object);

        EditorUI::splitWindow_end();
    }
    ImGui::EndChild();


    if (ImGui::Button(IDK_ICON_PLUS " add"))
    {
        m_selected_object = 1;
        engine.createGameObject("REEEE");
    }

    ImGui::SameLine();

    if (ImGui::Button(IDK_ICON_TRASH " delete"))
    {
        engine.deleteGameObject(m_selected_object);
        std::cout << "Deleted object " << m_selected_object << "\n";
        m_selected_object = 0;
    }

    ImGui::End();
}

