CXX = g++
CXXFLAGS = -O3 -std=c++17 -Wall -pipe  $(EXTRACXXFLAGS) -Ilibchess # -I/opt/homebrew/opt/abseil/include
LDFLAGS = -pthread -Wl, $(CXXFLAGS) $(EXTRALDFLAGS)
# -L/opt/homebrew/opt/abseil/lib -labsl_base -labsl_hash

CXXFLAGS += `PKG_CONFIG_PATH=/opt/homebrew/opt/abseil/lib/pkgconfig pkg-config --cflags absl_flat_hash_map`
LDFLAGS += `PKG_CONFIG_PATH=/opt/homebrew/opt/abseil/lib/pkgconfig pkg-config  --libs absl_flat_hash_map`
CXXFLAGS += `PKG_CONFIG_PATH=/opt/homebrew/opt/abseil/lib/pkgconfig pkg-config --cflags absl_btree`
LDFLAGS += `PKG_CONFIG_PATH=/opt/homebrew/opt/abseil/lib/pkgconfig pkg-config  --libs absl_btree`

all : puzzler perft
	echo ok

puzzler : puzzler.o
	g++ puzzler.o -o puzzler ${LDFLAGS}
	./puzzler

puzzle.o :

perft : perft.o
	g++ perft.o -o perft ${LDFLAGS}
	./perft

perft.o :
