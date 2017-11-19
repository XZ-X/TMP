#include<iostream>
#include<fstream>
#include<string>
#include"xxzString.h"

using namespace std;
struct instruction{
	xxzString addr;
	xxzString type;
	xxzString op1;
	xxzString op2;
	xxzString op3;
};

istream& operator>>(istream& cin,instruction& ins){
	cin >> ins.addr;
	cin >> ins.type;
	if (ins.type == "J"){
		cin >> ins.op1;
	}
	else if(ins.type=="LW"){
		cin >> ins.op1 >> ins.op2;
	}
	else{
		cin >> ins.op1 >> ins.op2 >> ins.op3;
	}
	return cin;
}

struct record{
	xxzString addr0;
	xxzString addr_before;
	xxzString addr_end;
};

ostream& operator<<(ostream& cout, record rd){
	return  cout<<rd.addr0 << " " << rd.addr_before <<" "<< rd.addr_end;
}
instruction cmd[201];
record rcd[201];
int cmd_cnt = 0;
int rcd_cnt = -1;
int main(){
	while (cin.peek() != EOF&&cin.peek()!='\t'&&cmd_cnt<5){
		cin >> cmd[cmd_cnt++];
	}
	int seg_cnt = 0;
	xxzString jr;
	jr="#";
	for (int i = 0; i < cmd_cnt; i++){
		if (seg_cnt++ == 0){
			rcd[++rcd_cnt].addr0 = cmd[i].addr;
			rcd[rcd_cnt].addr_before = jr;
		}
		seg_cnt++;
		if (cmd[i].type == "J"){
			rcd[rcd_cnt].addr_end = cmd[i].op1;
			seg_cnt = 0;
			jr = cmd[i].addr;
			for (int k = 0; k < cmd_cnt; k++){
				if (cmd[k].addr == cmd[i].op1){
					i = k - 1;
					break;
				}
			}
		}
		
	}
	rcd[rcd_cnt].addr_end = "#";
	for (int i = 0; i <= rcd_cnt; i++){
		cout << rcd[i];
		cout << endl;
	}

	return 0;
}
