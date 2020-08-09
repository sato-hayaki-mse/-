#include <iostream>
#include <regex>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

//Student�N���X
class Student {

	string name;//���O
	int mexam = 0;//���ԃe�X�g
	int fexam = 0;//�����e�X�g
	int ppoint = 0;//����_
//�O�����瑀�삷�邽�߂̃A�N�Z�b�T
public:
	void setName(const string& newName) { name = newName; }//���O
	void setMexam(int newMexam) { mexam = newMexam; }//���ԃe�X�g
	void setFexam(int newFexam) { fexam = newFexam; }//�����e�X�g
	void setPpoint(int newPpoint) { ppoint = newPpoint; }//����_
//�\���֐�
	void show() {
		cout << "���O:" << name << "\t" << "���ԃe�X�g:" << mexam << "\t" << "�����e�X�g:" << fexam << "\t" << "����_:" << ppoint << endl;
	}
//�����_���v�Z���t�@�C���ɏ������ފ֐�
	auto f() {
		//Student.txt���쐬����������
		ofstream outfile("Student.txt", ios_base::app);
		double score = (mexam * 0.4) + (fexam * 0.4) + ppoint;//score�̌v�Z��
		double score1 = (mexam * 0.5) + (fexam * 0.5);//score1�̌v�Z��
			if (score > score1) {
				outfile << name << "\t" << score << endl;//score�̕����傫���ꍇ�t�@�C���ɏ�������
			}
			else if (score <= score1) {
				outfile << name << "\t" << score1 << endl;//score1�̕����傫���ꍇ�t�@�C���ɏ�������
			}
			outfile.close();//�t�@�C�������
	}

};

//student1�N���X
class Student1 {

public:
	string name;//���O
	double finalscore;//�ŏI����
	
public:
	void setName(const string& newName) { name = newName; }//���O
	string getName() { return name; }
	void setFscore(double newFscore) { finalscore = newFscore; }//�ŏI����
	double getFscore() { return finalscore; }

};

//��������J���}�ŋ�؂�f�[�^�̓�����vector��Ԃ��֐�
vector<string> split(string& input, char delimiter) {

	istringstream stream(input);
	string field;
	vector<string>result;
	while (getline(stream, field, delimiter)) {
		result.push_back(field);
	}
	return result;
}
//�t�@�C����ǂݍ��݃f�[�^�̓�����vector��Ԃ��֐�
auto readfile(string fileName) {
	vector<vector<string>>filedata;
	ifstream ifs(fileName);
	string str;

	while (getline(ifs, str)) {
		filedata.push_back(split(str, ','));
	}
	return filedata;
}
//�I�u�W�F�N�g��ǉ�����֐�
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
//�\���������s���֐�
void SHOW(vector<Student>v) {
	for (auto& p : v) {
		p.show();//�����o�֐�show()�̌Ăяo��
	}
}

//�����_���v�Z���t�@�C���ɏ������ފ֐�
void F(vector<Student>v) {
	for (auto& p : v) {
		p.f();//�����o�֐�f()�̌Ăяo��
	}
}


int main() {
	vector<vector<string>>datav;//�t�@�C���̃f�[�^��ێ�����vector
	datav = readfile("Student.csv");//�t�@�C����ǂݍ��݃f�[�^�����vector��Ԃ��֐�

	vector<Student>studentv;//���vector��p�ӂ���
	studentv = addStudentobject(datav);//�I�u�W�F�N�g��ǉ�����֐�
	cout << "�e�X�g����" << endl;

	SHOW(studentv);//�\������
	F(studentv);//�ŏI���т��v�Z���t�@�C���ɏ������ޏ���

	//classStudent1��vector�̍\�z
	vector<Student1>v;
	
	ifstream infile("Student.txt");//Student1.txt�̓ǂݍ���
	string newName;
	double newFscore;

	int n = 0;

	while (infile >> newName >> newFscore ) {//�f�[�^��ǂݍ���
	
		v.emplace_back();
		//���O�ƍŏI���т����ԂɊi�[
		v[n].setName(newName);
		v[n].setFscore(newFscore);
		n++;
	}
	//�~���ɕ��ёւ�
	sort(v.begin(), v.end(), [] (const auto & lhs, const auto & rhs) {
		return lhs.finalscore > rhs.finalscore;
	});
	//�o��
	cout << "�ŏI����" << endl;
	for (const auto& Student1 : v) {
		cout << "���O:" << Student1.name << "\t" << "�ŏI����:" << Student1.finalscore << endl;
	}

	infile.close();//�t�@�C�������
	
}