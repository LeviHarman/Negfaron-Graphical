Entity move_hero (Entity hero, ALLEGRO_BITMAP* tileset,vector<vector<Tile>> mv,int height,int width) {
	switch (hero.facing) {
	case 'u':
		if(hero.move_animation==true) {
			for(int col=0;col<height;col++) {
				for(int row=0;row<width;row++) {
					al_draw_bitmap_region(tileset, mv[col][row].sx * 16, mv[col][row].sy * 16, 16, 16, (row*16 - hero.wloc*16)+15*16, (col*16 - hero.hloc*16)+15*16+hero.frame, 0);
				}
			}	
			if (hero.frame<= 7) {
				al_draw_bitmap_region(tileset, 1 * 16, 3 * 16, 16, 16, 15*16, 15*16, 0);
			}
			else if (hero.frame < 15) {
				al_draw_bitmap_region(tileset, 2 * 16, 3 * 16, 16, 16, 15*16, 15*16, 0);
			}
			else if(hero.frame == 15) {
				al_draw_bitmap_region(tileset, 2 * 16, 3 * 16, 16, 16, 15*16, 15*16, 0);
				hero.move_animation = false;
				hero.hloc-=1;
			}
			hero.frame++;


		}
		else {
			al_draw_bitmap_region(tileset, 0 * 16, 3 * 16, 16, 16, 15*16, 15*16, 0);
		}
		break;
	case 'd':
		if(hero.move_animation==true) {
			for(int col=0;col<height;col++) {
				for(int row=0;row<width;row++) {
					al_draw_bitmap_region(tileset, mv[col][row].sx * 16, mv[col][row].sy * 16, 16, 16, (row*16 - hero.wloc*16)+15*16, (col*16 - hero.hloc*16)+15*16-hero.frame, 0);
				}
			}	
			if(hero.frame <=7) {
				al_draw_bitmap_region(tileset, 1 * 16, 2 * 16, 16, 16, 15*16, 15*16, 0);
			}
			else if(hero.frame <= 14) {
				al_draw_bitmap_region(tileset, 2 * 16, 2 * 16, 16, 16, 15*16, 15*16, 0);
			}
			else if(hero.frame==15) {
				al_draw_bitmap_region(tileset, 2 * 16, 2 * 16, 16, 16, 15*16, 15*16, 0);
				hero.move_animation = false;
				hero.hloc+=1;
			}
			hero.frame++;
		}
		else {
			al_draw_bitmap_region(tileset, 0 * 16, 2 * 16, 16, 16, 15*16, 15*16, 0);
		}
		break;
	case 'l':
		if(hero.move_animation==true) {
			for(int col=0;col<height;col++) {
				for(int row=0;row<width;row++) {
					al_draw_bitmap_region(tileset, mv[col][row].sx * 16, mv[col][row].sy * 16, 16, 16, (row*16 - hero.wloc*16)+15*16+hero.frame, (col*16 - hero.hloc*16)+15*16, 0);
				}
			}	

			if(hero.frame<=7) {
				al_draw_bitmap_region(tileset, 1 * 16, 4 * 16, 16, 16, 15*16, 15*16, 0);
			}
			else if(hero.frame<=14) {
				al_draw_bitmap_region(tileset, 2 * 16, 4 * 16, 16, 16, 15*16, 15*16, 0);
			}
			else if(hero.frame==15) {
				al_draw_bitmap_region(tileset, 2 * 16, 4 * 16, 16, 16, 15*16, 15*16, 0);
				hero.move_animation = false;
				hero.wloc-=1;
			}
			hero.frame++;
		}
		else {
			al_draw_bitmap_region(tileset, 0 * 16, 4 * 16, 16, 16, 15*16, 15*16, 0);
		}
		break;
	case 'r':
		if(hero.move_animation==true) {
			for(int col=0;col<height;col++) {
				for(int row=0;row<width;row++) {
					al_draw_bitmap_region(tileset, mv[col][row].sx * 16, mv[col][row].sy * 16, 16, 16, (row*16 - hero.wloc*16)+15*16-hero.frame, (col*16 - hero.hloc*16)+15*16, 0);
				}
			}	
			if(hero.frame<=7) {
				al_draw_bitmap_region(tileset, 1 * 16, 5 * 16, 16, 16, 15 * 16, 15 * 16, 0);
			}
			else if(hero.frame<=14) {
				al_draw_bitmap_region(tileset, 2 * 16, 5 * 16, 16, 16, 15*16, 15*16, 0);
			}
			else if(hero.frame==15) {
				al_draw_bitmap_region(tileset, 2 * 16, 5 * 16, 16, 16, 15*16, 15*16, 0);
				hero.move_animation = false;
				hero.wloc+=1;
			}
			hero.frame++;
		}
		else {
			al_draw_bitmap_region(tileset, 0 * 16, 5 * 16, 16, 16, 15*16, 15*16, 0);
		}
		break;
	}	
	return hero;
}