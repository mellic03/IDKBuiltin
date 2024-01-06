#pragma once

#include <IDKGameEngine/IDKGameEngine.hpp>

namespace idk { class Pointlight_CS; };

class idk::Pointlight_CS
{
private:
    struct ComponentData
    {
        int obj_id;
        int light_id;
    };

    idk::Allocator<ComponentData> m_data;

public:
    void        init    ( idk::EngineAPI & ) {  };
    void        stage_A ( idk::EngineAPI & );
    void        stage_B ( idk::EngineAPI & ) {  };
    void        stage_C ( idk::EngineAPI & ) {  };

    void        onObjectAssignment( int obj_id, idk::Engine & );
    void        onObjectCreation( int obj_id, idk::Engine & );
    void        onObjectDeletion( int obj_id, idk::Engine & );
    void        onObjectCopy( int src_obj_id, int dest_obj_id, idk::Engine & );

};


