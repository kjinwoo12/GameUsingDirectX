#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <conio.h>

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <list>
#include <deque>
#include <vector>
using namespace std;

struct VertexType {
	float x, y, z;
};

struct FaceType {
	int
		v1, v2, v3,
		t1, t2, t3,
		n1, n2, n3;
};

template<typename Out> void split(const string str, char delim, Out result) {
	stringstream ss(str);
	string item;
	while (getline(ss, item, delim)) *(result++) = item;
}

deque<string> split(const string str, const char delim) {
	deque<string> list;
	split(str, delim, back_inserter(list));

	return list;
}

int main() {
	FILE *file;

	file = fopen("../3dmodel/test.obj", "r");
	char chStr[512] = { 0, };

	deque<VertexType> vertexList, texcoordList, normalList;
	deque<FaceType> faceList;

	while (1) {
		fgets(chStr, 512, file);
		if (feof(file)) break;
		string str(chStr);
		deque<string> splitedStr = split(str, ' ');
		string firstWord = splitedStr.front();
		splitedStr.pop_front();

		if (firstWord.compare("v") == 0) {
			VertexType vertexType;
			vertexType.x = atof(splitedStr.front().c_str());
			splitedStr.pop_front();
			vertexType.y = atof(splitedStr.front().c_str());
			splitedStr.pop_front();
			vertexType.z = atof(splitedStr.front().c_str()) * -1.0f;
			splitedStr.pop_front();
			vertexList.push_back(vertexType);
		} else if (firstWord.compare("vt") == 0) {
			VertexType vertexType;
			vertexType.x = atof(splitedStr.front().c_str());
			splitedStr.pop_front();
			vertexType.y = 1.0f - atof(splitedStr.front().c_str());
			splitedStr.pop_front();
			texcoordList.push_back(vertexType);
		} else if (firstWord.compare("vn") == 0) {
			VertexType vertexType;
			vertexType.x = atof(splitedStr.front().c_str());
			splitedStr.pop_front();
			vertexType.y = 1.0f - atof(splitedStr.front().c_str());
			splitedStr.pop_front();
			vertexType.z = atof(splitedStr.front().c_str()) * -1.0f;
			splitedStr.pop_front();
			normalList.push_back(vertexType);
		} else if (firstWord.compare("f") == 0) {
			FaceType faceType;
			deque<string> splitedPos;
			string posStr;

			splitedPos = split(splitedStr.front(), '/');
			splitedStr.pop_front();
			posStr = splitedPos.front();
			faceType.v1 = (posStr.compare("") == 0) ? 0 : stoi(posStr);
			splitedPos.pop_front();
			posStr = splitedPos.front();
			faceType.t1 = (posStr.compare("") == 0) ? 0 : stoi(posStr);
			splitedPos.pop_front();
			posStr = splitedPos.front();
			faceType.n1 = (posStr.compare("") == 0) ? 0 : stoi(posStr);
			splitedPos.pop_front();

			splitedPos = split(splitedStr.front(), '/');
			splitedStr.pop_front();
			posStr = splitedPos.front();
			faceType.v2 = (posStr.compare("") == 0) ? 0 : stoi(posStr);
			splitedPos.pop_front();
			posStr = splitedPos.front();
			faceType.t2 = (posStr.compare("") == 0) ? 0 : stoi(posStr);
			splitedPos.pop_front();
			posStr = splitedPos.front();
			faceType.n2 = (posStr.compare("") == 0) ? 0 : stoi(posStr);
			splitedPos.pop_front();

			splitedPos = split(splitedStr.front(), '/');
			splitedStr.pop_front();
			posStr = splitedPos.front();
			faceType.v3 = (posStr.compare("") == 0) ? 0 : stoi(posStr);
			splitedPos.pop_front();
			posStr = splitedPos.front();
			faceType.t3 = (posStr.compare("") == 0) ? 0 : stoi(posStr);
			splitedPos.pop_front();
			posStr = splitedPos.front();
			faceType.n3 = (posStr.compare("") == 0) ? 0 : stoi(posStr);
			splitedPos.pop_front();

			faceList.push_back(faceType);
		} else {
			continue;
		}
	}
	fclose(file);

	int faceIndex = faceList.size();
	int vIndex, tIndex, nIndex;
	file = fopen("model.txt", "w");
	fprintf(file, "Vertex Count: %d\n\nData:\n\n", faceIndex * 3);
	for (int i = 0; i < faceIndex; i++) {
		FaceType faceType = faceList.front();
		faceList.pop_front();

		vIndex = faceType.v1 - 1;
		tIndex = faceType.t1 - 1;
		nIndex = faceType.n1 - 1;
		if (vIndex == -1) {
			fprintf(file, "0 0 0 ");
		} else {
			fprintf(file, "%f %f %f ", vertexList[vIndex].x, vertexList[vIndex].y, vertexList[vIndex].z);
		}
		if (tIndex == -1) {
			fprintf(file, "0 0 ");
		} else {
			fprintf(file, "%f %f ", texcoordList[tIndex].x, texcoordList[tIndex].y);
		}
		if (nIndex == -1) {
			fprintf(file, "0 0 0\n");
		} else {
			fprintf(file, "%f %f %f\n", vertexList[nIndex].x, vertexList[nIndex].y, vertexList[nIndex].z);
		}

		vIndex = faceType.v2 - 1;
		tIndex = faceType.t2 - 1;
		nIndex = faceType.n2 - 1;
		if (vIndex == -1) {
			fprintf(file, "0 0 0 ");
		} else {
			fprintf(file, "%f %f %f ", vertexList[vIndex].x, vertexList[vIndex].y, vertexList[vIndex].z);
		}
		if (tIndex == -1) {
			fprintf(file, "0 0 ");
		} else {
			fprintf(file, "%f %f ", texcoordList[tIndex].x, texcoordList[tIndex].y);
		}
		if (nIndex == -1) {
			fprintf(file, "0 0 0\n");
		} else {
			fprintf(file, "%f %f %f\n", vertexList[nIndex].x, vertexList[nIndex].y, vertexList[nIndex].z);
		}

		vIndex = faceType.v3 - 1;
		tIndex = faceType.t3 - 1;
		nIndex = faceType.n3 - 1;
		if (vIndex == -1) {
			fprintf(file, "0 0 0 ");
		} else {
			fprintf(file, "%f %f %f ", vertexList[vIndex].x, vertexList[vIndex].y, vertexList[vIndex].z);
		}
		if (tIndex == -1) {
			fprintf(file, "0 0 ");
		} else {
			fprintf(file, "%f %f ", texcoordList[tIndex].x, texcoordList[tIndex].y);
		}
		if (nIndex == -1) {
			fprintf(file, "0 0 0\n");
		} else {
			fprintf(file, "%f %f %f\n", vertexList[nIndex].x, vertexList[nIndex].y, vertexList[nIndex].z);
		}
	}
	fclose(file);


	printf("end");
	_getch();
	return 0;
}