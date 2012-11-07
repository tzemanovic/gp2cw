#pragma once
////////////////////////////////////////////////////
// input devices - keyboard, mouse
////////////////////////////////////////////////////

namespace zn
{
    typedef uint8 KeyType;
    typedef uint8 MouseButtonType;

    namespace Key
    {
        enum
        {
            A,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,
            ArrowLeft,
            ArrowRight,
            ArrowUp,
            ArrowDown,
            Num1,
            Num2,
            Num3,
            Num4,
            Num5,
            Num6,
            Num7,
            Num8,
            Num9,
            Num0,
            F1,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7,
            F8,
            F9,
            F10,
            F11,
            F12,
            Esc,
            Tab,
            Space,
            Return,
            LCtrl,
            RCtrl,
            LAlt,
            RAlt,
            LShift,
            RShift,
            Undef,
            Count
        };
    }

    namespace MouseButton
    {
        enum
        {
            LeftButton,
            MiddleButton,
            RightButton,
            XButton1,
            XButton2,
            Count
        };
    }
    
    typedef bool KeyStates[Key::Count];
}