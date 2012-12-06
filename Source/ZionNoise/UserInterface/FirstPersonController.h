#pragma once
////////////////////////////////////////////////////
// first person controller
////////////////////////////////////////////////////

#include "IKeyboardHandler.h"
#include "IMouseHandler.h"
#include "CharacterControllerInfo.h"

namespace zn
{
    class SceneNode;
    class FirstPersonCharacterComponent;

    class FirstPersonController : public IKeyboardHandler, public IMouseHandler
    {
    public:
        FirstPersonController( float yawInDegrees );
        virtual ~FirstPersonController();

        virtual bool VOnKeyMsg( const Message& msg );
        virtual bool VOnMouseMsg( const Message& msg );

        void Update( const float deltaMs );
        void SetControlledObject( shared_ptr< FirstPersonCharacterComponent > pFirstPersonComp );

    protected:
        shared_ptr< FirstPersonCharacterComponent > m_pControlledObject;

        float m_targetYaw;
	    float m_yaw;
	    float m_maxSpeed;
        
        bool m_keyState[Key::Count];
        bool m_keyOldState[Key::Count];
        uint16 m_mouseLastX;

        CharacterControllerInfo m_charInfo;
    };
}