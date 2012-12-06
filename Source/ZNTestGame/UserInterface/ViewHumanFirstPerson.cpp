////////////////////////////////////////////////////
// human first person view
////////////////////////////////////////////////////

#include "ZNTestGameStd.h"
#include "ViewHumanFirstPerson.h"

namespace zn
{
    ViewHumanFirstPerson::ViewHumanFirstPerson() : ViewHuman(), m_pHumanChar( NULL ), 
        m_isFreeCameraController( false ), m_pFirstPersonController( NULL )
    {

    }
    
    ViewHumanFirstPerson::~ViewHumanFirstPerson()
    {
        ZN_SAFE_DELETE( m_pFirstPersonController );
    }

    void ViewHumanFirstPerson::VInit()
    {
        ViewHuman::VInit();
        if( m_pRenderer )
        {
            m_pFirstPersonController = ZN_NEW FirstPersonController( 0 );
            m_pKeyboardHandler = m_pFirstPersonController;
            m_pMouseHandler = m_pFirstPersonController;
            g_pGame->GetWindow()->CaptureMouse();
        }
    }
    
    void ViewHumanFirstPerson::VUpdate( const float deltaMs )
    {
        if( !m_isFreeCameraController && m_pFirstPersonController )
        {
            m_pFirstPersonController->Update( deltaMs );
        }
        ViewHuman::VUpdate( deltaMs );
    }

    const bool ViewHumanFirstPerson::VProcessMessage( const Message& message )
    {
        if( message == Message::KeyUp )
        {
            if( message.key.type == Key::F2 )
            {
                if( m_isFreeCameraController )
                {
                    m_pCamera->SetTarget( m_pHumanChar );
                    m_pKeyboardHandler = m_pFirstPersonController;
                    m_pMouseHandler = m_pFirstPersonController;
                    m_isFreeCameraController = false;
                }
                else
                {
                    m_pCamera->ClearTarget();
                    m_pKeyboardHandler = m_pFreeCameraController;
                    m_pMouseHandler = m_pFreeCameraController;
                    m_isFreeCameraController = true;
                }
            }
        }
        return ViewHuman::VProcessMessage( message );
    }

    void ViewHumanFirstPerson::VSetOwner( GameObjectId id )
    {
        ViewHuman::VSetOwner( id );
        m_pHumanChar = m_pScene->FindGameObject( id );
        m_pCamera->SetTarget( m_pHumanChar );
    }

    void ViewHumanFirstPerson::SetControlledObject( shared_ptr< FirstPersonCharacterComponent > pFirstPersonComp )
    {
        if( m_pFirstPersonController )
        {
            m_pFirstPersonController->SetControlledObject( pFirstPersonComp );
        }
    }
}