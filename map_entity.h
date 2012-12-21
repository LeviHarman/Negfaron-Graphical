//HOUSE - entities for house.
vector<vector<Entity>> init_map_house_entity(vector<vector<Entity>> &mve) {
	Entity rug;
	rug.set_warp("home");
	rug.set_hero_loc(16,9);
	mve[17][15] = rug;
	mve[17][16] = rug;

	return mve;
}

//HOME - entities for home.
vector<vector<Entity>> init_map_home_entity(vector<vector<Entity>> &mve) {
 	Entity sign;
	sign.entity_event("Hello, entity event is working.");
	mve[2][7] = sign; //2 down one over
		
	Entity door;
	door.set_warp("house");
	door.set_hero_loc(16,15);
	mve[15][9] = door;

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