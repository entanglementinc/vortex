/*
* MCE, the real life implementation of McEliece encryption scheme.
* Copyright Projet SECRET, INRIA, Rocquencourt and Bhaskar Biswas and 
* Nicolas Sendrier (Bhaskar.Biswas@inria.fr, Nicolas.Sendrier@inria.fr).
*
* This is free software; you can redistribute it and/or modify it
* under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation; either version 2.1 of
* the License, or (at your option) any later version.
*
* This software is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this software; if not, write to the Free
* Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
* 02110-1301 USA, or see the FSF site: http://www.fsf.org.
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "precomp.h"

#ifndef INFINITY
#define INFINITY (1.0 / 0.0)
#endif

typedef struct tnode {
  int m, t;
  struct tnode ** sons;
} * tree_t;

typedef struct lnode {
  tree_t tree;
  struct lnode * next;
} * list_t;

list_t list_alloc(tree_t a, list_t s) {
  list_t l = (list_t) malloc(sizeof (struct lnode));
  l->tree = a;
  l->next = s;
  return l;
}

tree_t leaf_alloc(int m, int t) {
  tree_t a = (tree_t) malloc(sizeof (struct tnode));
  a->m = m;
  a->t = t;
  a->sons = NULL;
  return a;
}

tree_t tree_alloc(int m, int t, tree_t * s) {
  tree_t a = (tree_t) malloc(sizeof (struct tnode));
  a->m = m;
  a->t = t;
  a->sons = s;
  return a;
}

int l2(unsigned long x) {
  static char table[256] = {
    0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
  };

#if __WORDSIZE == 64
  if (x >> 32)
    if (x >> 48)
      if (x >> 56)
	return table[x >> 56] + 56;
      else
	return table[x >> 48] + 48;
    else if (x >> 40)
      return table[x >> 40] + 40;
    else
      return table[x >> 32] + 32;
  else
#endif
    if (x >> 16)
      if (x >> 24)
	return table[x >> 24] + 24;
      else
	return table[x >> 16] + 16;
    else if (x >> 8)
      return table[x >> 8] + 8;
    else
      return table[x];
}

int is_leaf(int m, int t) {
  static int leaf[6] = {7, 5, 4, 4, 3, 3};
  if (m < 6)
    return (t <= 32);
  else if (m > 16)
    return (t <= 1);
  else if (m > 11)
    return (t <= 2);
  else
    return (leaf[m - 6] >= t);
}

double bino_d(int a, int b) {
  if (b == 0)
    return 1;
  return (bino_d(a, b - 1) * (a - b + 1)) / b;
}

double binomial_d(int a, int b) {
  if (b > a / 2)
    return bino_d(a, a - b);
  if (b < 0)
    return 0;
  return bino_d(a, b);
}

double log_bino_d(int a, int b) {
  if (b == 0)
    return 0;
  return log_bino_d(a, b - 1) + log2(a - b + 1) - log2(b);
}

double log_binomial_d(int a, int b) {
  if (b > a / 2)
    return log_bino_d(a, a - b);
  if (b < 0)
    return -INFINITY;
  return log_bino_d(a, b);
}

// The following 4 functions compute a lower bound of the minimal
// self-information (log_2 of the inverse of the probability) of a
// constant weight word generated by the current implementation of the
// dichotomic algorithm. Every time something has to be rounded
// because of a small precision of computation, the worst case is
// assumed

double dicho_si_lb_node(int i, distrib_t d) {
  double y;

  if (i == d.max)
    y = (1UL << PREC_PROBA) - distrib_get_proba(d, i);
  else
    y = distrib_get_proba(d, i + 1) - distrib_get_proba(d, i);
  y = ldexp(y, -PREC_PROBA);
  y += ldexp(1, 2 - PREC_INTER);

  return -log2(y);
}

double dicho_si_lb_leaf(int m, int t, int l) {
  double y;
  unsigned long u;

  u = binomial_d(1 << m, t);
  u &= (((unsigned) -1) << l); // mask the l least significant bits
  y = 1.0 / u;
  y += ldexp(1, 2 - PREC_INTER - l);

  return -log2(y);
}

void dicho_si_lb_rec(int m, int t, precomp_t p, double ** pe) {
  int i;
  double x;
  distrib_t d;

  if (t > (1 << m) - t) {
    dicho_si_lb_rec(m, (1 << m) - t, p, pe);
    pe[m][t] = pe[m][(1 << m) - t];
  }
  else if ((pe[m][t] == 0) && (t > 0)) {
    if (t == 1)
      pe[m][t] = m;
    else if (is_leaf(m, t)) {
      pe[m][t] = dicho_si_lb_leaf(m, t, p.leaf_info[m][t].deadbits);
    }
    else {
      d = precomp_get_distrib(p, m, t);
      for (i = d.min; i <= d.max; ++i) {
	dicho_si_lb_rec(m - 1, i, p, pe);
	dicho_si_lb_rec(m - 1, t - i, p, pe);
	x = dicho_si_lb_node(i, d);
	x += pe[m - 1][i] + pe[m - 1][t - i];
	if ((pe[m][t] == 0) || (x < pe[m][t]))
	  pe[m][t] = x;
      }
    }
  }
}

double ** dicho_si_lb(precomp_t p) {
  int i;
  double ** pe, x;

  pe = (double **) calloc(p.m + 1, sizeof (double *));
  for (i = 0; i <= p.m; ++i)
    pe[i] = (double *) calloc(p.t + 1, sizeof (double));

  dicho_si_lb_rec(p.m, p.t, p, pe);

  return pe;
}

// The following 4 functions compute the minimal self-information
// (log_2 of the inverse of the probability) of a constant weight word
// generated by the dichotomic algorithm (the minimal self-information
// corresponds to the maximal probability)

double dicho_si_node(int i, distrib_t d) {
  double y;

  if (i == d.max)
    y = (1UL << PREC_PROBA) - distrib_get_proba(d, i);
  else
    y = distrib_get_proba(d, i + 1) - distrib_get_proba(d, i);

  return PREC_PROBA - log2(y);
}

// only called when binomial(2^m,t) is smaller than the largest
// unsigned long
double dicho_si_leaf(int m, int t, int l) {
  unsigned long u;

  u = binomial_d(1 << m, t);
  u &= (((unsigned) -1) << l); // mask the l least significant bits
  return log2(u);
}

void dicho_si_rec(int m, int t, precomp_t p, double ** pe) {
  int i;
  double x;
  distrib_t d;

  if (t > (1 << m) - t) {
    dicho_si_lb_rec(m, (1 << m) - t, p, pe);
    pe[m][t] = pe[m][(1 << m) - t];
  }
  else if ((pe[m][t] == 0) && (t > 0)) {
    if (t == 1)
      pe[m][t] = m;
    else if (is_leaf(m, t))
      pe[m][t] = dicho_si_leaf(m, t, p.leaf_info[m][t].deadbits);
    else {
      d = precomp_get_distrib(p, m, t);
      for (i = d.min; i <= d.max; ++i) {
	dicho_si_rec(m - 1, i, p, pe);
	dicho_si_rec(m - 1, t - i, p, pe);
	x = dicho_si_node(i, d) + pe[m - 1][i] + pe[m - 1][t - i];
	if ((pe[m][t] == 0) || (x < pe[m][t]))
	  pe[m][t] = x;
      }
    }
  }
}

double ** dicho_si(precomp_t p) {
  int i;
  double ** pe, x;

  pe = (double **) calloc(p.m + 1, sizeof (double *));
  for (i = 0; i <= p.m; ++i)
    pe[i] = (double *) calloc(p.t + 1, sizeof (double));

  // dynamic programming using the array pe
  dicho_si_rec(p.m, p.t, p, pe);

  return pe;
}

double ** si_lb;
double min = 0;

// smaller than anything we could compute but greater than any error
// due to floating operations

#define EPSILON (1.0 / (1UL << PREC_INTER)) 

double * dicho_self_info_bounds(precomp_t p) {
  double * res;
  double ** si;

  res = malloc(2 * sizeof (double));

  // si[i][j] is the minimal self-information (log_2 of the inverse of
  // the probability) of a word of length 2^i and weight j produced
  // with the dichotomic algorithm
  si = dicho_si(p);

  // si_lb[i][j] is the same thing as si[i][j], except that we do not
  // consider the algorithm but its implentation. We compute the
  // worst-case lower bound for the minimal self-information
  si_lb = dicho_si_lb(p);

  res[0] = si_lb[p.m][p.t] + (p.real_m - p.m) * p.real_t + EPSILON;
  res[1] = si[p.m][p.t] + (p.real_m - p.m) * p.real_t + EPSILON;
  free(si);
  free(si_lb);

  return res;
}

unsigned long update_delta(int i, distrib_t d, unsigned long delta) {
  unsigned long u;

  u = (i == d.max) ? delta : ((distrib_get_proba(d, i + 1) * delta) >> PREC_PROBA);
  u -= ((distrib_get_proba(d, i) * delta) >> PREC_PROBA);

  return u;
}

unsigned long adjust_delta(unsigned long delta, int * l) {
  *l = PREC_INTER - l2(delta - 1) - 1;
  return (delta << (*l));
}

#define ABOVE_MIN(len, delta, z) ((len) + PREC_INTER - log2(delta) + (z) + EPSILON >= min)

double dicho_si_from_list(list_t l, unsigned long delta, int len, double z, precomp_t p) {
  int m, t, j_up, j_down;
  unsigned long u, delta_down, delta_up;
  double x;

  if (ABOVE_MIN(len, delta, z))
    return INFINITY;

  if (l == NULL)
    return min = len + PREC_INTER - log2(delta);

  t = l->tree->t;
  m = l->tree->m;

  if (t == 0)
    return dicho_si_from_list(l->next, delta, len, z, p);

  if (t == 1)
    return dicho_si_from_list(l->next, delta, len + m, z - m, p);

  x = INFINITY; // default value

  z -= si_lb[m][t];
  len += p.leaf_info[m][t].deadbits;
  // the new value of delta will be derived from either delta_up or
  // delta_down. Though the highest probability (lowest
  // self-information) is likely to happen when the "up" path is
  // taken, we cannot be sure and we have to try both

  u = binomial_d(1 << m, t);
  u >>= p.leaf_info[m][t].deadbits;
  // round up
  delta_up = adjust_delta((delta - 1) / u + 1, &j_up);
  // round down
  delta_down = adjust_delta(delta / u, &j_down);

  x = dicho_si_from_list(l->next, delta_up, len + j_up, z, p);

  if ((x == INFINITY) && (delta_up != delta_down))
    x = dicho_si_from_list(l->next, delta_down, len + j_down, z, p);

  return x;
}

double tree_search(tree_t a, list_t path, list_t todo, unsigned long delta, int len, double z, precomp_t p) {
  int i, j, m, t;
  unsigned long u;
  distrib_t d;
  list_t l;
  double x;

  m = a->m;
  t = a->t;

  if (ABOVE_MIN(len, delta, z + si_lb[m][t]))
    return INFINITY;

  x = INFINITY; // default value

  if (a->sons == NULL) {
    z += si_lb[m][t];
    l = list_alloc(a, path);
    if (todo == NULL)
      x = dicho_si_from_list(l, delta, len, z, p);
    else {
      z -= si_lb[todo->tree->m][todo->tree->t];
      x = tree_search(todo->tree, l, todo->next, delta, len, z, p);
    }
    free(l);
  }
  else {
    d = precomp_get_distrib(p, m, t);
    for (i = d.min; (i <= d.max) && (x == INFINITY); ++i) {
      u = update_delta(i, d, delta);
      u = adjust_delta(u, &j);
      l = list_alloc(a->sons[t - i], todo);
      x = tree_search(a->sons[i], path, l, u, len + j, z + si_lb[m - 1][t - i], p);
      free(l);
    }
  }

  return x;
}

tree_t dicho_build_tree(int m, int t, precomp_t p) {
  unsigned long u;
  int i;
  distrib_t d;
  tree_t * a;

  if (t == 0)
    return leaf_alloc(m, t);

  if (t == 1)
    return leaf_alloc(m, t);

  if (t > (1 << m) - t)
    return dicho_build_tree(m, (1 << m) - t, p);

  if (is_leaf(m, t))
    return leaf_alloc(m, t);

  d = precomp_get_distrib(p, m, t);
  a = malloc((d.max + 1) * sizeof (tree_t *));
  for (i = d.min; i <= d.max; ++i)
    a[i] = dicho_build_tree(m - 1, i, p);

  return tree_alloc(m, t, a);
}

void clear_tree(tree_t a, precomp_t p) {
  int i;
  distrib_t d;

  if (a->sons != NULL) {
    d = precomp_get_distrib(p, a->m, a->t);
    for (i = d.min; i <= d.max; ++i)
      clear_tree(a->sons[i], p);
    free(a->sons);
  }
  free(a);
}

double dicho_searchmin(precomp_t p, double min_value) {
  double res;
  tree_t a;

  // needed in the search
  si_lb = dicho_si_lb(p);
  min = min_value - (p.real_m - p.m) * p.real_t;

  a = dicho_build_tree(p.m, p.t, p);
  res = tree_search(a, NULL, NULL, 1UL << PREC_INTER, 0, 0, p);
  clear_tree(a, p);
  free(si_lb);

  return min + (p.real_m - p.m) * p.real_t;
}

distrib_t init_proba(int m, int t, int i) {
  int n, j;
  distrib_t dist;
  double x, * y;

  dist.min = i;
  dist.max = t - i;
  dist.prob = (unsigned long *) malloc((dist.max - dist.min + 1) * sizeof (unsigned long));
  y = (double *) malloc((dist.max + 1) * sizeof (double));
  n = 1 << (m - 1);

  for (x = 0, j = dist.min; j <= dist.max; ++j) {
    y[j] = x;
    x += binomial_d(n, j) * binomial_d(n, t - j);
  }

  for (j = dist.min; j <= dist.max; ++j)
    distrib_get_proba(dist, j) = (unsigned long) round(ldexp(y[j] / x, PREC_PROBA));

  free(y);

  return dist;
}

leaf_info_t leaf_info(int m, int t) {
  int i, l;
  double x, y;
  unsigned long u, v;
  leaf_info_t li;

  u = binomial_d(1 << m, t);

  i = l2(u);
  l = i - PREC_PROBA;
  if (l < 0)
    l = 0;
  x = 0;
  for (; l < i - 2; ++l) {
    v = u & (((unsigned) -1) << l); // mask the l least significant bits
    y = 1.0 / v;
    y += ldexp(1, 2 - PREC_INTER - l);
    if ((x == 0) || (y < x)) {
      li.deadbits = l;
      li.maximum = u >> l;
      x = y;
    }
  }

  return li;
}

// maximal difference between the actual self-information and the real
// thing
double max_si_loss(int m, int t, distrib_t d) {
  int i;
  double x, y;

  for (y = 0, i = d.min; i <= d.max; ++i) {
    x = binomial_d(1 << (m - 1), i) * binomial_d(1 << (m - 1), t - i);
    x = binomial_d(1 << m, t) / x;
    x = log2(x);

    x -= dicho_si_lb_node(i, d);
    if (x > y)
      y = x;
  }
  return y;
}

void distrib_clear(distrib_t dist) {
  free(dist.prob);
}

precomp_t precomp_build(int m, int t, int reduc) {
  int i, j, k;
  double x, y, z;
  int * start, * end;
  distrib_t tmp;
  precomp_t p;

  p.real_m = m;
  p.real_t = t;
  m -= reduc;
  p.m = m;
  t = (t < (1 << m) - t) ? t : ((1 << m) - t);
  p.t = t;

  p.leaf_info = (leaf_info_t **) malloc((m + 1) * sizeof (leaf_info_t *));
  for (i = (m < 5) ? m : 5; i <= m; ++i) {
    for (j = (1 << (i - 1)); j >= 2; --j)
      if (is_leaf(i, j))
	break;
    p.leaf_info[i] = (leaf_info_t *) malloc((j + 1) * sizeof (leaf_info_t));
    for (k = 2; k <= j; ++k)
      p.leaf_info[i][k] = leaf_info(i, k);
  }

  if (is_leaf(m, t)) {
    p.distrib = NULL;
    p.offset = NULL;
    return p;
  }
  p.distrib = (distrib_t **) calloc(m + 1, sizeof (distrib_t *));
  p.offset = start = calloc(m + 1, sizeof (int));
  end = calloc(m + 1, sizeof (int));
  start[m] = end[m] = t;
  while (start[m] <= end[m]) {
    p.distrib[m] = (distrib_t *) calloc(end[m] - start[m] + 1, sizeof (distrib_t));
    for (x = 0, i = 0; i <= end[m] - start[m]; ++i) {
      if (i + start[m] > (1 << (m - 1))) { // impossible ?
	fprintf(stderr, "erreur init : m=%d t=%d\n", m, i + start[m]);
	exit(0);
      }
      k = (i + start[m]) / 2;
      p.distrib[m][i] = init_proba(m, i + start[m], k);
      z = max_si_loss(m, i + start[m], p.distrib[m][i]);
      for (--k; k >= 0; --k) {
	tmp = init_proba(m, i + start[m], k);
	y = max_si_loss(m, i + start[m], tmp);
	if (y < z) { // en cas d'�galit� on prend le k le plus grand
	  distrib_clear(p.distrib[m][i]);
	  p.distrib[m][i] = tmp;
	  z = y;
	  j = k;
	}
	else
	  distrib_clear(tmp);
      }
    }

    for (j = 0, k = end[m], i = 0; i <= end[m] - start[m]; ++i) {
      if (p.distrib[m][i].max > j)
	j = p.distrib[m][i].max;
      if (p.distrib[m][i].min < k)
	k = p.distrib[m][i].min;
    }
    m--;
    end[m] = j;
    start[m] = k;
#define MIN(x,y) ((x < y) ? x : y)
    // on reajuste sachant que si on a i tel que start <= i <= end et
    // 2*i > 2^m, on prendra 2^m - i au lieu de i
    k = MIN(start[m], (1 << m) - end[m]);
    j = MIN(end[m], (1 << m) - start[m]);
    start[m] = k;
    end[m] = MIN(j, 1 << (m - 1));

    while (is_leaf(m, start[m]) && (start[m] <= end[m])) {
      ++start[m];
    }
  }
  free(end);

  return p;
}

void write_precomp(precomp_t p, FILE * output_stream) {
  int i, j, k, l;
  int * start, * end;
  distrib_t ** d;

  start = (int *) calloc(p.m + 1, sizeof (int));
  end = (int *) calloc(p.m + 1, sizeof (int));

  d = p.distrib;
  l = p.m;
  start[l] = end[l] = p.t;
  while (1) {
    for (j = 0, k = end[l], i = 0; i <= end[l] - start[l]; ++i) {
      if (d[l][i].max > j)
	j = d[l][i].max;
      if (d[l][i].min < k)
	k = d[l][i].min;
    }
    end[l - 1] = j;
    start[l - 1] = k;
    // ajustement
    k = MIN(start[l - 1], (1 << (l - 1)) - end[l - 1]);
    j = MIN(end[l - 1], (1 << (l - 1)) - start[l - 1]);
    start[l - 1] = k;
    end[l - 1] = MIN(j, 1 << (l - 2));

    while (is_leaf(l - 1, start[l - 1]))
      start[l - 1]++;
    if (start[l - 1] > end[l - 1])
      break;
    l--;
  }
  fprintf(output_stream,"#include <stdlib.h>\n");
  fprintf(output_stream,"#include \"precomp.h\"\n\n");
  fprintf(output_stream,"precomp_t cwdata = {\n  %d, %d, %d, %d, (int []) {", p.m, p.t, p.real_m, p.real_t);
  for (k = 0; k < l; ++k)
    fprintf(output_stream,"0, ");
  fprintf(output_stream,"%d", start[l]);
  for (k = l + 1; k <= p.m; ++k)
    fprintf(output_stream,", %d", start[k]);
  fprintf(output_stream,"},\n  (distrib_t *[]) {\n    ");
  for (k = 0; k < l; ++k)
    fprintf(output_stream,"NULL, ");
  fprintf(output_stream,"\n");
  for (; l <= p.m; ++l) {
    fprintf(output_stream, "    (distrib_t []) {\n");
    for (i = 0; i <= end[l] - start[l]; ++i) {
      fprintf(output_stream, "      {%d, %d, (unsigned long []) {0", d[l][i].min, d[l][i].max);
      for (j = d[l][i].min + 1; j <= d[l][i].max; ++j)
	fprintf(output_stream, ", %u", distrib_get_proba(d[l][i], j));
	fprintf(output_stream, "}}");
      if (i < end[l] - start[l])
	fprintf(output_stream, ",\n");
      else
	fprintf(output_stream, "\n");
    }
    fprintf(output_stream, "    }");
    if (l < p.m)
      fprintf(output_stream, ",\n");
    else
      fprintf(output_stream, "\n");
  }
  fprintf(output_stream, "  },");
  fprintf(output_stream,"  (leaf_info_t *[]) {\n    NULL, NULL, NULL, NULL, NULL,\n");
  l = p.m;
  for (i = 5; i <= p.m; ++i) {
    fprintf(output_stream, "    (leaf_info_t []) {{0, 0}, {0, 0}, ");
    for (j = (1 << (i - 1)); j >= 2; --j)
      if (is_leaf(i, j))
	break;
    for (k = 2; k <= j; ++k) {
      fprintf(output_stream, "{%d, %d}", p.leaf_info[i][k].maximum, p.leaf_info[i][k].deadbits);
      if (k < j)
	fprintf(output_stream, ", ");
      else
	fprintf(output_stream, "}");
    }
    if (i == p.m)
      fprintf(output_stream, "\n");
    else if (!is_leaf(i + 1, 2)) {
      fprintf(output_stream, "\n");
      break;
    }
    else
      fprintf(output_stream, ",\n");
  }
  fprintf(output_stream, "  }\n};\n");
  free(start);
  free(end);
}

void clear_precomp(precomp_t p) {
  int m, i, j, end;

  if ((p.t > (1 << p.m)) || is_leaf(p.m, p.t))
    return;

  end = p.t;
  for (m = p.m; m >= 6; --m) {
    end = MIN(MIN(end, (1 << m) - p.offset[m]), 1 << (m - 1));
    j = end - p.offset[m];
    if (j < 0)
      break;
    end = 0;
    for (i = 0; i <= j; ++i) {
      if (end < p.distrib[m][i].max)
	end = p.distrib[m][i].max;
      distrib_clear(p.distrib[m][i]);
    }
    // ajustement
    end = MIN(end, (1 << (m - 1)) - p.offset[m - 1]);
    free(p.distrib[m]);
  }
  free(p.offset);
  free(p.distrib);
}