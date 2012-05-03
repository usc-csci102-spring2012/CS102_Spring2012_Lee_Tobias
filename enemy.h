#ifndef ENEMY_H_
#define ENEMY_H_
#include "lozobj.h"
#include <ctime>

class Enemy: public LoZObject { //An enemy. Or, more accurately, three of them.
	private:
		int type; //Decides the type of enemy to appear: 1 moves randomly, 2 moves towards you, and 3 shoots at you stationarily
		int target; //To determine when to move again, so they don't appear spazzy when moving
	public:
		Enemy(int x, int y, int ty) : LoZObject(x, y) {
			type = ty;
			//id = t + '0';
			id = 'H';
			srand(time(NULL));
			target = rand() % 10 + 5;
			if (type == 3)
				target = 15;
		}
		
		void draw(QPainter& g) {
			g.setPen(QPen(QColor(144,104,40)));
			g.setBrush(QBrush(QColor(144,104,40), Qt::SolidPattern));
			g.drawRect(x, y, 29, 29);
			
			if (type == 1) {
				g.setPen(QPen(QColor(74,74,74)));
				g.setBrush(QBrush(QColor(74,74,74), Qt::SolidPattern));
				g.drawEllipse(x, y, 29, 29);
			}
			else if (type == 2) {
				g.setPen(QPen(QColor(124,86,80)));
				g.setBrush(QBrush(QColor(124,86,80), Qt::SolidPattern));
				g.drawEllipse(x+5, y+5, 19, 19);
			}
			else if (type == 3) {
				g.setPen(QPen(QColor(116,114,150)));
				g.setBrush(QBrush(QColor(116,114,150), Qt::SolidPattern));
				g.drawRect(x, y, 29, 29);
			}
		}
		
		void moved(int m, int n) { //To actually move the enemy
			t = 0;
			target = rand() % 10 + 5;
			x = m * 30;
			y = n * 30;
			if (type == 3)
				target = 30;
		}
		//Getters and setters
		int getTarget() {
			return target;
		}
		
		int getTick() {
			return t;
		}
		
		void tick() {
			t++;
		}
		
		int getType() {
			return type;
		}
		
		bool canMove() {
			return t >= target;
		}
		
};
#endif
