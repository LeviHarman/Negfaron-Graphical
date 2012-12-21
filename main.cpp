#include "main.h"
#include "maps.h"
#include "map_entity.h"

enum KEYS{UP,DOWN,LEFT,RIGHT};
vector<vector<Tile>> make_map(int x, int y, string map) {

	vector<vector<Tile>> mv(x, vector<Tile>(y));

	int counter = 0;

	for(int i=0;i<x;i++) {
		for(int j=0;j<y;j++) {
			switch(map[counter]) {
			case 'X'://Wooden log
				mv[i][j].set_values('x','n',0,0);
				break;
			case 'O' ://empty
				mv[i][j].set_values('o','y',1,3);
				break;
			case 'V': //the void
				mv[i][j].set_values('v','n',2,4);
				break;
			case 'G'://grass (long)
				mv[i][j].set_values('g','y',1,1);
				break;
			case 'T'://tree
				mv[i][j].set_values('t','n',0,2);
				break;
			case 'S'://sign
				mv[i][j].set_values('s','n',0,3);
				break;
			case 'B'://blood
				mv[i][j].set_values('b','y',1,4);
				break;
			case 'D': //dirt
				mv[i][j].set_values('d','y',2,3);
				break;
			case 'W': //dirt
				mv[i][j].set_values('w','y',4,3);
				break;
			case 'F': //floor
				mv[i][j].set_values('f','y',1,2);
				break;
			case 'R': //left rug
				mv[i][j].set_values('r','y',5,3);
				break;
			case 'Y': //right rug
				mv[i][j].set_values('y','y',5,4);
				break;
			case '1'://left of roof
				mv[i][j].set_values('1','n',7,3);
				break;
			case '2'://roof center
				mv[i][j].set_values('2','n',7,4);
				break;
			case '3'://small window leftside on roof
				mv[i][j].set_values('3','n',7,5);
				break;
			case '4': //flowerpot window
				mv[i][j].set_values('4','n',7,6);
				break;
			case '5': //small window rightside on roof
				mv[i][j].set_values('5','n',7,7);
				break;
			case '6'://right of roof
				mv[i][j].set_values('6','n',7,8);
				break;
			case '7': //left wall
				mv[i][j].set_values('7','n',8,3);
				break;
			case '8': //wall
				mv[i][j].set_values('8','n',8,4);
				break;
			case '9': //rake
				mv[i][j].set_values('9','n',8,5);
				break;
			case '!': //door
				mv[i][j].set_values('!','y',8,6);
				break;
			case '@': //broom
				mv[i][j].set_values('@','n',8,7);
				break;
			case '#': //right wall
				mv[i][j].set_values('#','n',8,8);
				break;
			case '$': //left of shingles
				mv[i][j].set_values('$','n',6,3);
				break;
			case '%': //shingles
				mv[i][j].set_values('%','n',6,4);
				break;
			case '^': //right of shingles
				mv[i][j].set_values('^','n',6,5);
				break;

			}
			counter++;
		}
	}
	return mv;
}

int main(void)
{
	bool done = false;
	int width = 30;  //row x
	int height = 30; //col y
	string cur_map;
	bool move_animation = false;
	int frame;

	bool keys[4] = {false,false,false,false};

	Entity hero;
	hero.set_loc(12,15);

	int FPS = 10;
	
	char facing = 'd';

	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue=NULL;
	ALLEGRO_TIMER* timer=NULL;
	ALLEGRO_BITMAP *tileset = NULL;
	ALLEGRO_SAMPLE *sample;

	if(!al_init())												//initialize allegro
		return -1;

	display = al_create_display((width*16)-1,(height*16)-1);	//create our display object

	if(!display)												//test display object
		return -1;

	al_install_keyboard();
	al_init_primitives_addon();
	al_init_image_addon();

	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(1);
	sample = al_load_sample("collision.ogg");

	timer=al_create_timer(1.0/FPS);
	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_start_timer(timer);

	vector<vector<Entity>> mve(width, vector<Entity>(height));
	init_map_house(cur_map, mve);
	vector<vector<Tile>> mv = make_map(height,width,cur_map);

	init_map_house_entity(mve);

	tileset = al_load_bitmap("tileset.png");
	al_convert_mask_to_alpha(tileset, al_map_rgb(0,255,255));

	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue,&ev);

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode) {

			case ALLEGRO_KEY_UP:
				if (move_animation == false) {
					facing = 'u';
					keys[UP] = true;
				
					if (hero.can_pass(facing,mv,hero)) {
						move_animation = true; //start animation
					}
					frame = 1;
				}
				break;

			case ALLEGRO_KEY_DOWN:
				if (move_animation == false) {
					facing = 'd';
					keys[DOWN]=true;
				
					if (hero.can_pass(facing,mv,hero)) {
						move_animation = true; //start animation
					}
					frame = 1;
				}
				break;

			case ALLEGRO_KEY_RIGHT:
				if(move_animation == false) {
					facing = 'r';
					keys[RIGHT]=true;

					if (hero.can_pass(facing,mv,hero)) {
						move_animation = true;
					}
					frame = 1;
				}
				break;

			case ALLEGRO_KEY_LEFT:
				if(move_animation==false) {
					facing = 'l';
					keys[LEFT]=true;

					if(hero.can_pass(facing,mv,hero)) {
						move_animation = true;
					}
					frame = 1;
				}
				break;

			case ALLEGRO_KEY_Z:
				switch(facing) {
				case 'u':
					if(mve[hero.hloc-1][hero.wloc].interact == 'y') {
						cout<<mve[hero.hloc-1][hero.wloc].dialogue;
					}
					break;
				case 'd':
					if(mve[hero.hloc+1][hero.wloc].interact == 'y') {
						cout<<mve[hero.hloc+1][hero.wloc].dialogue;
					}
					break;
				case 'l':
					if(mve[hero.hloc][hero.wloc-1].interact == 'y') {
						cout<<mve[hero.hloc][hero.wloc-1].dialogue;
					}
					break;
				case 'r':
					if(mve[hero.hloc][hero.wloc+1].interact == 'y') {
						cout<<mve[hero.hloc][hero.wloc+1].dialogue;
					}
					break;
				break;
				}

			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				done = true;
			}
			switch(ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN]=false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT]=false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT]=false;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		if (move_animation == false) {
			if (keys[UP]==true) {
				if (hero.can_pass(facing,mv,hero)) {
					frame = 1;
					move_animation = true;
				}
			}	
			else if (keys[DOWN]==true) {
				if (hero.can_pass(facing,mv,hero)) {
					frame = 1;
					move_animation = true;
				}
			}
			else if (keys[LEFT] == true) {
				if (hero.can_pass(facing,mv,hero)) {
					frame = 1;
					move_animation = true;
				}		
			}
			else if (keys[RIGHT] == true) {
				if (hero.can_pass(facing,mv,hero)) {
					frame = 1;
					move_animation = true;
				}
			}
		}

		//CHECK FOR ON STEP EVENT################################################################################################
		if(mve[hero.hloc][hero.wloc].step_on == 'y') {
			if (mve[hero.hloc][hero.wloc].map_warp == "house") {
				hero.set_loc(mve[hero.hloc][hero.wloc].warp_col,mve[hero.hloc][hero.wloc].warp_row);
				init_map_entity_cleanup(mve);
				init_map_house_entity(mve);
				init_map_house(cur_map,mve);
				mv = make_map(height,width,cur_map);
			}
			else if (mve[hero.hloc][hero.wloc].map_warp == "home") {
				hero.set_loc(mve[hero.hloc][hero.wloc].warp_col,mve[hero.hloc][hero.wloc].warp_row);
				init_map_entity_cleanup(mve);
				init_map_home_entity(mve);
				init_map_home(cur_map,mve);
				mv = make_map(height,width,cur_map);
			}
		}

		//DRAW MAP################################################################################################################
		for(int col=0;col<height;col++) {
			for(int row=0;row<width;row++) {
				al_draw_bitmap_region(tileset, mv[col][row].sx * 16, mv[col][row].sy * 16, 16, 16, row*16, col*16, 0);
			}
		}
		


		switch (facing) {
		case 'u':
			if(move_animation==true) {
				if (hero.can_pass(facing,mv,hero)) {
					al_draw_bitmap_region(tileset, 0 * 16, 3 * 16, 16, 16, hero.wloc*16, (hero.hloc*16-4)-frame*2, 0);
					if(frame == 7) {
						move_animation = false;
						hero.hloc-=1;
					}
				}
				frame++;
			}
			else {
				al_draw_bitmap_region(tileset, 0 * 16, 3 * 16, 16, 16, hero.wloc*16, hero.hloc*16-4, 0);
			}
			break;
		case 'd':
			if(move_animation==true) {
				if(hero.can_pass(facing,mv,hero)) {
					al_draw_bitmap_region(tileset, 0 * 16, 2 * 16, 16, 16, hero.wloc*16, (hero.hloc*16-4)+frame*2, 0);
					if(frame==7) {
						move_animation = false;
						hero.hloc+=1;
					}
				}
				frame++;
			}
			else {
				al_draw_bitmap_region(tileset, 0 * 16, 2 * 16, 16, 16, hero.wloc*16, hero.hloc*16-4, 0);
			}
			break;
		case 'l':
			if(move_animation==true) {
				if(hero.can_pass(facing,mv,hero)) {
					al_draw_bitmap_region(tileset, 0 * 16, 4 * 16, 16, 16, hero.wloc*16-frame*2, hero.hloc*16-4, 0);
				}
				if(frame==7) {
					move_animation = false;
					hero.wloc-=1;
				}
				frame++;
			}
			else {
				al_draw_bitmap_region(tileset, 0 * 16, 4 * 16, 16, 16, hero.wloc*16, hero.hloc*16-4, 0);
			}
			break;
		case 'r':
			if(move_animation==true) {
				if(hero.can_pass(facing,mv,hero)) {
					al_draw_bitmap_region(tileset, 0 * 16, 5 * 16, 16, 16, hero.wloc*16+frame*2, hero.hloc*16-4, 0);
				}
				if(frame==7) {
					move_animation = false;
					hero.wloc+=1;
				}
				frame++;
			}
			else {
				al_draw_bitmap_region(tileset, 0 * 16, 5 * 16, 16, 16, hero.wloc*16, hero.hloc*16-4, 0);
			}
			break;
		}		

		al_flip_display();
	}

	al_destroy_display(display);
	al_destroy_bitmap(tileset);
	al_destroy_sample(sample);

	return 0;
}