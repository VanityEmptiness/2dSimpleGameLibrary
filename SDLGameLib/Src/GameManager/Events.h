#pragma once
#include "../../Vendors/Include/SDL/SDL.h"

#include <functional>
#include <vector>

class EventDispatcher
{
public:
	std::vector<std::function<void(const SDL_Event&)>> _on_event_dispatch_functions_list;

	inline void AddListener(std::function<void(const SDL_Event&)> callback)
	{
		this->_on_event_dispatch_functions_list.push_back(callback);
	}

	inline void _Dispatch(const SDL_Event& _event)
	{
		for (const auto& callback : this->_on_event_dispatch_functions_list)
			callback(_event);
	}

};

inline EventDispatcher* event_handler = new EventDispatcher();
