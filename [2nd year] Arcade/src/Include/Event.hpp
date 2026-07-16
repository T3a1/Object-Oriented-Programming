/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Event
*/

#pragma once

namespace Arc
{
    /**
     * @enum Key
     * @brief Enumeration of all supported keyboard and mouse inputs.
     */
    enum Key {
        None,
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
        Underscore,
        Dash,
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
        Tab,
        Left,
        Right,
        Up,
        Down,
        Space,
        Enter,
        Escape,
        MouseLeft,
        MouseRight,
        Backspace,
    };

    /**
     * @enum Type
     * @brief Enumeration of event types in the system.
     */
    enum Type
    {
        KeyPressed,
        Quit
    };

    /**
     * @struct Mouse
     * @brief Represents mouse position coordinates.
     */
    struct Mouse
    {
        int x;
        int y;
    };

    /**
     * @struct Event
     * @brief Represents a user input event.
     */
    struct Event
    {
        Type type;
        Key code;
        Mouse mouse;
    };
}
