#ifndef BLOCK_H_
#define BLOCK_H_
#include "lozobj.h"

class Block : public LoZObject { //This is a Block. It can be movable or not.
	private:
		QImage image; 
		QRect rect;
		bool movable;
	public:
		Block(int x, int y, bool b) : LoZObject(x, y) { //Constructor
			image.load("data/block.png");
			rect = image.rect();
			movable = b;
			if (movable)
				id = 'M';
			else
				id = 'B';
		}
		
		void move(int dir) { //Moves a block, if it is movable, in the given direction
			if (!movable)
				return;
			switch (dir) { //My way of numbering directions may seem kinda funny, so I'll explain right now. Look at a number pad. Look at where 2, 4, 6, and 8 are positioned. Guess which one is up?
				case 2: y += 30; break;
				case 4: x -= 30; break;
				case 6: x += 30;break;
				case 8: y -= 30; break;
			}
			
			movable = false;
			id = 'B';
		}
		
		void draw(QPainter& g) {
			/*rect.moveTo(x, y); I'll use this as soon as I'm allowed more processing power and Qt gets better
			g.drawImage(rect, image);*/
			
			//Draws a brown square
			g.setPen(QPen(QColor(152,32,0)));
			g.setBrush(QBrush(QColor(152,32,0), Qt::SolidPattern));
			g.drawRect(x, y, 29, 29);
		}
		
};
#endif
