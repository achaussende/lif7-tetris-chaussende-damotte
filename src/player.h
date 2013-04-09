/*player.h*/

#ifndef PLAYER_H
#define PLAYER_H

typedef struct
{
    char name[25];
    unsigned int score;
}Player;

/* Mutateurs & Accesseurs */

void setName (Player player, const char * name);
char getName (Player player);

void setScore (Player player, unsigned int score);
unsigned int getScore (Player player);

#endif
