/*player.h*/
/**
    \file [player.h]
    \brief 	Contient la déclaration des fonctions,
    procédures d'initialisation d'un nouveau joueur
    \author {Damotte Alan, Chaussende Adrien}
    \version 0.1
    \date Mars 2013
*/
#ifndef PLAYER_H
#define PLAYER_H

/**
    @struct Player
    @brief Structure d'un Player
*/
typedef struct
{
    char name[26]; // 25 caractères + \0
    unsigned int score;
}Player;

/* Mutateurs & Accesseurs */
/**

        @brief mutateur du nom d'un joueur
        @param un pointeur sur Player et pointeur sur un char
*/
void setName (Player * player, const char * name);

/**

        @brief assesseur du nom d'un joueur
        @param un pointeur sur Player
        @return pointeur sur un char
*/
char * getName (const Player * player);

/**

        @brief mutateur du score d'un joueur
        @param un pointeur Player et un entier naturel score
*/
void setScore (Player * player, const unsigned int score);

/**

        @brief assesseur du score d'un joueur
        @param un pointeur sur Player
        @return un entier score
*/
unsigned int getScore (const Player * player);

/* Méthodes */

/**

        @brief méthode d'initialisation d'un joueur
        @param un pointeur sur Player, pointeur sur un char pour le nom
        et un entier score
*/
void initPlayer(Player * player, const char * name, const unsigned int score);

/**

        @brief méthode de création d'un joueur
        @param pointeur sur un char pour le nom et un entier score
        @return un pointeur sur Player
*/
Player * createPlayer(const char * name, const unsigned int score);

/**

        @brief méthode de libération d'un joueur
        @param un pointeur sur Player
*/
void freePlayer(Player * player);
#endif
