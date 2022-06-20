//��ɴʷ�������
#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

#define distant 4  //����*�ĳ���

//����token���еĽṹ
struct Token {
	string value1;
	string value2;
};

//�ڵ�ľ�������
struct Specificnode {
	string dec="";
	string stmt="";
	string exp="";
};

//�����﷨�������Ľڵ�
struct Treenode {
	Treenode* child[10];
	Treenode* sibling;
	int idchild=0;//���ӵĸ���
	string nodekind;//�ڵ�����
	Specificnode specificnode;//��ϸ����
	int idnum=0;//��ʶ������
	string value;//�ڵ��ֵ���еĽڵ�ֻ��һ����ʶ����Ҳ��value�ˣ�
	string id[10];//���ֱ�ʶ����ֵ
};

//�����﷨�������ĺ���
Treenode* programhead(); //����ͷ
Treenode* declarehead(); //����
//Treenode* programbody(); //������ 
Treenode* typedec();  //��������
Treenode* vardec();   //��������
Treenode* procdec();//��������
Treenode* typedeclist(); //���������еĲ��ֺ���
Treenode* vardeclist(); //���������еĲ��ֺ���
Treenode* paramdeclist(); //���������еĲ��ֺ���
Treenode* paramlist(); //���������е��βκ���
//Treenode* procdecpart(); //���������еı�������
Treenode* probody(); //���������еĺ�����,�������ֱ������������
//Treenode* stmtlist(); //����б�
Treenode* stmt(); //����һ�����ڵ�
Treenode* assign1(); //���ɸ�ֵ���ʽ
Treenode* write1(); //���ɶ�д���ʽ
Treenode* read1(); //���ɶ�д���ʽ
Treenode* if1();  //����ѡ����ʽ
//Treenode* stmtmore(); //���ɸ�������ڵ�

//ȫ�ֱ���
int size1= 0;//token���еĳ���
vector<Token> token;//token����
int subscript=0;//�﷨���������е��±꣬��Ƕ����ĸ�token����
int size2 = 0;//��������������Ĳ�νṹ

//�ֽ��������+ | - | *| / | ( | ) | [ | ] | ; | . | < | : | = | ' | := | > | " | ,
char SingleDelimiter[18][20]= {"PLUS","MINUS","TIMES","OVER","LPAREN","RPAREN",
" LMIDPAREN","RMIDPAREN", "SEMI","DOT","LT","COLON","EQ","COMMA","ASSIGN","RT","SY","JSP1"};

// �����ֵ�����,Ϊ��ʵ��ӳ���ϵ
string  reservedWords[21] = { "program","type","var","procedure","begin","end","array","of","record","if","then","else",
"fi","while","do","endwh","read","write","return","integer","char" };
string reservedWords1[21] = { "PROGRAM","TYPE","VAR","PROCEDURE","BEGIN","END","ARRAY","OF","RECORD","IF","THEN","ELSE",
"FI","WHILE","DO","ENDWH","READ","WRITE","RETURN","INTEGER","CHAR" };


//��ӡ������
void printwrong() {
	cout << "������ĳ�����дʷ�����" << endl;
}

//��ӡ�﷨���Ŀո�
void printq(int size3) {
	Sleep(1000);
	for (int w = 0; w < distant * size3; w++) {
		cout << " ";
	}
}


//��ӡtoken���е�����̨
void printtoken(vector<Token>token) {
	cout << "�������ξ����ʷ�������֮���Token����Ϊ:" << endl;
	for (int i = 0; i < size1-1; i++) {
		cout << token[i].value1 << "," << token[i].value2 << endl;
	}
	cout << token[size1 - 1].value1 << "," << token[size1 - 1].value2 << endl<<"EOF";
	
}

//ͨ��һ�������ַ���,����token����,�ʷ��������ĺ��ĳ���
void generatetoken(vector<char> input, int len) {
	int i = 0;
	while (i < len) {
		//�������'\n'�Ϳո�
		if (input[i] == ' ' || input[i] == '\n') {
			i = i + 1;
			continue;
		}
		//�����������
		if (input[i] >= '0' && input[i] <= '9') {
			string tmp = "";
			tmp += input[i];
			int j = i + 1;
			while (j < len) {
				if (input[j] >= '0' && input[j] <= '9') {
					tmp += input[j];
					j++;
				}
				else {
					i = j;
					break;
				}
			}
			//����Ҫ�ж�������ѧ�±껹�����֣�����ط����±��Ѿ���i+1�ˣ����Բ����ٱ�
			if (i >= len) {
				Token token1;
				token1.value1 = "NUM";
				token1.value2 = tmp;
				size1 = size1 + 1;
				token.push_back(token1);
			}
			else {
				//�������ұ���]�����ж������������͵��±�
				if (input[i] == ']') {
					Token token1;
					token1.value1 = "UNDERANGE";
					token1.value2 = tmp;
					size1 = size1 + 1;
					token.push_back(token1);
				}
				else {
					Token token1;
					token1.value1 = "NUM";
					token1.value2 = tmp;
					size1 = size1 + 1;
					token.push_back(token1);
				}
			}
			continue;
		}
		//��������ַ�
		if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) {
			string tmp = "";
			tmp += input[i];
			int j = i + 1;
			while (j < len) {
				if ((input[j] >= 'a' && input[j] <= 'z') || (input[j] >= 'A' && input[j] <= 'Z') || (input[j] >= '0' && input[j] <= '9')) {
					tmp += input[j];
					j = j + 1;
				}
				else {
					i = j;
					break;
				}
			}
			//cout << "\n" << "******" << tmp << endl;
			if (tmp.length()==1) {    //�����char���͵�
				Token token1;
				token1.value1 = "CHAR";
				token1.value2 = tmp;
				size1 = size1 + 1;
				token.push_back(token1);
			}
			else {
				//�ж������Ǳ�����
				bool flag2 = false;
				for (int k = 0; k < 21; k++) {
					if (tmp == reservedWords[k]) {
						Token token1;
						token1.value1 = "reserved word";
						token1.value2 = reservedWords1[k]; //���ｫ�����ֵ�Сдת��ɴ�д
						size1 = size1 + 1;
						token.push_back(token1);
						flag2 = true;
						break;
					}
				}
				//�����������ͨ�ַ���
				if (!flag2) {
					Token token1;
					token1.value1 = "ID";
					token1.value2 = tmp;
					size1 = size1 + 1;
					token.push_back(token1);
				}

			}
			continue;
		}
		//���������ע�ͺͳ�����
		if (input[i] == '{') {
			int j = i; //ͨ��˫ָ���ҵ���һ��}
			bool flag = false; //��ʶ�Ƿ��ҵ���}
			while (j < len) {
				if (input[j] == '}') {
					i = j + 1;
					flag = true;
					break;
				}
				j = j + 1;
			}
			if (!flag) {
				printwrong();
			}
			continue;
		}
		//���������ע��,������
		if (input[i] == '}') {
			i = i + 1;
			continue;
		}
		//����������ֽ��+
		if (input[i] == '+') {
			Token token1;
			token1.value1 = SingleDelimiter[0];
			token1.value2 = '+';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��-
		if (input[i] == '-') {
			Token token1;
			token1.value1 = SingleDelimiter[1];
			token1.value2 = '-';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��*
		if (input[i] == '*') {
			Token token1;
			token1.value1 = SingleDelimiter[2];
			token1.value2 = '*';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��/
		if (input[i] == '/') {
			Token token1;
			token1.value1 = SingleDelimiter[3];
			token1.value2 = '/';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��(
		if (input[i] == '(') {
			Token token1;
			token1.value1 = SingleDelimiter[4];
			token1.value2 = '(';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��)
		if (input[i] == ')') {
			Token token1;
			token1.value1 = SingleDelimiter[5];
			token1.value2 = ')';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��[
		if (input[i] == '[') {
			Token token1;
			token1.value1 = SingleDelimiter[6];
			token1.value2 = '[';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��]
		if (input[i] == ']') {
			Token token1;
			token1.value1 = SingleDelimiter[7];
			token1.value2 = ']';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��:
		if (input[i] == ';') {
			Token token1;
			token1.value1 = SingleDelimiter[8];
			token1.value2 = ';';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��.
		if (input[i] == '.') {
			Token token1;
			token1.value1 = SingleDelimiter[9];
			token1.value2 = '.';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��<
		if (input[i] == '<') {
			Token token1;
			token1.value1 = SingleDelimiter[10];
			token1.value2 = '<';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��:����ط��ÿ���һ���ǲ���:=
		if (input[i] == ':') {
			int j = i + 1;
			if (j >= len) {
				Token token1;
				token1.value1 = SingleDelimiter[11];
				token1.value2 = ':';
				size1 = size1 + 1;
				token.push_back(token1);
				i = i + 1;
			}
			else {
				if (input[j] == '=') {
					Token token1;
					token1.value1 = SingleDelimiter[14];
					token1.value2 = ":=";
					size1 = size1 + 1;
					token.push_back(token1);
					i = i + 2;
				}
				else {
					Token token1;
					token1.value1 = SingleDelimiter[11];
					token1.value2 = ':';
					size1 = size1 + 1;
					token.push_back(token1);
					i = i + 1;
				}
			}
			continue;
		}
		//����������ֽ��=
		if (input[i] == '=') {
			Token token1;
			token1.value1 = SingleDelimiter[12];
			token1.value2 = '=';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��'
		if (input[i] == '\'') {
			Token token1;
			token1.value1 = SingleDelimiter[13];
			token1.value2 = '\'';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��>
		if (input[i] == '>') {
			Token token1;
			token1.value1 = SingleDelimiter[15];
			token1.value2 = '>';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��"
		if (input[i] == '"') {
			Token token1;
			token1.value1 = SingleDelimiter[16];
			token1.value2 = '"';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//����������ֽ��,
		if (input[i] == ',') {
			Token token1;
			token1.value1 = SingleDelimiter[17];
			token1.value2 = ',';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		//printwrong();
		i = i + 1;
	}
}

//ͨ���±꣬ÿ�εõ�һ��token
Token gettoken(int m) {
	return token[m];
}

//�����﷨�������ĸ��ڵ�
Treenode* program() {
	Treenode* root = new Treenode;
	if (root) {
		cout << "\n" << "���򾭹��﷨������֮����﷨������Ϊ:" << endl;
		cout << "Prok"<<endl;
		root->idchild = 3;
		root->child[0] = programhead();
		root->child[1] = declarehead();
		root->child[2] = probody();
		root->sibling = NULL;
		root->nodekind = "Prok";//�ڵ�����Ϊ���ڵ�
		if (gettoken(subscript).value1 == "DOT") {
			cout << "�﷨���������ɳɹ�";
			return root;
		}
		else {
			return NULL;
		}
	}
}

//��������ͷͷ�����������ڵ�
Treenode* programhead() {
	Treenode* tmp ;
	tmp = new Treenode;
	if (tmp) {
		if (token[subscript].value2 == "PROGRAM") {
			size2 = size2 + 1;
			printq(size2);//���ô�ӡ�ո�
			cout << "PheadK"<<" ";
			tmp->idchild = 0;
			tmp->nodekind = "PheadK";
			//tmp->sibling = declarehead();
			subscript = subscript + 1;
			cout << token[subscript].value2<<endl;
			size2 = size2 - 1;//����
			tmp->value = token[subscript].value2;
			subscript = subscript + 1;
		}
		else {
			return NULL;
		}
	}
	return tmp;
}

//�����������������ڵ�
Treenode* declarehead() {
	Treenode* tmp1 = new Treenode;
	Treenode* tmp2 = new Treenode;
	Treenode* tmp3 = new Treenode;;
	Treenode* tp1 = typedec();
	Treenode* tp2 = vardec();
	Treenode* tp3 = procdec();
	//�Թ��������ڵ��ϸ��
	if (tmp3) {
		tmp3->child[0] = tp3;
		tmp3->sibling = NULL;
		tmp3->nodekind = "Proc";
	}
	//�Ա��������ڵ��ϸ��
	if (tmp2) {
		tmp2->child[0] = tp2;
		tmp2->sibling = tmp3;
		tmp2->nodekind = "Varc";
	}
	//�����������ڵ��ϸ��
	if (tmp1) {
		tmp1->child[0] = tp1;
		tmp1->nodekind = "TypeK";
		tmp1->sibling = tmp2;
	}
	//cout << 3;
	//�жϲ�ͬ����õ��ķ���ֵ
	if (tp1 != NULL) {
		return tmp1;
	}
	else {
		if (tp2 != NULL) {
			return tmp2;
		}
		else {
			return tmp3;//�����ǲ���NULL��������ô����
		}
	}
	return NULL;
}
//
////���������庯���ڵ�
//Treenode* programbody() {
//	return NULL;
//}

//�����������ִ������
Treenode* typedec() {
	Treenode* t = new Treenode;
	if (token[subscript].value2 == "TYPE") {
		size2 = size2 + 1;
		printq(size2);//���ô�ӡ�ո�
		cout << "TYPE" << endl;
		subscript=subscript+1;
		//�������������ڵ�
		t->nodekind = "Typek";
		t->child[0] = typedeclist();
		size2 = size2 - 1;//ע����˵�ʱ��
		return t;
	}
	else return NULL;
}

//���������������
Treenode* vardec() {
	Treenode* t = new Treenode;
	if (token[subscript].value2 == "VAR") {
		size2 = size2 + 1;
		printq(size2);//���ô�ӡ�ո�
		cout << "VAR" << endl;
		subscript = subscript + 1;
		//�������������ڵ�
		t->nodekind = "Vark";
		t->child[0] = vardeclist();
		size2 = size2 - 1;//ע����˵�ʱ��
		return t;
	}
	else return NULL;
}

//���������������
Treenode* procdec() {
	Treenode* t = new Treenode;
	if (token[subscript].value2 == "PROCEDURE") {
		size2 = size2 + 1;
		printq(size2);//���ô�ӡ�ո�
		cout << "PROCEDURE" << endl;
		subscript = subscript + 1;
		//�������������ڵ�
		t->nodekind = "PROCEDURE";
		t->child[0] = paramdeclist();
		size2 = size2 - 1;//ע����˵�ʱ��
		return t;
	}
	else return NULL;
}

//���������ľ��庯��
Treenode* typedeclist() {
	if (token[subscript].value2 == "VAR" || token[subscript].value2 == "PROCEDURE" ||
		token[subscript].value2 == "BEGIN" || token[subscript].value1 == "DOT") {//����Ҫϸ��һ���סvalue1��value2
		return NULL;
	}
	else {
		Treenode* t = new Treenode;
		if (t) {
			//������Ϣ
			t->value = token[subscript].value2;
			subscript = subscript + 2;
			t->nodekind = "Deck";
			t->specificnode.dec = token[subscript].value2;
			subscript = subscript + 2;
			//��ӡ
			size2 = size2 + 1;
			printq(size2);
			cout << t->nodekind << " " << t->specificnode.dec << " " << t->value<<endl;
			size2 = size2 - 1;//ע�����ʱ��
			//�ݹ����
			t->sibling = typedeclist();
		}
		return t;
	}
}

//���������ľ��庯��
Treenode* vardeclist() {
	if (token[subscript].value2 == "PROCEDURE" || token[subscript].value2 == "BEGIN" || token[subscript].value1 == "DOT") {//����Ҫϸ��һ���סvalue1��value2
		return NULL;
	}
	else {
		Treenode* t = new Treenode;
		if (t) {
			//��������ڵ�ľ�����
			t->nodekind = "Deck";
			t->specificnode.dec = token[subscript].value2;
			subscript = subscript + 1;
			while (token[subscript].value1 != "SEMI") {
				//�����token��������,������;ʱ
				t->id[t->idnum] = token[subscript].value2;
				t->idnum = t->idnum + 1;
				subscript = subscript+1;
				//������������������ж�
				if (token[subscript].value1 == "JSP1") {
					subscript = subscript + 1;
				}
			}
			//��;����һ��token
			subscript = subscript + 1;
			//��ӡ����
			size2 = size2 + 1;
			printq(size2);
			cout << "DecK" << " " << t->specificnode.dec;
			for (int w = 0; w < t->idnum; w++) {
				cout << " " << t->id[w];
			}
			cout << endl;
			size2 = size2 - 1;
			//�ݹ����
			t->sibling = vardeclist();
		}
	}
}

//���������еĲ��ֺ���
Treenode* paramdeclist() {
	if (token[subscript].value1 == "ID" || token[subscript].value1 == "CHAR") {
		//���ɺ������ڵ㲿����Ϣ
		Treenode* t = new Treenode;
		t->nodekind = "HDeck";//����ط������Դ���һ���������ڵ�
		t->value = token[subscript].value2;
		subscript = subscript + 1;
		//��ӡ��Ϣ
		size2 = size2 + 1;
		printq(size2);
		cout << "HDeck" <<" "<< t->value<<endl;
		//�����βΣ����������������岿�֣���Ϊ���ӽڵ�
		t->child[0]= paramlist(); //���������е��βκ���
		t->child[1]= vardec(); //���������еı�������,�����֮ǰд���˵�
		t->child[2]= probody(); //���������еĺ�����
		size2 = size2 - 1;
		return t;
	}
	else return NULL;
}
//���������е��βκ���
Treenode* paramlist() {
	//��ȥ֮��������һ��������
	subscript = subscript + 1;
	//���кö���β�ʱ,���ɽڵ�
	Treenode* t = new Treenode;
	while (token[subscript].value1 != "RPAREN") {
		if (token[subscript].value1 == "JSP1") {
			//����,������
			subscript = subscript + 1;
		}
		t->id[t->idnum] = token[subscript].value2;
		t->idnum = t->idnum + 1;
		subscript = subscript + 1;
	}
	//����token����������
	subscript = subscript + 2;
	//��ӡ��Ϣ
	size2 = size2 + 1;
	printq(size2);
	cout << "DecK" << " " << "value" << " " << "param";
	for (int w = 0; w < t->idnum; w++) {
		cout << " " << t->id[w];
	}
	cout << endl;
	size2 = size2 - 1;
	return t;
}

//���������еĺ�����
Treenode* probody() {
	Treenode* t = new Treenode;
	if (token[subscript].value2 == "BEGIN") {
		size2 = size2 + 1;
		printq(size2);//���ô�ӡ�ո�
		cout << "StmLK" << endl;
		subscript = subscript + 1;
		//���ɺ��������������ڵ�
		t->nodekind = "StmLK";
		//��߽����жϣ��ǲ�����䶼������
		while (token[subscript].value2 != "END" && token[subscript].value2 != "ENDWH") {
			t->child[t->idchild] = stmt();
			t->idchild = t->idchild + 1;
		}
		subscript = subscript + 1;
		size2 = size2 - 1;//ע����˵�ʱ��
		return t;
	}
	else return NULL;

}

////��������б�
//Treenode* stmtlist() {
//	Treenode* tmp1 = new Treenode;
//	Treenode* tmp2 = new Treenode;
//	tmp1 = stmt();
//	tmp2 = stmtmore();
//	tmp1->sibling = tmp2;
//	return tmp1;
//}

//�õ�һ�����ڵ�
Treenode* stmt(){
	if (token[subscript].value1 == "ID"||token[subscript].value1=="CHAR") {
		//˵���Ǹ�ֵ�ڵ����,���ɸ�ֵ�ڵ�
		Treenode* tmp1 = new Treenode;
		tmp1->nodekind = "StmtK";
		tmp1->specificnode.stmt = "AssignK";
		//��ӡ���
		size2 = size2 + 1;
		printq(size2);
		//��߼�һЩ�ж������ֺ������ú͸�ֵ���
		if (token[subscript+1].value1 == "LPAREN") {
			cout << "StmtK" << " " << "CALL" << endl;
		}
		else {
			cout << "StmtK" << " " << "AssignK" << endl;
		}
		//cout << "StmtK" << " " << "AssignK" << endl;
		//�������ɸ�ֵ�ڵ�ϸ�Ĳ��֣�
		tmp1->child[0] = assign1();
		size2 = size2 - 1;
		return tmp1;
	}
	else {
		if (token[subscript].value2 == "WRITE") {
			//˵����д���ڵ�
			Treenode* tmp1 = new Treenode;
			tmp1->nodekind = "StmtK";
			tmp1->specificnode.stmt = "WRITE";
			subscript = subscript + 1;
			//��ӡ���
			size2 = size2 + 1;
			printq(size2);
			cout << "StmtK" << " " << "WRITE" << endl;
			//��������д�ڵ�ϸ�Ĳ��֣�
			tmp1->child[0] = write1();
			size2 = size2 - 1;
			return tmp1;
		}
		else {
			if (token[subscript].value2 == "READ") {
				//˵���Ƕ���ڵ�
				Treenode* tmp1 = new Treenode;
				tmp1->nodekind = "StmtK";
				tmp1->specificnode.stmt = "READ";
				subscript = subscript + 1;
				//��ӡ���
				size2 = size2 + 1;
				printq(size2);
				cout << "StmtK" << " " << "READ" << endl;
				//�������ɶ��ڵ�ϸ�Ĳ��֣�
				tmp1->child[0] = read1();
				size2 = size2 - 1;
				return tmp1;
			}
			else {
				if (token[subscript].value2 == "IF") {
					//˵�����жϽڵ�
					Treenode* tmp1 = new Treenode;
					tmp1->nodekind = "StmtK";
					tmp1->specificnode.stmt = "IF";
					subscript = subscript + 1;
					size2 = size2 + 1;
					printq(size2);
					cout << "StmtK" << " " << "IF" << endl;
					//��������ѡ��ڵ�if�жϲ��֣�
					tmp1->child[0] = if1();
					//��ӡthen����
					size2 = size2 + 1;
					printq(size2);
					cout << "StmtK" << " " << "THEN" << endl;
					subscript = subscript + 1;
					tmp1->child[2] = assign1();
					size2 = size2 - 1;
					//�����else
					if (token[subscript].value2 == "ELSE") {
						size2 = size2 + 1;
						printq(size2);
						cout << "StmtK" << " " << "ELSE" << endl;
						subscript = subscript + 1;
						tmp1->child[3] = assign1();
						size2 = size2 - 1;
					}
					//����FI�Ĵ���
					subscript = subscript + 2;
					//������һ��ʼ��if�ж�
					size2 = size2 - 1;
					return tmp1;

				}
				else {
					subscript = subscript + 1;
					return NULL;
				}
			}
		}
			
	}
}

//���ɸ�ֵ���ʽ�ڵ�
Treenode* assign1() {
	//��ļ�һ�㣬������;��ֹͣ
	Treenode* tmp1 = new Treenode;
	while (token[subscript].value1 != "SEMI"&& token[subscript].value2 != "END" && token[subscript].value2 != "ENDWH"
		&& token[subscript].value2 != "ELSE" && token[subscript].value2 != "FI") {
		if (token[subscript].value1 == "JSP1" || token[subscript].value1 == "ASSIGN" || token[subscript].value1 == "EQ"
			|| token[subscript].value1 == "LPAREN" || token[subscript].value1 == "RPAREN"||token[subscript].value1=="SY"
			||token[subscript].value1=="COMMA") {
			subscript = subscript + 1;
		}
		else {
			tmp1->nodekind = "ExpK";
			tmp1->specificnode.stmt = "IdK";
			size2 = size2 + 1;
			printq(size2);
			//��߶Ը�ֵ���Ĳ�ͬ���Ž�������
			//�Ӽ��˳�
			if ((token[subscript].value1 == "PLUS") || (token[subscript].value1 == "MINUS") || (token[subscript].value1 == "TIMES")
				|| (token[subscript].value1 == "OVER")) {
				cout << "ExpK" << " " << "OP" << " " << token[subscript].value2 << endl;
			}
			else {
				//����
				if (token[subscript].value1 == "NUM") {
					cout << "ExpK" << " " << "const" << " " << token[subscript].value2 << endl;
				}
				else {
					cout << "ExpK" << " " << token[subscript].value2 << " " << "IdK" << endl;
				}
				//cout << "ExpK" << " " << token[subscript].value2 << " " << "IdK" << endl;
			}
			subscript = subscript + 1;
			size2 = size2 - 1;
		}
		//tmp1->nodekind = "ExpK";
		//tmp1->specificnode.stmt = "IdK";
		//size2 = size2 + 1;
		//printq(size2);
		//if ((token[subscript].value1 == "PLUS") || (token[subscript].value1 == "MINUS") || (token[subscript].value1 == "TIMES")
		//	|| (token[subscript].value1 == "OVER")) {
		//	cout << "ExpK" << " " << "OP" << " " << token[subscript].value2 << endl;
		//}
		//else {
		//	cout << "ExpK" << " " << token[subscript].value2 << " " << "IdK" << endl;
		//}
		//subscript = subscript + 1;
		//size2 = size2 - 1;
	}
	if (token[subscript].value1 == "SEMI") {
		subscript = subscript + 1;
	}
	return tmp1;
}

//����д���ʽ
Treenode* write1() {
	Treenode* tmp1 = new Treenode;
	while ((token[subscript].value1 != "SEMI" && token[subscript].value2 != "END" && token[subscript].value2 != "ENDWH")) {
		if (token[subscript].value1 == "LPAREN" || token[subscript].value1 == "RPAREN") {
			subscript = subscript + 1;
		}
		else {
			tmp1->nodekind = "ExpK";
			tmp1->specificnode.stmt = "IdK";
			size2 = size2 + 1;
			printq(size2);
			cout << "ExpK" << " " << token[subscript].value2 << " " << "IdK" << endl;
			subscript = subscript + 1;
			size2 = size2 - 1;
		}
	}
	if (token[subscript].value1 == "SEMI") {
		subscript = subscript + 1;
	}
	return tmp1;

}

//���ɶ����ʽ
Treenode* read1() {
	Treenode* tmp1 = new Treenode;
	while ((token[subscript].value1 != "SEMI" && token[subscript].value2 != "END" && token[subscript].value2 != "ENDWH")) {
		if (token[subscript].value1 == "LPAREN" || token[subscript].value1 == "RPAREN") {
			subscript = subscript + 1;
		}
		else {
			tmp1->nodekind = "ExpK";
			tmp1->specificnode.stmt = "IdK";
			size2 = size2 + 1;
			printq(size2);
			cout << "ExpK" << " " << token[subscript].value2 << " " << "IdK" << endl;
			subscript = subscript + 1;
			size2 = size2 - 1;
		}
	}
	if (token[subscript].value1 == "SEMI") {
		subscript = subscript + 1;
	}
	return tmp1;
}

//����if���ʽ
Treenode* if1() {
	Treenode* tmp1 = new Treenode;
	while (token[subscript].value2 != "THEN") {
		if (token[subscript].value1 == "LPAREN" || token[subscript].value1 == "RPAREN") {
			subscript = subscript + 1;
		}
		else {
			tmp1->nodekind = "ExpK";
			size2 = size2 + 1;
			printq(size2);
			//��߶Ը�ֵ���Ĳ�ͬ���Ž�������
			//�Ӽ��˳�
			if ((token[subscript].value1 == "PLUS") || (token[subscript].value1 == "MINUS") || (token[subscript].value1 == "TIMES")
				|| (token[subscript].value1 == "OVER")|| (token[subscript].value1 == "LT")|| (token[subscript].value1 == "RT")) {
				cout << "ExpK" << " " << "OP" << " " << token[subscript].value2 << endl;
			}
			else {
				//����
				if (token[subscript].value1 == "NUM") {
					cout << "ExpK" << " " << "const" << " " << token[subscript].value2 << endl;
				}
				else {
					cout << "ExpK" << " " << token[subscript].value2 << " " << "IdK" << endl;
				}
				//cout << "ExpK" << " " << token[subscript].value2 << " " << "IdK" << endl;
			}
			subscript = subscript + 1;
			size2 = size2 - 1;
		}
	}
	return tmp1;
}

////�õ���������ڵ�
//Treenode* stmtmore() {
//	if (token[subscript].value2 == "END" || token[subscript].value2 == "ENDWH") {
//		subscript = subscript + 1;
//		return NULL;
//	}
//	else {
//
//	}
//}


int main() {
	//��������ַ���
	vector<char> input;
	char tmp = ' ';
	cout << "������SNL����Ƭ�Σ�" << endl;
	while (tmp != '.') {
		tmp = getchar();
		input.push_back(char(tmp));
		
	}
	//��ӡ��һ��
	int len = input.size();
	//for (int i = 0; i < len; i++) {
	//	cout << input[i];
	//}
	generatetoken(input, len); //���ַ������token����
	//system("cls");
	printtoken(token); //��token�������
	//Sleep(5000);
	//�﷨������
	Treenode* root = program();
	return 0;
	
}
