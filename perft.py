import chess
import time

# https://www.chessprogramming.org/Perft_Results

def perft(depth: int, board: chess.Board) -> int:
  if depth == 1:
    return board.legal_moves.count()
  elif depth > 1:
    count = 0

    # Very small improvement
    # xpush = board.push
    # xpop = board.pop

    for move in board.legal_moves:
      board.push(move)
      count += perft(depth - 1, board)
      board.pop()
    return count
  else:
    return 1


global_board = chess.Board()
def global_perft(depth: int) -> int:
  global global_board
  if depth == 1:
    return global_board.legal_moves.count()
  elif depth > 1:
    count = 0
    for move in global_board.legal_moves:
      global_board.push(move)
      count += global_perft(depth - 1)
      global_board.pop()
    return count
  else:
    return 1

if __name__ == "__main__":
  for d in range(1, 7):
    t1 = time.time()
    res = perft(d, chess.Board())
    dt = time.time() - t1
    print(f'{d:2d} {res:10d} {dt:.1f}')
