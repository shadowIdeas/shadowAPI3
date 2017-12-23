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
	std::shared_ptr<T> CreateElement();

	template<typename T>
	std::shared_ptr<T> GetElementById(int id);

	void RemoveElement(int id);
private:
	std::mutex _elementMutex;
	int _idCounter;
	std::vector<std::shared_ptr<OverlayElement>> _elements;

	OverlayManager();
	~OverlayManager();
};

template<typename T>
inline std::shared_ptr<T> OverlayManager::CreateElement()
{
	std::lock_guard<std::mutex> guard(_elementMutex);

	auto element = std::make_shared<T>(++_idCounter);
	_elements.push_back(element);
	return element;
}

template<typename T>
inline std::shared_ptr<T> OverlayManager::GetElementById(int id)
{
	std::lock_guard<std::mutex> guard(_elementMutex);

	for (size_t i = 0; i < _elements.size(); i++)
	{
		auto element = _elements[i];

		if (element->GetId() == id)
		{
			std::shared_ptr<T> castedElement = std::dynamic_pointer_cast<T>(element);
			return castedElement;
		}
	}

	return std::shared_ptr<T>();
}
