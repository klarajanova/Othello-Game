/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
    Popis:    Hlavièkový soubor k ai.cpp
*/

#ifndef CORE_AI_H
#define CORE_AI_H

namespace Core
{
    class Game;


    /**
     *  @brief Artificial Intelligence
     */
    class AI
    {
        public:
            /**
             *  Enum with constants for difficulty
             */
            enum Difficulty {
                NONE,           ///< No difficulty & No AI in use
                EASY,           ///< Easy difficulty
                INTERMEDIATE    ///< Intermediate difficulty
            };
            static void play(Game *game, Difficulty difficulty); ///< Makes move depending on difficulty

        private:
            static void easy(Game *game);
            static void intermediate(Game *game);
    };
}

#endif // CORE_AI_H
