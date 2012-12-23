#include "main.h"
#include "maps.h"
#include "map_entity.h"
#include "make_map.h"

enum KEYS{UP,DOWN,LEFT,RIGHT};

int main(void)
{
	//Allegro variables
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue=NULL;
	ALLEGRO_TIMER* timer=NULL;
	ALLEGRO_BITMAP *tileset = NULL;
	ALLEGRO_SAMPLE *sample;

	//primitive variables
	bool done = false;
	bool keys[4] = {false,false,false,false};
	bool redraw = false;

	//integer variables
	int width = 30;  //row x
	int height = 30; //col y
	int FPS = 60;

	//string variables
	string cur_map;
	
	//Object variables
	Entity hero;
	hero.set_loc(12,15);
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

	sample = al_load_sample("collision.ogg");
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
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN]=true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT]=true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT]=true;
				break;
			case ALLEGRO_KEY_Z:
				switch(hero.facing) {
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

			//end game
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

		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			//DRAW MAP################################################################################################################
			for(int col=0;col<height;col++) {
				for(int row=0;row<width;row++) {
					al_draw_bitmap_region(tileset, mv[col][row].sx * 16, mv[col][row].sy * 16, 16, 16, row*16, col*16, 0);
				}
			}	

			//DRAW & ANIMATE HERO####################################################################################################
			switch (hero.facing) {
			case 'u':
				if(hero.move_animation==true) {
					if (hero.frame<= 7) {
						al_draw_bitmap_region(tileset, 1 * 16, 3 * 16, 16, 16, hero.wloc*16, (hero.hloc*16-4)-hero.frame, 0);
					}
					else if (hero.frame < 15) {
						al_draw_bitmap_region(tileset, 2 * 16, 3 * 16, 16, 16, hero.wloc*16, (hero.hloc*16-4)-hero.frame, 0);
					}
					else if(hero.frame == 15) {
						al_draw_bitmap_region(tileset, 2 * 16, 3 * 16, 16, 16, hero.wloc*16, (hero.hloc*16-4)-hero.frame, 0);
						hero.move_animation = false;
						hero.hloc-=1;
					}
					hero.frame++;
				}
				else {
					al_draw_bitmap_region(tileset, 0 * 16, 3 * 16, 16, 16, hero.wloc*16, hero.hloc*16-4, 0);
				}
				break;
			case 'd':
				if(hero.move_animation==true) {
					if(hero.frame <=7) {
						al_draw_bitmap_region(tileset, 1 * 16, 2 * 16, 16, 16, hero.wloc*16, (hero.hloc*16-4)+hero.frame, 0);
					}
					else if(hero.frame <= 14) {
						al_draw_bitmap_region(tileset, 2 * 16, 2 * 16, 16, 16, hero.wloc*16, (hero.hloc*16-4)+hero.frame, 0);
					}
					else if(hero.frame==15) {
						al_draw_bitmap_region(tileset, 2 * 16, 2 * 16, 16, 16, hero.wloc*16, (hero.hloc*16-4)+hero.frame, 0);
						hero.move_animation = false;
						hero.hloc+=1;
					}
					hero.frame++;
				}
				else {
					al_draw_bitmap_region(tileset, 0 * 16, 2 * 16, 16, 16, hero.wloc*16, hero.hloc*16-4, 0);
				}
				break;
			case 'l':
				if(hero.move_animation==true) {
					if(hero.frame<=7) {
						al_draw_bitmap_region(tileset, 1 * 16, 4 * 16, 16, 16, hero.wloc*16-hero.frame, hero.hloc*16-4, 0);
					}
					else if(hero.frame<=14) {
						al_draw_bitmap_region(tileset, 2 * 16, 4 * 16, 16, 16, hero.wloc*16-hero.frame, hero.hloc*16-4, 0);
					}
					else if(hero.frame==15) {
						al_draw_bitmap_region(tileset, 2 * 16, 4 * 16, 16, 16, hero.wloc*16-hero.frame, hero.hloc*16-4, 0);
						hero.move_animation = false;
						hero.wloc-=1;
					}
					hero.frame++;
				}
				else {
					al_draw_bitmap_region(tileset, 0 * 16, 4 * 16, 16, 16, hero.wloc*16, hero.hloc*16-4, 0);
				}
				break;
			case 'r':
				if(hero.move_animation==true) {
					if(hero.frame<=7) {
						al_draw_bitmap_region(tileset, 1 * 16, 5 * 16, 16, 16, hero.wloc*16+hero.frame, hero.hloc*16-4, 0);
					}
					else if(hero.frame<=14) {
						al_draw_bitmap_region(tileset, 2 * 16, 5 * 16, 16, 16, hero.wloc*16+hero.frame, hero.hloc*16-4, 0);
					}
					else if(hero.frame==15) {
						al_draw_bitmap_region(tileset, 2 * 16, 5 * 16, 16, 16, hero.wloc*16+hero.frame, hero.hloc*16-4, 0);
						hero.move_animation = false;
						hero.wloc+=1;
					}
					hero.frame++;
				}
				else {
					al_draw_bitmap_region(tileset, 0 * 16, 5 * 16, 16, 16, hero.wloc*16, hero.hloc*16-4, 0);
				}
				break;
			}	

			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}

	al_destroy_display(display);
	al_destroy_bitmap(tileset);
	al_destroy_sample(sample);

	return 0;
}