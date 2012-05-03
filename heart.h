#ifndef HEART_H_
#define HEART_H_
#include "lozobj.h"

class Heart : public LoZObject { //Heart Containers increase Link's maximum health and heal him
	private:
		QImage image;
		QRect rect;
	public:
		Heart(int x, int y) : LoZObject(x, y) {
			image.load("data/heart.png");
			rect = image.rect();
			id = '<';
		}
		
		void draw(QPainter& g) {
			rect.moveTo(x, y);
			g.drawImage(rect, image);
		}
		
		
};
#endif
