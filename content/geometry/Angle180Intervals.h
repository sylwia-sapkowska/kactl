/**
 * Author: Wzięte z tonowak
 * Description: ZAKŁADA, że punkty są posortowane przez \texttt{angle\_sort}.
 *  Zwraca $n$ par $[i, r]$, gdzie $r$ jest maksymalnym cyklicznie indeksem,
 *  że wszystkie punkty w tym cyklicznym przedziale są ściśle ,,po prawej''
 *  stronie wektora $(0,0) \to in[i]$, albo są na tej półprostej.
 *  Wymaga $n \geq 1$.
 * Time: O(n)
 */
#pragma once

#include "AngleSort.h"

template<class P> vector<pii> angle180_intervals(vector<P> in) {
	int n = sz(in);
	vi nxt(n);
	iota(all(nxt), 1);
	int r = nxt[n - 1] = 0;
	vector<pii> ret(n);
	rep(l, 0, n) {
		if(nxt[r] == l) r = nxt[r];
		auto good = [&](int i) {
			auto c = in[l].cross(in[i]);
			if(c != 0) return c < 0;
			if((P(0, 0) < in[l]) != (P(0, 0) < in[i]))
				return false;
			return l < i;
		};
		while(nxt[r] != l and good(nxt[r]))
			r = nxt[r];
		ret[l] = {l, r};
	}
	return ret;
}
