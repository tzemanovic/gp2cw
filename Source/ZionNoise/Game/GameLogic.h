#pragma once
////////////////////////////////////////////////////
// game logic
////////////////////////////////////////////////////

#include "..\Utilities\IView.h"

namespace zn
{
    typedef list< shared_ptr< IView > > ViewList;
    //typedef map< GameObjectId, shared_ptr< GameObject > > GameObjectMap;

    class GameLogic
    {
        friend class Game;
    public:
        GameLogic();
        ~GameLogic();

        // add view
        void AddView( shared_ptr< IView > pView, GameObjectId gameObjectId );

    private:
        ViewList m_viewList;
        //GameObjectMap m_gameObjectMap;
    };
}