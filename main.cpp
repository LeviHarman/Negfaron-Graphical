#include "main.h"
#include "maps.h"

//al_draw_bitmap_region(image, sx * 16, sy * 16, 16, 16, x, y, 0);

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

	al_start_timer(timer);

	vector<vector<Entity>> mve(width, vector<Entity>(height));
	init_map_house(cur_map, mve);
	vector<vector<Tile>> mv = make_map(height,width,cur_map);

	Entity rug;
	rug.set_warp("home");
	rug.set_hero_loc(16,9);
	mve[17][15] = rug;
	mve[17][16] = rug;

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
				facing = 'u';
				if(mv[hero.hloc-1][hero.wloc].pass == 'y') {
					hero.hloc-=1;
				}
				else if(mv[hero.hloc-1][hero.wloc].pass == 'n') {
					al_play_sample(sample, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				break;
			case ALLEGRO_KEY_DOWN:
				facing = 'd';
				if(mv[hero.hloc+1][hero.wloc].pass == 'y') {
					hero.hloc+=1;
				}
				else if(mv[hero.hloc+1][hero.wloc].pass == 'n') {
					al_play_sample(sample, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				break;
			case ALLEGRO_KEY_RIGHT:
				facing = 'r';
				if(mv[hero.hloc][hero.wloc+1].pass == 'y') {
					hero.wloc+=1;
				}
				else if(mv[hero.hloc][hero.wloc+1].pass == 'n') {
					al_play_sample(sample, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				break;
			case ALLEGRO_KEY_LEFT:
				facing = 'l';
				if(mv[hero.hloc][hero.wloc-1].pass == 'y') {
					hero.wloc-=1;
				}
				else if(mv[hero.hloc][hero.wloc-1].pass == 'n') {
					al_play_sample(sample, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				break;
			case ALLEGRO_KEY_Z:
				switch(facing) {
				case 'u':
					if(mve[hero.hloc-1][hero.wloc].interact == 'y') {
						cout<<"Welcome to Negfaron!";
					}
					break;
				case 'd':
					if(mve[hero.hloc+1][hero.wloc].interact == 'y') {
						cout<<"Welcome to Negfaron!";
					}
					break;
				case 'l':
					if(mve[hero.hloc][hero.wloc-1].interact == 'y') {
						cout<<"Welcome to Negfaron!";
					}
					break;
				case 'r':
					if(mve[hero.hloc][hero.wloc+1].interact == 'y') {
						cout<<"Welcome to Negfaron!";
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
		}

		//check for step_on event
		if(mve[hero.hloc][hero.wloc].step_on == 'y') {
			//vector<vector<Entity>> mve(width, vector<Entity>(height));
			if (mve[hero.hloc][hero.wloc].map_warp == "house") {
				hero.set_loc(mve[hero.hloc][hero.wloc].warp_col,mve[hero.hloc][hero.wloc].warp_row);
				for (int i=0;i<30;i++){
					for (int j = 0;j<30;j++) {
					mve[i][j].cleanup();
					}
				}

				Entity rug;
				rug.set_warp("home");
				rug.set_hero_loc(16,9);
				mve[17][15] = rug;
				mve[17][16] = rug;

				init_map_house(cur_map,mve);
				mv = make_map(height,width,cur_map);
			}

			else if (mve[hero.hloc][hero.wloc].map_warp == "home") {
				hero.set_loc(mve[hero.hloc][hero.wloc].warp_col,mve[hero.hloc][hero.wloc].warp_row);
				

				for (int i=0;i<30;i++){
					for (int j = 0;j<30;j++) {
					mve[i][j].cleanup();
					}
				}

 				Entity sign;
				sign.entity_event("Hello, entity event is working.");
				mve[2][7] = sign; //2 down one over
		
				Entity door;
				door.set_warp("house");
				door.set_hero_loc(16,15);
				mve[15][9] = door;

				init_map_home(cur_map,mve);
				mv = make_map(height,width,cur_map);
			}
		}

		//draw map
		for(int col=0;col<height;col++) {
			for(int row=0;row<width;row++) {
				al_draw_bitmap_region(tileset, mv[col][row].sx * 16, mv[col][row].sy * 16, 16, 16, row*16, col*16, 0);
			}
		}
		
		switch (facing) {
		case 'u':
			al_draw_bitmap_region(tileset, 0 * 16, 3 * 16, 16, 16, hero.wloc*16, hero.hloc*16, 0);
			break;
		case 'd':
			al_draw_bitmap_region(tileset, 0 * 16, 2 * 16, 16, 16, hero.wloc*16, hero.hloc*16, 0);
			break;
		case 'l':
			al_draw_bitmap_region(tileset, 0 * 16, 4 * 16, 16, 16, hero.wloc*16, hero.hloc*16, 0);
			break;
		case 'r':
			al_draw_bitmap_region(tileset, 0 * 16, 5 * 16, 16, 16, hero.wloc*16, hero.hloc*16, 0);
			break;
		}		

		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
	}

	al_destroy_display(display);
	al_destroy_bitmap(tileset);
	al_destroy_sample(sample);

	return 0;
}