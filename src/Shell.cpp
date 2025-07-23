#include "Shell.h"

void Shell::MoveShell() {
	pos.move(dir);
}

bool Shell::isShellCollidingWithShell(Shell sh) {
	return IsObjectsCollide(sh);
}
