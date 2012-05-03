#ifndef LOZOBJECT_H_
#define LOZOBJECT_H_
#include <QPainter>
#include <QRect>
#include <QImage>

class LoZObject { //The parent to most everything in this game
	protected:
		int x, y; //X and Y coordinates
		int t; //Internal clock for each object
		int id; //ID to be identified by
	public:
		LoZObject(int m, int n) { //Constructor
			x = m;
			y = n;
			t = 0;
			id = 0;
		}
		//Getters and Setters
		int getX() {return x;}
		int getY() {return y;}
		void setX(int m) {x = m;}
		void setY(int n) {y = n;}
		//Progress clock if the object needs it
		virtual void tick() {t++;}
		//Draws object
		virtual void draw(QPainter& g) = 0;
		//Gets ID
		int getID() {return id;}
		//Gets, in general, a Rectangle containing the object
		virtual QRect getWrecked() {
			return QRect(x, y, 30, 30);
		}
};
#endif
