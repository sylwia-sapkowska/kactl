/**
 * Author: Adamant
 * Date: 2026-11-23
 * Description: 
 * Time: $O(26N) lub O(log(A)N)$
 * Status: stress-tested a bit
 */

const int N = 5e5;
const int A = 26;
int len[2*N];
int suflink[2*N];
int pwyst[2*N];
array<int, A> to[2*N];
int sz = 1, last = 0;
void add_letter(char c) {
    int p = last;
    last = sz++;
    len[last] = pwyst[last] = len[p] + 1;
    for(; to[p][c] == 0; p = suflink[p]) {
        to[p][c] = last;
    }
    int q = to[p][c];
    if(q == last) {
        return;
    }
    if(len[q] == len[p] + 1) {
        suflink[last] = q;
        return;
    }
    int cl = sz++;
    to[cl] = to[q];
    suflink[cl] = suflink[q];
    pwyst[cl] = pwyst[q];
    len[cl] = len[p] + 1;
    suflink[q] = suflink[last] = cl;
    for(; to[p][c] == q; p = suflink[p]) {
        to[p][c] = cl;
    }
}