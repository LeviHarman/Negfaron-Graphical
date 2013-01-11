//ENTITY MESAGE - Draw Dialogue Box
void entity_message (ALLEGRO_BITMAP* tileset, Creature * hero, ALLEGRO_FONT* font,vector<Entity> mve ,vector<int> wid_height) {
	al_draw_bitmap_region(tileset, 0*16,6*16,16,16,16*1,16*25,0);
	al_draw_bitmap_region(tileset, 2*16,6*16,16,16,16*28,16*25,0);

	al_draw_bitmap_region(tileset, 0*16,7*16,16,16,16*1,16*26,0);
	al_draw_bitmap_region(tileset, 2*16,7*16,16,16,16*28,16*26,0);

	al_draw_bitmap_region(tileset, 0*16,7*16,16,16,16*1,16*27,0);
	al_draw_bitmap_region(tileset, 2*16,7*16,16,16,16*28,16*27,0);

	al_draw_bitmap_region(tileset, 0*16,8*16,16,16,16*1,16*28,0);
	al_draw_bitmap_region(tileset, 2*16,8*16,16,16,16*28,16*28,0);

	for (int i=0;i<26;i++) {
		al_draw_bitmap_region(tileset, 1*16,6*16,16,16,16*(i+2),16*25,0);
	}

	for (int i=0;i<26;i++) {
		al_draw_bitmap_region(tileset, 1*16,7*16,16,16,16*(i+2),16*26,0);
	}

	for (int i=0;i<26;i++) {
		al_draw_bitmap_region(tileset, 1*16,7*16,16,16,16*(i+2),16*27,0);
	}

	for (int i=0;i<26;i++) {
		al_draw_bitmap_region(tileset, 1*16,8*16,16,16,16*(i+2),16*28,0);
	}

	switch (hero->facing) 
	{
	case 'u':
		al_draw_textf(font,al_map_rgb(0,0,0),32,410,0,mve[( (hero->hloc-1)*30)+hero->wloc].dialogue.c_str());
		break;
	case 'd':
		al_draw_textf(font,al_map_rgb(0,0,0),32,416,0,mve[( (hero->hloc+1)*30)+hero->wloc].dialogue.c_str());
		break;
	case'l':
		al_draw_textf(font,al_map_rgb(0,0,0),32,416,0,mve[(hero->hloc*30)+hero->wloc-1].dialogue.c_str());
		break;
	case 'r':
		al_draw_textf(font,al_map_rgb(0,0,0),32,416,0,mve[(hero->hloc*30)+hero->wloc+1].dialogue.c_str());
		break;
	}
}

//mv[( (hero.hloc+1)*30)+hero.wloc] {