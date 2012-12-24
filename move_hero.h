/*draws 3 frame animations.
variables
tileset, tile width, Entity being animated,  1-3
column for first, second, and third frames. 4-6
row for first,second, and third frames. 7-9
animation height in tiles, animation width in tiles. 10,11
radj, and cadj are for adjusting the center of animation. makes function tweakable.
*/

Entity three_frame_animation(ALLEGRO_BITMAP* tileset, int tw, Entity hero,int ci1,int ci2, int ci3, int ri1, int ri2, int ri3,int aheight,int awidth,int radj, int cadj) {
	if(hero.sta_frame<=9) {
		al_draw_bitmap_region(tileset, (ri1)*tw, (ci1)*tw, tw*awidth, tw*aheight, (16+radj)*tw, (16+cadj)*tw, 0);
	}
	else if(hero.sta_frame<=19) {
		al_draw_bitmap_region(tileset, (ri2)*tw, (ci2)*tw, tw*awidth, tw*aheight, (16+radj)*tw, (16+cadj)*tw, 0);
	}
	else if(hero.sta_frame<=29) {
		al_draw_bitmap_region(tileset, (ri3)*tw, (ci3)*tw, tw*awidth, tw*aheight, (16+radj)*tw, (16+cadj)*tw, 0);
	}
	else if (hero.sta_frame <= 30) {
		al_draw_bitmap_region(tileset, (ri3)*tw, (ci3)*tw, tw*awidth, tw*aheight, (16+radj)*tw, (16+cadj)*tw, 0);
		hero.is_swing_hoe = false;
	}
	return hero;
}

/*
Draws the walking animation

Variable description

Entity being animated, tileset,map vector 1-3
tile width, animation height in tiles, and animation width in tiles
height, and width of map in tiles.
ci1,ci2,ci3 column of the three animations
ri1,ri2,ri3 row of the three animations

*/

Entity walk_animation (Entity hero, ALLEGRO_BITMAP* tileset, vector<vector<Tile>> mv, int tw, int aheight, int awidth, int height, int width, int ci1,int ci2,int ci3,int ri1, int ri2, int ri3) {
	if(hero.move_animation==true) {
		int frameintv=0;
		int frameinth=0;
		int hl=0;
		int vl=0;
		switch (hero.facing) {
		case 'u':
			vl = -1;
			frameintv = hero.frame;
			break;
		case 'd' :
			vl=1;
			frameintv = hero.frame *-1;
			break;
		case 'l' :
			hl=-1;
			frameinth = hero.frame;
			break;
		case 'r':
			hl=1;
			frameinth = hero.frame *-1;
			break;
		}

		for(int col=0;col<height;col++) {
			for(int row=0;row<width;row++) {
				al_draw_bitmap_region(tileset, mv[col][row].sx * tw, mv[col][row].sy * tw, tw, tw, (row*tw - hero.wloc*tw)+15*tw+frameinth, (col*tw - hero.hloc*tw)+15*tw+frameintv, 0);
			}
		}	

		if (hero.frame<= 7) {
			al_draw_bitmap_region(tileset, ri2*tw, ci2*tw, tw, tw, 15*tw, 15*tw, 0);
		}
		else if (hero.frame < 15) {
			al_draw_bitmap_region(tileset, ri3*tw, ci3*tw, tw, tw, 15*tw, 15*tw, 0);
		}
		else if(hero.frame == 15) {
			al_draw_bitmap_region(tileset, ri3*tw, ci3*tw, tw, tw, 15*tw, 15*tw, 0);
			hero.move_animation = false;
			hero.hloc+=vl;
			hero.wloc+=hl;
		}
		hero.frame++;
	}
	else {
		al_draw_bitmap_region(tileset, ri1 * tw, ci1 * tw, tw, tw, 15*tw, 15*tw, 0);
	}

	return hero;
}

Entity move_hero (Entity hero, ALLEGRO_BITMAP* tileset,vector<vector<Tile>> mv,int height,int width) {
	int tw = 16;

	if(hero.move_animation==false) {
		if(hero.is_swing_hoe == true) {
			switch (hero.facing) {
			case 'u':
				hero = three_frame_animation(tileset,tw,hero,16,16,16,0,1,2,2,1,-1,-2);
				break;
			case 'd' :
				hero = three_frame_animation(tileset,tw,hero,13,13,13,0,1,2,3,1,-1,-2);
				break;
			case 'l':
				hero = three_frame_animation(tileset,tw,hero,18,18,18,0,2,4,2,2,-2,-2);
				break;
			case 'r':
				hero = three_frame_animation(tileset,tw,hero,20,20,20,0,2,4,2,2,-1,-2);
				break;
			}

			hero.sta_frame++;
		}
	}
	if(hero.is_swing_hoe == false) {
		switch (hero.facing) {
		case 'u':
			hero = walk_animation(hero,tileset,mv,tw,1,1,height,width,3,3,3,0,1,2);
			break;
		case 'd':
			hero = walk_animation(hero,tileset,mv,tw,1,1,height,width,2,2,2,0,1,2);
			break;
		case 'l':
			hero = walk_animation(hero,tileset,mv,tw,1,1,height,width,4,4,4,0,1,2);
			break;
		case 'r':
			hero = walk_animation(hero,tileset,mv,tw,1,1,height,width,5,5,5,0,1,2);
			break;
		}
	}
	return hero;
}