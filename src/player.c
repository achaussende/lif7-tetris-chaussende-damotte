#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "player.h"

void setName (Player player, const char * name[])
{
    assert(strlen(name) <= 25);
    strcpy(player.name, name);
}

char getName (const Player player)
{
    return player.name;
}

void setScore (Player player, unsigned int score)
{
    player.score = score;
}

unsigned int getScore (const Player player)
{
    return player.score;
}
