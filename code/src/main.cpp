/**
 * @file
 * Main driver for suite of regret minimisation algorithms
 */

#include <iostream>
#include <boost/program_options.hpp> // for handling input arguments
#include <chrono>                    // for timing

#include "k-regret/common/hello-world.h"

int main( int argc, char** argv)
{
  std::cout << Util::hi_string << std::endl;
	return 0;
}
