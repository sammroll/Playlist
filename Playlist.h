#ifndef __PLAYLIST__
#define __PLAYLIST__
#include <iostream>
#include "SongNode.h"
using namespace std;

class Playlist {
public:
	Playlist();

	~Playlist();

	int getNodeCount();

	void insertFront(SongNode* songNode);

	bool remove(string id);

	void changeSongPosition(int songPosition, int newPosition);

	void insertAfter(SongNode* prevNode, SongNode* newNode);

	int getTotalTime();

	void printPlaylist();

	void printByArtist(string artist);

	bool contains(const string& id);

	void clearList();

private:
	void init();

	void eraseList(SongNode* head);

	void printTableHeadings();

	void printTableRow(SongNode* song, int position);

	SongNode* head = nullptr;
	int nodeCount = 0;
};
#endif

