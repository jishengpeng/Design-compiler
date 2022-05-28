//��ɴʷ�������
#include <iostream>
#include <vector>
using namespace std;

//����token���еĽṹ
struct Token {
	string value1;
	string value2;
};

//ȫ�ֱ���
int size1= 0;//token���еĳ���
vector<Token> token;//token����

//�ֽ��������+ | - | *| / | ( | ) | [ | ] | ; | . | < | : | = | ' | := | > | "
char SingleDelimiter[17][20]= {"PLUS","MINUS","TIMES","OVER","LPAREN","RPAREN",
" LMIDPAREN","RMIDPAREN", "SEMI","DOT","LT","COLON","EQ","COMMA","ASSIGN","RT","SY"};

// �����ֵ�����
string  reservedWords[21] = { "program","type","var","procedure","begin","end","array","of","record","if","then","else",
"fi","while","do","endwh","read","write","return","integer","char" };


//��ӡ������
void printwrong() {
	cout << "������ĳ�����дʷ�����" << endl;
}


//��ӡtoken����
void printtoken(vector<Token>token) {
	cout << "�������ξ����ʷ�������֮���Token����Ϊ:" << endl;
	for (int i = 0; i < size1-1; i++) {
		cout << token[i].value1 << "," << token[i].value2 << endl;
	}
	cout << token[size1 - 1].value1 << "," << token[size1 - 1].value2 << endl<<"EOF";
	
}

//ͨ��һ�������ַ���,��ȡtoken����
void gettoken(vector<char> input, int len) {
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
				token1.value2 = "val=" + tmp;
				size1 = size1 + 1;
				token.push_back(token1);
			}
			else {
				//�������ұ���]�����ж������������͵��±�
				if (input[i] == ']') {
					Token token1;
					token1.value1 = "UNDERANGE";
					token1.value2 = "val=" + tmp;
					size1 = size1 + 1;
					token.push_back(token1);
				}
				else {
					Token token1;
					token1.value1 = "NUM";
					token1.value2 = "val=" + tmp;
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
				token1.value2 = "char=" + tmp;
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
						token1.value2 = tmp;
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
		//����������ֽ��
		if (input[i] == '"') {
			Token token1;
			token1.value1 = SingleDelimiter[16];
			token1.value2 = '"';
			size1 = size1 + 1;
			token.push_back(token1);
			i = i + 1;
			continue;
		}
		printwrong();
		i = i + 1;
	}
}

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
	gettoken(input, len); //���ַ������token����
	//system("cls");
	printtoken(token); //��token�������
	return 0;
	
}
