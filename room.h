#ifndef ROOM_H_
#define ROOM_H_
#include <QPainter>
#include <QRect>
#include <QImage>
#include <string>
#include <fstream>
#include "wall.h"
#include "ground.h"
#include "block.h"
#include "torch.h"
#include "door.h"
#include "hole.h"
#include "enemy.h"
#include "switch.h"
#include "key.h"
#include "heart.h"
#include "warp.h"
#include "shot.h"
#include <vector>
#include <ctime>

class Room { //I've said before many times, but all the magic happens here.
	private:
		std::string name;
		std::ifstream in;
		//QImage image;
		std::string safe; //Squares you can walk on.
		//QRect rect;
		LoZObject* data[15][11]; //Every single object in the room. If it's not defined by external input file, it is Ground
		std::vector<LoZObject*> ens; //All the enemies
		bool visited; //Prevents some enemies from respawning
		LoZObject* shot; //The shot
	public:
		void setVisited(bool b) {
			visited = b;
		}
		
		void init() { //Reinitializes based on the input file
			ens.clear();
			in.open((name+".in").c_str());
			for (int i = 0; i < 15; i++)
				for (int j = 0; j < 11; j++)
					data[i][j] = new Ground(30 * i, 30 * j);
			int a, b;
			char c;
			int d, e, f;
			while (!in.eof()) { //Reads input file for what LoZObjects to place in the room.
				in >> a >> b >> c;
				if (c == 'W') {
					in >> d >> e >> f;
					for (int i = a; i <= e; i++)
						for (int j = b; j <= f; j++)
							data[i][j] = new Wall(30 * i, 30 * j, d);
				}
				else if (c == 'B') {
					data[a][b] = new Block(30 * a, 30 * b, false);
				}
				else if (c == '@') {
					data[a][b] = new Torch(30 * a, 30 * b);
				}
				else if (c == 'D') {
					in >> d >> e;
					data[a][b] = new Door(30 * a, 30 * b, d, e);
				}
				else if (c == 'M') {
					data[a][b] = new Block(30 * a, 30 * b, true);
				}
				else if (c == 'H') {
					//data[a][b] = new Hole (30 * a, 30 * b);
					in >> e >> f;
					for (int i = a; i <= e; i++)
						for (int j = b; j <= f; j++)
							data[i][j] = new Hole(30 * i, 30 * j);
				}
				else if (c == 'E') {
					in >> d;
					//data[a][b] = new Enemy (30 * a, 30 * b, d);
					if (!visited) {
						ens.push_back(new Enemy(30 * a, 30 * b, d));
						data[a][b] = ens[ens.size()-1];
					}
				}
				else if (c == 'S') {
					in >> d >> e;
					data[a][b] = new Switch(30 * a, 30 * b, d == 1, e);
				}
				else if (c == '<') {
					data[a][b] = new Heart(30 * a, 30 * b);
				}
				else if(c == '?') {
					in >> d;
					data[a][b] = new Warp(30 * a, 30 * b, d);
				}
			}
			in.close();
		}
		Room(std::string fname) {
			srand(time(NULL));
			ens.clear();
			safe = "GESDHK<?";
			name = fname;
			shot = new Shot(0, 0);
			//image.load((fname+".png").c_str());
			//rect = image.rect();
			
			init();
			visited = false;
		}
		
		void draw(QPainter& g) { //Draws everything
				for (int i = 0; i < 15; i++)
					for (int j = 0; j < 11; j++)
						if (data[i][j] != NULL)
							data[i][j]->draw(g);
				shot->draw(g);
				data[0][0]->draw(g);
				
				if (name == "room/room1i") { //If at the game over room...
					g.setPen(QPen(QColor(0,0,0)));
					g.setBrush(QBrush(QColor(0,0,0), Qt::SolidPattern));
					QFont f("Courier", 15);
					QFontMetrics fo(f);
					int tew = fo.width("End of the line");
					g.setFont(f);
					g.translate(QPoint(225, 60));
					g.drawText(-tew/2, 0, "End of the line");
					tew = fo.width("Play Again?");
					g.translate(QPoint(0, 30));
					g.drawText(-tew/2, 0, "Play Again?");
					tew = fo.width("Yes      No");
					g.translate(QPoint(0, 30));
					g.drawText(-tew/2, 0, "Yes      No");
					g.translate(QPoint(-225, -120));
				}
		}
		
		LoZObject* getMap(int i, int j) { //Unused function...
			return data[i][j];
		}
		
		bool conts(std::string s, char c) { //Because C++ doesn't have a string.contains(char) function naturally.
			for (int i = 0; i < s.size(); i++)
				if (s[i] == c)
					return true;
			return false;
		}

		void move (int m, int n, int dir) { //Moves a movable block if possible
			if (name == "room/room1g")
				if (data[10][3]->getID() == 'H')
					return;
			switch (dir) {
				case 2:	if (conts(safe, data[m][n+1]->getID())) {
							data[m][n] = new Ground(30 * m, 30 * n);
							if (data[m][n+1]->getID() != 'H')
								data[m][n+1] = new Block(30 * m, 30 * (n+1), false);
						}
						break;
				case 4:	if (conts(safe, data[m-1][n]->getID())) {
							data[m][n] = new Ground(30 * m, 30 * n);
							if (data[m-1][n]->getID() != 'H')
								data[m-1][n] = new Block(30 * (m-1), 30 * n, false);
						}
						break;
				case 6:	if (conts(safe, data[m+1][n]->getID())) {
							data[m][n] = new Ground(30 * m, 30 * n);
							if (data[m+1][n]->getID() != 'H')
								data[m+1][n] = new Block(30 * (m+1), 30 * n, false);
						}
						break;
				case 8:	if (conts(safe, data[m][n-1]->getID())) {
							data[m][n] = new Ground(30 * m, 30 * n);
							if (data[m][n-1]->getID() != 'H')
								data[m][n-1] = new Block(30 * m, 30 * (n-1), false);
						}
						break;
			}
		}
		
		void checkDoors() { //Check to see if closed doors can be opened
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 11; j++) {
					if (data[i][j]->getID() == 'X') {
						switch (((Door*)data[i][j])->getHash()) {
							case 1:	if (data[7][3]->getID() == 'B')
										((Door*)data[i][j])->setHash(0);
									break;
							case 3: if (ens.empty()) {
										((Door*)data[i][j])->setHash(0);
										visited = true;
									}
									break;
							case 4: //Covered by switch
									break;
							case 5: if (data[10][7]->getID() != 'M')
										((Door*)data[i][j])->setHash(0);
									break;
						}
					}
				}
			}
		}
		
		void checkSwitches(int m, int n) { //Checks if any switches are pressed and does stuff if they are
			if (m % 30 != 0 || n % 30 != 0)
				return;
			if (data[m / 30][n / 30]->getID() == 'S') {
				switch (((Switch*)data[m / 30][n / 30])->getHash()) {
					case 1: data[7][5] = new Key(210, 150);
							((Switch*)data[m / 30][n / 30])->press();
							break;
					case 2: ((Door*)data[7][0])->setHash(0);
							((Switch*)data[m/30][n/30])->press();
							break;
				}
			}
		}
		
		int checkCollision(int x, int y, int d, bool k) { //Checks collisions between Link and objects
			int m = x / 30;
			int n = y / 30;
			int num = -2;
			if (!conts(safe, data[m][n]->getID()))
				num = -1;
			if (x % 30 != 0)
				if (!conts(safe, data[m+1][n]->getID()))
					num = -1;
			if (y % 30 != 0)
				if (!conts(safe, data[m][n+1]->getID()))
					num = -1;
			if (x % 30 != 0 && y % 30 != 0)
				if (!conts(safe, data[m+1][n+1]->getID()))
					num = -1;
			
			//Check doors
			/*if (data[m][n]->getID() == 'D')
				num = ((Door*)data[m][n])->getNext();
			if (x % 30 != 0)
				if (data[m+1][n]->getID() == 'D')
					num = ((Door*)data[m+1][n])->getNext();
			if (y % 30 != 0)
				if (data[m][n+1]->getID() == 'D')
					num = ((Door*)data[m][n+1])->getNext();
			if (x % 30 != 0 && y % 30 != 0)
				if (data[m+1][n+1]->getID() == 'D')
					num = ((Door*)data[m+1][n+1])->getNext();*/
			if (x % 30 == 0 && y % 30 == 0)
				if (data[m][n]->getID() == 'D')
					num = ((Door*)data[m][n])->getNext();
					
			//Check Locks
			if (data[m][n]->getID() == '*' && k)
				((Door*)data[m][n])->setHash(0);
			if (x % 30 != 0)
				if (data[m+1][n]->getID() == '*' && k)
					((Door*)data[m+1][n])->setHash(0);
			if (y % 30 != 0)
				if (data[m][n+1]->getID() == '*' && k)
					((Door*)data[m][n+1])->setHash(0);
			if (x % 30 != 0 && y % 30 != 0)
				if (data[m+1][n+1]->getID() == '*' && k)
					((Door*)data[m+1][n+1])->setHash(0);
			
			//Check blocks
			if (data[m][n]->getID() == 'M')
				move(m, n, d);
			if (x % 30 != 0)
				if (data[m+1][n]->getID() == 'M')
					move(m+1, n, d);
			if (y % 30 != 0)
				if (data[m][n+1]->getID() == 'M')
					move(m, n+1, d);
			if (x % 30 != 0 && y % 30 != 0)
				if (data[m+1][n+1]->getID() == 'M')
					move(m+1, n+1, d);
					
			//Check holes
			if (data[m][n]->getID() == 'H')
				num = -10;
			if (x % 30 != 0)
				if (data[m+1][n]->getID() == 'H')
					num = -10;
			if (y % 30 != 0)
				if (data[m][n+1]->getID() == 'H')
					num = -10;
			if (x % 30 != 0 && y % 30 != 0)
				if (data[m+1][n+1]->getID() == 'H')
					num = -10;
					
			//Check Warps
			if (data[m][n]->getID() == '?')
				num = 100 + ((Warp*)data[m][n])->getNext();
			if (x % 30 != 0)
				if (data[m+1][n]->getID() == '?')
					num = 100 + ((Warp*)data[m+1][n])->getNext();
			if (y % 30 != 0)
				if (data[m][n+1]->getID() == '?')
					num = 100 + ((Warp*)data[m][n+1])->getNext();
			if (x % 30 != 0 && y % 30 != 0)
				if (data[m+1][n+1]->getID() == '?')
					num = 100 + ((Warp*)data[m+1][n+1])->getNext();
					
			//Check Heart Pieces
			if (data[m][n]->getID() == '<') {
				data[m][n] = new Ground(30 * m, 30 * n);
				num = -13;
			}
			if (x % 30 != 0)
				if (data[m+1][n]->getID() == '<') {
					data[m+1][n] = new Ground (30 * m + 30, 30 * n);
					num = -13;
				}
			if (y % 30 != 0)
				if (data[m][n+1]->getID() == '<') {
					data[m][n+1] = new Ground (30 * m, 30 * n + 30);
					num = -13;
				}
			if (x % 30 != 0 && y % 30 != 0)
				if (data[m+1][n+1]->getID() == '<') {
					data[m+1][n+1] = new Ground (30 * m + 30, 30 * n + 30);
					num = -13;
				}
			
			//Check keys
			if (data[m][n]->getID() == 'K') {
				data[m][n] = new Ground(30 * m, 30 * n);
				num = -8;
			}
			if (x % 30 != 0)
				if (data[m+1][n]->getID() == 'K') {
					data[m+1][n] = new Ground (30 * m + 30, 30 * n);
					num = -8;
				}
			if (y % 30 != 0)
				if (data[m][n+1]->getID() == 'K') {
					data[m][n+1] = new Ground (30 * m, 30 * n + 30);
					num = -8;
				}
			if (x % 30 != 0 && y % 30 != 0)
				if (data[m+1][n+1]->getID() == 'K') {
					data[m+1][n+1] = new Ground (30 * m + 30, 30 * n + 30);
					num = -8;
				}
					
			checkDoors();
			checkSwitches(x, y);
			return num;
		}
		
		void moveEnemies(LoZObject*& link) { //Enemy AI. Rather basic. Also, rather messy.
			int q = link->getX();
			int w = link->getY();
			shot->tick();
			if (QRect(q, w, 30, 30).intersects(QRect(shot->getX(), shot->getY(), 10, 10))) {
				((Shot*)shot)->repos(0, 0);
				((Shot*)shot)->stop();
				((Link*)link)->damage(1);
			}
			if (ens.empty())
				return;
			for (int i = 0; i < ens.size()-1; i++) {
				ens[i]->tick();
				int m = ens[i]->getX() / 30;
				int n = ens[i]->getY() / 30;
				if (((Enemy*)ens[i])->canMove()) {
					if (((Enemy*)ens[i])->getType() == 1) {
						switch (rand() % 4) {
							case 1:	if (data[m+1][n]->getID() == 'G') {
										data[m+1][n] = ens[i];
										data[m][n] = new Ground(30 * m, 30 * n);
										((Enemy*)ens[i])->moved(m+1, n);
									}
									else if (data[m+1][n]->getID() == 'H')
										ens.erase(ens.begin()+i--);
									break;
							case 2:	if (data[m][n+1]->getID() == 'G') {
										data[m][n+1] = ens[i];
										data[m][n] = new Ground(30 * m, 30 * n);
										((Enemy*)ens[i])->moved(m, n+1);
									}
									else if (data[m][n+1]->getID() == 'H')
										ens.erase(ens.begin()+i--);
									break;
							case 3:	if (data[m][n-1]->getID() == 'G') {
										data[m][n-1] = ens[i];
										data[m][n] = new Ground(30 * m, 30 * n);
										((Enemy*)ens[i])->moved(m, n-1);
									}
									else if (data[m][n-1]->getID() == 'H')
										ens.erase(ens.begin()+i--);
									break;
							case 0:	if (data[m-1][n]->getID() == 'G') {
										data[m-1][n] = ens[i];
										data[m][n] = new Ground(30 * m, 30 * n);
										((Enemy*)ens[i])->moved(m-1, n);
									}
									else if (data[m-1][n]->getID() == 'H')
										ens.erase(ens.begin()+i--);
									break;
						}
					}
					else if (((Enemy*)ens[i])->getType() == 2) {
						int up = -1, right = -1;
						if (ens[i]->getX() < q)
							right = 1;
						else if (ens[i]->getX() > q)
							right = 0;
						if (ens[i]->getY() < w)
							up = 2;
						else if (ens[i]->getY() > w)
							up = 3;
						int dir = 0;
						if (up == -1)
							dir = right;
						else if (right == -1)
							dir = up;
						else {
							if (rand() % 2 == 1)
								dir = up;
							else
								dir = right;
						}
						
						switch (dir) {
							case 1:	if (data[m+1][n]->getID() == 'G') {
										data[m+1][n] = ens[i];
										data[m][n] = new Ground(30 * m, 30 * n);
										((Enemy*)ens[i])->moved(m+1, n);
									}
									else if (data[m+1][n]->getID() == 'H')
										ens.erase(ens.begin()+i--);
									break;
							case 2:	if (data[m][n+1]->getID() == 'G') {
										data[m][n+1] = ens[i];
										data[m][n] = new Ground(30 * m, 30 * n);
										((Enemy*)ens[i])->moved(m, n+1);
									}
									else if (data[m][n+1]->getID() == 'H')
										ens.erase(ens.begin()+i--);
									break;
							case 3:	if (data[m][n-1]->getID() == 'G') {
										data[m][n-1] = ens[i];
										data[m][n] = new Ground(30 * m, 30 * n);
										((Enemy*)ens[i])->moved(m, n-1);
									}
									else if (data[m][n-1]->getID() == 'H')
										ens.erase(ens.begin()+i--);
									break;
							case 0:	if (data[m-1][n]->getID() == 'G') {
										data[m-1][n] = ens[i];
										data[m][n] = new Ground(30 * m, 30 * n);
										((Enemy*)ens[i])->moved(m-1, n);
									}
									else if (data[m-1][n]->getID() == 'H')
										ens.erase(ens.begin()+i--);
									break;
							default: ((Enemy*)ens[i])->moved(m, n);
						}	
					}
					else if (((Enemy*)ens[i])->getType() == 3) {
						((Shot*)shot)->repos(m * 30 + 15, n * 30 + 15);
						((Shot*)shot)->target(q, w);
						((Enemy*)ens[i])->moved(m, n);
					}
				}
			}
		}
		
		std::vector<LoZObject*>* getEns() {
			if (ens.empty())
				return NULL;
			return &ens;
		}
		void killEnemy(int i) {
			if (ens.empty())
				return;
			int m = ens[i]->getX() / 30;
			int n = ens[i]->getY() / 30;
			ens.erase(ens.begin() + i);
			data[m][n] = new Ground (30 * m, 30 * n);
		}
};
#endif
