class Creature: public Entity {
public:
	int frame,sta_frame;
	int corn_seeds, turnip_seeds;
	int wait_time;
	bool move_animation, is_swing_hoe;
	char facing;
	bool can_interact(bool,vector<Entity>&);
	bool can_pass(char,vector<Tile>&);
	void creature_turning(char,vector<Tile>&);
};

/*
   can_interact: hvar and wvar are used to convert char facing into
   a + or - value used to call the .interact function of Hero class
*/
bool Creature::can_interact (bool write_dialogue, vector<Entity> &mve){
	bool can_interact = false;
	int hvar = 0;
	int wvar = 0;

	switch(facing) {
	case 'u':
		hvar = -1;
		break;
	case 'd':
		hvar = 1;
		break;
	case 'l':
		wvar = -1;
		break;
	case 'r':
		wvar = 1;
		break;
	}

	if(mve[( (hloc+hvar)*30)+wloc+wvar].interact == 'y') {
		can_interact = true;
		write_dialogue = true;
	}

	return can_interact;
}

void Creature::creature_turning(char facing1, vector<Tile> &mv) {

	if (is_swing_hoe == false) {
					
		if(facing != facing1) {
			facing = facing1;
			wait_time = 0;
		}

		else if (can_pass(facing,mv)&& wait_time > 3) {
			frame = 1;
			move_animation = true;
		}
	}
}

bool Creature::can_pass(char dir, vector<Tile> &mv) {
	switch(dir) {
	case 'l':
		if(mv[(hloc*30)+wloc-1].pass == 'y') {
			return true;
		}
		else
			return false;
		break;
	case 'r':
		if(mv[(hloc*30)+wloc+1].pass == 'y') {
			return true;
		}
		else
			return false;
		break;
	case 'u':
		if(mv[( (hloc-1)*30)+wloc].pass == 'y') {
			return true;
		}
		else
			return false;
		break;
	case 'd':
		if(mv[( (hloc+1)*30)+wloc].pass == 'y') {
			return true;
		}
		else
			return false;
		break;
	}
}