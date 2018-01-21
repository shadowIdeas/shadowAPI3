#pragma once

struct Zone
{
	std::wstring name;
	float aX;
	float aY;
	float aZ;
	float bX;
	float bY;
	float bZ;
};

class ZoneManager
{
public:
	static ZoneManager & GetInstance();

	std::wstring FindZone(float x, float y, float z);
	std::wstring FindCity(float x, float y, float z);
private:
	std::vector<Zone> _cities;
	std::vector<Zone> _zones;

	ZoneManager();

	void AddCity(std::wstring name, float aX, float aY, float aZ, float bX, float bY, float bZ);
	void AddZone(std::wstring name, float aX, float aY, float aZ, float bX, float bY, float bZ);
};