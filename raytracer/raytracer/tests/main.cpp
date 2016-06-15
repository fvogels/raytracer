#ifdef TEST_BUILD
#define CATCH_CONFIG_RUNNER
#include "Catch.h"
#include "easylogging++.h"

int main(int argc, char* const argv[])
{
	el::Configurations defaultConf;
	defaultConf.setToDefault();
	defaultConf.set(el::Level::Debug, el::ConfigurationType::Format, "[%level] (%fbase:%line) %msg");
	el::Loggers::reconfigureLogger("stdlib", defaultConf);

	return Catch::Session().run(argc, argv);
}

#endif
