#pragma once
////////////////////////////////////////////////////
// window styles
////////////////////////////////////////////////////

namespace zn
{
    typedef uint8 WindowStyleType; 
    namespace WindowStyle
    {
        enum
        {
            Window = 0,
            Fullscreen = 1 << 0,
            Default = Window
        };
    }
}