#include "PlayableBoardUnit.h"

bool PlayableBoardUnit::isAttackable() {
	return true;
}

PlayableBoardUnit::Stats PlayableBoardUnit::getStats() {
	return _stats;
}

PlayableBoardUnit::PlayableBoardUnit(PlayableBoardUnit& Base) : _stats(Base._stats) {

}
