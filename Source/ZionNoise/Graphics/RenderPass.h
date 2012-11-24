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
	        Count
        };
    }

    typedef uint16 RenderPassType;
}