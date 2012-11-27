#pragma once
////////////////////////////////////////////////////
// game object component
////////////////////////////////////////////////////

#include "GameObjectComponentType.h"

namespace zn
{
    class GameObject;

    class IGameObjectComponent
    {
    public:
        IGameObjectComponent( GameObjectComponentType type ) : m_type( type ) 
        {
            
        }

        virtual ~IGameObjectComponent() { m_pGameObject.reset(); }

        GameObjectComponentType GetType() { return m_type; }

        virtual void VUpdate( const float deltaMs ) {}
        virtual bool VInit() { return true; }

        void SetGameObject( shared_ptr< GameObject > pGameObject )
        {
            m_pGameObject = pGameObject;
        }

    protected:
        GameObjectComponentType m_type;
        shared_ptr< GameObject > m_pGameObject;
    };
}