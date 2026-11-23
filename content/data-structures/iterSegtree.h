/**
 * Author: AI Cash
 * Date: 2026-11-23
 * License: CC0
 * Source: https://codeforces.com/blog/entry/18051
 * Description: Dodaj na przedziale, znajdź minimum na przedziale
 * Time: O(\log N)
 * Status: stress-tested
 */
struct segtree {
    int h, siz;
    vi t, lazy;
    segtree(int n) {
        h = ceil(log2(n));
        siz = n + 1; // ustaw 1<<h jesli masz operacje nieprzemienne
        t.assign(2*siz, 0);
        lazy.assign(siz, 0);
    }
    void apply(int pos, int val) {
        t[pos] += val;
        if(pos < siz) lazy[pos] += val;
    }
    void up(int p) {
       while(p > 1) p/=2, t[p] = min(t[2*p], t[2*p + 1]) + lazy[p];
    }
    void down(int p) {
        for(int i=h; i>0; --i) {
            int pos = p >> i;
            if(lazy[pos]) {
                apply(2*pos, lazy[pos]);
                apply(2*pos + 1, lazy[pos]);
                lazy[pos] = 0;
            }
        }
    }
    void update(int l, int r, int val) {
        l+=siz, r+=siz;
        int l0 = l, r0 = r;
        for(; l < r; l/=2, r/=2) {
            if(l&1) apply(l++, val);
            if(r&1) apply(--r, val);
        }
        up(l0);
        up(r0 - 1);
    }
    int query(int l, int r) {
        l+=siz, r+=siz;
        down(l);
        down(r-1);
        int ans = oo;
        for(; l < r; l/=2, r/=2) {
            if(l&1) ans = min(ans, t[l++]);
            if(r&1) ans = min(ans, t[--r]);
        }
        return ans;
    }
};