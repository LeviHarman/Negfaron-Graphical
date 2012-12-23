//ENTITY MESAGE - Draw Dialogue Box
void entity_message (ALLEGRO_BITMAP* tileset) {
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

}