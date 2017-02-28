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
#define SIZE 13//读取14-2特征个数+label
#define SIZE_OF_TEST 15060
vector<vector<string> > XX, XX2;
vector<vector<string> > X(SIZE_OF_TRAIN ,vector<string>(SIZE,"")); //二维vector，初始化为-1
vector<vector<string> > X2(SIZE_OF_TEST ,vector<string>(SIZE,"")); //二维vector，初始化为-1

void data_file(ifstream &f){ //读取训练集数据存储
	string s, title;
	getline(f,title);
	while(!f.eof()){
		vector<string> temp;
		for(int i=0;i<(SIZE+1);i++){
			getline(f, s, ','); //每次读取一个
			//数据集  处理方面
			//第三列和第四列信息重复  舍弃第四列
			//第十四列 个人认为  native-country 无关性较大   舍弃
			if(i!=3&&i!=13)temp.push_back(s);
		}
		getline(f, s);
		temp.push_back(s);
		XX.push_back(temp);
	}
}

void data_file2(ifstream &f){ //读取测试集数据存储
	string s, title;
	getline(f,title);
	while(!f.eof()){
		vector<string> temp;
		for(int i=0;i<(SIZE+1);i++){
			getline(f, s, ','); //每次读取一个
			if(i!=3&&i!=13)temp.push_back(s);
		}
		getline(f, s);
		temp.push_back(s);
		XX2.push_back(temp);
	}
}

//字符串转换为数字
int stringToNum(const string& str){
    istringstream iss(str);
    int num;
    iss >> num;
    return num;
}

// 两个属性 计数
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
	ofstream s("s2.txt"); //统计结果写入 s2.txt
		for(int i=0; i<vec1.size();i++){
			s<<vec1[i]<<" ";
			for(int j=0; j<16;j++){
				s<<(count1[i][j])<<" ";
			}
			s<<endl;
		}
}


void dealwith_attributes(){//处理数据集
	for(int i=0; i<SIZE_OF_TRAIN;i++){
		//第一列age
		//分为<=20(0) 20<age<=30(1) 30<age<=40(2)
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

		//第二列 workclass  8类
		X[i][1]=XX[i][1];
		//第三列 fnlwgt
		//分为<=100000(0) 100000<fnlwgt<=200000(1) 200000<fnlwgt<=300000(2)
		//300000<fnlwgt<=400000(3)  fnlwgt>400000(4) 5类
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

		//第四、五列特征
		//重划分为pre_school到5th_6th(0), 7th-8th到10th(1), 11th到HS-grad(2),
		//Some-college到Assoc-acdm(3),  Bachelors到Masters(4),  Prof-school 到Doctorate(5)
		//分别为一类       共6类
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

		//第六列 marital-status  共8类
		X[i][4]=XX[i][4];
		//第七列 occupation  共 14类
		X[i][5]=XX[i][5];
		//第八列 relationship  共 6类
		X[i][6]=XX[i][6];
		//第九列 race
		X[i][7]=XX[i][7];
		//第十列 sex  共2类
		X[i][8]=XX[i][8];

		//第11列 capital-gain  资本利得  分3类
		if(stringToNum(XX[i][9])<=0){
			X[i][9]="0";
		}
		else if(stringToNum(XX[i][9])<=10000){
			X[i][9]="1";
		}
		else if(stringToNum(XX[i][9])<=100000){
			X[i][9]="2";
		}

		//第12列 capital-loss  资本损失
		if(stringToNum(XX[i][10])<=0){
			X[i][10]="0";
		}
		else if(stringToNum(XX[i][10])<=3000){
			X[i][10]="1";
		}
		else if(stringToNum(XX[i][10])>3000){
			X[i][10]="2";
		}

		//第13列 hours-per-week   和工作职业有很大关系
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
		//第14列 native-country
		//第15列 label
	}
}

void dealwith_attributes2(){//处理数据集
	for(int i=0; i<SIZE_OF_TEST;i++){
		//第一列age
		//分为<=20(0) 20<age<=30(1) 30<age<=40(2)
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

		//第二列 workclass  8类
		X2[i][1]=XX2[i][1];
		//第三列 fnlwgt
		//分为<=100000(0) 100000<fnlwgt<=200000(1) 200000<fnlwgt<=300000(2)
		//300000<fnlwgt<=400000(3)  fnlwgt>400000(4) 5类
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

		//第四、五列特征
		//重划分为pre_school到5th_6th(0), 7th-8th到10th(1), 11th到HS-grad(2),
		//Some-college到Assoc-acdm(3),  Bachelors到Masters(4),  Prof-school 到Doctorate(5)
		//分别为一类       共6类
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

		//第六列 marital-status  共8类
		X2[i][4]=XX2[i][4];
		//第七列 occupation  共 14类
		X2[i][5]=XX2[i][5];
		//第八列 relationship  共 6类
		X2[i][6]=XX2[i][6];
		//第九列 race
		X2[i][7]=XX2[i][7];
		//第十列 sex  共2类
		X2[i][8]=XX2[i][8];

		//第11列 capital-gain  资本利得  分3类
		if(stringToNum(XX2[i][9])<=0){
			X2[i][9]="0";
		}
		else if(stringToNum(XX2[i][9])<=10000){
			X2[i][9]="1";
		}
		else if(stringToNum(XX2[i][9])<=100000){
			X2[i][9]="2";
		}

		//第12列 capital-loss  资本损失
		if(stringToNum(XX2[i][10])<=0){
			X2[i][10]="0";
		}
		else if(stringToNum(XX2[i][10])<=3000){
			X2[i][10]="1";
		}
		else if(stringToNum(XX2[i][10])>3000){
			X2[i][10]="2";
		}

		//第13列 hours-per-week   和工作职业有很大关系
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


		//第14列 native-country
		//第15列 label
		X2[i][12]=XX2[i][12];
	}

}


struct Node{
	int yes_or_no; //特征值
	int split_attri; //用于分割的特征编号
	int N_leaf;  //这个节点下面label为0的节点个数
	int P_leaf;  //这个节点下面label为1的节点个数
	string split;   //特征值       离散特征为多值
	vector<Node *>children; //孩子节点

//	vector<Node *>right_child;

	Node(){
		yes_or_no=-1;
		split_attri=-1;
		split="";
		N_leaf=0;
		P_leaf=0;
	}
};

//存储此时样本集所有属性对应的取值
// 输入：  unused_items：未划分的训练集数据
// 返回： attri_values：第i列属性对应的取值vector<int>的map映射
map<int,vector<string> > get_attri_values(vector<vector<string> >unused_items){
	map<int,vector<string> > attri_values;//存储某个属性对应的取值
	int i,j,k;
	for(i=0; i<unused_items[0].size(); i++){//按照列遍历
		vector<string> values;
		bool existed = false;
		for (j=0; j<unused_items.size(); j++){
			for (k=0; k<values.size(); k++){
				if(values[k]==(unused_items[j][i])) { //存在
					existed = true;
					break;
				}
			}
			if(!existed){ //不存在 新的属性值
				values.push_back(unused_items[j][i]);
			}
			existed = false;
		}
		attri_values[i] = values;  //第i个属性包含属性所有值 values
	}
	return attri_values;
}

double LOG(double n){ //需要考虑到 n*log(n)， n=0 时的情况
	if(n==0) return 0;
	return (double)log(n)/log(2.0);
}

//计算熵
//条件熵 包含具体属性 值
// 输入：  unused_items：训练集数据
//		len：训练集数据行数
//		attribute 计算条件熵，需要的属性列编号
//		value 计算条件熵，具体的属性值
//		isparent 为true则是计算经验熵，false是计算条件熵
// 输出：isparent 为true则输出经验熵
double Entropy(vector<vector<string> >unused_items, int len, int attribute, string value, bool isparent){
	int count1=0, count2=0, count3=0, count4=0;
	int num_of_items = unused_items.size(); //unused_items最后一列是标签
	if(isparent){ //如果是父亲节点  计算数据集的经验熵
		for(int i=0; i<num_of_items; i++){
			if(unused_items[i][len-1]=="1") count1++;
			else count2++;
		}
	}
	else{
		//子节点
		//根据具体属性值value 计算条件熵
		string temp[num_of_items];
		for(int j=0; j<num_of_items; j++){
			temp[j]=unused_items[j][attribute]; //这个特征列
		}

		for(int j=0; j<num_of_items; j++){
			if(unused_items[j][attribute]==(value)) {
				if(unused_items[j][len-1]=="1") count1++;
				else count2++;
			}
		}
	}
	//注意下面的判断条件  要考虑到样例全都判定到某一分支 导致另一分支为0的可能
	//根据公式计算熵啦
	double t1=(double)count1/(count1+count2), t2=(double)count2/(count1+count2);
	return -t1*LOG(t1)-t2*LOG(t2);
}


// 输入：unused_items：整个训练集数据
//		len：训练集数据行数
//		attribute 计算条件熵，需要的属性列编号
//		values 当前属性对应的属性值
// 输出：信息增益
double Entropy_gain(vector<vector<string> >unused_items, int len, int attribute, vector<string> values){
	int num_of_items = unused_items.size(); //unused_items最后一列是标签
	int j,k,i;
	//父亲节点的熵
	double entropy = Entropy(unused_items, len, attribute, "", true);
	//节点 划分后
	double child_entropy=0;
//	vector<string> values=attri_values[attribute]; //这个属性包含的所有属性值
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


// 多数投票  mis是误判数
int Majority_Vote(vector<vector<string> > unused_items, int len, int *mis){
	int p=0, n=0;
	int num_of_items = unused_items.size();
	for(int i=0; i<num_of_items; i++){
		if(unused_items[i][len-1]=="1") p++;
		else n++;
	}
	if(p*1.5>=n) {
		(*mis) += n; //误判数+n
		return 1;  //多数投票
	}
	else {
		(*mis) += p; //误判数+p
		return 0;
	}
}

//判断剩下的所有值是否是相同标签label
//确定是否到达叶子节点  终止递归的一种条件
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
//	int num_of_items = unused_items.size(); //unused_items最后一列是标签
//
//	int temp[num_of_items];
//	for(int j=0; j<num_of_items; j++){
//		temp[j]=unused_items[j][attribute]; //这个特征列
//	}
//
//	for(int j=0; j<num_of_items; j++){
//		if(unused_items[j][attribute]>(*split)) { //大于分界值
//			if(unused_items[j][len-1]==1) count1++;
//			else count2++;
//		}
//		else {
//			if(unused_items[j][len-1]==1) count3++;//小于等于分界值
//			else count4++;
//		}
//	}
//	// 计算gini指数
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

// 输入：unused_items：整个训练集数据
//		choose 1选择ID3 2 选择CART
//		remain_attribute 剩余的特征编号
// 输出：树节点
Node *Bulid_Decision_Tree(Node * p, vector<vector<string> >unused_items,
		vector<int> remain_attribute, int choose, int *mis){
	if(p==NULL) p=new Node();

	if(remain_attribute.size() == 1){//所有的属性均已经分完(就剩最后一标签列), 但是还有样例剩余
		int label = Majority_Vote(unused_items, 1, mis);
		p->yes_or_no = label;
//		cout<<"no more attri!!!!"<<endl;
		return p;
	}
	if(SameLabel(unused_items, "1", remain_attribute.size())){//相同分类 叶子节点
		p->yes_or_no = 1;
//		cout<<"same lable1!!!!"<<endl;
		return p;
	}
	if(SameLabel(unused_items, "0", remain_attribute.size())){//相同分类 叶子节点
		p->yes_or_no = 0;
//		cout<<"same lable0!!!!"<<endl;
		return p;
	}

	//存储每个属性对应的取值
	map<int,vector<string> > attri_values = get_attri_values(unused_items);

	int max_attri=remain_attribute[0], cnt=0; //max_split 标记划分左右子树的标准
	vector <int>::iterator it1;
	if(choose==1){  //ID3
		double gain=0, max_gain=0;
		//cnt记录在第几列
		for(cnt=0, it1=remain_attribute.begin(); it1<remain_attribute.end()-1; cnt++, it1++){ //最后一列是标签列
			gain = Entropy_gain(unused_items, remain_attribute.size(), cnt, attri_values[cnt]);//计算信息增益
			if(gain > max_gain) {  //要选择信息增益最大的特征作为决策点
				max_gain = gain;
				max_attri = *it1;   //增益最大时的特征（编号）
			}
//			cout<<"当前属性信息增益: "<<gain<<"  最大信息增益"<<max_gain<<endl;
		}
	}
	else if(choose==2){ //CART
		double gini=0, min_gini=1;
		for(cnt=0, it1=remain_attribute.begin(); it1<remain_attribute.end()-1; cnt++, it1++){
			gini=GINI(unused_items, remain_attribute.size(), cnt);
			if(min_gini > gini) { //要选择gini指数最小的特征作为决策点
				min_gini = gini;
				max_attri = *it1;   //gini指数最小时的特征（编号）
			}
			cout<<"gini指数:  "<<gini<<endl;
		}
	}
	p->split_attri = max_attri; //属性编号

	//计算这个节点下面的label 为0 或者1 的数目
	int P=0, N=0;
	for(int i=0; i<unused_items.size(); i++){
		if(unused_items[i][unused_items[0].size()-1]=="0") N++;
		else P++;
	}
	//计算这个节点下面的label 为0 或者1 的数目
	p->P_leaf=P;
	p->N_leaf=N;

	//根据新的特征来划分样例，  更新样例和特征
	vector<int> new_attribute;
	vector<int>::iterator it2;
	int mark_pos, pos;

	for(pos=0, it2=remain_attribute.begin(); it2<remain_attribute.end(); it2++,pos++){
		if((*it2)!=max_attri) new_attribute.push_back(*it2); //更新特征
		else{
			mark_pos=pos;//记录这个特征所在unused_items（会更新的 变长）的列编号s
		}
	}

	//更新样例 要去掉已经用于划分的max_attri特征列
	//---------------------------------------children（new）--------------------------------------------------
	vector <string> values = attri_values[mark_pos]; //这个属性包含的属性离散值
	vector <string>::iterator it3;
	for(it3=values.begin(); it3<values.end(); it3++){
		vector<vector<string> > new_unused_items;
		for(int i=0; i<unused_items.size(); i++){
			vector<string> temp_unused_items;
			for(int ii=0; ii<remain_attribute.size(); ii++){ //样例更新
				if(ii!=mark_pos)temp_unused_items.push_back(unused_items[i][ii]);
			}
			if(unused_items[i][mark_pos]==*it3)
				new_unused_items.push_back(temp_unused_items);
		}
		//到达子节点的属性  values.size() 枝
		Node * new_node =(Node *) new Node();
		new_node->split=*it3;
		if(new_unused_items.size()==0){ //这个节点为叶子节点
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
		attri=p->split_attri; //用于划分子树的特征编号
		string value=test[attri];

		if(p->children.size()==0){ // 是叶子节点
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
		if(!flag){ //不存在这个分支
			*label=(p->P_leaf)>=(p->N_leaf)?1:0;
			return ;
		}

	}
}

Node * forest_root(vector<vector<string> >unused_items, int choose){
	Node * t =new Node();
	vector<vector<string> > random_unused_items, random_unused_items2;
	vector<int>attri_after_random;
	//训练集随机有放回抽取样本
	for(int i=0; i<unused_items.size(); i++){
		int r=rand()%unused_items.size();
		random_unused_items.push_back(unused_items[r]);
	}
	// 随机选取m个属性
	int m=ceil(log(SIZE)/log(2.0));  //remain_attribute中选取m个属性
	int len = SIZE-1;
	//生成m个不同的随机数
	set<int> ran_num;
	set<int>::iterator it;
	while(true){
		int r=rand()%len;
		ran_num.insert(r);
		if(ran_num.size()==m) break;
	}

	//随机选择属性以后  更新数据再传入Bulid_Decision_Tree函数构建树
	for(it=ran_num.begin();it!=ran_num.end();it++){
		attri_after_random.push_back(*it); //属性编号
	}
	attri_after_random.push_back(len);
	for(int i=0; i<random_unused_items.size(); i++){
		vector<string> temp;
		for(int j=0; j<attri_after_random.size(); j++){
			temp.push_back(random_unused_items[i][attri_after_random[j]]);
		}
		random_unused_items2.push_back(temp);
	}

	int mis=0; //mis是误判数
	t = Bulid_Decision_Tree(t, random_unused_items2, attri_after_random, choose, &mis);
	return t;
}

//计算F1评测指标
double F1_evaluation(int label[], int pre[], int size){//
	int TP=0, FN=0, FP=0, TN=0;
	for(int i=0; i<size; i++){
		if(label[i]==1){
			if(pre[i]==1) TP++; //本来为1  预测为1
			else FN++; //本来为1  预测为-1
		}
		else{
			if(pre[i]==1) FP++; //本来为-1  预测为1
			else TN++; //本来为-1  预测为-1
		}
	}
	cout<<TP<<"　"<<FN<<" "<<FP<<" "<<TN<<endl;
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

	//读取数据
	data_file(train);
	data_file2(test);
//	relationship_of_Edu_and_EduNum();
	//处理 数据
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

	//决策树训练：
//	//划分训练集和测试集
//	vector<vector<string> > test_from_train;
//	vector<vector<string> >::iterator iter;
//	int index=SIZE_OF_TRAIN/4; //开始位置
//	int length=SIZE_OF_TRAIN/4; //抽取测试集大小 剩余是训练集  4折
//	for(iter=X.begin()+index; iter!=X.begin()+index+length; iter++){
//			test_from_train.push_back(*iter);
//	}
//	X.erase(X.begin()+index, X.begin()+index+length);

	int t;
	cout<<"input number of trees in the forest (t): ";
	cin>>t;
	vector<Node *> roots;

	int choose=1;
	for(int num=0; num<t; num++){ //生成forest  t棵树
		Node *root=new Node();
		root=forest_root(X, choose);
		roots.push_back(root);
	}
	//	while(count<t){
	//		//随机从训练集选取200个样本用于测试生成的这批树的性能
	//		vector<vector<string> > temp_items;
	//		vector<Node *> temp_roots;
	//		//训练集 随机抽取样本
	//		for(int i=0; i<200; i++){ //200个样本
	//			int r=rand()%X.size();
	//			temp_items.push_back(X[r]);
	//		}
	//		for(int num=0; num<20; num++){ //每次生成20棵树
	//			Node *root=new Node();
	//			root=forest_root(X, choose);
	//			temp_roots.push_back(root);
	//		}
	//		int pre[temp_items.size()];
	//		int test_label[temp_items.size()];
	//		// 计算这40棵树的F1
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

		//测试——森林
	//	int pre[test_from_train.size()];
	//	int test_label[test_from_train.size()];
	//
	//	for(int i=0; i<test_from_train.size(); i++){ //遍历测试样例
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
		for(int i=0; i<SIZE_OF_TEST; i++){ //遍历SIZE_OF_TEST个测试样例
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
			 label=(P*2>=N?1:0); //多数投票 确定label
			 pre[i]=label;
			 s<<label<<endl;
		}
	return 0;
}

