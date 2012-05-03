#ifndef LOZ_H_
#define LOZ_H_

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QApplication>
#include <ctime>
#include <sstream>
#include <string>
#include "link.h"
#include "block.h"
#include "torch.h"
#include "room.h"
#define dungeons 1
#define rooms 9
class LoZ : public QWidget {
	private:
		Q_OBJECT
		int timerID;
		LoZObject* link;
		int curdun, curroom;
		Room* room[dungeons][rooms];
		bool up, down, left, right;
		int prevx, prevy;
		int scale;
	public:
		LoZ(QWidget* parent = 0){
			timerID = startTimer(150);
			srand(NULL);
			scale = 10;
			curdun = 0;
			prevx = 210;
			prevy = 270;
			curroom = 0;
			link = new Link(210, 270);
			for (int i = 0; i < dungeons; i++)
				for (int j = 0; j < rooms; j++) {
					std::string r = "room/room";
					r += (char)(i+'1');
					r += (char)(j+'a');
					room[i][j] = new Room(r);
					}
			up = false;
			down = false;
			left = false;
			right = false;
		}
	protected:
		
		void checkSword() { //Manages if sword killed anything
			if (room[curdun][curroom]->getEns() == NULL)
				return;
			if (room[curdun][curroom]->getEns()->size() == 0)
				return;
			for (int i = 0; i < room[curdun][curroom]->getEns()->size(); i++) {
				if (((Link*)link)->getSword()->getWrecked().intersects(room[curdun][curroom]->getEns()->at(i)->getWrecked())) {
					room[curdun][curroom]->killEnemy(i);
					i--;
					if (room[curdun][curroom]->getEns() == NULL)
						return;
				}
			}
		}
		
		void paintEvent(QPaintEvent* event) { //Draws everything
			QPainter painter(this);
			//Draws status bar
			painter.translate(QPoint(0, 45));
			painter.setPen(QPen(QColor(247,207,135)));
			painter.setBrush(QBrush(QColor(247,207,135), Qt::SolidPattern));
			painter.drawRect(0, -45, 450, 45);
			//Draws current room
			room[curdun][curroom]->draw(painter);
			//Draws Link
			link->draw(painter);
			((Link*)link)->showStatus(painter);
		}
		
		void timerEvent(QTimerEvent* event) { //Allows time to pass
			link->tick();
			if (((Link*)link)->getShow('z')) {
				checkSword();
			}
			room[curdun][curroom]->moveEnemies(link);
			//All movement
			int oldx = link->getX();
			int oldy = link->getY();
			if (up)
				((Link*)link)->moveUp(scale);
			if (down)
				((Link*)link)->moveDown(scale);
			if (left)
				((Link*)link)->moveLeft(scale);
			if (right)
				((Link*)link)->moveRight(scale);
			//Checks collisions and whatnot
			int col = room[curdun][curroom]->checkCollision(link->getX(), link->getY(), ((Link*)link)->getDirection(), ((Link*)link)->hasKey());
			if (col == -1) { //If Link would walk into an obstacle, he goes back.
				link->setX(oldx);
				link->setY(oldy);
			}
			else if (col >= 100) { //If Link stepped into a warp, he warps
				link->setX(210);
				link->setY(270);
				curroom = col - 100;
				if (curroom == 0) { //Warping back to the first room means starting a new game, so everything is reset.
					for (int i = 0; i < dungeons; i++)
						for (int j = 0; j < rooms; j++) {
							room[i][j]->setVisited(false);
							room[i][j]->init();
						}
						if (((Link*)link)->hasKey())
							((Link*)link)->useKey();
						if (((Link*)link)->getMaxH() != 6)
							((Link*)link)->gain(-1);
						((Link*)link)->heal(999);
					
				}
				if (curroom == 9001) //Quit game warp
					exit(0);
				
			}
			else if (col >= 0) { //Door
				curroom = col;
				if (link->getX() == 0)
					link->setX(390);
				else if (link->getX() == 420)
					link->setX(30);
				else if (link->getY() == 0)
					link->setY(270);
				else if (link->getY() == 300)
					link->setY(30);
					
					room[curdun][curroom]->init();
				
				prevx = link->getX();
				prevy = link->getY();
			}
			else if (col == -10) { //Enemy
				link->setX(prevx);
				link->setY(prevy);
				((Link*)link)->damage(1);
				
				if (((Link*)link)->getCurH() <= 0) {
					link->setX(210);
					link->setY(270);
					curroom = 8;
					((Link*)link)->heal(999);
				}
			}
			else if (col == -8) { //Key
				((Link*)link)->getKey();
			}
			else if (col == -13) { //Piece of Heart
				((Link*)link)->gain(1);
			}
			repaint();
		}
		
		void keyPressEvent(QKeyEvent* event) { //Allows the game to be interactive
			/*switch (event->key()) {
				case Qt::Key_Left: ((Link*)link)->moveX(-1); break;
				case Qt::Key_Right: ((Link*)link)->moveX(1); break;
				case Qt::Key_Down: ((Link*)link)->moveY(1); break;
				case Qt::Key_Up: ((Link*)link)->moveY(-1); break;
				default: QWidget::keyPressEvent(event);
			}*/
			switch (event->key()) {
				case Qt::Key_Left: left = true; break;
				case Qt::Key_Right: right = true; break;
				case Qt::Key_Up: up = true; break;
				case Qt::Key_Down: down = true; break;
				case Qt::Key_Z: if (!event->isAutoRepeat()) {
									((Link*)link)->setShow('z', true);
								}
								break;
				default: QWidget::keyPressEvent(event);
			}
		}
		
		void keyReleaseEvent(QKeyEvent* event) { //This and the above function are to handle multiple inputs
			switch (event->key()) {
				case Qt::Key_Left: left = false; break;
				case Qt::Key_Right: right = false; break;
				case Qt::Key_Up: up = false; break;
				case Qt::Key_Down: down = false; break;
				case Qt::Key_Z: ((Link*)link)->setShow('z', false); break;
				default: QWidget::keyReleaseEvent(event);
			}
		}
};
#endif
