#pragma once
////////////////////////////////////////////////////
// math
////////////////////////////////////////////////////

namespace zn
{
    namespace Math
    {
        inline float RadiansToDegrees( float angle )
        {
            return angle * 180.f / ZN_PI;
        }

        inline float DegreesToRadians( float angle )
        {
            return angle * ZN_PI / 180.f;
        }

        inline float Maxf( float x, float y )
        {
            return x >= y ? x : y;
        }

        inline float Minf( float x, float y )
        {
            return x < y ? x : y;
        }
    }
}