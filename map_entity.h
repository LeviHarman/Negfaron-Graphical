//HOUSE - entities for house.
vector<vector<Entity>> init_map_house_entity(vector<vector<Entity>> &mve) {
	Entity rug;
	rug.set_warp("home");
	rug.set_hero_loc(5,9);
	mve[17][15] = rug;
	mve[17][16] = rug;

	Entity spider;
	spider.entity_event("I am the holy log. You will do my bidding.");
	mve[15][13] = spider;

	return mve;
}

//HOME - entities for home.
vector<vector<Entity>> init_map_home_entity(vector<vector<Entity>> &mve) {
 	Entity sign;
	sign.entity_event("Levis House.");
	mve[22][5] = sign;
		
	Entity door;
	door.set_warp("house");
	door.set_hero_loc(16,15);
	mve[4][9] = door;

	return mve;
}

//RESET MVE
vector<vector<Entity>> init_map_entity_cleanup(vector<vector<Entity>> &mve) {
	for (int i=0;i<30;i++){
		for (int j = 0;j<30;j++) {
		mve[i][j].cleanup();
		}
	}
	return mve;
}