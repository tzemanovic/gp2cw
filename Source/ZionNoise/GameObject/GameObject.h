#pragma once
////////////////////////////////////////////////////
// game object
////////////////////////////////////////////////////

#include "Component\IGameObjectComponent.h"

namespace zn
{
    class GameObject
    {
        typedef map< GameObjectComponentType, shared_ptr< IGameObjectComponent > > GameObjectComponentsMap;
    public:
        explicit GameObject( GameObjectId id );
        ~GameObject();

        void Destroy();
        void AddComponent( shared_ptr< GameObject > pGameObject, shared_ptr< IGameObjectComponent > pComponent );
        bool Init();
        void Update( const float deltaMs );

        template< class TComponent >
        weak_ptr< TComponent > GetComponent( GameObjectComponentType type )
        {
            GameObjectComponentsMap::iterator componentPair = m_components.find( type );
            if( componentPair != m_components.end() )
            {
                shared_ptr< IGameObjectComponent > pBaseComponent( componentPair->second );
                shared_ptr< TComponent > pChildComponent( static_pointer_cast< TComponent >( pBaseComponent ) );
                weak_ptr< TComponent > pWeakChildComponent( pChildComponent );
                return pWeakChildComponent;
            }
            return weak_ptr< TComponent >();
        }
        GameObjectId GetId() { return m_id; }

    private:
        GameObjectId m_id;
        GameObjectComponentsMap m_components;
    };
}