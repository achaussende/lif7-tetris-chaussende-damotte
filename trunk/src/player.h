/*player.h*/

#ifndef PLAYER_H
#define PLAYER_H

typedef struct
{
    char name;
    int score; //long or short int ?
}Player;

/* Mutateurs & Accesseurs */

void setName (Player player, char name);
char getName (Player player);

void setScore (Player player, int score);
int getScore (Player player);

#endif
