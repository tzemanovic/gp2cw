#pragma once
////////////////////////////////////////////////////
// lua script manager
////////////////////////////////////////////////////

#include "..\Utilities\INoCopy.h"
#include "..\Game\Game.h"

namespace zn
{
    class LuaScriptManager : private INoCopy
    {
    public:
        ~LuaScriptManager();

        static LuaScriptManager* Get()
        {
            static LuaScriptManager instance;
            return &instance;
        }

        bool Init();
        void Bind();
        void ExecuteFile( const string& filename );

        lua_State* GetLuaState()
	    {
		    return m_pLuaState;
	    }

        static Game* GetGame()
        {
            return g_pGame;
        }

        class_< Game >* GetGameScope() { return gameScope; }

    private:
        LuaScriptManager();
        void Prebind();

        lua_State* m_pLuaState;
        class_< Game >* gameScope;
    };
}