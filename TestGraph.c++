// --------------------------------
// projects/g++/graph/TestGraph.c++
// Copyright (C) 2017
// Glenn P. Downing
// --------------------------------

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair

#include "boost/graph/adjacency_list.hpp"   // adjacency_list
#include "boost/graph/topological_sort.hpp" // topological_sort

#include "gtest/gtest.h"

#include "Graph.h"

using namespace std;

using testing::Test;
using testing::Types;

// ---------
// TestGraph
// ---------

template <typename G> struct TestGraph : Test {
  // --------
  // typedefs
  // --------

  using graph_type = G;
  using vertex_descriptor = typename G::vertex_descriptor;
  using edge_descriptor = typename G::edge_descriptor;
  using vertex_iterator = typename G::vertex_iterator;
  using edge_iterator = typename G::edge_iterator;
  using adjacency_iterator = typename G::adjacency_iterator;
  using vertices_size_type = typename G::vertices_size_type;
  using edges_size_type = typename G::edges_size_type;
};

// directed, sparse, unweighted
// possibly connected
// possibly cyclic
typedef Types<
    boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>,
            Graph>
    graph_types;

TYPED_TEST_CASE(TestGraph, graph_types);

// ----------
// Add Vertex
// ----------

TYPED_TEST(TestGraph, test_vertex_1) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using vertices_size_type = typename TestFixture::vertices_size_type;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);

  vertex_descriptor vd = vertex(0, g);
  ASSERT_EQ(vdA, vd);

  vertices_size_type vs = num_vertices(g);
  ASSERT_EQ(1, vs);
}

TYPED_TEST(TestGraph, test_vertex_2) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using vertices_size_type = typename TestFixture::vertices_size_type;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);
  
  vertex_descriptor vd = vertex(1, g);
  ASSERT_EQ(vdB, vd);

  vertices_size_type vs = num_vertices(g);
  ASSERT_EQ(3, vs);
}

// ------------
// num_vertices
// ------------
TYPED_TEST(TestGraph, test_num_vertices_1) {
    using graph_type = typename TestFixture::graph_type;
    using vertex_descriptor = typename TestFixture::vertex_descriptor;
    using vertices_size_type = typename TestFixture::vertices_size_type;

    graph_type g;
    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(0, vs);

    vertex_descriptor vdR = add_vertex(g);
    vs = num_vertices(g); 
    ASSERT_EQ(1, vs);
}

TYPED_TEST(TestGraph, test_num_vertices_2) {
    using graph_type = typename TestFixture::graph_type;
    using vertex_descriptor = typename TestFixture::vertex_descriptor;
    using vertices_size_type = typename TestFixture::vertices_size_type;

    graph_type g;
    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(0, vs);

    vertex_descriptor vdR = add_vertex(g);
    vs = num_vertices(g); 
    ASSERT_EQ(1, vs);

    vertex_descriptor vdS = add_vertex(g);
    vertex_descriptor vdT = add_vertex(g);
    vs = num_vertices(g); 
    ASSERT_EQ(3, vs);
}

TYPED_TEST(TestGraph, test_num_vertices_3) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using edge_descriptor = typename TestFixture::edge_descriptor;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);
  vertex_descriptor vdD = add_vertex(g);

 ASSERT_EQ(4, num_vertices(g));

  edge_descriptor edCA = add_edge(vdC, vdA, g).first;
  edge_descriptor edCB = add_edge(vdC, vdB, g).first;
  edge_descriptor edCD = add_edge(vdC, vdD, g).first;

 ASSERT_EQ(4, num_vertices(g));
    vertex_descriptor vdE = add_vertex(g);
 ASSERT_EQ(5, num_vertices(g));

}


// ----------------
// Iterate Vertices
// ----------------

TYPED_TEST(TestGraph, test_vertices_1) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using vertex_iterator = typename TestFixture::vertex_iterator;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);

  pair<vertex_iterator, vertex_iterator> p = vertices(g);
  vertex_iterator b = p.first;
  vertex_iterator e = p.second;
  if (b != e) {
    vertex_descriptor vd = *b;
    ASSERT_EQ(vdA, vd);
  }
  ++b;
  if (b != e) {
    vertex_descriptor vd = *b;
    ASSERT_EQ(vdB, vd);
  }
  ++b;
  ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, test_vertices_2) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using vertex_iterator = typename TestFixture::vertex_iterator;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);

  pair<vertex_iterator, vertex_iterator> p = vertices(g);
  vertex_iterator b = p.first;
  vertex_iterator e = p.second;
  if (b != e) {
    vertex_descriptor vd = *b;
    ASSERT_EQ(vdA, vd);
  }
  ++b;
  if (b != e) {
    vertex_descriptor vd = *b;
    ASSERT_EQ(vdB, vd);
  }
  ++b;
  ASSERT_EQ(e, b);
  
  vertex_descriptor vdC = add_vertex(g);
  pair<vertex_iterator, vertex_iterator> p2 = vertices(g);
  vertex_iterator b2 = p2.first;
  vertex_iterator e2 = p2.second;
  if (b2 != e2) {
    vertex_descriptor vd = *b2;
    ASSERT_EQ(vdA, vd);
  }
  ++b2;
  if (b2 != e2) {
    vertex_descriptor vd = *b2;
    ASSERT_EQ(vdB, vd);
  }
  ++b2;
  if (b2 != e2) {
    vertex_descriptor vd = *b2;
    ASSERT_EQ(vdC, vd);
  }
  ++b2;
  ASSERT_EQ(e2, b2);
}
//-----
// Edge
//-----

TYPED_TEST(TestGraph, test_edge_1) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using edge_descriptor = typename TestFixture::edge_descriptor;
  using edges_size_type = typename TestFixture::edges_size_type;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);

  edge_descriptor edAB = add_edge(vdA, vdB, g).first;
  pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
  ASSERT_EQ(edAB, p1.first);
  ASSERT_EQ(false, p1.second);

  pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);

  ASSERT_EQ(edAB, p2.first);
  ASSERT_EQ(true, p2.second);

  edges_size_type es = num_edges(g);
  ASSERT_EQ(1, es);

  vertex_descriptor vd1 = source(edAB, g);
  ASSERT_EQ(vdA, vd1);

  vertex_descriptor vd2 = target(edAB, g);
  ASSERT_EQ(vdB, vd2);
}

TYPED_TEST(TestGraph, test_edge_2) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using edge_descriptor = typename TestFixture::edge_descriptor;
  using edges_size_type = typename TestFixture::edges_size_type;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);
  vertex_descriptor vdD = add_vertex(g);



  edge_descriptor edCA = add_edge(vdC, vdA, g).first;
  edge_descriptor edCB = add_edge(vdC, vdB, g).first;
  edge_descriptor edCD = add_edge(vdC, vdD, g).first;

  pair<edge_descriptor, bool> p2 = edge(vdC, vdB, g);

  ASSERT_EQ(edCB, p2.first);
  ASSERT_EQ(true, p2.second);

  edges_size_type es = num_edges(g);
  ASSERT_EQ(3, es);

  vertex_descriptor vd1 = source(edCA, g);
  ASSERT_EQ(vdC, vd1);

  vertex_descriptor vd2 = target(edCA, g);
  ASSERT_EQ(vdA, vd2);
}

TYPED_TEST(TestGraph, test_edge_3) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using edge_descriptor = typename TestFixture::edge_descriptor;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);
  vertex_descriptor vdD = add_vertex(g);



  edge_descriptor edCA = add_edge(vdC, vdA, g).first;
  edge_descriptor edCB = add_edge(vdC, vdB, g).first;
  edge_descriptor edCD = add_edge(vdC, vdD, g).first;

    ASSERT_EQ(3, num_edges(g));
  pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);

  ASSERT_EQ(false, p2.second);
  ASSERT_EQ(3, num_edges(g));

}
//--------------
// Iterate Edges
// -------------
TYPED_TEST(TestGraph, test_edges_1) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using edge_descriptor = typename TestFixture::edge_descriptor;
  using edge_iterator = typename TestFixture::edge_iterator;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);
  edge_descriptor edAB = add_edge(vdA, vdB, g).first;
  edge_descriptor edAC = add_edge(vdA, vdC, g).first;

  pair<edge_iterator, edge_iterator> p = edges(g);
  edge_iterator b = p.first;
  edge_iterator e = p.second;
  
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edAB, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edAC, ed);
  }
  ++b;
  ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, test_edges_2) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using edge_descriptor = typename TestFixture::edge_descriptor;
  using edge_iterator = typename TestFixture::edge_iterator;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);
  pair<edge_descriptor,bool> p1 = add_edge(vdA, vdB, g);
  pair<edge_descriptor,bool> p2 = add_edge(vdA, vdC, g);
  pair<edge_descriptor,bool> p3 = add_edge(vdB, vdA, g);
  pair<edge_descriptor,bool> p4 = add_edge(vdB, vdC, g);
  pair<edge_descriptor,bool> p5 = add_edge(vdC, vdA, g);
  pair<edge_descriptor,bool> p6 = add_edge(vdC, vdB, g);

  ASSERT_TRUE(p1.second);
  ASSERT_TRUE(p2.second);
  ASSERT_TRUE(p3.second);
  ASSERT_TRUE(p4.second);
  ASSERT_TRUE(p5.second);
  ASSERT_TRUE(p6.second);

  pair<edge_iterator, edge_iterator> p = edges(g);
  edge_iterator b = p.first;
  edge_iterator e = p.second;
  
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(p1.first, ed);
  }
  ++b;++b;++b;++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(p5.first, ed);
  }
  ++b;++b;
  ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, test_edges_3) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using edge_descriptor = typename TestFixture::edge_descriptor;
  using edge_iterator = typename TestFixture::edge_iterator;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);
  edge_descriptor edAB = add_edge(vdA, vdB, g).first;
  edge_descriptor edAC = add_edge(vdA, vdC, g).first;

  pair<edge_iterator, edge_iterator> p = edges(g);
  edge_iterator b = p.first;
  edge_iterator e = p.second;
  
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edAB, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edAC, ed);
  }
  ++b;
  ASSERT_EQ(e, b);

  edge_descriptor edBC = add_edge(vdB, vdC, g).first;
  pair<edge_iterator, edge_iterator> p2 = edges(g);
  edge_iterator b2 = p2.first;
  edge_iterator e2 = p2.second;
  
  if (b2 != e2) {
    edge_descriptor ed = *b2;
    ASSERT_EQ(edAB, ed);
  }
  ++b2;
  if (b2 != e2) {
    edge_descriptor ed = *b2;
    ASSERT_EQ(edAC, ed);
  }
  ++b2;
  if (b2 != e2) {
    edge_descriptor ed = *b2;
    ASSERT_EQ(edBC, ed);
  }
  ++b2;
  ASSERT_EQ(e2, b2);
}

//------------------
// More Adding Edges
// -----------------
TYPED_TEST(TestGraph, test_add_edges_1) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using edge_descriptor = typename TestFixture::edge_descriptor;
  using edge_iterator = typename TestFixture::edge_iterator;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);
  vertex_descriptor vdD = add_vertex(g);
  vertex_descriptor vdE = add_vertex(g);
  vertex_descriptor vdF = add_vertex(g);
  vertex_descriptor vdG = add_vertex(g);

  edge_descriptor edDB = add_edge(vdD, vdB, g).first;
  edge_descriptor edDC = add_edge(vdD, vdC, g).first;
  edge_descriptor edDF = add_edge(vdD, vdF, g).first;
  edge_descriptor edDG = add_edge(vdD, vdG, g).first;

  pair<edge_iterator, edge_iterator> p = edges(g);
  edge_iterator b = p.first;
  edge_iterator e = p.second;

  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edDB, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edDC, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edDF, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edDG, ed);
  }
  ++b;
  ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, test_add_edges_2) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using edge_descriptor = typename TestFixture::edge_descriptor;
  using edge_iterator = typename TestFixture::edge_iterator;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);
  vertex_descriptor vdD = add_vertex(g);
  vertex_descriptor vdE = add_vertex(g);
  vertex_descriptor vdF = add_vertex(g);
  vertex_descriptor vdG = add_vertex(g);

  edge_descriptor edAB = add_edge(vdA, vdB, g).first;
  edge_descriptor edAC = add_edge(vdA, vdC, g).first;
  edge_descriptor edAF = add_edge(vdA, vdF, g).first;
  edge_descriptor edAG = add_edge(vdA, vdG, g).first;
  
  edge_descriptor edDB = add_edge(vdD, vdB, g).first;
  edge_descriptor edDC = add_edge(vdD, vdC, g).first;
  edge_descriptor edDF = add_edge(vdD, vdF, g).first;
  edge_descriptor edDG = add_edge(vdD, vdG, g).first;
  
  edge_descriptor edGB = add_edge(vdG, vdB, g).first;
  edge_descriptor edGC = add_edge(vdG, vdC, g).first;
  edge_descriptor edGF = add_edge(vdG, vdF, g).first;
  edge_descriptor edGA = add_edge(vdG, vdA, g).first;

  pair<edge_iterator, edge_iterator> p = edges(g);
  edge_iterator b = p.first;
  edge_iterator e = p.second;

  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edAB, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edAC, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edAF, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edAG, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edDB, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edDC, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edDF, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edDG, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edGA, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edGB, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edGC, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edGF, ed);
  }
  ++b;
  ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, test_add_edges_sequence_1) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using edge_descriptor = typename TestFixture::edge_descriptor;
  using edge_iterator = typename TestFixture::edge_iterator;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);

  edge_descriptor edAB = add_edge(vdA, vdB, g).first;
  edge_descriptor edBC = add_edge(vdB, vdC, g).first;
  edge_descriptor edAC = add_edge(vdA, vdC, g).first;

  pair<edge_iterator, edge_iterator> p = edges(g);
  edge_iterator b = p.first;
  edge_iterator e = p.second;

  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edAB, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edAC, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edBC, ed);
  }
  ++b;
  ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, test_add_edges_sequence_2) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using edge_descriptor = typename TestFixture::edge_descriptor;
  using edge_iterator = typename TestFixture::edge_iterator;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);
  vertex_descriptor vdD = add_vertex(g);
  vertex_descriptor vdE = add_vertex(g);

  edge_descriptor edDE = add_edge(vdD, vdE, g).first;
  edge_descriptor edCD = add_edge(vdC, vdD, g).first;
  edge_descriptor edCE = add_edge(vdC, vdE, g).first;
  edge_descriptor edAB = add_edge(vdA, vdB, g).first;

  pair<edge_iterator, edge_iterator> p = edges(g);
  edge_iterator b = p.first;
  edge_iterator e = p.second;

  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edAB, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edCD, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edCE, ed);
  }
  ++b;
  if (b != e) {
    edge_descriptor ed = *b;
    ASSERT_EQ(edDE, ed);
  }
  ++b;
  ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, test_add_edges_failure_1) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using edge_descriptor = typename TestFixture::edge_descriptor;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);

  edge_descriptor edAB = add_edge(vdA, vdB, g).first;
  edge_descriptor edBC = add_edge(vdB, vdC, g).first;
  edge_descriptor edAC = add_edge(vdA, vdC, g).first;
    
    ASSERT_FALSE(add_edge(vdA, vdC, g).second);

}

TYPED_TEST(TestGraph, test_add_edges_failure_2) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using edge_descriptor = typename TestFixture::edge_descriptor;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);

  edge_descriptor edAB = add_edge(vdA, vdB, g).first;
  edge_descriptor edBC = add_edge(vdB, vdC, g).first;
  edge_descriptor edAC = add_edge(vdA, vdC, g).first;


  ASSERT_EQ(edAC, add_edge(vdA, vdC, g).first);
}

TYPED_TEST(TestGraph, test_add_edges_failure_3) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using edge_descriptor = typename TestFixture::edge_descriptor;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);

  edge_descriptor edAB = add_edge(vdA, vdB, g).first;
  edge_descriptor edBC = add_edge(vdB, vdC, g).first;
  edge_descriptor edAC = add_edge(vdA, vdC, g).first;


  ASSERT_EQ(edBC, add_edge(vdB, vdC, g).first);
}

// -----------------
// Adjacent Vertices
// -----------------
TYPED_TEST(TestGraph, test_adjacent_vertices_1) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using adjacency_iterator = typename TestFixture::adjacency_iterator;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);

  add_edge(vdA, vdB, g);
  add_edge(vdA, vdC, g);

  pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
  adjacency_iterator b = p.first;
  adjacency_iterator e = p.second;
  if (b != e) {
    vertex_descriptor vd = *b;
    ASSERT_EQ(vdB, vd);
  }
  ++b;
  if (b != e) {
    vertex_descriptor vd = *b;
    ASSERT_EQ(vdC, vd);
  }
  ++b;
  ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, test_adjacent_vertices_2) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using adjacency_iterator = typename TestFixture::adjacency_iterator;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);
  vertex_descriptor vdD = add_vertex(g);
  vertex_descriptor vdE = add_vertex(g);
  vertex_descriptor vdF = add_vertex(g);
  vertex_descriptor vdG = add_vertex(g);

 add_edge(vdA, vdB, g);
 add_edge(vdA, vdC, g);
 add_edge(vdA, vdF, g);
 add_edge(vdA, vdG, g);
  
 add_edge(vdD, vdB, g);
 add_edge(vdD, vdC, g);
 add_edge(vdD, vdF, g);
 add_edge(vdD, vdG, g);
  
 add_edge(vdG, vdB, g);
 add_edge(vdG, vdC, g);
 add_edge(vdG, vdF, g);
 add_edge(vdG, vdA, g);

  pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdD, g);
  adjacency_iterator b = p.first;
  adjacency_iterator e = p.second;
    if (b != e) {
        vertex_descriptor a = *b;
        ASSERT_EQ(vdB, a);
    }
    ++b;
    if (b != e) {
        vertex_descriptor a = *b;
        ASSERT_EQ(vdC, a);
    }
    ++b;
    if (b != e) {
        vertex_descriptor a = *b;
        ASSERT_EQ(vdF, a);
    }
    ++b;
    if (b != e) {
        vertex_descriptor a = *b;
        ASSERT_EQ(vdG, a);
    }
    ++b;
    ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, test_adjacent_vertices_3) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using adjacency_iterator = typename TestFixture::adjacency_iterator;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);
  vertex_descriptor vdD = add_vertex(g);
  vertex_descriptor vdE = add_vertex(g);
  vertex_descriptor vdF = add_vertex(g);
  vertex_descriptor vdG = add_vertex(g);

 add_edge(vdA, vdB, g);
 add_edge(vdA, vdC, g);
 add_edge(vdA, vdF, g);
 add_edge(vdA, vdG, g);
  
 add_edge(vdD, vdB, g);
 add_edge(vdD, vdC, g);
 add_edge(vdD, vdF, g);
 add_edge(vdD, vdG, g);
  
 add_edge(vdG, vdB, g);
 add_edge(vdG, vdC, g);
 add_edge(vdG, vdF, g);
 add_edge(vdG, vdA, g);

  pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdC, g);
  adjacency_iterator b = p.first;
  adjacency_iterator e = p.second;
    ASSERT_TRUE(e == b);
}

TYPED_TEST(TestGraph, test_adjacent_vertices_4) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using adjacency_iterator = typename TestFixture::adjacency_iterator;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);
  vertex_descriptor vdD = add_vertex(g);
  vertex_descriptor vdE = add_vertex(g);
  vertex_descriptor vdF = add_vertex(g);
  vertex_descriptor vdG = add_vertex(g);

 add_edge(vdA, vdB, g);
 add_edge(vdA, vdC, g);
 add_edge(vdA, vdF, g);
 add_edge(vdA, vdG, g);
  
 add_edge(vdD, vdG, g);
 add_edge(vdD, vdC, g);
 add_edge(vdD, vdF, g);
 add_edge(vdD, vdB, g);
  
 add_edge(vdG, vdB, g);
 add_edge(vdG, vdC, g);
 add_edge(vdG, vdF, g);
 add_edge(vdG, vdA, g);

  pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdD, g);
  adjacency_iterator b = p.first;
  adjacency_iterator e = p.second;

    if(b != e) {
        ASSERT_EQ(vdB, *b);
    }
    ++b;
    if(b != e) {
        ASSERT_EQ(vdC, *b);
    }
    ++b;
    if(b != e) {
        ASSERT_EQ(vdF, *b);
    }
    ++b;
    if(b != e) {
        ASSERT_EQ(vdG, *b);
    }
    ++b;

    ASSERT_EQ(e, b);
}

TYPED_TEST(TestGraph, test_adjacent_vertices_5) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using adjacency_iterator = typename TestFixture::adjacency_iterator;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);
  vertex_descriptor vdD = add_vertex(g);
  vertex_descriptor vdE = add_vertex(g);
  vertex_descriptor vdF = add_vertex(g);
  vertex_descriptor vdG = add_vertex(g);

 add_edge(vdA, vdB, g);
 add_edge(vdA, vdC, g);
  
 add_edge(vdD, vdB, g);
 add_edge(vdD, vdC, g);
 add_edge(vdD, vdF, g);
 add_edge(vdD, vdG, g);
  
 add_edge(vdG, vdB, g);
 add_edge(vdG, vdC, g);
 add_edge(vdG, vdF, g);
 add_edge(vdG, vdA, g);

  pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
  adjacency_iterator b = p.first;
  adjacency_iterator e = p.second;
    ASSERT_TRUE(e == ++++b);
}

TYPED_TEST(TestGraph, test_adjacent_vertices_6) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using adjacency_iterator = typename TestFixture::adjacency_iterator;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);
  vertex_descriptor vdD = add_vertex(g);
  vertex_descriptor vdE = add_vertex(g);
  vertex_descriptor vdF = add_vertex(g);
  vertex_descriptor vdG = add_vertex(g);

 add_edge(vdA, vdB, g);
 add_edge(vdA, vdC, g);
 add_edge(vdA, vdF, g);
 add_edge(vdA, vdG, g);
  
 add_edge(vdD, vdB, g);
 add_edge(vdD, vdC, g);
 add_edge(vdD, vdF, g);
 add_edge(vdD, vdG, g);
  
 add_edge(vdG, vdB, g);
 add_edge(vdG, vdC, g);
 add_edge(vdG, vdF, g);
 add_edge(vdG, vdA, g);

  pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdG, g);
  adjacency_iterator b = p.first;
    ASSERT_EQ(vdA, * b);
}

TYPED_TEST(TestGraph, test_adjacent_vertices_7) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using adjacency_iterator = typename TestFixture::adjacency_iterator;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);
  vertex_descriptor vdD = add_vertex(g);
  vertex_descriptor vdE = add_vertex(g);
  vertex_descriptor vdF = add_vertex(g);
  vertex_descriptor vdG = add_vertex(g);

 add_edge(vdA, vdB, g);
 add_edge(vdA, vdC, g);
 add_edge(vdA, vdF, g);
 add_edge(vdA, vdG, g);
  
 add_edge(vdD, vdB, g);
 add_edge(vdD, vdC, g);
 add_edge(vdD, vdF, g);
 add_edge(vdD, vdG, g);
  
 add_edge(vdG, vdB, g);
 add_edge(vdG, vdC, g);
 add_edge(vdG, vdF, g);
 add_edge(vdG, vdA, g);

 vertex_descriptor vdH = add_vertex(g);
  pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdC, g);
  adjacency_iterator b = p.first;
  adjacency_iterator e = p.second;
    ASSERT_TRUE(e == b);
}

TYPED_TEST(TestGraph, test_adjacent_vertices_8) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using adjacency_iterator = typename TestFixture::adjacency_iterator;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);
  vertex_descriptor vdD = add_vertex(g);
  vertex_descriptor vdE = add_vertex(g);
  vertex_descriptor vdF = add_vertex(g);
  vertex_descriptor vdG = add_vertex(g);

 add_edge(vdA, vdB, g);
 add_edge(vdA, vdC, g);
 add_edge(vdA, vdF, g);
 add_edge(vdA, vdG, g);
  
 add_edge(vdD, vdB, g);
 add_edge(vdD, vdC, g);
 add_edge(vdD, vdF, g);
 add_edge(vdD, vdG, g);
  
 add_edge(vdG, vdB, g);
 add_edge(vdG, vdC, g);
 add_edge(vdG, vdF, g);
 add_edge(vdG, vdA, g);

  pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdC, g);
  adjacency_iterator b = p.first;
  adjacency_iterator e = p.second;
    ASSERT_TRUE(e == b);

    add_edge(vdC, vdG, g);
  pair<adjacency_iterator, adjacency_iterator> p2 = adjacent_vertices(vdC, g);
  adjacency_iterator b2 = p2.first;
  adjacency_iterator e2 = p2.second;
    ASSERT_NE(e2, b2);
}

// ------
// source
// ------

TYPED_TEST(TestGraph, test_source) {
    using graph_type = typename TestFixture::graph_type;
    using vertex_descriptor = typename TestFixture::vertex_descriptor;
    using edge_descriptor = typename TestFixture::edge_descriptor;

    graph_type g;
  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);

 edge_descriptor edAB = add_edge(vdA, vdB, g).first;
 edge_descriptor adAC = add_edge(vdA, vdC, g).first;

 ASSERT_EQ(2, num_edges(g));
    vertex_descriptor x = source(edAB, g);
    ASSERT_EQ(vdA, x);
}

// ------
// target
// ------

TYPED_TEST(TestGraph, test_target) {

    using graph_type = typename TestFixture::graph_type;
    using vertex_descriptor = typename TestFixture::vertex_descriptor;
    using edge_descriptor = typename TestFixture::edge_descriptor;

    graph_type g;
  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);

 edge_descriptor edAB = add_edge(vdA, vdB, g).first;
 edge_descriptor adAC = add_edge(vdA, vdC, g).first;

 ASSERT_EQ(2, num_edges(g));
    vertex_descriptor x = target(edAB, g);
    ASSERT_EQ(vdB, x);
}


//----------
// num_edges
//----------

TYPED_TEST(TestGraph, test_num_edges) {
  using graph_type = typename TestFixture::graph_type;
  using vertex_descriptor = typename TestFixture::vertex_descriptor;
  using edges_size_type = typename TestFixture::edges_size_type;

  graph_type g;

  vertex_descriptor vdA = add_vertex(g);
  vertex_descriptor vdB = add_vertex(g);
  vertex_descriptor vdC = add_vertex(g);
  vertex_descriptor vdD = add_vertex(g);
  vertex_descriptor vdE = add_vertex(g);
  vertex_descriptor vdF = add_vertex(g);
  vertex_descriptor vdG = add_vertex(g);

  edges_size_type n = num_edges(g);
 ASSERT_EQ(0, n); 

 add_edge(vdA, vdB, g);
 add_edge(vdA, vdC, g);
 add_edge(vdA, vdF, g);
 add_edge(vdA, vdG, g);
  
 add_edge(vdD, vdB, g);
 add_edge(vdD, vdC, g);
 add_edge(vdD, vdF, g);
 add_edge(vdD, vdG, g);
  
 add_edge(vdG, vdB, g);
 add_edge(vdG, vdC, g);
 add_edge(vdG, vdF, g);
 add_edge(vdG, vdA, g);

  n = num_edges(g);
    ASSERT_EQ(12, n);
}


