/**
 * Author: Wzięte z tonowak
 * Description: Zwraca wektory posortowane kątowo zgodnie z ruchem wskazówek zegara,
 *  zaczynając od najbliższego kątowo do wektora $(0, 1)$ włącznie.
 *  Aby posortować po argumencie (kącie) swapujemy x, y,
 *  używamy \texttt{angle\_sort} i ponownie swapujemy x, y.
 *  Zakłada, że nie ma punktu $(0, 0)$ na wejściu. Dokładne dla \texttt{P = Point<ll>}.
 * Time: O(n \log n)
 */
#pragma once

#include "Point.h"

template<class P> vector<P> angle_sort(vector<P> t) {
	for(P p : t) assert(!(p == P(0, 0)));
	auto it = partition(all(t), [](P a){ return P(0, 0) < a; });
	auto cmp = [&](P a, P b) { return a.cross(b) < 0; };
	sort(t.begin(), it, cmp);
	sort(it, t.end(), cmp);
	return t;
}
