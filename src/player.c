#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "player.h"

void setName (Player player, const char name)
{
    player.name = name;
}

char getName (const Player player)
{
    return player.name;
}

void setScore (Player player, int score)
{
    player.score = score;
}

int getScore (const PLayer player)
{
    return player.score;
}
