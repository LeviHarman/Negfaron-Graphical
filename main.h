#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Tile {
public:
	char cid, pass;
	int sy,sx;
	void set_values (char,char,int,int);
};

void Tile::set_values(char cid1,char pass1,int sy1,int sx1) {
	cid = cid1;
	pass = pass1;
	sy = sy1;
	sx = sx1;
}

class Entity {
public:
	int wloc, hloc, frame;
	int warp_row, warp_col;
	char interact,step_on,facing;
	string dialogue,map_warp;
	bool move_animation;
	void set_loc(int,int);
	void entity_event(string);
	void set_warp(string);
	void set_hero_loc(int,int);
	void cleanup ();
	bool can_pass(char,vector<vector<Tile>>,Entity);
};

void Entity::cleanup() {
	wloc = NULL;
	hloc = NULL;
	frame = NULL;
	warp_row=NULL;
	warp_col=NULL;
	interact = NULL;
	step_on=NULL;
	facing = NULL;
}

bool Entity::can_pass(char dir, vector<vector<Tile>> mv,Entity hero) {
	switch(dir) {
	case 'l':
		if(mv[hero.hloc][hero.wloc-1].pass == 'y') {
			return true;
		}
		else
			return false;
		break;
	case 'r':
		if(mv[hero.hloc][hero.wloc+1].pass == 'y') {
			return true;
		}
		else
			return false;
		break;
	case 'u':
		if(mv[hero.hloc-1][hero.wloc].pass == 'y') {
			return true;
		}
		else
			return false;
		break;
	case 'd':
		if(mv[hero.hloc+1][hero.wloc].pass == 'y') {
			return true;
		}
		else
			return false;
		break;
	}
}

void Entity::set_hero_loc(int row,int col) {
	warp_row = row;
	warp_col = col;
}

void Entity::set_warp(string map_warp1) {
	step_on = 'y';
	map_warp = map_warp1;
}

void Entity::set_loc(int wloc1,int hloc1) {
	hloc = hloc1;
	wloc = wloc1;
}

void Entity::entity_event(string dialogue1) {
	interact = 'y';
	dialogue = dialogue1;
}