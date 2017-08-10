// ---------------------------------------------------------------------
//
// Copyright (C) 2004 - 2015 by the deal.II authors
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



// certain comparisons between sparse matrix iterators didn't compile.

#include "../tests.h"
#include <deal.II/lac/trilinos_sparsity_pattern.h>
#include <deal.II/lac/sparsity_pattern.h>
#include <deal.II/lac/trilinos_sparse_matrix.h>


void test ()
{
  // create a sparsity pattern with totally
  // empty lines (not even diagonals, since
  // not quadratic)
  TrilinosWrappers::SparsityPattern sparsity(4,5,1);
  sparsity.add (1,1);
  sparsity.add (3,1);
  sparsity.compress ();

  // attach a sparse matrix to it
  TrilinosWrappers::SparseMatrix A(sparsity);

  TrilinosWrappers::SparseMatrix::iterator k = A.begin(),
                                           j = ++A.begin();

  AssertThrow (k < j, ExcInternalError());
  AssertThrow (j > k, ExcInternalError());

  AssertThrow (!(j < k), ExcInternalError());
  AssertThrow (!(k > j), ExcInternalError());

  AssertThrow (k != j, ExcInternalError());
  AssertThrow (!(k == j), ExcInternalError());

  AssertThrow (k == k, ExcInternalError());
  AssertThrow (!(k != k), ExcInternalError());

  deallog << "OK" << std::endl;
}



int main (int argc, char **argv)
{
  initlog();
  deallog.threshold_double(1.e-10);

  Utilities::MPI::MPI_InitFinalize mpi_initialization (argc, argv, testing_max_num_threads());

  try
    {
      test ();
    }
  catch (std::exception &exc)
    {
      deallog << std::endl << std::endl
              << "----------------------------------------------------"
              << std::endl;
      deallog << "Exception on processing: " << std::endl
              << exc.what() << std::endl
              << "Aborting!" << std::endl
              << "----------------------------------------------------"
              << std::endl;

      return 1;
    }
  catch (...)
    {
      deallog << std::endl << std::endl
              << "----------------------------------------------------"
              << std::endl;
      deallog << "Unknown exception!" << std::endl
              << "Aborting!" << std::endl
              << "----------------------------------------------------"
              << std::endl;
      return 1;
    };
}
