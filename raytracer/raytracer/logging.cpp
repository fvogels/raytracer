#include "logging.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

void logging::configure()
{
	el::Configurations defaultConf;
	defaultConf.setToDefault();
	defaultConf.set(el::Level::Debug, el::ConfigurationType::Format, "[%level] (%fbase:%line) %msg");
	defaultConf.set(el::Level::Debug, el::ConfigurationType::Enabled, "false");
	el::Loggers::reconfigureLogger("stdlib", defaultConf);
}