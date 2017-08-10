// ---------------------------------------------------------------------
//
// Copyright (C) 2001 - 2015 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE at
// the top level of the deal.II distribution.
//
// ---------------------------------------------------------------------


// like matrix_out.cc, but test for Trilinos matrices
//
// also test some of the other options of the MatrixOut::Options class


#include "../tests.h"
#include <deal.II/lac/matrix_out.h>
#include <deal.II/lac/trilinos_sparse_matrix.h>

int main (int argc, char **argv)
{
  Utilities::MPI::MPI_InitFinalize mpi_initialization (argc, argv, testing_max_num_threads());

  std::ofstream logfile("output");
  deallog << std::fixed;
  deallog << std::setprecision(2);
  deallog.attach(logfile);
  deallog.threshold_double(1.e-10);

  // test for a rectangular sparse
  // matrix
  if (true)
    {
      TrilinosWrappers::SparsityPattern sparsity (4,8,7);
      for (unsigned int i=0; i<4; ++i)
        for (unsigned int j=0; j<8; ++j)
          if (i==j+1)
            sparsity.add (i,j);
      sparsity.compress ();

      TrilinosWrappers::SparseMatrix sparse_matrix(sparsity);
      for (unsigned int i=0; i<4; ++i)
        for (unsigned int j=0; j<8; ++j)
          if (i==j+1)
            sparse_matrix.set(i,j, i+3*j);

      MatrixOut matrix_out;
      matrix_out.build_patches (sparse_matrix, "sparse_matrix",
                                MatrixOut::Options (true, 1, true));
      matrix_out.write_gnuplot (logfile);
    }
}
