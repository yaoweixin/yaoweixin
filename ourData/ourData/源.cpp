#include<iostream>
#include<cmath>
#include<ctime>
#include<stdlib.h>
#include<algorithm>

using namespace std;

const int N = 90;
const int Max = 40000;
const int Min = 10000;
const float Div = 10000;
const int TopNum = 8;
const int DownNum = 5;
const int FleeNum = 16;
const int ChooseNum = 10;
int breakNum;
int kuangNum;
int FleePeople[10];
float RightChoose;
float AllChoose;

class data {
public:
	float score;
	bool situation[21];
	
};


struct Info {
	float score;
	bool situation[21];
	float poss;
	bool isEighty;
}AllInfo[1000];

void InitScore() {
	for (int index = 0; index < N; index++) {
		AllInfo[index].score = (rand() % (Max - Min) + Min) / Div;
		//cout << AllInfo[index].score << endl;
		AllInfo[index].poss = 0.05*(1 - AllInfo[index].score / 4);
	}
}

void ChooseFlee() {
	kuangNum = rand() % (TopNum - DownNum) + DownNum;
	int tempFlee = kuangNum;

	while (tempFlee != 0) {
		int index = rand() % (50);
		if (AllInfo[index].isEighty != true) {
			FleePeople[kuangNum - tempFlee] = index;
			tempFlee--;
			AllInfo[index].isEighty = true;
			cout << index << endl;
		}
	}
}

void ExecFlee() {
	for (int i = 0; i < kuangNum; i++) {
		int tempNum = FleeNum;
		while (tempNum != 0) {
			int index = rand() % 20 + 1;
			if (AllInfo[FleePeople[i]].situation[index] != true) {
				AllInfo[FleePeople[i]].situation[index] = true;
				tempNum--;
			}
		}
	}
}

void BreakFlee() {
	breakNum = rand() % 4;
	for (int i = 0; i < N; i++) {
		int tempNum = breakNum;
		while (tempNum != 0) {
			int index = rand() % N;
			if (AllInfo[index].situation[i] != true) {
				AllInfo[index].situation[i] = true;
				tempNum--;
			}

		}
	}
}

void Output() {
	for (int i = 0; i < N; i++) {
		cout << AllInfo[i].score << " " << AllInfo[i].poss << " ";
		for (int j = 1; j <= 20; j++)cout << AllInfo[i].situation[j] << " ";
		cout << endl;
	}
}

void Update(int j) {
	for (int i = 0; i < ChooseNum; i++) {
		if (AllInfo[i].situation[j] == true) {
			RightChoose++;
			AllInfo[i].poss += 0.005;
		}
		else {
			AllInfo[i].poss -= 0.005;
		}
		AllChoose++;
	}
}

bool cmp(Info a, Info b) {
	return a.poss > b.poss;
}

int main() {

	InitScore();
	sort(AllInfo, AllInfo + N, cmp);

	ChooseFlee();
	ExecFlee();
	BreakFlee();

	Output();

	for (int i = 1; i <= 20; i++) {
		Update(i);
		sort(AllInfo, AllInfo + N, cmp);
	}

	cout << RightChoose / AllChoose << endl;//Êä³öE
	cout << AllChoose << endl;

	return 0;

}