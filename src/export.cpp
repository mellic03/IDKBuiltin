#include "EditorUI.hpp"
#include <libidk/idk_export.hpp>


IDK_EXPORT_API
(
    idk::Module *getInstance()
    {
        static EditorUI_Module *editor_ui = nullptr;
    
        if (editor_ui == nullptr)
        {
            editor_ui = new EditorUI_Module;
        }

        return reinterpret_cast<idk::Module *>(editor_ui);
    }
)

