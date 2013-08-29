#pragma once
#include <map>
#include <string>

template <typename R>
class ResourceManager {
protected:
	std::map<std::string, R*> store;
	virtual R *load_from_file(std::string filename) = 0;
	virtual void dispose(R *resource) = 0;
	ResourceManager();
	virtual ~ResourceManager();
public:
	R *get(std::string which);
	void clear();
};

template <typename R> ResourceManager<R>::ResourceManager(void)
{
}


template <typename R> ResourceManager<R>::~ResourceManager(void)
{
}

template <typename R> R *ResourceManager<R>::get(std::string filename) {
	if(filename == "") {
		return NULL;
	}
	R *item = NULL;
	try {
		item = store.at(filename);
	} catch(std::out_of_range e) {
		item = load_from_file(filename);
		if(item == NULL) {
			return NULL;
		}
		store[filename] = item;
	}
	return item;
}

template <typename R> void ResourceManager<R>::clear() {
	for(auto p : store) {
		delete p.second;
	}
	store.clear();
}