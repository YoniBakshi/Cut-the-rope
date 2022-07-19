#include <cstdlib>
#include "Controller.h"

int main() try
{
    auto c = Controller();
    c.run();

	return EXIT_SUCCESS;
}
catch (std::exception& ex)
{
    std::cerr << "Exception: " << ex.what() << '\n';
    return EXIT_FAILURE;
}
catch (...)
{
    std::cerr << "Unknown exception\n";
    return EXIT_FAILURE;
}