#include "InstanceManager.h"
InstanceManager::InstanceManager(){}
ErrorHandler* InstanceManager::handler=new ErrorHandler();
InstanceManager* InstanceManager::manager=new InstanceManager();
