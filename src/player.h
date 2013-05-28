/*player.h*/

#ifndef PLAYER_H
#define PLAYER_H

typedef struct
{
    char name[26]; // 25 caractères + \0
    unsigned int score;
}Player;

/* Mutateurs & Accesseurs */

void setName (Player * player, const char * name);
char * getName (const Player * player);

void setScore (Player * player, unsigned int score);
unsigned int getScore (const Player * player);

/* Méthodes */

void initPlayer(Player * player, const char * name, unsigned int score);
Player * createPlayer(const char * name, unsigned int score);

#endif
