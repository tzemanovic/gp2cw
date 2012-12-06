#pragma once
////////////////////////////////////////////////////
// game logic
////////////////////////////////////////////////////

#include "..\Utilities\IView.h"

namespace zn
{
    class GameObject;

    typedef list< shared_ptr< IView > > ViewList;
    typedef map< GameObjectId, shared_ptr< GameObject > > GameObjectMap;

    class GameLogic
    {
        friend class Game;

    public:
        GameLogic();
        ~GameLogic();

        // add view
        void AddView( shared_ptr< IView > pView );
        void Update( const float deltaMs );

        shared_ptr< GameObject > GetGameObject( GameObjectId id );
        void AddGameObject( shared_ptr< GameObject > pGameObject );

    protected:
        ViewList m_viewList;
        GameObjectMap m_gameObjectMap;
    };
}