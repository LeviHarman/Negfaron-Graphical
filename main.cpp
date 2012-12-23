//Programmed by Levi Harman
//Date: Started Dec. 2012

#include "main.h"
#include "maps.h"
#include "map_entity.h"
#include "make_map.h"
#include "move_hero.h"
#include "entity_message.h"

enum KEYS{UP,DOWN,LEFT,RIGHT};

int main(void)
{
	//Allegro variables
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue=NULL;
	ALLEGRO_TIMER* timer=NULL;
	ALLEGRO_BITMAP *tileset = NULL;
	ALLEGRO_SAMPLE *sample;
	ALLEGRO_FONT *font;

	//primitive variables
	bool done = false;
	bool keys[4] = {false,false,false,false};
	bool redraw = true;
	bool write_dialogue = false;

	//integer variables
	int width = 30;  //row x
	int height = 30; //col y
	int FPS = 60;

	//string variables
	string cur_map;
	
	//Object variables
	Entity hero;
	hero.set_loc(12,15);
	hero.frame = NULL;
	hero.facing = 'd';
	hero.move_animation = false;
	
	if(!al_init())
		return -1;

	display = al_create_display((width*16)-1,(height*16)-1);

	if(!display)
		return -1;

	//Allegro module init
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(1);
	al_init_font_addon();
	al_init_ttf_addon();

	sample = al_load_sample("collision.ogg");
	font = al_load_font("FROMAN.ttf",16,0);
	timer=al_create_timer(1.0/FPS);
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
			case ALLEGRO_KEY_Z:
				if(write_dialogue == true) {
					write_dialogue = false;
				}
				else {
					switch(hero.facing) {
					case 'u':
						if(mve[hero.hloc-1][hero.wloc].interact == 'y') {
							write_dialogue = true;
						}
						break;
					case 'd':
						if(mve[hero.hloc+1][hero.wloc].interact == 'y') {
							write_dialogue = true;
						}
						break;
					case 'l':
						if(mve[hero.hloc][hero.wloc-1].interact == 'y') {
							write_dialogue = true;
						}
						break;
					case 'r':
						if(mve[hero.hloc][hero.wloc+1].interact == 'y') {
							write_dialogue = true;
						}

						break;
					break;
					}
				}
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {

			//end game
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				done = true;
			}

			//keys no longer held down.
			switch(ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				//al_resize_display(display,(hero.hloc/16)+16,hero.wloc/.16);
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
		if (hero.move_animation == false) {
			if (keys[UP]==true) {
				hero.facing = 'u';
				if (hero.can_pass(hero.facing,mv,hero)) {
					hero.frame = 1;
					hero.move_animation = true;
				}
			}	
			else if (keys[DOWN]==true) {
				hero.facing = 'd';
				if (hero.can_pass(hero.facing,mv,hero)) {
					hero.frame = 1;
					hero.move_animation = true;
				}
			}
			else if (keys[LEFT] == true) {
				hero.facing = 'l';
				if (hero.can_pass(hero.facing,mv,hero)) {
					hero.frame = 1;
					hero.move_animation = true;
				}		
			}
			else if (keys[RIGHT] == true) {
				hero.facing = 'r';
				if (hero.can_pass(hero.facing,mv,hero)) {
					hero.frame = 1;
					hero.move_animation = true;
				}
			}
		}

		//CHECK FOR ON STEP EVENT###################################################################################################
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

		//This block runs 60 times per second########################################################################################
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			//DRAW MAP###############################################################################################################
			for(int col=0;col<height;col++) {
				for(int row=0;row<width;row++) {
					al_draw_bitmap_region(tileset, mv[col][row].sx * 16, mv[col][row].sy * 16, 16, 16, (row*16 - hero.wloc*16)+height/2*16, (col*16 - hero.hloc*16)+width/2*16+hero.frame-16, 0);
				}
			}	

			//DRAW & ANIMATE HERO####################################################################################################
			hero = move_hero(hero,tileset,mv,height,width);

			//display message
			if(write_dialogue ==true) {
				entity_message(tileset,hero,font,mve,height,width);
			}
			
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}

	al_destroy_display(display);
	al_destroy_bitmap(tileset);
	al_destroy_sample(sample);
	al_destroy_font(font);
	al_destroy_event_queue(event_queue);
	al_destroy_timer (timer);

	return 0;
}