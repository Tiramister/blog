#include <vector>

using namespace std;

using u8 = unsigned char;
using u16 = unsigned short;

class BitVector {
  u16 length, cnum, bnum;
  // bit列の長さ、chunk数、chunk毎のblock数

  static const int cw = 256, bw = 8;
  // chunkの幅、blockの幅

  vector<u8> bit;  // 元データ
  vector<u16> chunk;
  vector<vector<u8>> blocks;
  static const vector<u8> table = {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
  };  // 理想は3bit整数だが、そんなものはないので妥協

public:
  explicit BitVector(int N) : length(N) {
    cnum = (length + cw - 1) / cw;
    bnum = cw / bw;

    bit.assign(cnum * bnum, 0);
    chunk.assign(cnum + 1, 0);
    blocks.assign(cnum, vector<u8>(bnum, 0));
  }

  /** pos bit 目を b に変える */
  void set(int pos, u8 b) {
    int bpos = pos / bw;
    int offset = pos % bw;

    if (b == 0) {
      bit[bpos] &= ~(1 << offset);
    } else if (b == 1) {
      bit[bpos] |= (1 << offset);
    }
  }

  /** pos bit 目を返す */
  u8 access(int pos) const {
    int bpos = pos / bw;
    int offset = pos % bw;
    return bit[bpos] >> offset & 1;
  }

  /** numの立っているbit数を返す */
  u8 popCount(u8 num) const {
    return table[num];
  }

  /** 前計算 chunk と blocks を適切に埋める */
  void build() {
    chunk[0] = 0;
    for (int i = 0; i < cnum; ++i) {
      blocks[i][0] = 0;
      for (int j = 0; j < bnum - 1; ++j) {
        blocks[i][j + 1] = blocks[i][j] + popCount(bit[i * bnum + j]);
      }
      chunk[i + 1] = chunk[i] + blocks[i][bnum - 1] + popCount(bit[(i + 1) * bnum - 1]);
    }
  }

  /** [0, pos) にある 1 の数を返す */
  int rank(int pos) const {
    int cpos = pos / cw;
    int bpos = pos % cw / bw;
    int offset = pos % bw;

    // 余った部分から、必要な部分だけをbitmaskで抽出する
    u8 masked = (bit[cpos * bnum + bpos]) & ((1 << offset) - 1);
    return chunk[cpos] + blocks[cpos][bpos] + popCount(masked);
  }

  /**
   * rank(idx)=num なる最小の idx を返す
   * そもそも 1 が num 個なかったら -1 を返す
   */
  int select(int num) const {
    if (num == 0) return 0;
    if (rank(length) < num) return -1;

    int ok = length, ng = 0;
    while (ok - ng > 1) {
      int mid = (ok + ng) / 2;
      if (rank(mid) >= num) {
        ok = mid;
      } else {
        ng = mid;
      }
    }

    return ok;
  }
};
