

#include <time.h>
#include <iostream>
#include "libchess/Position.h"
#include "libchess/Color.h"
#include "libchess/Move.h"

using namespace libchess;
using namespace constants;

std::uint64_t perft(bool root, Position& pos, int depth) {
  if (depth == 1) {
    return pos.legal_move_list().size();
  } else if (depth > 1) {
    std::uint64_t count = 0;
    const MoveList ml = pos.legal_move_list();
    for (int i = 0; i < ml.size(); i++) {
      pos.make_move(ml.values()[i]);
      if (depth == 2) {
	count += pos.legal_move_list().size();
      } else {
	count += perft(root, pos, depth - 1);
      }
      pos.unmake_move();
    }
    return count;
  } else {
    return 1;
  }
}

int main(int argc, char* argv[]) {
  Position pos(STARTPOS_FEN);
  for (int d = 1; d < 8; d++) {
    auto t1 = time(0L);
    auto res = perft(true, pos, d);
    auto dt = time(0L) - t1;
    std::cout << "d: " << d << " " <<  res << " " << dt << "s" << std::endl;
  }

}
