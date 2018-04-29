#pragma once
#include "Room.h"
#include "Hallway.h"
#include "Texture.h"
#include "Light.h"

class RoomGen : public Mesh {
public:
	RoomGen(std::vector<Light>* lights);
	~RoomGen();

	glm::vec3 getRandomRoomPosition();
	std::vector<BoundingBox> getBoundingBox();
	static const float ROOM_HEIGHT;
private:
	struct Connection {
		Room* first;
		Room* second;
		Hallway* hallway;
	};

	MeshManager manager;

	std::vector<Room*> rooms; //store generated rooms
	std::vector<Connection> connections; //store connections between rooms
	
	void addHallways();
	Room* getClosestRoom(Room);
	float getDistanceBetween(Room, Room);

	void connect(Room* r1, Room* r2);
	void connectHorizontally(Room* r1, Room* r2);
	void connectVertically(Room* r1, Room* r2);
	void connectIndirectly(Room* r1, Room* r2);
	void connectIndirectlyHorizontalFirst(Room* r1, Room* r2);
	void connectIndirectlyVerticalFirst(Room* r1, Room* r2);
	bool canConnectHorizontally(Room, Room);
	bool canConnectVertically(Room, Room);

	bool areConnected(Room*, Room*);

	void removeFromVector(std::vector<Room*>&, Room*);

	float MIN_TUNNEL_WIDTH = 1.5f;	//minimum width for a hallway

	std::vector<Room*> findBiggestNetwork();
	std::vector<Room*> getAdjacentRooms(Room*);
};

