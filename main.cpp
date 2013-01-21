//Programmed by Levi Harman
//Date: Started Dec. 2012

#include "neg_headers/main.h"
#include "neg_headers/creature.h"
#include "neg_headers/maps.h"
#include "neg_headers/map_entity.h"
#include "neg_headers/entity_message.h"
#include "neg_headers/game_system.h"

int main(void)
{
	if(!al_init())
		return -1;

	Game_system gs;
	gs.set_values();
	gs.loop();

	return 0;
}