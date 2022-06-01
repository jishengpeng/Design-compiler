//节点的具体类型
struct Specificnode {
	string dec="";
	string stmt="";
	string exp="";
};

//定义语法分析树的节点
struct Treenode {
	Treenode* child[10];
	Treenode* sibling;
	int idchild=0;//儿子的个数
	string nodekind;//节点类型
	Specificnode specificnode;//详细类型
	int idnum=0;//标识符个数
	string value;//节点的值（有的节点只有一个标识符。也用value了）
	string id[10];//部分标识符的值
};

//定义语法分析器的函数
Treenode* programhead(); //程序头
Treenode* declarehead(); //声明
//Treenode* programbody(); //程序体 
Treenode* typedec();  //类型声明
Treenode* vardec();   //变量声明
Treenode* procdec();//过程声明
Treenode* typedeclist(); //类型声明中的部分函数
Treenode* vardeclist(); //变量声明中的部分函数
Treenode* paramdeclist(); //过程声明中的部分函数
Treenode* paramlist(); //过程声明中的形参函数
//Treenode* procdecpart(); //过程声明中的变量声明
Treenode* probody(); //过程声明中的函数体,后面可以直接用作程序体
//Treenode* stmtlist(); //语句列表
Treenode* stmt(); //生成一个语句节点
Treenode* assign1(); //生成赋值表达式
Treenode* write1(); //生成读写表达式
Treenode* read1(); //生成读写表达式
Treenode* if1();  //生成选择表达式
//Treenode* stmtmore(); //生成更多的语句节点



//创建语法分析树的根节点
Treenode* program() {
	Treenode* root = new Treenode;
	if (root) {
		cout << "\n" << "程序经过语法分析器之后的语法分析树为:" << endl;
		cout << "Prok"<<endl;
		root->idchild = 3;
		root->child[0] = programhead();
		root->child[1] = declarehead();
		root->child[2] = probody();
		root->sibling = NULL;
		root->nodekind = "Prok";//节点类型为根节点
		if (gettoken(subscript).value1 == "DOT") {
			cout << "语法分析树生成成功";
			return root;
		}
		else {
			return NULL;
		}
	}
}


//类型声明部分处理程序
Treenode* typedec() {
	Treenode* t = new Treenode;
	if (token[subscript].value2 == "TYPE") {
		size2 = size2 + 1;
		printq(size2);//调用打印空格
		cout << "TYPE" << endl;
		subscript=subscript+1;
		//生成类型声明节点
		t->nodekind = "Typek";
		t->child[0] = typedeclist();
		size2 = size2 - 1;//注意回退的时机
		return t;
	}
	else return NULL;
}

//变量声明处理程序
Treenode* vardec() {
	Treenode* t = new Treenode;
	if (token[subscript].value2 == "VAR") {
		size2 = size2 + 1;
		printq(size2);//调用打印空格
		cout << "VAR" << endl;
		subscript = subscript + 1;
		//生成类型声明节点
		t->nodekind = "Vark";
		t->child[0] = vardeclist();
		size2 = size2 - 1;//注意回退的时机
		return t;
	}
	else return NULL;
}

//函数声明处理程序
Treenode* procdec() {
	Treenode* t = new Treenode;
	if (token[subscript].value2 == "PROCEDURE") {
		size2 = size2 + 1;
		printq(size2);//调用打印空格
		cout << "PROCEDURE" << endl;
		subscript = subscript + 1;
		//生成类型声明节点
		t->nodekind = "PROCEDURE";
		t->child[0] = paramdeclist();
		size2 = size2 - 1;//注意回退的时机
		return t;
	}
	else return NULL;
}

//类型声明的具体函数
Treenode* typedeclist() {
	if (token[subscript].value2 == "VAR" || token[subscript].value2 == "PROCEDURE" ||
		token[subscript].value2 == "BEGIN" || token[subscript].value1 == "DOT") {//这里要细节一点记住value1和value2
		return NULL;
	}
	else {
		Treenode* t = new Treenode;
		if (t) {
			//生成信息
			t->value = token[subscript].value2;
			subscript = subscript + 2;
			t->nodekind = "Deck";
			t->specificnode.dec = token[subscript].value2;
			subscript = subscript + 2;
			//打印
			size2 = size2 + 1;
			printq(size2);
			cout << t->nodekind << " " << t->specificnode.dec << " " << t->value<<endl;
			size2 = size2 - 1;//注意回退时机
			//递归调用
			t->sibling = typedeclist();
		}
		return t;
	}
}

//生成赋值表达式节点
Treenode* assign1() {
	//想的简单一点，就遇到;就停止
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
			//这边对赋值语句的不同符号进行区分
			//加减乘除
			if ((token[subscript].value1 == "PLUS") || (token[subscript].value1 == "MINUS") || (token[subscript].value1 == "TIMES")
				|| (token[subscript].value1 == "OVER")) {
				cout << "ExpK" << " " << "OP" << " " << token[subscript].value2 << endl;
			}
			else {
				//整数
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


//生成if表达式
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
			//这边对赋值语句的不同符号进行区分
			//加减乘除
			if ((token[subscript].value1 == "PLUS") || (token[subscript].value1 == "MINUS") || (token[subscript].value1 == "TIMES")
				|| (token[subscript].value1 == "OVER")|| (token[subscript].value1 == "LT")|| (token[subscript].value1 == "RT")) {
				cout << "ExpK" << " " << "OP" << " " << token[subscript].value2 << endl;
			}
			else {
				//整数
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