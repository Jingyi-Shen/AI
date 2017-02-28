//============================================================================
// Name        : AI_PRO.cpp
// Author      : sjy_14353260
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string.h>
#include <algorithm>
#include <cmath>
#include<fstream>
#include<sstream>
#include <time.h>
using namespace std;

#define SIZE_OF_TRAIN 30162//14//949//583//23//583//2
#define SIZE 13//��ȡ14-2��������+label
#define SIZE_OF_TEST 15060
vector<vector<string> > XX, XX2;
vector<vector<string> > X(SIZE_OF_TRAIN ,vector<string>(SIZE,"")); //��άvector����ʼ��Ϊ-1
vector<vector<string> > X2(SIZE_OF_TEST ,vector<string>(SIZE,"")); //��άvector����ʼ��Ϊ-1

void data_file(ifstream &f){ //��ȡѵ�������ݴ洢
	string s, title;
	getline(f,title);
	while(!f.eof()){
		vector<string> temp;
		for(int i=0;i<(SIZE+1);i++){
			getline(f, s, ','); //ÿ�ζ�ȡһ��
			//���ݼ�  ������
			//�����к͵�������Ϣ�ظ�  ����������
			//��ʮ���� ������Ϊ  native-country �޹��Խϴ�   ����
			if(i!=3&&i!=13)temp.push_back(s);
		}
		getline(f, s);
		temp.push_back(s);
		XX.push_back(temp);
	}
}

void data_file2(ifstream &f){ //��ȡ���Լ����ݴ洢
	string s, title;
	getline(f,title);
	while(!f.eof()){
		vector<string> temp;
		for(int i=0;i<(SIZE+1);i++){
			getline(f, s, ','); //ÿ�ζ�ȡһ��
			if(i!=3&&i!=13)temp.push_back(s);
		}
		getline(f, s);
		temp.push_back(s);
		XX2.push_back(temp);
	}
}

//�ַ���ת��Ϊ����
int stringToNum(const string& str){
    istringstream iss(str);
    int num;
    iss >> num;
    return num;
}

// �������� ����
void relationship_of_Edu_and_EduNum(){
	vector<string>  vec1;
	vector<string>::iterator it1;
	for(int i=0; i<SIZE_OF_TRAIN;i++){
		bool flag=true;
		for(it1=vec1.begin(); it1!=vec1.end(); it1++){
			if((*it1) == X[i][3]){ //education
				flag=false;
				break;
			}
		}
		if(flag) {
			if(X[i][3]!="")
				vec1.push_back(X[i][3]); //17
		}
	}


	int count1[vec1.size()][16], t=0;
	memset(count1,0,sizeof(count1));
	for(int i=0; i<SIZE_OF_TRAIN;i++){
		for(t=0, it1=vec1.begin(); it1!=vec1.end(); it1++, t++){
			for(int j=0;j<16;j++){
				if((*it1)==X[i][3] && (stringToNum(X[i][4])-1)==j){
					count1[t][j]++;
				}
			}
		}
	}
	ofstream s("s2.txt"); //ͳ�ƽ��д�� s2.txt
		for(int i=0; i<vec1.size();i++){
			s<<vec1[i]<<" ";
			for(int j=0; j<16;j++){
				s<<(count1[i][j])<<" ";
			}
			s<<endl;
		}
}


void dealwith_attributes(){//�������ݼ�
	for(int i=0; i<SIZE_OF_TRAIN;i++){
		//��һ��age
		//��Ϊ<=20(0) 20<age<=30(1) 30<age<=40(2)
		//40<age<=50(3)  50<age<=60(4) age>60(5)
		if(stringToNum(XX[i][0])<=20){
			X[i][0]="0_age_20";
		}
		else if(stringToNum(XX[i][0])<=30){
			X[i][0]="20_age_30";
		}
		else if(stringToNum(XX[i][0])<=40){
			X[i][0]="30_age_40";
		}
		else if(stringToNum(XX[i][0])<=50){
			X[i][0]="40_age_50";
		}
		else if(stringToNum(XX[i][0])<=60){
			X[i][0]="50_age_60";
		}
		else if(stringToNum(XX[i][0])>60){
			X[i][0]="60_age";
		}

		//�ڶ��� workclass  8��
		X[i][1]=XX[i][1];
		//������ fnlwgt
		//��Ϊ<=100000(0) 100000<fnlwgt<=200000(1) 200000<fnlwgt<=300000(2)
		//300000<fnlwgt<=400000(3)  fnlwgt>400000(4) 5��
		if(stringToNum(XX[i][2])<=100000){
			X[i][2]="0_fnlwgt_1";
		}
		else if(stringToNum(XX[i][2])<=200000){
			X[i][2]="1_fnlwgt_2";
		}
		else if(stringToNum(XX[i][2])<=300000){
			X[i][2]="2_fnlwgt_3";
		}
		else if(stringToNum(XX[i][2])<=400000){
			X[i][2]="3_fnlwgt_4";
		}
		else if(stringToNum(XX[i][2])>400000){
			X[i][2]="4_fnlwgt";
		}

		//���ġ���������
		//�ػ���Ϊpre_school��5th_6th(0), 7th-8th��10th(1), 11th��HS-grad(2),
		//Some-college��Assoc-acdm(3),  Bachelors��Masters(4),  Prof-school ��Doctorate(5)
		//�ֱ�Ϊһ��       ��6��
		if(stringToNum(XX[i][3])<=3){
			X[i][3]="education0";
		}
		else if(stringToNum(XX[i][3])<=6){
			X[i][3]="education1";
		}
		else if(stringToNum(XX[i][3])<=9){
			X[i][3]="education2";
		}
		else if(stringToNum(XX[i][3])<=12){
			X[i][3]="education3";
		}
		else if(stringToNum(XX[i][3])<=14){
			X[i][3]="education4";
		}
		else if(stringToNum(XX[i][3])>14){
			X[i][3]="education5";
		}

		//������ marital-status  ��8��
		X[i][4]=XX[i][4];
		//������ occupation  �� 14��
		X[i][5]=XX[i][5];
		//�ڰ��� relationship  �� 6��
		X[i][6]=XX[i][6];
		//�ھ��� race
		X[i][7]=XX[i][7];
		//��ʮ�� sex  ��2��
		X[i][8]=XX[i][8];

		//��11�� capital-gain  �ʱ�����  ��3��
		if(stringToNum(XX[i][9])<=0){
			X[i][9]="0";
		}
		else if(stringToNum(XX[i][9])<=10000){
			X[i][9]="1";
		}
		else if(stringToNum(XX[i][9])<=100000){
			X[i][9]="2";
		}

		//��12�� capital-loss  �ʱ���ʧ
		if(stringToNum(XX[i][10])<=0){
			X[i][10]="0";
		}
		else if(stringToNum(XX[i][10])<=3000){
			X[i][10]="1";
		}
		else if(stringToNum(XX[i][10])>3000){
			X[i][10]="2";
		}

		//��13�� hours-per-week   �͹���ְҵ�кܴ��ϵ
		if(stringToNum(XX[i][11])<=40){
			X[i][11]="h_40";
		}
		else if(stringToNum(XX[i][11])<=50){
			X[i][11]="40_h_50";
		}
		else if(stringToNum(XX[i][11])<=60){
			X[i][11]="50_h_60";
		}
		else if(stringToNum(XX[i][11])>60){
			X[i][11]="60_h";
		}
		X[i][12]=XX[i][12];
		//��14�� native-country
		//��15�� label
	}
}

void dealwith_attributes2(){//�������ݼ�
	for(int i=0; i<SIZE_OF_TEST;i++){
		//��һ��age
		//��Ϊ<=20(0) 20<age<=30(1) 30<age<=40(2)
		//40<age<=50(3)  50<age<=60(4) age>60(5)
		if(stringToNum(XX2[i][0])<=20){
			X2[i][0]="0_age_20";
		}
		else if(stringToNum(XX2[i][0])<=30){
			X2[i][0]="20_age_30";
		}
		else if(stringToNum(XX2[i][0])<=40){
			X2[i][0]="30_age_40";
		}
		else if(stringToNum(XX2[i][0])<=50){
			X2[i][0]="40_age_50";
		}
		else if(stringToNum(XX2[i][0])<=60){
			X2[i][0]="50_age_60";
		}
		else if(stringToNum(XX2[i][0])>60){
			X2[i][0]="60_age";
		}

		//�ڶ��� workclass  8��
		X2[i][1]=XX2[i][1];
		//������ fnlwgt
		//��Ϊ<=100000(0) 100000<fnlwgt<=200000(1) 200000<fnlwgt<=300000(2)
		//300000<fnlwgt<=400000(3)  fnlwgt>400000(4) 5��
		if(stringToNum(XX2[i][2])<=100000){
			X2[i][2]="0_fnlwgt_1";
		}
		else if(stringToNum(XX2[i][2])<=200000){
			X2[i][2]="1_fnlwgt_2";
		}
		else if(stringToNum(XX2[i][2])<=300000){
			X2[i][2]="2_fnlwgt_3";
		}
		else if(stringToNum(XX2[i][2])<=400000){
			X2[i][2]="3_fnlwgt_4";
		}
		else if(stringToNum(XX2[i][2])>400000){
			X2[i][2]="4_fnlwgt";
		}

		//���ġ���������
		//�ػ���Ϊpre_school��5th_6th(0), 7th-8th��10th(1), 11th��HS-grad(2),
		//Some-college��Assoc-acdm(3),  Bachelors��Masters(4),  Prof-school ��Doctorate(5)
		//�ֱ�Ϊһ��       ��6��
		if(stringToNum(XX2[i][3])<=3){
			X2[i][3]="education0";
		}
		else if(stringToNum(XX2[i][3])<=6){
			X2[i][3]="education1";
		}
		else if(stringToNum(XX2[i][3])<=9){
			X2[i][3]="education2";
		}
		else if(stringToNum(XX2[i][3])<=12){
			X2[i][3]="education3";
		}
		else if(stringToNum(XX2[i][3])<=14){
			X2[i][3]="education4";
		}
		else if(stringToNum(XX2[i][3])>14){
			X2[i][3]="education5";
		}

		//������ marital-status  ��8��
		X2[i][4]=XX2[i][4];
		//������ occupation  �� 14��
		X2[i][5]=XX2[i][5];
		//�ڰ��� relationship  �� 6��
		X2[i][6]=XX2[i][6];
		//�ھ��� race
		X2[i][7]=XX2[i][7];
		//��ʮ�� sex  ��2��
		X2[i][8]=XX2[i][8];

		//��11�� capital-gain  �ʱ�����  ��3��
		if(stringToNum(XX2[i][9])<=0){
			X2[i][9]="0";
		}
		else if(stringToNum(XX2[i][9])<=10000){
			X2[i][9]="1";
		}
		else if(stringToNum(XX2[i][9])<=100000){
			X2[i][9]="2";
		}

		//��12�� capital-loss  �ʱ���ʧ
		if(stringToNum(XX2[i][10])<=0){
			X2[i][10]="0";
		}
		else if(stringToNum(XX2[i][10])<=3000){
			X2[i][10]="1";
		}
		else if(stringToNum(XX2[i][10])>3000){
			X2[i][10]="2";
		}

		//��13�� hours-per-week   �͹���ְҵ�кܴ��ϵ
		if(stringToNum(XX2[i][11])<=40){
			X2[i][11]="h_40";
		}
		else if(stringToNum(XX2[i][11])<=50){
			X2[i][11]="40_h_50";
		}
		else if(stringToNum(XX2[i][11])<=60){
			X2[i][11]="50_h_60";
		}
		else if(stringToNum(XX2[i][11])>60){
			X2[i][11]="60_h";
		}


		//��14�� native-country
		//��15�� label
		X2[i][12]=XX2[i][12];
	}

}


struct Node{
	int yes_or_no; //����ֵ
	int split_attri; //���ڷָ���������
	int N_leaf;  //����ڵ�����labelΪ0�Ľڵ����
	int P_leaf;  //����ڵ�����labelΪ1�Ľڵ����
	string split;   //����ֵ       ��ɢ����Ϊ��ֵ
	vector<Node *>children; //���ӽڵ�

//	vector<Node *>right_child;

	Node(){
		yes_or_no=-1;
		split_attri=-1;
		split="";
		N_leaf=0;
		P_leaf=0;
	}
};

//�洢��ʱ�������������Զ�Ӧ��ȡֵ
// ���룺  unused_items��δ���ֵ�ѵ��������
// ���أ� attri_values����i�����Զ�Ӧ��ȡֵvector<int>��mapӳ��
map<int,vector<string> > get_attri_values(vector<vector<string> >unused_items){
	map<int,vector<string> > attri_values;//�洢ĳ�����Զ�Ӧ��ȡֵ
	int i,j,k;
	for(i=0; i<unused_items[0].size(); i++){//�����б���
		vector<string> values;
		bool existed = false;
		for (j=0; j<unused_items.size(); j++){
			for (k=0; k<values.size(); k++){
				if(values[k]==(unused_items[j][i])) { //����
					existed = true;
					break;
				}
			}
			if(!existed){ //������ �µ�����ֵ
				values.push_back(unused_items[j][i]);
			}
			existed = false;
		}
		attri_values[i] = values;  //��i�����԰�����������ֵ values
	}
	return attri_values;
}

double LOG(double n){ //��Ҫ���ǵ� n*log(n)�� n=0 ʱ�����
	if(n==0) return 0;
	return (double)log(n)/log(2.0);
}

//������
//������ ������������ ֵ
// ���룺  unused_items��ѵ��������
//		len��ѵ������������
//		attribute ���������أ���Ҫ�������б��
//		value ���������أ����������ֵ
//		isparent Ϊtrue���Ǽ��㾭���أ�false�Ǽ���������
// �����isparent Ϊtrue�����������
double Entropy(vector<vector<string> >unused_items, int len, int attribute, string value, bool isparent){
	int count1=0, count2=0, count3=0, count4=0;
	int num_of_items = unused_items.size(); //unused_items���һ���Ǳ�ǩ
	if(isparent){ //����Ǹ��׽ڵ�  �������ݼ��ľ�����
		for(int i=0; i<num_of_items; i++){
			if(unused_items[i][len-1]=="1") count1++;
			else count2++;
		}
	}
	else{
		//�ӽڵ�
		//���ݾ�������ֵvalue ����������
		string temp[num_of_items];
		for(int j=0; j<num_of_items; j++){
			temp[j]=unused_items[j][attribute]; //���������
		}

		for(int j=0; j<num_of_items; j++){
			if(unused_items[j][attribute]==(value)) {
				if(unused_items[j][len-1]=="1") count1++;
				else count2++;
			}
		}
	}
	//ע��������ж�����  Ҫ���ǵ�����ȫ���ж���ĳһ��֧ ������һ��֧Ϊ0�Ŀ���
	//���ݹ�ʽ��������
	double t1=(double)count1/(count1+count2), t2=(double)count2/(count1+count2);
	return -t1*LOG(t1)-t2*LOG(t2);
}


// ���룺unused_items������ѵ��������
//		len��ѵ������������
//		attribute ���������أ���Ҫ�������б��
//		values ��ǰ���Զ�Ӧ������ֵ
// �������Ϣ����
double Entropy_gain(vector<vector<string> >unused_items, int len, int attribute, vector<string> values){
	int num_of_items = unused_items.size(); //unused_items���һ���Ǳ�ǩ
	int j,k,i;
	//���׽ڵ����
	double entropy = Entropy(unused_items, len, attribute, "", true);
	//�ڵ� ���ֺ�
	double child_entropy=0;
//	vector<string> values=attri_values[attribute]; //������԰�������������ֵ
	vector<double> ratio;
	vector<int> count;
	for(i=0; i<values.size(); i++){
		int temp = 0;
		for(k=0; k<num_of_items; k++){
			if(unused_items[k][attribute]==values[i]) temp++;
		}
		count.push_back(temp);
	}
	for(j=0; j<values.size(); j++){
		child_entropy+=double(count[j]) /
				num_of_items*Entropy(unused_items, len, attribute, values[j], false);
	}
//	cout<<entropy<<" entropy  "<<child_entropy<<endl;
	return (entropy-child_entropy);
}


// ����ͶƱ  mis��������
int Majority_Vote(vector<vector<string> > unused_items, int len, int *mis){
	int p=0, n=0;
	int num_of_items = unused_items.size();
	for(int i=0; i<num_of_items; i++){
		if(unused_items[i][len-1]=="1") p++;
		else n++;
	}
	if(p*1.5>=n) {
		(*mis) += n; //������+n
		return 1;  //����ͶƱ
	}
	else {
		(*mis) += p; //������+p
		return 0;
	}
}

//�ж�ʣ�µ�����ֵ�Ƿ�����ͬ��ǩlabel
//ȷ���Ƿ񵽴�Ҷ�ӽڵ�  ��ֹ�ݹ��һ������
bool SameLabel(vector<vector<string> >unused_items, string label, int len){
	for(int i=0; i<unused_items.size(); i++){
		if(unused_items[i][len-1]!=label) {
			return false;
		}
	}
	return true;
}

double GINI(vector<vector<string> >unused_items, int len, int attribute){
//	int count1=0, count2=0, count3=0, count4=0;
//	int num_of_items = unused_items.size(); //unused_items���һ���Ǳ�ǩ
//
//	int temp[num_of_items];
//	for(int j=0; j<num_of_items; j++){
//		temp[j]=unused_items[j][attribute]; //���������
//	}
//
//	for(int j=0; j<num_of_items; j++){
//		if(unused_items[j][attribute]>(*split)) { //���ڷֽ�ֵ
//			if(unused_items[j][len-1]==1) count1++;
//			else count2++;
//		}
//		else {
//			if(unused_items[j][len-1]==1) count3++;//С�ڵ��ڷֽ�ֵ
//			else count4++;
//		}
//	}
//	// ����giniָ��
//	double sum1=count1+count2, sum2=count3+count4;
//	double temp1, temp2;
//	if(sum1)temp1 = (double)sum1/(sum1+sum2)*
//			(1-(double)(count1/sum1)*(double)(count1/sum1)-(double)(count2/sum1)*(double)(count2/sum1));
//	else temp1=0;
//	if(sum2)temp2 = (double)sum2/(sum1+sum2)*
//			(1-(double)(count3/sum2)*(double)(count3/sum2)-(double)(count4/sum2)*(double)(count4/sum2));
//	else temp2=0;
//	return temp1+temp2;
	return 0;
}

// ���룺unused_items������ѵ��������
//		choose 1ѡ��ID3 2 ѡ��CART
//		remain_attribute ʣ����������
// ��������ڵ�
Node *Bulid_Decision_Tree(Node * p, vector<vector<string> >unused_items,
		vector<int> remain_attribute, int choose, int *mis){
	if(p==NULL) p=new Node();

	if(remain_attribute.size() == 1){//���е����Ծ��Ѿ�����(��ʣ���һ��ǩ��), ���ǻ�������ʣ��
		int label = Majority_Vote(unused_items, 1, mis);
		p->yes_or_no = label;
//		cout<<"no more attri!!!!"<<endl;
		return p;
	}
	if(SameLabel(unused_items, "1", remain_attribute.size())){//��ͬ���� Ҷ�ӽڵ�
		p->yes_or_no = 1;
//		cout<<"same lable1!!!!"<<endl;
		return p;
	}
	if(SameLabel(unused_items, "0", remain_attribute.size())){//��ͬ���� Ҷ�ӽڵ�
		p->yes_or_no = 0;
//		cout<<"same lable0!!!!"<<endl;
		return p;
	}

	//�洢ÿ�����Զ�Ӧ��ȡֵ
	map<int,vector<string> > attri_values = get_attri_values(unused_items);

	int max_attri=remain_attribute[0], cnt=0; //max_split ��ǻ������������ı�׼
	vector <int>::iterator it1;
	if(choose==1){  //ID3
		double gain=0, max_gain=0;
		//cnt��¼�ڵڼ���
		for(cnt=0, it1=remain_attribute.begin(); it1<remain_attribute.end()-1; cnt++, it1++){ //���һ���Ǳ�ǩ��
			gain = Entropy_gain(unused_items, remain_attribute.size(), cnt, attri_values[cnt]);//������Ϣ����
			if(gain > max_gain) {  //Ҫѡ����Ϣ��������������Ϊ���ߵ�
				max_gain = gain;
				max_attri = *it1;   //�������ʱ����������ţ�
			}
//			cout<<"��ǰ������Ϣ����: "<<gain<<"  �����Ϣ����"<<max_gain<<endl;
		}
	}
	else if(choose==2){ //CART
		double gini=0, min_gini=1;
		for(cnt=0, it1=remain_attribute.begin(); it1<remain_attribute.end()-1; cnt++, it1++){
			gini=GINI(unused_items, remain_attribute.size(), cnt);
			if(min_gini > gini) { //Ҫѡ��giniָ����С��������Ϊ���ߵ�
				min_gini = gini;
				max_attri = *it1;   //giniָ����Сʱ����������ţ�
			}
			cout<<"giniָ��:  "<<gini<<endl;
		}
	}
	p->split_attri = max_attri; //���Ա��

	//��������ڵ������label Ϊ0 ����1 ����Ŀ
	int P=0, N=0;
	for(int i=0; i<unused_items.size(); i++){
		if(unused_items[i][unused_items[0].size()-1]=="0") N++;
		else P++;
	}
	//��������ڵ������label Ϊ0 ����1 ����Ŀ
	p->P_leaf=P;
	p->N_leaf=N;

	//�����µ�����������������  ��������������
	vector<int> new_attribute;
	vector<int>::iterator it2;
	int mark_pos, pos;

	for(pos=0, it2=remain_attribute.begin(); it2<remain_attribute.end(); it2++,pos++){
		if((*it2)!=max_attri) new_attribute.push_back(*it2); //��������
		else{
			mark_pos=pos;//��¼�����������unused_items������µ� �䳤�����б��s
		}
	}

	//�������� Ҫȥ���Ѿ����ڻ��ֵ�max_attri������
	//---------------------------------------children��new��--------------------------------------------------
	vector <string> values = attri_values[mark_pos]; //������԰�����������ɢֵ
	vector <string>::iterator it3;
	for(it3=values.begin(); it3<values.end(); it3++){
		vector<vector<string> > new_unused_items;
		for(int i=0; i<unused_items.size(); i++){
			vector<string> temp_unused_items;
			for(int ii=0; ii<remain_attribute.size(); ii++){ //��������
				if(ii!=mark_pos)temp_unused_items.push_back(unused_items[i][ii]);
			}
			if(unused_items[i][mark_pos]==*it3)
				new_unused_items.push_back(temp_unused_items);
		}
		//�����ӽڵ������  values.size() ֦
		Node * new_node =(Node *) new Node();
		new_node->split=*it3;
		if(new_unused_items.size()==0){ //����ڵ�ΪҶ�ӽڵ�
			p->yes_or_no = Majority_Vote(unused_items, remain_attribute.size(), mis);
			p->split=*it3;
//			cout<<"leaf node"<<endl;
			return p;
		}
		else
			Bulid_Decision_Tree(new_node, new_unused_items, new_attribute, choose, mis);

		p->children.push_back(new_node);
	}
	return p;
}

void search_tree(Node *p, vector<string> test, vector<int> remain_attribute, int *label){
	if(p!=NULL){
		int attri;
		string split;
		attri=p->split_attri; //���ڻ����������������
		string value=test[attri];

		if(p->children.size()==0){ // ��Ҷ�ӽڵ�
//			cout<<"p->children.size()==0"<<endl;
			*label=p->yes_or_no;
			return ;
		}

		vector<Node *>children = p->children;
		bool flag=false;
		for(int j=0; j<children.size(); j++){
//			cout<<"split: "<<children[j]->split<<" "<<value<<endl;
			if(children[j]->split==value) {
				flag=true;
				search_tree(children[j], test, remain_attribute, label);
			}
		}
		if(!flag){ //�����������֧
			*label=(p->P_leaf)>=(p->N_leaf)?1:0;
			return ;
		}

	}
}

Node * forest_root(vector<vector<string> >unused_items, int choose){
	Node * t =new Node();
	vector<vector<string> > random_unused_items, random_unused_items2;
	vector<int>attri_after_random;
	//ѵ��������зŻس�ȡ����
	for(int i=0; i<unused_items.size(); i++){
		int r=rand()%unused_items.size();
		random_unused_items.push_back(unused_items[r]);
	}
	// ���ѡȡm������
	int m=ceil(log(SIZE)/log(2.0));  //remain_attribute��ѡȡm������
	int len = SIZE-1;
	//����m����ͬ�������
	set<int> ran_num;
	set<int>::iterator it;
	while(true){
		int r=rand()%len;
		ran_num.insert(r);
		if(ran_num.size()==m) break;
	}

	//���ѡ�������Ժ�  ���������ٴ���Bulid_Decision_Tree����������
	for(it=ran_num.begin();it!=ran_num.end();it++){
		attri_after_random.push_back(*it); //���Ա��
	}
	attri_after_random.push_back(len);
	for(int i=0; i<random_unused_items.size(); i++){
		vector<string> temp;
		for(int j=0; j<attri_after_random.size(); j++){
			temp.push_back(random_unused_items[i][attri_after_random[j]]);
		}
		random_unused_items2.push_back(temp);
	}

	int mis=0; //mis��������
	t = Bulid_Decision_Tree(t, random_unused_items2, attri_after_random, choose, &mis);
	return t;
}

//����F1����ָ��
double F1_evaluation(int label[], int pre[], int size){//
	int TP=0, FN=0, FP=0, TN=0;
	for(int i=0; i<size; i++){
		if(label[i]==1){
			if(pre[i]==1) TP++; //����Ϊ1  Ԥ��Ϊ1
			else FN++; //����Ϊ1  Ԥ��Ϊ-1
		}
		else{
			if(pre[i]==1) FP++; //����Ϊ-1  Ԥ��Ϊ1
			else TN++; //����Ϊ-1  Ԥ��Ϊ-1
		}
	}
	cout<<TP<<"��"<<FN<<" "<<FP<<" "<<TN<<endl;
	double Accuracy=(double)(TP+TN)/(TP+FN+FP+TN);
	double Recall=(double)TP/(TP+FN);
	double Precision=(double)TP/(TP+FP);
	double F1=(double)2*Precision*Recall/(Precision+Recall);
//	cout<<"Accuracy :"<<Accuracy<<endl;
//	cout<<"Recall :"<<Recall<<endl;
//	cout<<"Precision :"<<Precision<<endl;

	cout<<"F1 :"<<F1<<endl;
	return F1;
}

int main() {
	ifstream train("train.csv");
	ifstream test("test.csv");
//	ifstream train("1.txt");
//	ifstream test("1.txt");

	if((!train.is_open()) || (!test.is_open())){
		cout << "Error opening file";
		return 0;
	}

	//��ȡ����
	data_file(train);
	data_file2(test);
//	relationship_of_Edu_and_EduNum();
	//���� ����
	dealwith_attributes();
	dealwith_attributes2();

//	ofstream ssss("s.txt");
//		for(int i=0; i<SIZE_OF_TRAIN;i++){
//			for(int j=0; j<X[0].size();j++){
//				ssss<<(X[i][j])<<" ";
//			}
//			ssss<<endl;
//		}
	srand(time(0));

	//������ѵ����
//	//����ѵ�����Ͳ��Լ�
//	vector<vector<string> > test_from_train;
//	vector<vector<string> >::iterator iter;
//	int index=SIZE_OF_TRAIN/4; //��ʼλ��
//	int length=SIZE_OF_TRAIN/4; //��ȡ���Լ���С ʣ����ѵ����  4��
//	for(iter=X.begin()+index; iter!=X.begin()+index+length; iter++){
//			test_from_train.push_back(*iter);
//	}
//	X.erase(X.begin()+index, X.begin()+index+length);

	int t;
	cout<<"input number of trees in the forest (t): ";
	cin>>t;
	vector<Node *> roots;

	int choose=1;
	for(int num=0; num<t; num++){ //����forest  t����
		Node *root=new Node();
		root=forest_root(X, choose);
		roots.push_back(root);
	}
	//	while(count<t){
	//		//�����ѵ����ѡȡ200���������ڲ������ɵ�������������
	//		vector<vector<string> > temp_items;
	//		vector<Node *> temp_roots;
	//		//ѵ���� �����ȡ����
	//		for(int i=0; i<200; i++){ //200������
	//			int r=rand()%X.size();
	//			temp_items.push_back(X[r]);
	//		}
	//		for(int num=0; num<20; num++){ //ÿ������20����
	//			Node *root=new Node();
	//			root=forest_root(X, choose);
	//			temp_roots.push_back(root);
	//		}
	//		int pre[temp_items.size()];
	//		int test_label[temp_items.size()];
	//		// ������40������F1
	//		for(int i=0;i<temp_items.size();i++){
	//			 int label, N=0, P=0;
	//			 vector<int> attribute;
	//			 for(int j=0; j<SIZE; j++) attribute.push_back(j);
	//			 for(int num=0; num<temp_roots.size(); num++){
	//				 search_tree(temp_roots[num], temp_items[i], attribute, &label);
	//				 if(label==1) P++;
	//				 else if(label==0) N++;
	//			 }
	//			 cout<<P<<"  :  "<<N<<endl;
	//			 label=(P>=N?1:0);
	//			 pre[i]=label;
	//		}
	//		 for(int i=0; i<temp_items.size(); i++) test_label[i]=stringToNum(temp_items[i][SIZE-1]);
	//		 double f1=F1_evaluation(test_label, pre, temp_items.size());
	//		 vector<Node *>::iterator temp_roots_it;
	//		 cout<<"F!: "<<f1<<endl;
	//		 if(f1>0.55){
	//			 for(temp_roots_it=temp_roots.begin(); temp_roots_it!=temp_roots.end(); temp_roots_it++)
	//				 roots.push_back(*temp_roots_it);
	//			 count+=20;
	//		 }
	//		 cout<<"COUNT: "<<count<<endl;
	//	}

		//���ԡ���ɭ��
	//	int pre[test_from_train.size()];
	//	int test_label[test_from_train.size()];
	//
	//	for(int i=0; i<test_from_train.size(); i++){ //������������
	//		 int label;
	//		 vector<int> attribute;
	//		 for(int j=0; j<SIZE-1; j++) attribute.push_back(j);
	//		 int N=0, P=0;
	//		 for(int num=0; num<roots.size(); num++){
	//			 search_tree(roots[num], test_from_train[i], attribute, &label);
	//			 if(label==1) P++;
	//			 else if(label==0) N++;
	//		 }
	//		 cout<<P<<"  :  "<<N<<endl;
	//		 label=(P*2>=N?1:0);
	//		 pre[i]=label;
	//	}
	//	cout<<"----------------------F1-measure------------------------------ "<<endl;
	//	for(int i=0; i<test_from_train.size(); i++) test_label[i]=test_from_train[i][SIZE-1];
	//	F1_evaluation(test_label, pre, test_from_train.size());

		int pre[SIZE_OF_TEST];
		ofstream s("result2.txt");
//		ofstream ss("P_N.txt");
		for(int i=0; i<SIZE_OF_TEST; i++){ //����SIZE_OF_TEST����������
			 int label;
			 vector<int> attribute;
			 for(int j=0; j<SIZE; j++) attribute.push_back(j);
			 int N=0, P=0;
			 for(int num=0; num<roots.size(); num++){
				 search_tree(roots[num], X2[i], attribute, &label);
				 if(label==1) P++;
				 else if(label==0) N++;
			 }
//			 ss<<i<<": "<<P<<" "<<N<<endl;
			 label=(P*2>=N?1:0); //����ͶƱ ȷ��label
			 pre[i]=label;
			 s<<label<<endl;
		}
	return 0;
}

