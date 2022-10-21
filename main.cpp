#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>

using namespace std;
double to_num(string str) {
    stringstream data(str);
    double result = 0;
    data >> result;
    return result;
}
class transactions {
private:
	int code, cashierno;
	double exchangerate, equevalentinEGP;
	string name, type, currency;
public:
	transactions() {}
	transactions(int cd, int cno, string nm, double exchr, string typ, string curr) {
		code = cd;
		cashierno = cno;
		exchangerate = exchr;
		currency = curr;
		name = nm;
		type = typ;
	}
	void addNew(string curr) {

		double buyrate, sellrate;
		ifstream file("exchangeRates.txt");
		if(file.is_open()){
        while(!file.eof()){
            string buy_rate;
            string sell_rate;
            getline(file,curr,',');
            getline(file,buy_rate,',');
            getline(file,sell_rate,'\n');
            if(currency==curr){
                buyrate=to_num(buy_rate);
                sellrate=to_num(sell_rate);
                //cout<<curr<<" "<<buyrate <<" "<< sellrate;
                if(type =="sell"){
                    equevalentinEGP=exchangerate*sellrate;
                }else if(type=="buy"){
                    equevalentinEGP=exchangerate*buyrate;
                }
            }
        }
        file.close();
    }
		else { cout << "file failed to open\n"; }
		ofstream transactionfile("transactions.txt");
		transactionfile << code << "," << name << "," << cashierno << "," << exchangerate << "," << currency << "," << type << "," << equevalentinEGP<<"\n";
		cout << code << " " << name << " " << cashierno << " " << exchangerate << " " << currency << " " << type << " " << equevalentinEGP;
		transactionfile.close();
	}
	void searchedittrans(int cod,string n,int cn ,double er ,string curr,string tp ,double equev) {

        ifstream file("transactions.txt");
		if(file.is_open()){
            while(!file.eof()){
            string cashierno,code;
            string exchangerate, equevalentinEGP;
            string name, type, currency;
            getline(file, code,',');
            getline(file,name,',');
            getline(file, cashierno,',');
            getline(file,exchangerate,',');
            getline(file, currency,',');
            getline(file,type,',');
            getline(file,equevalentinEGP,'\n');
            if(code=="cod"){
                file<<cod <<","<<n<< "," << cn << "," << er << "," << curr<< "," << tp << "," << equev<<"\n";
            }
            file.close();
            }
        }
        /*string line;
        int index;
        ifstream transactionfile("transactions.txt");
		if (transactionfile.is_open()) {
			while (!transactionfile.eof()) {
				getline(transactionfile, line);
			}transactionfile.close();
			ofstream transactionfile("transactions.txt");
			while (!transactionfile.eof()) {
				if (index = line.find("code", 0) != string::npos) {
					transactionfile.seekp(index);
					//transactionfile.write(editword, strlen(editword));
					transactionfile <<cod <<","<<n<< "," << cn << "," << er << "," << curr<< "," << tp << "," << equev<<"\n";
					cout <<cod <<","<<n<< "," << cn << "," << er << "," << curr<< "," << tp << "," << equev<<"\n";
				}
			}
			transactionfile.close();
		}
		else { cout << "file failed to open\n"; }*/

	}
	void importexchangerate() {
		string curr;
		double br, sr;
		ifstream exchangeratefile("exchangeRates.txt");
		if (exchangeratefile.is_open()) {
			cout << "currency buy rate sell rate" << endl;
			while (!exchangeratefile.eof()) {
				exchangeratefile >> curr >> br >> sr;
				cout << curr << " " << br << " " << sr << endl;
			}
			exchangeratefile.close();
		}
		else { cout << "file failed to open\n"; }
	}
	void searcheditrate(string curr, double sell, double buy) {
	    ifstream file("exchangeRates.txt");
		if(file.is_open()){
            while(!file.eof()){
            string buy_rate;
            string sell_rate;
            getline(file,curr,',');
            getline(file,buy_rate,',');
            getline(file,sell_rate,'\n');
            if(currency==curr){
                file<<curr<<","<<buy<<","<<sell<<endl;
            }
            file.close();
            }
        }

	}
	void editsaveexchangerate(string curr, double buy, double sell) {
		ofstream exchangeratefile(filename);
		exchangeratefile << curr << " " << buy << " " << sell;
		exchangeratefile.close();
	}
	 void importcurrencybalance(){
	     string curr;
		double amount, avgprice;
		ifstream currencybalancefile("currencybalance.txt");
		if (currencybalancefile.is_open()) {
			cout << "currency buy rate sell rate" << endl;
			while (!currencybalancefile.eof()) {
				currencybalancefile >> curr >> amount >> avgprice;
				cout << curr << " " << avgprice<<" " << amount <<endl;
			}
			currencybalancefile.close();
		}
		else {
			cout << "file failed to open\n";
		}
	}
	void reportprofit() {
		string operation, line;
		int index1 = 0, index2 = 0;
		double sellprofit, totalsp = 0, buyprofit, totalbp = 0, profit;

		ifstream file("transactions.txt");
		if(file.is_open()){
        while(!file.eof()){
            string cashierno,code;
            string exchangerate, equevalentinEGP;
            string name, type, currency;
            getline(file, code,',');
            getline(file,name,',');
            getline(file, cashierno,',');
            getline(file,exchangerate,',');
            getline(file, currency,',');
            getline(file,type,',');
            getline(file,equevalentinEGP,'\n');
            if (type=="sell") {
					sellprofit=to_num(exchangerate);
                    totalsp += sellprofit;
				}
				if (type=="buy") {
					buyprofit=to_num(exchangerate);
					totalbp += buyprofit;
				}
        }
        file.close();
    }
		profit = totalsp - totalbp;
		cout << profit << endl;
	}
	~transactions() {}
};
int main()
{
	string process;
	int x = 0;
	transactions trans;
	while (process != "end") {
		cout << "Start\n";
		cout << "What do you want to do?\n";
		cout << "Add new Transaction: Enter add\n";
		cout << "Search/Edit transactions: Enter set\n";
		cout << "Import an exchange rates list: Enter ierl\n";
		cout << "Edit/save new exchange rates list: Enter newr\n";
		cout << "import currencies balance: Enter icb\n";
		cout << "Get report on:\n";
		cout << "Profit: Enter p\n";
		cout << "Currencies balance: Enter cb\n";
		cout << "Current exchange rates list: Enter cerl\n";
		cout << "Exit program: Enter end\n";
		cin >> process;
		int cashierno;
		double exchangerate, equevalentinEGP;
		string name, type, currency, line;
		ifstream myfile("transactions.txt");
		if (myfile.is_open()) {
			while (!myfile.eof()) {
				getline(myfile, line);
				myfile >> x >> name >> cashierno >> exchangerate >> currency >> type >> equevalentinEGP;
			}
			myfile.close();
		}
		if (process == "add") {
			int cashierno;
			double exchangerate;
			string name, type, currency;
			cout << "please enter the exchange information:" << endl;
			cout << "Enter cashier no.:" << endl;
			cin >> cashierno;
			cout << "Enter name" << endl;
			cin >> name;
			cout << "Enter currency (USD, Euro​, PoundSterling​, SwissFranc, JapaneseYen, SR​, KuwaitDinar​, UAED, Chineseyuan)" << endl;
			cin >> currency;
			cout << "Enter amount to be converted" << endl;
			cin >> exchangerate;
			cout << "Enter transaction type(sell, buy)in small letters" << endl;
			cin >> type;
			//trans();
			transactions t1(++x, cashierno, name, exchangerate, type, currency);
			t1.addNew(currency);
			trans = t1;
		}
		else if (process == "set") {
            int cn;
            double er, equev;
            string n, tp, curr;
            cout<<"search transaction by code\n"<<endl;
            cout<<"enter transaction code"<<endl;
			int code;
			cin >> code;
			cout << "enter the new name:" << endl;
			cin >> n;
			cout << "edit cashier number:" << endl;
			cin >> cn;
			cout << "edit money amount:" << endl;
			cin >> er;
			cout << "edit currency" << endl;
			cin >> curr;
			cout << "edit type:" << endl;
			cin >> tp;
			cout << "edit equivalent amount:" << endl;
			cin >> equev;
			trans.searchedittrans(code,string n,int cn ,double er ,string curr,string tp ,double equev));
		}
		else if (process == "ierl") {
			trans.importexchangerate();
		}
		else if (process == "newr") {
            string operation;
            cout << "do you want to edit current exhange list or append to it?"<<<endl;
            cout << "for search & edit current currency exchange rates enter 'se' in small letters"<<endl;
            cout << "for append to exchange rates enter 'app' in small letters"<<endl;
            cin>> operation;
            if(operation=="se"){
                cout<<"search for currency & edit exchange rates"<<endl;
                string word;
                double newsell, newbuy;
                cout << "enter the currency you want to search for:" << endl;
                cin >> word;
                cout << "enter the new sell rate:" << endl;
                cin >> newsell;
                cout << "enter the new buy rate:" << endl;
                cin >> newbuy;
                trans.searcheditrate(word, newsell, newbuy);
            }else if(operation=="app"){
                string curr;
                double sell, buy;
                cout << "enter the new currency\n";
                cin >> curr;
                cout << "enter its buy rate\n" << endl;
                cin >> buy;
                cout << "enter its sell rate\n";
                cin>>sell;
                trans.editsaveexchangerate(curr, buy, sell);
                }
		}
		else if (process == "icb") {
			trans.importcurrencybalance();
		}
		else if (process == "p") {
			trans.reportprofit();
		}
		else if (process == "cb") {
			trans.importcurrencybalance();
		}
		else if (process == "cerl") {
			trans.importexchangerate();
		}
		else {
			cout << "input is invalid\n" << endl;
		}
	}
	return 0;
}
