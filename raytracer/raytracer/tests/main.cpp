#ifdef TEST_BUILD
#define CATCH_CONFIG_RUNNER
#include "Catch.h"
#include "easylogging++.h"
#include "logging.h"

int main(int argc, char* const argv[])
{
    logging::configure();

    Catch::ConfigData data;
    data.abortAfter = 5;  // Makes the tests stop running after 5 failures
    
    Catch::Session session;
    session.useConfigData(data);
    return session.run(argc, argv);
}

#endif
