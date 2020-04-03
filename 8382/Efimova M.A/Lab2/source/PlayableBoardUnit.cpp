#include "PlayableBoardUnit.h"

PlayableBoardUnit::PlayableBoardUnit() {

}

PlayableBoardUnit::Stats PlayableBoardUnit::getStats() {
	return _stats;
}

PlayableBoardUnit::PlayableBoardUnit(PlayableBoardUnit& Base) : _stats(Base._stats) {

}
