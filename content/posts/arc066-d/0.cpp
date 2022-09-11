ll rec(ll v) {
    if (v == 0) return 1;

    if (v & 1) {
        // 最下位は1で確定
        // 繰り上がりはないので、それより上についてそのまま考えればいい
        return rec(v >> 1);
    } else {
        // 最下位は0で確定
        // 繰り上がりが起こるか否かで場合分け
        return rec(v >> 1) + rec((v >> 1) - 1);
    }
}