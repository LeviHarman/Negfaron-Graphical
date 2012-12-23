Entity move_hero (Entity hero, ALLEGRO_BITMAP* tileset,vector<vector<Tile>> mv,int height,int width) {
	if(hero.move_animation==false) {
		if(hero.is_swing_hoe == true) {
			switch (hero.facing) {
			case 'u':
				if(hero.sta_frame<=9) {
					al_draw_bitmap_region(tileset, 0 * 16, 17 * 16, 16, 16, 15 * 16, 15 * 16, 0);
					al_draw_bitmap_region(tileset, 0 * 16, 16 * 16, 16, 16, 15 * 16, 14 * 16, 0);
				}
				else if(hero.sta_frame<=19) {
					al_draw_bitmap_region(tileset, 1 * 16, 17 * 16, 16, 16, 15 * 16, 15 * 16, 0);
					al_draw_bitmap_region(tileset, 1 * 16, 16 * 16, 16, 16, 15 * 16, 14 * 16, 0);
				}
				else if(hero.sta_frame<=29) {
					al_draw_bitmap_region(tileset, 2 * 16, 17 * 16, 16, 16, 15 * 16, 15 * 16, 0);
					al_draw_bitmap_region(tileset, 2 * 16, 16 * 16, 16, 16, 15 * 16, 14 * 16, 0);
				}
				else if (hero.sta_frame <= 30) {
					al_draw_bitmap_region(tileset, 2 * 16, 17 * 16, 16, 16, 15 * 16, 15 * 16, 0);
					al_draw_bitmap_region(tileset, 2 * 16, 16 * 16, 16, 16, 15 * 16, 14 * 16, 0);
					hero.is_swing_hoe = false;
				}
				break;
			case 'd' :
				if(hero.sta_frame<=9) {
					al_draw_bitmap_region(tileset, 0 * 16, 13 * 16, 16, 16, 15 * 16, 14 * 16, 0);
					al_draw_bitmap_region(tileset, 0 * 16, 14 * 16, 16, 16, 15 * 16, 15 * 16, 0);
				}
				else if(hero.sta_frame<=19) {
					al_draw_bitmap_region(tileset, 1 * 16, 13 * 16, 16, 16, 15 * 16, 14 * 16, 0);
					al_draw_bitmap_region(tileset, 1 * 16, 14 * 16, 16, 16, 15 * 16, 15 * 16, 0);
				}
				else if(hero.sta_frame<=29) {
					al_draw_bitmap_region(tileset, 2 * 16, 13 * 16, 16, 16, 15 * 16, 14 * 16, 0);
					al_draw_bitmap_region(tileset, 2 * 16, 14 * 16, 16, 16, 15 * 16, 15 * 16, 0);
					al_draw_bitmap_region(tileset, 2 * 16, 15 * 16, 16, 16, 15 * 16, 16 * 16, 0);
				}
				else if (hero.sta_frame <= 30) {
					al_draw_bitmap_region(tileset, 2 * 16, 13 * 16, 16, 16, 15 * 16, 14 * 16, 0);
					al_draw_bitmap_region(tileset, 2 * 16, 14 * 16, 16, 16, 15 * 16, 15 * 16, 0);
					al_draw_bitmap_region(tileset, 2 * 16, 15 * 16, 16, 16, 15 * 16, 16 * 16, 0);
					hero.is_swing_hoe = false;
				}
				break;
			case 'l':
				if(hero.sta_frame<=9) {
					al_draw_bitmap_region(tileset, 0 * 16, 18 * 16, 16, 16, 15 * 16, 14 * 16, 0);
					al_draw_bitmap_region(tileset, 0 * 16, 19 * 16, 16, 16, 15 * 16, 15 * 16, 0);
				}
				else if(hero.sta_frame<=19) {
					al_draw_bitmap_region(tileset, 1 * 16, 18 * 16, 16, 16, 14 * 16, 14 * 16, 0);
					al_draw_bitmap_region(tileset, 1 * 16, 19 * 16, 16, 16, 14 * 16, 15 * 16, 0);
					al_draw_bitmap_region(tileset, 2 * 16, 18 * 16, 16, 16, 15 * 16, 14 * 16, 0);
					al_draw_bitmap_region(tileset, 2 * 16, 19 * 16, 16, 16, 15 * 16, 15 * 16, 0);
				}
				else if(hero.sta_frame<=29) {
					al_draw_bitmap_region(tileset, 3 * 16, 19 * 16, 16, 16, 14 * 16, 15 * 16, 0);
					al_draw_bitmap_region(tileset, 4 * 16, 19 * 16, 16, 16, 15 * 16, 15 * 16, 0);
				}
				else if (hero.sta_frame <= 30) {
					al_draw_bitmap_region(tileset, 3 * 16, 19 * 16, 16, 16, 14 * 16, 15 * 16, 0);
					al_draw_bitmap_region(tileset, 4 * 16, 19 * 16, 16, 16, 15 * 16, 15 * 16, 0);
					hero.is_swing_hoe = false;
				}
				break;
			case 'r':
				if(hero.sta_frame<=9) {
					al_draw_bitmap_region(tileset, 0 * 16, 20 * 16, 16, 16, 15 * 16, 14 * 16, 0);
					al_draw_bitmap_region(tileset, 0 * 16, 21 * 16, 16, 16, 15 * 16, 15 * 16, 0);
				}
				else if(hero.sta_frame<=19) {
					al_draw_bitmap_region(tileset, 1 * 16, 20 * 16, 16, 16, 15 * 16, 14 * 16, 0);
					al_draw_bitmap_region(tileset, 1 * 16, 21 * 16, 16, 16, 15 * 16, 15 * 16, 0);
					al_draw_bitmap_region(tileset, 2 * 16, 20 * 16, 16, 16, 16 * 16, 14 * 16, 0);
					al_draw_bitmap_region(tileset, 2 * 16, 21 * 16, 16, 16, 16 * 16, 15 * 16, 0);
				}
				else if(hero.sta_frame<=29) {
					al_draw_bitmap_region(tileset, 3 * 16, 21 * 16, 16, 16, 15 * 16, 15 * 16, 0);
					al_draw_bitmap_region(tileset, 4 * 16, 21 * 16, 16, 16, 16 * 16, 15 * 16, 0);
				}
				else if (hero.sta_frame <= 30) {
					al_draw_bitmap_region(tileset, 3 * 16, 21 * 16, 16, 16, 15 * 16, 15 * 16, 0);
					al_draw_bitmap_region(tileset, 4 * 16, 21 * 16, 16, 16, 16 * 16, 15 * 16, 0);
					hero.is_swing_hoe = false;
				}
				break;
				break;
			}

			hero.sta_frame++;
		}
	}
	if(hero.is_swing_hoe == false) {
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
	}
	return hero;
}