/**
 * Author: Wzięte z tonowak
 * Description: Generatorka wielokątów wypukłych (kolejność zgodna z ruchem wskazówek zegara).
 *  Zwraca wielokąt z co najmniej $n \cdot \texttt{PROC}$ punktami w zakresie $[-\texttt{range}, \texttt{range}]$.
 *  Jeśli $n$ $(n > 2)$ jest około $\texttt{range}^{2/3}$, to powinno chodzić $O(n \log n)$.
 *  Dla większych $n$ może nie dać rady. Bez \texttt{strictly\_convex} mogą być trzy punkty współliniowe.
 *  Ostatni punkt jest zawsze w $(0, 0)$ - można dodać przesunięcie o wektor dla pełnej losowości.
 */
#pragma once

#include "AngleSort.h"
#include "../contest/losowanie.h"

typedef Point<ll> P;
vi num_split(int value, int n) {
	vi v(n, value);
	rep(i, 0, n - 1)
		v[i] = int(rd(0, value));
	sort(all(v));
	adjacent_difference(all(v), v.begin());
	return v;
}
vi capped_zero_split(int cap, int n) {
	int m = int(rd(1, n - 1));
	auto lf = num_split(cap, m);
	auto rg = num_split(cap, n - m);
	for (int i : rg)
		lf.emplace_back(-i);
	return lf;
}
vector<P> gen_convex_polygon(int n, int range, bool strictly_convex = false) {
	assert(n > 2);
	vector<P> t;
	const double PROC = 0.9;
	do {
		t.clear();
		auto dx = capped_zero_split(range, n);
		auto dy = capped_zero_split(range, n);
		shuffle(all(dx), rng);
		rep(i, 0, n)
			if (dx[i] || dy[i])
				t.emplace_back(dx[i], dy[i]);
		t = angle_sort(t);
		if (strictly_convex && !t.empty()) {
			vector<P> nt(1, t[0]);
			rep(i, 1, sz(t)) {
				if (!nt.back().cross(t[i]))
					nt.back() = nt.back() + t[i];
				else
					nt.emplace_back(t[i]);
			}
			while (!nt.empty() && !nt.back().cross(nt[0])) {
				nt[0] = nt[0] + nt.back();
				nt.pop_back();
			}
			t = nt;
		}
	} while (sz(t) < n * PROC);
	partial_sum(all(t), t.begin());
	return t;
}
