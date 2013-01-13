//Programmed by Levi Harman
//Date: Started Dec. 2012

#include "neg_headers/main.h"
#include "neg_headers/creature.h"
#include "neg_headers/maps.h"
#include "neg_headers/map_entity.h"
#include "neg_headers/make_map.h"
#include "neg_headers/draw_map.h"
#include "neg_headers/move_hero.h"
#include "neg_headers/entity_message.h"

enum KEYS{UP,DOWN,LEFT,RIGHT};

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
	
	/*
	wid_height initialization
	*/
	vector<int> wid_height;
	wid_height.push_back(1);
	wid_height.push_back(1);
	wid_height[0] = 30; //col x
	wid_height[1] = 30; //col y

	/*
	Integer variables
	*/
	int FPS = 100;

	/*
	Timing variables
	*/
	time_t timer1 = clock();
	int frame_counter = 0; 

	/*
	String variables
	*/
	string cur_map;
	
	/*
	Object variables
	*/
	Creature hero;
	hero.set_loc(12,15);
	hero.facing = 'd';
	hero.is_swing_hoe = false;
	hero.move_animation = false;
	hero.wait_time=1;
	
	if(!al_init())
		return -1;

	display = al_create_display((wid_height[0]*16)-1,(wid_height[1]*16)-1);

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
	sample = al_load_sample("neg_resources/collision.ogg");
	font = al_load_font("neg_resources/arial.ttf",16,0);
	timer = al_create_timer(1.0/FPS);
	event_queue = al_create_event_queue();

	//game init
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_start_timer(timer);

	vector<Entity> mve(wid_height[0]*wid_height[1]);
	init_map_house(cur_map, mve);
	vector<Tile> mv = make_map(wid_height,cur_map);
	init_map_house_entity(mve);

	tileset = al_load_bitmap("neg_resources/tileset.png");
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
				if (hero.move_animation == false && hero.is_swing_hoe == false) {
					hero.sta_frame = 1;
					hero.is_swing_hoe = true;
				}
				break;
			case ALLEGRO_KEY_Z:
				if(write_dialogue == true) {
					write_dialogue = false;
				}
				else if (hero.can_interact(write_dialogue,mve) == true){ //neeeds if statement.
					write_dialogue = true;
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
		if (hero.move_animation == false) {
			if (keys[UP]==true) {
				hero.creature_turning('u',mv);
			}	
			else if (keys[DOWN]==true) {
				hero.creature_turning('d',mv);
			}
			else if (keys[LEFT] == true) {
				hero.creature_turning('l',mv);
			}
			else if (keys[RIGHT] == true) {
				hero.creature_turning('r',mv);
			}
		}

		//CHECK FOR ON STEP EVENT
		if(mve[(hero.hloc*30)+hero.wloc].step_on == 'y') {
			if (mve[(hero.hloc*30)+hero.wloc].map_warp == "house") {
				hero.set_loc(mve[(hero.hloc*30)+hero.wloc].warp_col,mve[(hero.hloc*30)+hero.wloc].warp_row);
				init_map_entity_cleanup(mve);
				init_map_house_entity(mve);
				init_map_house(cur_map,mve);
				mv = make_map(wid_height,cur_map);
			}
			else if (mve[(hero.hloc*30)+hero.wloc].map_warp == "home") {
				hero.set_loc(mve[(hero.hloc*30)+hero.wloc].warp_col,mve[(hero.hloc*30)+hero.wloc].warp_row);
				init_map_entity_cleanup(mve);
				init_map_home_entity(mve);
				init_map_home(cur_map,mve);
				mv = make_map(wid_height,cur_map);
			}
		}

		hero.wait_time++;
		//This block runs 60 times per second
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			//DRAW MAP
			draw_map(tileset,wid_height,mv,hero,0,0);

			//DRAW & ANIMATE HERO
			frame_counter++;
			if ((clock() - timer1) >= 1000) {
				cout<<frame_counter<<"\n";
				frame_counter = 0;
				timer1 = clock();
			}
			move_hero(hero,tileset,mv,wid_height);

			//display message
			if(write_dialogue == true) {
				entity_message(tileset,hero,font,mve,wid_height);
			}
			
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
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

	return 0;
}