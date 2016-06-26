#ifdef TEST_BUILD
#define CATCH_CONFIG_RUNNER
#include "Catch.h"
#include "easylogging++.h"
#include "logging.h"

int main(int argc, char* const argv[])
{
    logging::configure();

    return Catch::Session().run(argc, argv);
}

#endif
