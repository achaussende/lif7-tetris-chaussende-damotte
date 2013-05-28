#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "player.h"

/* Mutateurs & Accesseurs */

void setName (Player * player, const char * name)
{
    if(strlen(name) <= 25)
    {
        strcpy(player->name, name);
    }
    else
    {
        printf("Nom de joueur trop long. \n");
    }

}

char * getName (const Player * player)
{
    return player->name;
}

void setScore (Player * player, unsigned int score)
{
    player->score = score;
}

unsigned int getScore (const Player * player)
{
    return player->score;
}

/* Méthodes */

void initPlayer(Player * player, const char * name, unsigned int score)
{
    if(player == NULL)
    {
        printf("Erreur de joueur : adresse invalide. \n");
    }
    else
    {
        setName(player, name);
        setScore(player, score);
    }
}

Player * createPlayer(const char * name, unsigned int score)
{
    Player * player = (Player*)malloc(sizeof(Player));

    initPlayer(player, name, score);

    return player;
}
