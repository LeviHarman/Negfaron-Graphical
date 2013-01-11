//Draws map and you can modify pixel by pixel with radj and cadj. (Row adjustment and Column adjustment). Set them to zero if you desire no modification.

void draw_map (ALLEGRO_BITMAP* tileset, vector<int> wid_height, vector<Tile> mv, Entity *hero, int radj, int cadj) 
{
	for(int col=0;col<wid_height[0];col++) {
		for(int row=0;row<wid_height[1];row++) {
			al_draw_bitmap_region(

				tileset, 
				mv[(col*30)+row].sx * 16, mv[(col*30)+row].sy * 16,
				16,
				16,
				(row*16 - hero->wloc*16)+((wid_height[1]/2)*16) + radj,
				(col*16 - hero->hloc*16)+((wid_height[0]/2)*16) + cadj,
				0); 

		}
	}	
}