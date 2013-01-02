vector<Tile> make_map(vector<int> wid_height, string map) {

	vector<Tile> mv(wid_height[0]*wid_height[1]);

	for(int i=0;i<mv.size();i++) {
		switch(map[i]) {
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
	return mv;
}