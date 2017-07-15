// --------------------------
// projects/c++/graph/Graph.h
// Copyright (C) 2017
// Glenn P. Downing
// --------------------------

#ifndef Graph_h
#define Graph_h

// --------
// includes
// --------

#include <algorithm> // find
#include <cassert>   // assert
#include <cstddef>   // size_t
#include <utility>   // make_pair, pair
#include <vector>    // vector

#include <iostream>

// -----
// Graph
// -----

class Graph {
public:
  // --------
  // typedefs
  // --------

  typedef std::size_t vertex_descriptor;
  typedef std::pair<vertex_descriptor, vertex_descriptor> edge_descriptor;

  typedef std::vector<std::size_t>::const_iterator adjacency_iterator;

  typedef std::size_t vertices_size_type;
  typedef std::size_t edges_size_type;

  class vertex_iterator {

  private:
    const Graph *g;
    std::size_t _p;

  public:
    vertex_iterator(const Graph *tg, std::size_t p) : g(tg), _p(p) {}
    vertex_descriptor operator*() { return _p; }
    vertex_iterator &operator++() {
      ++_p;
      return *this;
    }
    vertex_iterator operator++(int) {
      vertex_iterator x = *this;
      ++(*this);
      return x;
    }
    vertex_iterator &operator--() {
      --_p;
      return *this;
    }
    vertex_iterator operator--(int) {
      vertex_iterator x = *this;
      --(*this);
      return x;
    }
    friend bool operator==(const vertex_iterator &lhs,
                           const vertex_iterator &rhs) {
      return (lhs.g == rhs.g && lhs._p == rhs._p);
    }
    friend bool operator!=(const vertex_iterator &lhs,
                           const vertex_iterator &rhs) {
      return !(lhs == rhs);
    }
  };

  class edge_iterator {
  private:
    std::size_t _sp; // source position
    std::size_t _tp; // target position
    const Graph *rg;

  public:
    edge_iterator(const Graph *g, vertex_descriptor s = 0,
                  vertex_descriptor t = 0)
        : _sp(s), _tp(t), rg(g) {}

    edge_iterator &operator++() {
      if (_tp + 1 < rg->g[_sp].size()) {
        ++_tp;
      } else if (_sp + 1 == rg->g.size()) {
          ++_sp;
          _tp = 0;
        } else {
            size_t p;
        for(p = _sp + 1; p < rg->g.size(); ++p) {
            if (rg->g[p].size()) {
                break;
            }
        }
        _sp = p;
        _tp = 0;
      }
      return *this;
    }

    edge_iterator operator++(int) {
      edge_iterator x = *this;
      ++(*this);
      return x;
    }
    edge_descriptor operator*() { return std::make_pair(_sp, rg->g[_sp][_tp]); }
    friend bool operator==(const edge_iterator &lhs, const edge_iterator &rhs) {
      return (lhs.rg == rhs.rg && lhs._sp == rhs._sp && lhs._tp == rhs._tp);
    }
    friend bool operator!=(const edge_iterator &lhs, const edge_iterator &rhs) {
      return !(lhs == rhs);
    }
  };

public:
  // --------
  // add_edge
  // --------

  /**
   * your documentation
   * @return pair with first being edge pair, second being true if success,
   * false if failure
   */

  // TODO check Boost result of add_edge failure, see what return.first is
  friend std::pair<edge_descriptor, bool>
  add_edge(vertex_descriptor s, vertex_descriptor e, Graph &t) {
    if (t.g[s].size() &&
        (std::find(t.g[s].begin(), t.g[s].end(), e) != t.g[s].end())) {
      return std::make_pair(std::make_pair(s, e), false);
    }
    t.g[s].push_back(e);
    return std::make_pair(std::make_pair(s, e), true);
  }

  // ----------
  // add_vertex
  // ----------

  /**
   * your documentation
   */
  friend vertex_descriptor add_vertex(Graph &t) {
    t.g.push_back(std::vector<vertex_descriptor>());
    vertex_descriptor v = t.g.end() - t.g.begin() - 1;
    return v;
  }

  // -----------------
  // adjacent_vertices
  // -----------------

  /**
   * your documentation
   */
  friend std::pair<adjacency_iterator, adjacency_iterator>
  adjacent_vertices(vertex_descriptor v, const Graph &t) {
    adjacency_iterator b = t.g[v].begin();
    adjacency_iterator e = t.g[v].end();
    return std::make_pair(b, e);
  }

  // ----
  // edge
  // ----

  /**
   * your documentation
   */
  friend std::pair<edge_descriptor, bool>
  edge(vertex_descriptor b, vertex_descriptor e, const Graph &tg) {
    edge_descriptor ed = std::make_pair(b, e);
    bool _find =
        (std::find(tg.g[b].begin(), tg.g[b].end(), e) != tg.g[b].end());
    return std::make_pair(ed, _find);
  }

  // -----
  // edges
  // -----

  /**
   * your documentation
   */
  friend std::pair<edge_iterator, edge_iterator> edges(const Graph &tg) {
    size_t p;
      for(p = 0; p < tg.g.size(); ++p) {
        if (tg.g[p].size()) {
            break;
        }
    }  
      edge_iterator b(&tg, p, 0);
    edge_iterator e(&tg, tg.g.size(), 0);
    return std::make_pair(b, e);
  }

  // ---------
  // num_edges
  // ---------

  /**
   * your documentation
   */
  friend edges_size_type num_edges(const Graph &tg) {
    edges_size_type s = 0;
    for (size_t p = 0; p < tg.g.size(); ++p) {
      s += tg.g[p].size();
    }
    return s;
  }

  // ------------
  // num_vertices
  // ------------

  /**
   * your documentation
   */
  friend vertices_size_type num_vertices(const Graph &tg) {
    vertices_size_type s = tg.g.size();
    return s;
  }

  // ------
  // source
  // ------

  /**
   * your documentation
   */
  friend vertex_descriptor source(edge_descriptor ed, const Graph &tg) {
    vertex_descriptor v = ed.first;
    return v;
  }

  // ------
  // target
  // ------

  /**
   * your documentation
   */
  friend vertex_descriptor target(edge_descriptor ed, const Graph &tg) {
    return ed.second;
  }

  // ------
  // vertex
  // ------

  /**
   * your documentation
   */
  friend vertex_descriptor vertex(vertices_size_type t, const Graph &tg) {
    vertex_descriptor vd = t;
    return vd;
  }

  // --------
  // vertices
  // --------

  /**
   * your documentation
   */
  friend std::pair<vertex_iterator, vertex_iterator> vertices(const Graph &tg) {
    vertex_iterator b(&tg, 0);
    vertex_iterator e(&tg, tg.g.end() - tg.g.begin());
    return std::make_pair(b, e);
  }

private:
  // ----
  // data
  // ----

  std::vector<std::vector<vertex_descriptor>> g;

  // -----
  // valid
  // -----

  /**
   * your documentation
   */
  bool valid() const { return true; }

public:
  // ------------
  // constructors
  // ------------

  /**
   * your documentation
   */
  Graph() : g(std::vector<std::vector<vertex_descriptor>>()) {
    assert(valid());
  }

  // Default copy, destructor, and copy assignment
  // Graph  (const Graph<T>&);
  // ~Graph ();
  // Graph& operator = (const Graph&);
};

#endif // Graph_h
