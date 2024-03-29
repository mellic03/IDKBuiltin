#pragma once

#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKGraphics/IDKGraphics.hpp>


namespace idk { class Camera_CS; };

class idk::Camera_CS: public idk::ComponentSystem
{
private:
    std::map<int, int> m_camera_ids;

public:

    void        init( idk::EngineAPI & );
    void        stage_A( idk::EngineAPI & );
    void        stage_B( idk::EngineAPI & )    {  };
    void        stage_C( idk::EngineAPI & )    {  };

    void        onObjectAssignment( int obj_id, idk::Engine & );
    void        onObjectCreation( int obj_id, idk::Engine & );
    void        onObjectDeletion( int obj_id, idk::Engine & );
    void        onObjectCopy( int src_obj_id, int dest_obj_id, idk::Engine & );
    void        onObjectInspect( int obj_id );

    idk::Camera &getCamera( idk::RenderEngine &, int obj_id );
    int          getCameraID( int obj_id );
};

