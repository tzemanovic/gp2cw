#pragma once
////////////////////////////////////////////////////
// movement controller
////////////////////////////////////////////////////

#include "IKeyboardHandler.h"
#include "IMouseHandler.h"

namespace zn
{
    class SceneNode;

    class MovementController : public IKeyboardHandler, public IMouseHandler
    {
    public:
        MovementController( shared_ptr< SceneNode > pControlledObject, float yawInDegrees, float pitchInDegrees );
        virtual ~MovementController();

        virtual bool VOnKeyMsg( const Message& msg );
        virtual bool VOnMouseMsg( const Message& msg );

        void Update( const float deltaMs );

    protected:
	    shared_ptr< SceneNode > m_pControlledObject;

        Mat4x4 m_toWorld, m_fromWorld, m_position, m_startingToWorld;

        float m_targetYaw;
	    float m_targetPitch;
	    float m_yaw;
	    float m_pitch;
	    float m_maxSpeed;
	    float m_currentSpeed;
        
        bool m_keyState[Key::Count];
        bool m_keyOldState[Key::Count];
        uint16 m_mouseLastX;
        uint16 m_mouseLastY;
    };
}