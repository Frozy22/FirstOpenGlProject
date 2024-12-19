#include "ServiceLocator.h"

ServiceLocator* ServiceLocator::instance = nullptr;

ServiceLocator* ServiceLocator::GetInstance()
{
	return instance;
}

ServiceLocator::ServiceLocator()
{
	if (instance != nullptr)
		throw "EVENTS::INITIALIZE::INSTANCE_NOT_NULL";

	instance = this;
}

ServiceLocator::~ServiceLocator()
{
	for (auto const& [key, service] : services)
	{
		service->Terminate();
	}

	services.clear();
}
