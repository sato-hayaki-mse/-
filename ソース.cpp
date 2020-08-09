#include <iostream>
#include <regex>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

//Studentクラス
class Student {

	string name;//名前
	int mexam = 0;//中間テスト
	int fexam = 0;//期末テスト
	int ppoint = 0;//平常点
//外部から操作するためのアクセッサ
public:
	void setName(const string& newName) { name = newName; }//名前
	void setMexam(int newMexam) { mexam = newMexam; }//中間テスト
	void setFexam(int newFexam) { fexam = newFexam; }//期末テスト
	void setPpoint(int newPpoint) { ppoint = newPpoint; }//平常点
//表示関数
	void show() {
		cout << "名前:" << name << "\t" << "中間テスト:" << mexam << "\t" << "期末テスト:" << fexam << "\t" << "平常点:" << ppoint << endl;
	}
//総合点を計算しファイルに書き込む関数
	auto f() {
		//Student.txtを作成し書き込む
		ofstream outfile("Student.txt", ios_base::app);
		double score = (mexam * 0.4) + (fexam * 0.4) + ppoint;//scoreの計算式
		double score1 = (mexam * 0.5) + (fexam * 0.5);//score1の計算式
			if (score > score1) {
				outfile << name << "\t" << score << endl;//scoreの方が大きい場合ファイルに書き込む
			}
			else if (score <= score1) {
				outfile << name << "\t" << score1 << endl;//score1の方が大きい場合ファイルに書き込む
			}
			outfile.close();//ファイルを閉じる
	}

};

//student1クラス
class Student1 {

public:
	string name;//名前
	double finalscore;//最終成績
	
public:
	void setName(const string& newName) { name = newName; }//名前
	string getName() { return name; }
	void setFscore(double newFscore) { finalscore = newFscore; }//最終成績
	double getFscore() { return finalscore; }

};

//文字列をカンマで区切りデータの入ったvectorを返す関数
vector<string> split(string& input, char delimiter) {

	istringstream stream(input);
	string field;
	vector<string>result;
	while (getline(stream, field, delimiter)) {
		result.push_back(field);
	}
	return result;
}
//ファイルを読み込みデータの入ったvectorを返す関数
auto readfile(string fileName) {
	vector<vector<string>>filedata;
	ifstream ifs(fileName);
	string str;

	while (getline(ifs, str)) {
		filedata.push_back(split(str, ','));
	}
	return filedata;
}
//オブジェクトを追加する関数
auto addStudentobject(vector<vector<string>>filedata) {
	vector<Student>v;

	for (size_t i = 0; i < filedata.size(); i++) {
		v.emplace_back();
		v[i].setName(filedata[i][0]);
		v[i].setMexam(stoi(filedata[i][1]));
		v[i].setFexam(stoi(filedata[i][2]));
		v[i].setPpoint(stoi(filedata[i][3]));
	}
	return v;
}
//表示処理を行う関数
void SHOW(vector<Student>v) {
	for (auto& p : v) {
		p.show();//メンバ関数show()の呼び出し
	}
}

//総合点を計算しファイルに書き込む関数
void F(vector<Student>v) {
	for (auto& p : v) {
		p.f();//メンバ関数f()の呼び出し
	}
}


int main() {
	vector<vector<string>>datav;//ファイルのデータを保持するvector
	datav = readfile("Student.csv");//ファイルを読み込みデータ入りのvectorを返す関数

	vector<Student>studentv;//空のvectorを用意する
	studentv = addStudentobject(datav);//オブジェクトを追加する関数
	cout << "テスト結果" << endl;

	SHOW(studentv);//表示処理
	F(studentv);//最終成績を計算しファイルに書き込む処理

	//classStudent1のvectorの構築
	vector<Student1>v;
	
	ifstream infile("Student.txt");//Student1.txtの読み込み
	string newName;
	double newFscore;

	int n = 0;

	while (infile >> newName >> newFscore ) {//データを読み込む
	
		v.emplace_back();
		//名前と最終成績を順番に格納
		v[n].setName(newName);
		v[n].setFscore(newFscore);
		n++;
	}
	//降順に並び替え
	sort(v.begin(), v.end(), [] (const auto & lhs, const auto & rhs) {
		return lhs.finalscore > rhs.finalscore;
	});
	//出力
	cout << "最終成績" << endl;
	for (const auto& Student1 : v) {
		cout << "名前:" << Student1.name << "\t" << "最終成績:" << Student1.finalscore << endl;
	}

	infile.close();//ファイルを閉じる
	
}