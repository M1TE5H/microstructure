#include <cassert>

#include <iostream>

#include <xmicrostructure/xmicrostructure.hpp>

int xmicrostructure_test() {

  {

    xmicrostructure::tensor<float, xmicrostructure::rank::tensor2,
                            xmicrostructure::dimension::two>
        distortion;

    assert(sizeof(distortion) == 4 * sizeof(float));

	std::cout << distortion << '\n';
  }

  return EXIT_SUCCESS;
}

int main() {
	std::cout << "xmicrostructure | test suite\n";
	return xmicrostructure_test();
	}