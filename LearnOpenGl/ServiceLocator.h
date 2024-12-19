#pragma once
#include <map>
#include <string>
#include "IService.h"
#include <typeinfo>

using namespace std;

class ServiceLocator
{
private:
	static ServiceLocator* instance;

	map<size_t, IService*> services;

public:
	static ServiceLocator* GetInstance();

	ServiceLocator();

	template <class T, class TInstance>
	void Register()
	{
		auto service = dynamic_cast<IService*>(new TInstance());
		services[typeid(T).hash_code()] = service;
	}

	template <class T>
	void RegisterInstance(T* instance)
	{
		auto service = dynamic_cast<IService*>(instance);
		services[typeid(T).hash_code()] = service;
	}
	
	template <class T>
	void UnRegisterService()
	{
		auto service = services[typeid(T).hash_code()];
		service->Terminate();
		services.erase(typeid(T).hash_code());
	}
	
	template <class T>
	T* Resolve() 
	{
		return dynamic_cast<T*>(services[typeid(T).hash_code()]);
	}

	~ServiceLocator();
};


