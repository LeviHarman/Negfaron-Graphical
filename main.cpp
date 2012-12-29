//Programmed by Levi Harman
//Date: Started Dec. 2012

#include "main.h"
#include "maps.h"
#include "map_entity.h"
#include "make_map.h"
#include "move_hero.h"
#include "entity_message.h"
#include <time.h>;

enum KEYS{UP,DOWN,LEFT,RIGHT};


/*
   can_interact: hvar and wvar are used to convert char facing into
   a + or - value used to call the .interact function of Hero class
*/
bool can_interact (Entity * hero, bool write_dialogue, vector<vector<Entity>> mve){
	int hvar = 0;
	int wvar = 0;

	switch(hero->facing) {
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

	if(mve[hero->hloc+hvar][hero->wloc+wvar].interact == 'y') {
		write_dialogue = true;
	}

	return can_interact;
}

int main(void)
{
	/*
	Allegro variables
	*/
	ALLEGRO_DISPLAY * display = NULL;
	ALLEGRO_EVENT_QUEUE * event_queue=NULL;
	ALLEGRO_TIMER * timer=NULL;
	ALLEGRO_BITMAP * tileset = NULL;
	ALLEGRO_SAMPLE * sample;
	ALLEGRO_FONT * font;

	/*
	Primitive variables
	*/
	bool done = false;
	bool keys[4] = {false,false,false,false};
	bool redraw = true;
	bool write_dialogue = false;
	bool game_start = false;
	
	/*
	Integer variables
	*/
	int width = 30;  //row x
	int height = 30; //col y
	int FPS = 30;
	int time1;
	int time2;

	/*
	String variables
	*/
	string cur_map;
	
	/*
	Object variables
	*/
	Entity * hero = new Entity;
	hero->set_loc(12,15);
	hero->frame = 6;
	hero->facing = 'd';
	hero->is_swing_hoe = false;
	hero->move_animation = false;
	hero->wait_time=1;
	
	if(!al_init())
		return -1;

	display = al_create_display((30*16)-1,(30*16)-1);

	if(!display)
		return -1;

	/*
	Initialize allegro modules.
	*/
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(1);
	al_init_font_addon();
	al_init_ttf_addon();

	/*
	Initialize allegro variables.
	*/
	sample = al_load_sample("collision.ogg");
	font = al_load_font("arial.ttf",16,0);
	timer = al_create_timer(1.0/FPS);
	event_queue = al_create_event_queue();

	//game init
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


	//game loop
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue,&ev);
		
		if(ev.type == ALLEGRO_EVENT_TIMER){
			redraw = true;
		}
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				write_dialogue = false;
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				write_dialogue = false;
				keys[DOWN]=true;
				break;
			case ALLEGRO_KEY_RIGHT:
				write_dialogue = false;
				keys[RIGHT]=true;
				break;
			case ALLEGRO_KEY_LEFT:
				write_dialogue = false;
				keys[LEFT]=true;
				break;
			case ALLEGRO_KEY_RCTRL:
				if (hero->move_animation == false && hero->is_swing_hoe == false) {
					hero->sta_frame = 1;
					hero->is_swing_hoe = true;
				}
				break;
			case ALLEGRO_KEY_Z:
				game_start = true;
				if(write_dialogue == true) {
					write_dialogue = false;
				}
				else {
					write_dialogue = can_interact(hero,write_dialogue,mve);
				}
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {

			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				done = true;
			}

			//keys no longer held down.
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

		//WAIT UNTIL ANIMATION IS OVER - If key is still pressed animate again. (Pokemon esque)
		if (hero->move_animation == false) {
			if (keys[UP]==true) {
				*hero = hero->hero_turning(*hero,'u',mv);
			}	
			else if (keys[DOWN]==true) {
				*hero = hero->hero_turning(*hero,'d',mv);
			}
			else if (keys[LEFT] == true) {
				*hero = hero->hero_turning(*hero,'l',mv);
			}
			else if (keys[RIGHT] == true) {
				*hero = hero->hero_turning(*hero,'r',mv);
			}
		}

		//CHECK FOR ON STEP EVENT###################################################################################################
		if(mve[hero->hloc][hero->wloc].step_on == 'y') {
			if (mve[hero->hloc][hero->wloc].map_warp == "house") {
				hero->set_loc(mve[hero->hloc][hero->wloc].warp_col,mve[hero->hloc][hero->wloc].warp_row);
				init_map_entity_cleanup(mve);
				init_map_house_entity(mve);
				init_map_house(cur_map,mve);
				mv = make_map(height,width,cur_map);
			}
			else if (mve[hero->hloc][hero->wloc].map_warp == "home") {
				hero->set_loc(mve[hero->hloc][hero->wloc].warp_col,mve[hero->hloc][hero->wloc].warp_row);
				init_map_entity_cleanup(mve);
				init_map_home_entity(mve);
				init_map_home(cur_map,mve);
				mv = make_map(height,width,cur_map);
			}
		}

		hero->wait_time++;
		//This block runs 60 times per second
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			if(game_start == true) {
				//DRAW MAP
				for(int col=0;col<height;col++) {
					for(int row=0;row<width;row++) {
						al_draw_bitmap_region(tileset, mv[col][row].sx * 16, mv[col][row].sy * 16, 16, 16, (row*16 - hero->wloc*16)+height/2*16, (col*16 - hero->hloc*16)+width/2*16+hero->frame-4, 0);
					}
				}	

				//DRAW & ANIMATE HERO
				*hero = move_hero(*hero,tileset,mv,height,width);

				//display message
				if(write_dialogue == true) {
					entity_message(tileset,*hero,font,mve,height,width);
				}
			
				al_flip_display();
				al_clear_to_color(al_map_rgb(0,0,0));
			}
		}
	}


	/*
	Cleanup
	*/
	al_destroy_display(display);
	al_destroy_bitmap(tileset);
	al_destroy_sample(sample);
	al_destroy_font(font);
	al_destroy_event_queue(event_queue);
	al_destroy_timer (timer);
	delete hero;

	return 0;
}