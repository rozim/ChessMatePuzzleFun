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
      count += perft(root, pos, depth - 1);
      pos.unmake_move();
    }
    return count;
  } else {
    return 1;
  }
}

// Somewhat hard to follow formulation based on Stockfish.
/*
std::uint64_t perft(bool root, Position& pos, int depth) {
  if (depth <= 0) {
    return 0;
  }
  uint64_t nodes = 0;
  const MoveList ml = pos.legal_move_list();
  const bool leaf = (depth == 2);

  for (int i = 0; i < ml.size(); i++) {
    if (root && depth <= 1) {
      nodes++;
    } {
      pos.make_move(ml.values()[i]);
      if (leaf) {
	nodes += pos.legal_move_list().size();
      } else {
	nodes += perft(false, pos, depth - 1);
      }
      pos.unmake_move();
    }
  }

  return nodes;
}
*/

int main(int argc, char* argv[]) {
  Position pos(STARTPOS_FEN);
  for (int d = 1; d < 8; d++) {
    auto t1 = time(0L);
    auto res = perft(true, pos, d);
    auto dt = time(0L) - t1;
    std::cout << "d: " << d << " " <<  res << " " << dt << "s" << std::endl;
  }

}
