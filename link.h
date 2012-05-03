#ifndef LINK_H_
#define LINK_H_
#include "lozobj.h"
#include "sword.h"
#include "key.h"
#include <string>

class Link : public LoZObject{ //Link.
	private:
		LoZObject* sword;
		int direction;
		bool show[26]; //With more items, this becomes useful for determining what gets shown
		//Health
		int maxhealth, health;
		//Managing status bar
		QImage image[2][3];
		QRect rect[2][3];
		int keys;
		QImage keyi;
		QRect keyr;
	public:
		Link(int x, int y) : LoZObject(x, y) {
			t = 50;
			keys = 0;
			sword = new Sword(x, y);
			keyi.load("data/key2.png");
			keyr = keyi.rect();
			direction = 6;
			for (int i = 0; i < 26; i++)
				show[i] = false;
			id = 'L';
			maxhealth = 6;
			health = 6;
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 3; j++) {
					std::string r = "data/heart";
					r += (char)(i+'0');
					r += (char)(j+'0');
					image[i][j].load(r.c_str());
					rect[i][j] = image[i][j].rect();
				}
			}
		}
		void draw(QPainter& g) {
			if (t > 16 || t % 4 == 2 || t % 4 == 3) {
				g.setPen(QPen(QColor(0,255,0)));
				g.setBrush(QBrush(QColor(0,255,0), Qt::SolidPattern));
				g.drawRect(x, y, 29, 29);
			}
			else {
				g.setPen(QPen(QColor(255, 0, 0)));
				g.setBrush(QBrush(QColor(255, 0, 0), Qt::SolidPattern));
				g.drawRect(x, y, 29, 29);
			}
			
			if (show['z'-'a'])
				drawSword(g);
			
		}
		//Managing visibility of items
		void setShow(int index, bool b) {
			show[index-'a'] = b;
		}
		
		bool getShow(int index) {
			return show[index-'a'];
		}
		
		void drawSword(QPainter & g) {
			((Sword*)sword)->reposition(x, y, direction);
			sword->draw(g);
			show['z'-'a'] = false;
		}
		//Movement
		void moveRight(int m) {
			x += m;
			direction = 6;
		}
		void moveLeft(int m) {
			x -= m;
			direction = 4;
		}
		void moveUp(int n) {
			y -= n;
			direction = 8;
		}
		void moveDown(int n) {
			y += n;
			direction = 2;
		}
		//Getters, etc.
		int getDirection() {
			return direction;
		}
		//Managing health
		int getMaxH() {
			return maxhealth;
		}
		
		int getCurH() {
			return health;
		}
		
		void damage(int d) {
			if (t > 16) {
				health -= d;
				if (health <= 0)
					health = 0;
				t = 0;
			}
		}
		
		void heal(int h) {
			health += h;
			if (health >= maxhealth)
				health = maxhealth;
		}
		
		void gain(int h) {
			maxhealth += h;
			heal(maxhealth);
		}
		//Status window
		void showStatus(QPainter& g) {
			for (int i = 0; i < health; i++) {
				if (i < 14) {
					if (i % 2 == 0) {
						rect[1][1].moveTo(300 + (i/2)*20, -40);
						g.drawImage(rect[1][1], image[1][1]);
					}
					else {
						rect[1][2].moveTo(308 + (i/2)*20, -40);
						g.drawImage(rect[1][2], image[1][2]);
					}
				}
				else {
					if (i % 2 == 0) {
						rect[1][1].moveTo(300 + ((i-14)/2)*20, -20);
						g.drawImage(rect[1][1], image[1][1]);
					}
					else {
						rect[1][2].moveTo(308 + ((i-14)/2)*20, -20);
						g.drawImage(rect[1][2], image[1][2]);
					}
				}
			}
			
			for (int i = health; i < maxhealth; i++) {
				if (i < 14) {
					if (i % 2 == 0) {
						rect[0][1].moveTo(300 + (i/2)*20, -40);
						g.drawImage(rect[0][1], image[0][1]);
					}
					else {
						rect[0][2].moveTo(308 + (i/2)*20, -40);
						g.drawImage(rect[0][2], image[0][2]);
					}
				}
				else {
					if (i % 2 == 0) {
						rect[0][1].moveTo(300 + ((i-14)/2)*20, -20);
						g.drawImage(rect[0][1], image[0][1]);
					}
					else {
						rect[0][2].moveTo(308 + ((i-14)/2)*20, -20);
						g.drawImage(rect[0][2], image[0][2]);
					}
				}
			}
			
			
			if (keys > 0) {
				keyr.moveTo(250, -37);
				g.drawImage(keyr, keyi);
			}
		}
		
		LoZObject* getSword() {
			return sword;
		}
		
		void getKey() {
			keys++;
		}
		
		void useKey() {
			keys--;
		}
		
		bool hasKey() {
			return keys != 0;
		}
};
#endif
