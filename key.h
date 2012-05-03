#ifndef KEY_H_
#define KEY_H_
#include "lozobj.h"

class Key : public LoZObject { //A Master Key to unlock all doors in a dungeon.
	private:
		QImage image;
		QRect rect;
	public:
		Key(int x, int y) : LoZObject(x, y) {
			image.load("data/key.png");
			rect = image.rect();
			id = 'K';
		}
		
		void draw(QPainter& g) {
			rect.moveTo(x, y);
			g.drawImage(rect, image);
		}
		
};
#endif
