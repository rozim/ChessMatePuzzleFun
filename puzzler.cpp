#include <assert.h>
#include <time.h>

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "libchess/Position.h"
#include "libchess/Color.h"
#include "libchess/Move.h"

using namespace libchess;

const int HASHES = 16384;
std::vector<std::uint64_t> g_hashes(HASHES);
std::uint64_t nodes;
std::uint64_t repeats;

bool search_any_moves_mate(Position& pos, int ply, int remain);
bool search_all_moves_mate(Position& pos, int ply, int remain);


void show_hashes(Position& pos, int ply, int remain,
		 std::vector<std::string> &pv,
		 std::vector<std::uint64_t>& pv_hashes,
		 //std::vector<std::string>& pv_fens,
		 std::set<std::uint64_t>& already
		 //std::map<std::uint64_t, std::string>& already_fen
		 ) {
  MoveList ml = pos.legal_move_list();
  if (remain <= 0) {
    if (ml.size() == 0 && pos.in_check()) {
      //already_seen = false;
      for (int i = 0; i < pv_hashes.size(); i++) {
	if (already.find(pv_hashes[i]) != already.end()) {
	  break;
	  //already_seen = true;
	  //return;
	  //if (true) {
	  //std::cout << " " << i << " fen=" << already_fen[pv_hashes[i]] << std::endl;

	  //}
	}
      }

      std::string pvs;
      for (int i = 0; i < pv.size(); i++) {
	if (pv[i] != "") {
	  pvs += pv[i] + " ";

	}
      }
      std::cout << "[#] " << pvs << std::endl;
      //std::vector<State>& history() const {
      //const auto& history = pos.history();
      for (int i = 0; i < pv_hashes.size(); i++) {
	already.insert(pv_hashes[i]);
      }
      //for (int i = 0; i < pv_fens.size(); i++) {
      //already_fen[pv_hashes[i]] = pv_fens[i];
      //}
    }
    return;
  }

  for (int i = 0; i < ml.size(); i++) {
    Move move = ml.values()[i];
    pos.make_move(move);
    const auto pos2_hash = pos.hash();
    if (g_hashes[pos2_hash % HASHES] == pos2_hash) {
      pv[ply] = move.to_str();
      pv[ply + 1] = "";
      // std::cout << "#" << " " << ply << " " << remain << " " << move.to_str() << std::endl;
      pv_hashes[ply] = pos2_hash;
      show_hashes(pos, ply + 1, remain - 1, pv, pv_hashes, already);
      pv[ply] = "";
      pv_hashes[ply] = 0;
    }
    pos.unmake_move();
  }
}



bool search_any_moves_mate(Position& pos, int ply, int remain) {
  if (ply == 0) {
    g_hashes.clear();
    nodes = 0;
    repeats = 0;
  }
  if (pos.is_repeat()) {
    repeats++;
    return false;
  }

  if (remain <= 0) {
    bool res = pos.in_check() && pos.legal_move_list().size() == 0;
    //bool res = ml.size() == 0 && pos.in_check();
    if (res) {
      g_hashes[pos.hash() % HASHES] = pos.hash();
    }
    return res;
  }

  const MoveList ml = pos.legal_move_list();
  for (int i = 0; i < ml.size(); i++) {
    const Move& move = ml.values()[i];
    pos.make_move(move);
    nodes++;
    bool res = search_all_moves_mate(pos, ply + 1, remain - 1);
    pos.unmake_move();
    if (res) {
      g_hashes[pos.hash() % HASHES] = pos.hash();
      return res;
    }
  }
  return false;
}

bool search_all_moves_mate(Position& pos, int ply, int remain) {
  if (pos.is_repeat()) {
    repeats++;
    return false;
  }



  if (remain <= 0) {
    //bool res = (ml.size() == 0 && pos.in_check());
    bool res = pos.in_check() && pos.legal_move_list().size() == 0;
    if (res) {
      g_hashes[pos.hash() % HASHES] = pos.hash();
    }
    return res;
  }
  const MoveList ml = pos.legal_move_list();

  for (int i = 0; i < ml.size(); i++) {
    const Move& move = ml.values()[i];
    pos.make_move(move);
    nodes++;
    bool res = search_any_moves_mate(pos, ply + 1, remain - 1);
    pos.unmake_move();
    if (!res) {
	return false;
      }

  }
  g_hashes[pos.hash() % HASHES] = pos.hash();
  return true;
}

// Square king_square(Color color) const;
// bool in_check() const;
// bool is_repeat(int times = 1) const;
// GameState game_state() const;
// Bitboard attackers_to(Square square) const;
//    Bitboard attackers_to(Square square, Color c) const;

// mated -> legal_move_list().empty() && in_check()


int main(int argc, char* argv[]) {
  std::ios_base::sync_with_stdio(false);
  std::cout.setf(std::ios::unitbuf);

  std::cout << "hi" << std::endl;
  //Position pos{constants::STARTPOS_FEN};
  //Position pos{"k7/2K5/8/8/4N3/3B4/8/8 w - - 0 1"};
  // Position pos{"1k6/8/K1R5/8/8/8/8/8 w - - 0 1"}; // R moves, Ka8, R mates
  // Position pos{"kbK5/pp6/1P6/8/8/8/8/R7 w - - 0 1"}; // Sam Lloyd classic
  //Position pos{"4k3/8/8/8/8/8/PPPPPPPP/RNBQKBNR w KQ - 0 1"}; // Mate in 6(?).
  Position pos{"kq6/qr2r3/2qB4/4Bp2/6qB/2B2r2/pp3BRB/5B1K b - - 0 1"};
  // Position pos{"3qkrbn/1p1nq1qp/2n2rr1/1q2p3/q4P2/2B5/PPN1N2P/NB2KRBN b - -"};
  MoveList ml = pos.legal_move_list();

  std::cout << pos.fen() << std::endl;
  pos.display();

  std::cout << std::endl;
  // std::cout << "moves: " << ml.size() << std::endl;
  // for (int i = 0; i < ml.size(); i++) {
  //   Move move = ml.values()[i];
  //   std::cout << move.to_str() << std::endl;

  //   pos.make_move(move);
  //   //std::cout << "\t" << pos.fen() << std::endl;
  //   pos.unmake_move();
  // }
  // std::cout << std::endl;

// 0 0 0s n=0
// 1 0 0s n=20
// 2 0 0s n=40
// 3 0 0s n=485
// 4 0 0s n=930
// 5 0 0s n=12013
// 6 0 0s n=23093
// 7 0 5s n=325401
// 8 0 8s n=626611

  for (int remain = 1; remain < 13; remain += 2) {
    time_t t1 = time(0L);
    bool res = search_any_moves_mate(pos, 0, remain);
    time_t dt = time(0L) - t1;
    std::cout << remain << " " << res << " " << dt << "s " << "n=" << nodes << " r=" << repeats << std::endl;
    if (res) {
      std::vector<std::string> pv(100);
      std::vector<std::uint64_t> pv_hashes(100);
      //std::vector<std::string> pv_fens(100);
      std::set<uint64_t> already;
      //std::map<std::uint64_t, std::string> already_fen;
      show_hashes(pos, 0, remain, pv, pv_hashes, already);
      std::cout << "already: " << already.size() << std::endl;
      break;
    }
  }
}
