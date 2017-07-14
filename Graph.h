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

#include <cassert>      // assert
#include <cstddef>      // size_t
#include <utility>      // make_pair, pair
#include <vector>       // vector
#include <algorithm>    // find

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

        typedef std::vector<std::vector<vertex_descriptor>>::iterator vertex_iterator;
        typedef std::vector<vertex_descriptor>::iterator adjacency_iterator;

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;


        class edge_iterator {
            private:
                std::size_t _sp; //source position
                std::size_t _tp; //target position
                const Graph & rg;
            public:
                edge_iterator(const Graph &g, vertex_descriptor s = 0, vertex_descriptor t = 0) : rg(g), _sp(s), _tp(t) {}
                
                edge_iterator& operator++() {
                    if (_tp + 1 == rg.g[_sp].size()) {
                        ++_sp;
                        _tp = 0;
                    } else {
                        ++_tp;
                    }
                    return *this;}

                edge_iterator operator++(int) {
                    edge_iterator x = *this
                    ++(*this);
                    return x;
                }
                edge_descriptor operator*() {
                    return std::make_pair(_sp, rg.g[_sp][_tp]);     
                }
                friend bool operator==(const edge_iterator & lhs, const edge_iterator & rhs) {
                    return (lhs.rg == rhs.rg && lhs._sp == rhs._sp && lhs._tp == rhs._tp);
                }
                friend bool operator!=(const edge_iterator & lhs, const edge_iterator & rhs) {
                    return !(lhs == rhs);
                }
        };

    public:
        // --------
        // add_edge
        // --------

        /**
         * your documentation
         * @return pair with first being edge pair, second being true if success, false if failure
         */

        //TODO check Boost result of add_edge failure, see what return.first is
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor s, vertex_descriptor e, Graph& t) {
            if (std::find(t.g[e].begin(), t.g[e].end(), s) != t.g[e].end())
                return std::make_pair(std::make_pair(s ,e), false);
            if (std::find(t.g[s].begin(), t.g[s].end(), e) != t.g[e].end())
                return std::make_pair(std::make_pair(s ,e), true);
            t.g[s].push_back(e);
            return std::make_pair(std::make_pair(s, e), true);}

        // ----------
        // add_vertex
        // ----------

        /**
         * your documentation
         */
        friend vertex_descriptor add_vertex (Graph& t) {
            t.g.push_back(std::vector<vertex_descriptor>());
            vertex_descriptor v = t.g.end() - t.g.begin() - 1;
            return v;}

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * your documentation
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor v, const Graph& t) {
            adjacency_iterator b = t.g[v].begin();
            adjacency_iterator e = t.g[v].end();
            return std::make_pair(b, e);}

        // ----
        // edge
        // ----

        /**
         * your documentation
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor b, vertex_descriptor e, const Graph& tg) {
            edge_descriptor ed = std::make_pair(b ,e);
            bool            b  = std::find(tg.g[b].begin(), tg.g[b].end(), e) != tg.g[b].end();
            return std::make_pair(ed, b);}

        // -----
        // edges
        // -----

        /**
         * your documentation
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& tg) {
            edge_iterator b(tg, 0, 0);
            edge_iterator e(tg, tg.g.size() - 1, tg.g[tg.g.size() - 1].size());
            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         * your documentation
         */
        friend edges_size_type num_edges (const Graph& tg) {
            edges_size_type s = 0;
            for (size_t p = 0; p < tg.g.size(); ++p) {
                s += tg.g[p].size();
            }
            return s;}

        // ------------
        // num_vertices
        // ------------

        /**
         * your documentation
         */
        friend vertices_size_type num_vertices (const Graph& tg) {
            vertices_size_type s = tg.size();
            return s;}

        // ------
        // source
        // ------

        /**
         * your documentation
         */
        friend vertex_descriptor source (edge_descriptor ed, const Graph& tg) {
            vertex_descriptor v = e.first;
            return v;}

        // ------
        // target
        // ------

        /**
         * your documentation
         */
        friend vertex_descriptor target (edge_descriptor ed, const Graph& tg) {
            vertex_descriptor v = tg.g[ed.first][ed.second];
            return v;}

        // ------
        // vertex
        // ------

        /**
         * your documentation
         */
        friend vertex_descriptor vertex (vertices_size_type t, const Graph& tg) {
            vertex_descriptor vd = t;
            return vd;}

        // --------
        // vertices
        // --------

        /**
         * your documentation
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& tg) {
            vertex_iterator b = tg.g.begin();
            vertex_iterator e = tg.g.end();
            return std::make_pair(b, e);}

    private:
        // ----
        // data
        // ----

        std::vector< std::vector<vertex_descriptor> > g;

        // -----
        // valid
        // -----

        /**
         * your documentation
         */
        bool valid () const {
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * your documentation
         */
        Graph () {
            g = std::vector<std::vector<vertex_descriptor>>();
            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

#endif // Graph_h
