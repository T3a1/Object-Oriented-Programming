/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** ArcError
*/

#pragma once

    #include <exception>
    #include <string>

    #undef EXIT_FAILURE
    #define EXIT_FAILURE 84

namespace Arc
{
    /**
     * @class AError
     * @brief Base exception class for all Arcade system exceptions.
     */
    class AError : public std::exception
    {
        public:
            /**
             * @brief Creates an error with a message.
             * @param message Error description
             */
            AError(std::string message) : _message(message) {};

            /**
             * @brief Returns the error message.
             * @return C-string describing the error
             */
            const char *what() const noexcept override {return _message.c_str();};
        private:
            std::string _message;
    };
    
    /**
     * @class ErrorMinor
     * @brief Exception for minor, recoverable errors.
     */
    class ErrorMinor : public AError
    {
        public:
            /**
             * @brief Creates a minor error.
             * @param message Error description
             */
            ErrorMinor(std::string message) : AError(std::move(message)) {}
    };

    /**
     * @class ErrorMajor
     * @brief Exception for major errors affecting functionality.
     */
    class ErrorMajor : public AError
    {
        public:
            /**
             * @brief Creates a major error.
             * @param message Error description
             */
            ErrorMajor(std::string message) : AError(std::move(message)) {}
    };

    /**
     * @class ErrorCritical
     * @brief Exception for critical, fatal errors.
     */
    class ErrorCritical : public AError
    {
        public:
            /**
             * @brief Creates a critical error.
             * @param message Error description
             */
            ErrorCritical(std::string message) : AError(std::move(message)) {}
    };

    /**
     * @class Miscellaneous
     * @brief Exception for miscellaneous errors.
     */
    class Miscellaneous : public AError
    {
        public:
            /**
             * @brief Creates a miscellaneous error.
             * @param message Error description
             */
            Miscellaneous(std::string message) : AError(std::move(message)) {}
    };
}