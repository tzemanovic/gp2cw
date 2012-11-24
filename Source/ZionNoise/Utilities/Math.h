#pragma once
////////////////////////////////////////////////////
// math
////////////////////////////////////////////////////

namespace zn
{
    class Math
    {
    public:
        static inline float RadiansToDegrees( float angle )
        {
            return angle * 180.f / ZN_PI;
        }

        static inline float DegreesToRadians( float angle )
        {
            return angle * ZN_PI / 180.f;
        }

        static inline float Maxf( float x, float y )
        {
            return x >= y ? x : y;
        }

        static inline float Minf( float x, float y )
        {
            return x < y ? x : y;
        }
    };
}