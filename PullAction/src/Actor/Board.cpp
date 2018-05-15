#include "Board.h"

Board::Board(std::string name, Object::Status status):
	Object(name,status)
{}

void Board::init() {
	for (int i = 0; i < 6 * 3; ++i) {
		insertAsChild(new Card("Card" + to_string(i)));
	}
	insertAsChild(new Cursor("Cursor"));
}
void Board::update() {
	if (game->kb.Down(SPACE)) {
		postMsg(game->root->getObjectFromChildren("Logo"),"BackToTitle");
		pauseAll();
	}
}
void Board::updatePause() {}
void Board::render() {}
void Board::renderPause() {}

int Board::receiveMsg(std::weak_ptr<Object> receiver, const std::string& msg) {
	runAll();
	return 0;
}
