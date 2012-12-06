#pragma once
////////////////////////////////////////////////////
// renderer passes
////////////////////////////////////////////////////

namespace zn
{
    namespace RenderPass
    {
        enum
        {
            First,
	        Sky,
	        GameObjects,
            HUD,
	        Count
        };
    }

    typedef uint16 RenderPassType;
}