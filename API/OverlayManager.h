#pragma once
#include <memory>
#include <mutex>

#include "OverlayElement.h"

class OverlayManager
{
public:
	static OverlayManager &GetInstance();

	void PresentProxy();
	void ResetProxy();

	template<typename T>
	std::shared_ptr<T> CreateElement(int clientId);

	template<typename T>
	std::shared_ptr<T> GetElementById(int clientId, int id);

	void RemoveElement(int clientId, int id);
	void Cleanup(int clientId);
private:
	std::mutex _elementMutex;
	int _idCounter;
	std::vector<std::shared_ptr<OverlayElement>> _elements;

	OverlayManager();
	~OverlayManager();
};

template<typename T>
inline std::shared_ptr<T> OverlayManager::CreateElement(int clientId)
{
	std::lock_guard<std::mutex> guard(_elementMutex);

	auto element = std::make_shared<T>(clientId, ++_idCounter);
	_elements.push_back(element);
	return element;
}

template<typename T>
inline std::shared_ptr<T> OverlayManager::GetElementById(int clientId, int id)
{
	std::lock_guard<std::mutex> guard(_elementMutex);

	for (size_t i = 0; i < _elements.size(); i++)
	{
		auto element = _elements[i];

		if (element->GetId() == id && element->GetClientId() == clientId && !element->IsRemoved())
		{
			std::shared_ptr<T> castedElement = std::dynamic_pointer_cast<T>(element);
			return castedElement;
		}
	}

	return std::shared_ptr<T>();
}
