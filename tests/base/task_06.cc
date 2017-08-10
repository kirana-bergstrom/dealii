// ---------------------------------------------------------------------
//
// Copyright (C) 2009 - 2015 by the deal.II authors
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


// make sure we can start tasks from individual threads. this requires that a
// task scheduler object is running on each thread we create

#include "../tests.h"
#include <unistd.h>

#include <deal.II/base/thread_management.h>


void test (int i)
{
  deallog << "Task " << i << " starting..." << std::endl;
  sleep (1);
  if (i<10)
    {
      Threads::new_task (test, 10+i).join ();
    }
  deallog << "Task " << i << " finished!" << std::endl;
}




int main()
{
  std::ofstream logfile("output");
  deallog.attach(logfile);
  deallog.threshold_double(1.e-10);

  {
    Threads::Thread<> t1 = Threads::new_thread (test, 1);
    Threads::Thread<> t2 = Threads::new_thread (test, 2);

    t1.join ();
    t2.join ();

    deallog << "OK" << std::endl;
  }

  deallog.detach ();
  logfile.close ();
  sort_file_contents ("output");
}
