#include <iostream>
#include "Playlist.h"
using namespace std;

Playlist::Playlist() {
	init();
}

Playlist::~Playlist() {
	eraseList(head);
	cout << "\n>>> Playlist destructor called <<<\n";
}

int Playlist::getNodeCount() {
	int count = 0;
	SongNode* currNode = head;

	
	if (currNode == nullptr) { //list is empty
		return count;
	}

	while (currNode != nullptr) { //count number of nodes
		count = count + 1;
		currNode = currNode->getNext();
	}

	return count;
}

void Playlist::insertFront(SongNode* songNode) {
	if (head == nullptr) { //nothing in linked list
		head = songNode;
	}
	else {
		songNode->setNext(head);
		head = songNode;
	}
}

bool Playlist::remove(string id) {
	
	if (!contains(id)) { //not in playlist
		return false;
	}

	SongNode* prev = head;
	SongNode* curr = head;

	while (curr->getUniqueID() != id) { //find node before chosen id
		prev = curr;
		curr = curr->getNext();
	}


	if (curr == head) { //the chosen id is the head
		head = curr->getNext();
		delete curr;
	}
	else { //make the previous' node next pointer point to what curr is currently pointing to
		
		prev->setNext(curr->getNext());
		delete curr;
	}

	return true;
}

void Playlist::changeSongPosition(int songPosition, int newPosition) {
	SongNode* curr = head;
	int pos = 1;

	while (curr != nullptr) { //Find songNode that is at songPosition
		if (pos == songPosition) {
			break;
		}
		pos = pos + 1;
		curr = curr->getNext();
	}

	//Remove songNode at songPosition from list
	if (songPosition == 1) {
		head = curr->getNext();
	}
	else {
		SongNode* prevOrig = head;
		int i = 1;

		while (prevOrig != nullptr && i < songPosition - 1) {
			prevOrig = prevOrig->getNext();
			i = i + 1;
		}
		
		prevOrig->setNext(curr->getNext());
	}

	//Insert song at newPosition
	if (newPosition == 1) {
		curr->setNext(head);
		head = curr;
	}
	else {
		SongNode* prevNew = head;
		int i = 1;

		while (i < newPosition - 1) {
			prevNew = prevNew->getNext();
			i = i + 1;
		}

		insertAfter(prevNew, curr);

	}
}

void Playlist::insertAfter(SongNode* prevNode, SongNode* newNode) {
	
	if (prevNode != nullptr) {
		newNode->setNext(prevNode->getNext());
		prevNode->setNext(newNode);
	}

}

int Playlist::getTotalTime() {
	int totalTime = 0;
	SongNode* curr = head;


	if (curr == nullptr) {
		return totalTime;
	}

	while (curr != nullptr) { 
		totalTime = totalTime + curr->getSongLength();
		curr = curr->getNext();
	}

	return totalTime;
}

void Playlist::printPlaylist() {
	SongNode* curr = head;
	int pos = 1;

	if (curr == nullptr) {
		printTableHeadings();
		cout << "\n\t>>> Playlist is empty! <<<\n";
	}
	else {
		printTableHeadings();
		while (curr != nullptr) {
			printTableRow(curr, pos);
			pos = pos + 1;
			curr = curr->getNext();
		}
	}
}

void Playlist::printByArtist(string artist) {
	SongNode* curr = head;
	int pos = 1;

	printTableHeadings();
	while (curr != nullptr) {
		if (curr->getArtistName() == artist) {
			printTableRow(curr, pos);
		}
		pos = pos + 1;
		curr = curr->getNext();
	}
}

bool Playlist::contains(const string& id) {
	SongNode* curr = head;

	while (curr != nullptr) {
		if (curr->getUniqueID() == id) {
			return true;
		}
		curr = curr->getNext();
	}

	return false;

}

void Playlist::clearList() {
	eraseList(head);
	init();
}

void Playlist::init() {
	head = nullptr;
	nodeCount = 0;
}

void Playlist::eraseList(SongNode* head) {
	SongNode* curr = head;
	SongNode* succ = nullptr;

	while (curr != nullptr) {
		succ = curr->getNext();
		delete curr;
		curr = succ;
	}
}

void Playlist::printTableHeadings() {
	cout << "\n\t------------------------- PLAYLIST ------------------------------" << endl;
	cout << "\t" << setw(5) << left << "Pos  ";
	cout << setw(12) << left << "Unique Id";
	cout << setw(20) << left << "Song";
	cout << setw(20) << left << "Artist";
	cout << setw(4) << left << "Time" << endl;
}

void Playlist::printTableRow(SongNode* song, int position) {
	cout << "\t" << setw(5) << left << position;
	cout << setw(12) << left << song->getUniqueID();
	cout << setw(20) << left << song->getSongName();
	cout << setw(20) << left << song->getArtistName();
	cout << setw(4) << right << song->getSongLength() << endl;
}
