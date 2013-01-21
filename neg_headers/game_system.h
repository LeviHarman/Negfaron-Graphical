class Game_system {
public:
enum KEYS{UP,DOWN,LEFT,RIGHT};
ALLEGRO_DISPLAY * display;
ALLEGRO_EVENT_QUEUE * event_queue;
ALLEGRO_TIMER * timer;
ALLEGRO_BITMAP * tileset;
ALLEGRO_SAMPLE * sample;
ALLEGRO_FONT * font;
bool done;
bool keys[4];
bool redraw;
bool write_dialogue;
vector<int> wid_height;
int FPS;
time_t timer1;
int frame_counter;
string cur_map;
Creature hero;
vector<Entity> mve;
vector<Tile> mv;

void loop();
void set_values();
void draw_map(int,int);
void walk_animation(int,int,int,int,int,int,int,int,int);
void move_hero();
void three_frame_animation(int,int,int,int,int,int,int,int,int,int,int);
void make_map();
};

void Game_system::set_values() {
/*
Allegro variables
*/
display=NULL;
event_queue=NULL;
timer=NULL;
tileset = NULL;
sample = NULL;
font = NULL;

/*
Primitive variables
*/
done = false;
keys[0] = false;
keys[1] = false;
keys[2] = false;
keys[3] = false;
redraw = true;
write_dialogue = false;
	
/*
wid_height initialization
*/
wid_height.push_back(1);
wid_height.push_back(1);
wid_height[0] = 30; //col x
wid_height[1] = 30; //col y

/*
Integer variables
*/
FPS = 100;

/*
Timing variables
*/
timer1 = clock();
frame_counter = 0; 

hero.set_loc(12,15);
hero.facing = 'd';
hero.is_swing_hoe = false;
hero.move_animation = false;
hero.wait_time=1;

display = al_create_display((wid_height[0]*16)-1,(wid_height[1]*16)-1);


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

mve.resize(wid_height[0]*wid_height[1]);
init_map_house(cur_map, mve);
make_map();
init_map_house_entity(mve);

tileset = al_load_bitmap("neg_resources/tileset.png");
al_convert_mask_to_alpha(tileset, al_map_rgb(0,255,255));
}

void Game_system::loop() {
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
				make_map();
			}
			else if (mve[(hero.hloc*30)+hero.wloc].map_warp == "home") {
				hero.set_loc(mve[(hero.hloc*30)+hero.wloc].warp_col,mve[(hero.hloc*30)+hero.wloc].warp_row);
				init_map_entity_cleanup(mve);
				init_map_home_entity(mve);
				init_map_home(cur_map,mve);
				make_map();
			}
		}

		hero.wait_time++;
		//This block runs 60 times per second
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			//DRAW MAP
			draw_map(0,0);

			//DRAW & ANIMATE HERO
			frame_counter++;
			if ((clock() - timer1) >= 1000) {
				cout<<frame_counter<<"\n";
				frame_counter = 0;
				timer1 = clock();
			}
			move_hero();

			//display message
			if(write_dialogue == true) {
				entity_message(tileset,hero,font,mve,wid_height);
			}
			
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
}

void Game_system::draw_map (int radj, int cadj) 
//Draws map and you can modify pixel by pixel with radj and cadj. (Row adjustment and Column adjustment). Set them to zero if you desire no modification.
{
	for(int col=0;col<wid_height[0];col++) {
		for(int row=0;row<wid_height[1];row++) {
			al_draw_bitmap_region(tileset, 
				mv[(col*30)+row].sx * 16, mv[(col*30)+row].sy * 16,
				16,16,
				(row*16 - hero.wloc*16)+((wid_height[1]/2)*16) + radj,
				(col*16 - hero.hloc*16)+((wid_height[0]/2)*16) + cadj,
				0); 
		}
	}	
}

void Game_system::walk_animation (int tw, int aheight, int awidth, int ci1,int ci2,int ci3,int ri1, int ri2, int ri3) 
/*
Draws the walking animation

Variable description
#######################
Entity being animated, tileset,map vector 1-3
tile width, animation height in tiles, and animation width in tiles
height, and width of map in tiles.
ci1,ci2,ci3 column of the three animations
ri1,ri2,ri3 row of the three animations

*/
{
	if(hero.move_animation==true) {
		int frameintv=0;
		int frameinth=0;
		int hl=0;
		int vl=0;

		switch (hero.facing) {
		case 'u':
			vl = -1;
			frameintv = hero.frame * 3;
			break;
		case 'd' :
			vl=1;
			frameintv = (hero.frame * 3) *-1;
			break;
		case 'l' :
			hl=-1;
			frameinth = hero.frame * 3;
			break;
		case 'r':
			hl=1;
			frameinth = (hero.frame * 3) *-1;
			break;
		}

		//Draw Map in motion
		draw_map(frameinth,frameintv);

		if (hero.frame<= 2) {
			al_draw_bitmap_region(tileset, ri2*tw, ci2*tw, tw, tw, 15*tw, 15*tw, 0);
		}
		else if (hero.frame < 5) {
			al_draw_bitmap_region(tileset, ri3*tw, ci3*tw, tw, tw, 15*tw, 15*tw, 0);
		}
		else if(hero.frame == 5) {
			al_draw_bitmap_region(tileset, ri3*tw, ci3*tw, tw, tw, 15*tw, 15*tw, 0);
			hero.move_animation = false;
			hero.hloc+=vl; //moving line.
			hero.wloc+=hl; // moving line.
		}
		hero.frame++;
	}
	else {
		al_draw_bitmap_region(tileset, ri1 * tw, ci1 * tw, tw, tw, 15*tw, 15*tw, 0);
	}
}

void Game_system::move_hero () {
	int tw = 16;

	if(hero.move_animation==false) {
		if(hero.is_swing_hoe == true) {
			switch (hero.facing) {
			case 'u':
				three_frame_animation(tw,16,16,16,0,1,2,2,1,-1,-2);
				break;
			case 'd' :
				three_frame_animation(tw,13,13,13,0,1,2,3,1,-1,-2);
				break;
			case 'l':
				three_frame_animation(tw,18,18,18,0,2,4,2,2,-2,-2);
				break;
			case 'r':
				three_frame_animation(tw,20,20,20,0,2,4,2,2,-1,-2);
				break;
			}

			hero.sta_frame++;
		}
	}
	if(hero.is_swing_hoe == false) {
		switch (hero.facing) {
		case 'u':
			walk_animation(tw,1,1,3,3,3,0,1,2);
			break;
		case 'd':
			walk_animation(tw,1,1,2,2,2,0,1,2);
			break;
		case 'l':
			walk_animation(tw,1,1,4,4,4,0,1,2);
			break;
		case 'r':
			walk_animation(tw,1,1,5,5,5,0,1,2);
			break;
		}
	}
}

void Game_system::three_frame_animation(int tw, int ci1,int ci2, int ci3, int ri1, int ri2, int ri3,int aheight,int awidth,int radj, int cadj) 
/*draws 3 frame animations.

variables description
##############################
tileset, tile width, Entity being animated,  1-3
column for first, second, and third frames. 4-6
row for first,second, and third frames. 7-9
animation height in tiles, animation width in tiles. 10,11
radj, and cadj are for adjusting the center of animation. makes function tweakable.
*/
{
	if(hero.sta_frame<=2) {
		al_draw_bitmap_region(tileset, (ri1)*tw, (ci1)*tw, tw*awidth, tw*aheight, (16+radj)*tw, (16+cadj)*tw, 0);
	}
	else if(hero.sta_frame<=4) {
		al_draw_bitmap_region(tileset, (ri2)*tw, (ci2)*tw, tw*awidth, tw*aheight, (16+radj)*tw, (16+cadj)*tw, 0);
	}
	else if(hero.sta_frame<=5) {
		al_draw_bitmap_region(tileset, (ri3)*tw, (ci3)*tw, tw*awidth, tw*aheight, (16+radj)*tw, (16+cadj)*tw, 0);
	}
	else if (hero.sta_frame <= 6) {
		al_draw_bitmap_region(tileset, (ri3)*tw, (ci3)*tw, tw*awidth, tw*aheight, (16+radj)*tw, (16+cadj)*tw, 0);
		hero.is_swing_hoe = false;
	}
}

void Game_system::make_map() {

	mv.resize(wid_height[0]*wid_height[1]);

	for(int i=0;i<mv.size();i++) {
		switch(cur_map[i]) {
		case 'X'://Wooden log
			mv[i].set_values('x','n',0,0);
			break;
		case 'O' ://empty
			mv[i].set_values('o','y',1,3);
			break;
		case 'V': //the void
			mv[i].set_values('v','n',2,4);
			break;
		case 'G'://grass (long)
			mv[i].set_values('g','y',1,1);
			break;
		case 'T'://tree
			mv[i].set_values('t','n',0,2);
			break;
		case 'S'://sign
			mv[i].set_values('s','n',0,3);
			break;
		case 'B'://blood
			mv[i].set_values('b','y',1,4);
			break;
		case 'D': //dirt
			mv[i].set_values('d','y',2,3);
			break;
		case 'W': //dirt
			mv[i].set_values('w','y',4,3);
			break;
		case 'F': //floor
			mv[i].set_values('f','y',1,2);
			break;
		case 'R': //left rug
			mv[i].set_values('r','y',5,3);
			break;
		case 'Y': //right rug
			mv[i].set_values('y','y',5,4);
			break;
		case '1'://left of roof
			mv[i].set_values('1','n',7,3);
			break;
		case '2'://roof center
			mv[i].set_values('2','n',7,4);
			break;
		case '3'://small window leftside on roof
			mv[i].set_values('3','n',7,5);
			break;
		case '4': //flowerpot window
			mv[i].set_values('4','n',7,6);
			break;
		case '5': //small window rightside on roof
			mv[i].set_values('5','n',7,7);
			break;
		case '6'://right of roof
			mv[i].set_values('6','n',7,8);
			break;
		case '7': //left wall
			mv[i].set_values('7','n',8,3);
			break;
		case '8': //wall
			mv[i].set_values('8','n',8,4);
			break;
		case '9': //rake
			mv[i].set_values('9','n',8,5);
			break;
		case '!': //door
			mv[i].set_values('!','y',8,6);
			break;
		case '@': //broom
			mv[i].set_values('@','n',8,7);
			break;
		case '#': //right wall
			mv[i].set_values('#','n',8,8);
			break;
		case '$': //left of shingles
			mv[i].set_values('$','n',6,3);
			break;
		case '%': //shingles
			mv[i].set_values('%','n',6,4);
			break;
		case '^': //right of shingles
			mv[i].set_values('^','n',6,5);
			break;
		case 'P': //Turnip greens
			mv[i].set_values('p','y',5,5);
			break;
		}
	}
}