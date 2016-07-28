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

    defaultConf.setToDefault();
    defaultConf.set(el::Level::Debug, el::ConfigurationType::Format, "[%level] (%fbase:%line) %msg");
    defaultConf.set(el::Level::Debug, el::ConfigurationType::Enabled, "false");
    el::Loggers::reconfigureLogger("mesh", defaultConf);

    defaultConf.setToDefault();
    defaultConf.set(el::Level::Info, el::ConfigurationType::Enabled, "true");
    el::Loggers::reconfigureLogger("performance", defaultConf);

    defaultConf.setToDefault();
    defaultConf.set(el::Level::Info, el::ConfigurationType::Enabled, "true");
    defaultConf.set(el::Level::Debug, el::ConfigurationType::Format, "[%level] (%fbase:%line) %msg");
    el::Loggers::reconfigureLogger("default", defaultConf);

    // el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Enabled, "false");
}