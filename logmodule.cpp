#include "logmodule.h"

LogModule * LogModule::logModule = NULL;

LogModule::LogModule(QObject *parent) : QObject(parent)
{

}

LogModule * LogModule::getInstance()
{
    if(logModule == NULL){
        logModule = new LogModule();
    }
    return logModule;
}

LogModule::~LogModule()
{
    delete logModule;
}
