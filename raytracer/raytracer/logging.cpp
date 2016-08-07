#include "logging.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

void logging::configure()
{
    el::Configurations defaultConf;

    defaultConf.setToDefault();
    defaultConf.set(el::Level::Info, el::ConfigurationType::Enabled, "true");
    el::Loggers::reconfigureLogger("performance", defaultConf);

    defaultConf.setToDefault();
    defaultConf.set(el::Level::Info, el::ConfigurationType::Enabled, "true");
    defaultConf.set(el::Level::Debug, el::ConfigurationType::Format, "[%level] (%fbase:%line) %msg");
    el::Loggers::reconfigureLogger("default", defaultConf);
}

void logging::quiet()
{
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Enabled, "false");
}