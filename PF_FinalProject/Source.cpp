#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
using namespace std;
using std::cout;
using std::cin;

void faculty_members();
void requestbox(int& a);

int i = 0;
int add = 0;
const int n = 20, SIZE = 10;
const int fac = 20;
string reqbox[SIZE];
string faclist[fac];
static int faccount = 0;

struct inventory {

	string name;
	string itemid;
	string cat;
	int itemc;
	string all_to;

}arr[n];

struct record {

	string name1;
	int amount;

}arr2[n];

void update_inventory()
{
	ifstream fin;
	string edit;
	cout << "Which item's data do you want to edit?" << endl;
	cin >> edit;
	int count = 0;
	ofstream fout;
	bool item = false;
	fout.open("projectfile.txt", ios::trunc);
	for (int x = 0; x < i; ++x) {
		if (edit == arr[x].name) {
			item = true;
			cout << "Enter new name: "; cin >> arr[x].name;
			cout << "Enter Item ID: "; cin >> arr[x].itemid;
			cout << "Enter Category: "; cin >> arr[x].cat;
			cout << "Enter new Itemcount: "; cin >> arr[x].itemc;
			cout << "Who is this item allocated to? \n(Enter NONE if not yet allocated)"; cin >> arr[x].all_to;
			while (count < i) {
				fout << arr[count].name << "   " << arr[count].itemid << "   " << arr[count].cat << "   " << arr[count].itemc << "   " << arr[count].all_to << endl;
				count++;
			}
		}
		if (item)
			break;
	}
	if (!item)
	{
		cout << "Error! Couldn't find an item named " << edit;
	}


	fin.close();
	fout.close();

}

void returnitem() {

	string name2;
	int m = 0;
	ifstream fin;
	fin.open("projectfile.txt", ios::app);
	bool item = false, nameverify = false, itemverify = false;;
	int  quan, count = 0, delt = 0, var = 0; string myname;
	ofstream fout;
	for (int i = 0; i < 1; ++i) {
		cout << "What is your name?" << endl;
		cin >> myname;
		for (int w = 0; w < fac; ++w) {
			if (arr[w].all_to == myname) {
				name2 = arr[w].name;
				nameverify = true;
				break;
			}
		}
	}

	if (!nameverify) {
		cout << "You haven't borrowed anything!" << endl;
		return;
	}

	cout << "Which item do you want to return?" << endl;
	string returnn; cin >> returnn;
	for (int m = 0; m < n; ++m) {
		if (name2 == returnn) {
			itemverify = true;
			break;
		}
		else
			itemverify = false;
	}
	if (!itemverify) {
		cout << "You haven't borrowed any such thing!" << endl;
		return;
	}
	string newname;
	cout << "Enter number of items you're returning: " << endl;
	cin >> quan;
	fout.open("projectfile.txt", ios::trunc);
	for (int x = 0; x < i; ++x) {
		if (returnn == arr[x].name) {
			item = true;
			var = arr[x].itemc;
		}

		int temp = 0, temp2 = 0;
		for (int l = 0; l <= faccount; l++)
		{
			if (myname == arr2[l].name1)
			{
				if (quan < arr2[l].amount)
				{
					temp = arr2[l].amount - quan;
					arr2[l].amount = temp;
					cout << "you are still holding " << temp << " items" << endl;


					while (m <= i)
					{

						if (arr[m].all_to == myname)
						{
							arr[m].itemc = arr[m].itemc + quan;
							break;
						}
						++m;
					}

					while (count < i) {
						fout << arr[count].name << " " << arr[count].itemid << " " << arr[count].cat << " " << arr[count].itemc << " " << arr[count].all_to << endl;
						count++;
					}
					return;

				}
				else if (quan > arr2[l].amount)
				{

					temp2 = quan - arr2[l].amount;

					cout << "you have returned " << temp2 << " items extra" << endl;
					arr2[l] = arr2[l + 1];

				}

			}
		}


		arr[x].itemc = arr[x].itemc + quan;
		newname = arr[x].all_to;
		arr[x].all_to = "NONE";
		while (count < i) {
			fout << arr[count].name << " " << arr[count].itemid << " " << arr[count].cat << " " << arr[count].itemc << " " << arr[count].all_to << endl;
			count++;
		}


		if (item)
			break;
	}

	if (!item) {
		cout << "No such item exists" << endl;
		return;
	}

	int index = 0;

	for (int k = 0; k < i; ++k) {

		if (faclist[k] == newname) {
			index = k;
			break;
		}
	}

	for (int j = index; j <= faccount; ++j) {
		faclist[j] = faclist[j + 1];
	}

	fin.close();
	fout.close();


}

void borrowitem() {

	ifstream fin;
	fin.open("projectfile.txt");
	ofstream fout;
	int  quantity, count = 0;
	char ans;
	cout << "What is your name?" << endl;
	string myname; int num;
	getline(cin >> ws, myname);
	cout << "which item do you need?" << endl;
	string choice; cin >> choice;
	char answer;
	cout << "What Quantity?" << endl;
	cin >> quantity;

	bool item = false;
	fout.open("projectfile.txt", ios::trunc | ios::out);
	for (int x = 0; x < i; ++x) {
		if (choice == arr[x].name) {
			if (arr[x].itemc == 0) {
				while (count < i) {
					fout << arr[count].name << " " << arr[count].itemid << " " << arr[count].cat << " " << arr[count].itemc << " " << arr[count].all_to << endl;
					count++;
				}
				cout << "Item is out of stock!" << endl;
				return;
			}
			else if (quantity > arr[x].itemc) {
				for (int l = 0; 1; ++l) {
					cout << "This much quantity is not available! " << endl;
					cout << "Retrieve lesser quantity? " << endl;
					cin >> answer;
					if (answer == 'Y' || answer == 'y') {
						cout << "Enter new quantity: " << endl;
						cin >> quantity;
						if (quantity < arr[x].itemc) {
							faclist[faccount++] = myname;
							num = faccount - 1;
							arr2[num].name1 = myname;
							arr2[num].amount = quantity;
							break;
						}
						else
							continue;
					}
					else {
						while (count < i) {
							fout << arr[count].name << " " << arr[count].itemid << " " << arr[count].cat << " " << arr[count].itemc << " " << arr[count].all_to << endl;
							count++;
						}
						return;
					}
				}
			}
			else if (quantity < arr[x].itemc)
			{
				faclist[faccount++] = myname;
				num = faccount;
				arr2[num].name1 = myname;
				arr2[num].amount = quantity;
			}

			item = true;
			arr[x].itemc = arr[x].itemc - quantity;
			arr[x].all_to = myname;
			while (count < i) {
				fout << arr[count].name << " " << arr[count].itemid << " " << arr[count].cat << " " << arr[count].itemc << " " << arr[count].all_to << endl;
				count++;
			}

		}
		if (item)
			break;
	}
	char user_ch;
	if (!item)
	{
		while (count < i) {
			fout << arr[count].name << " " << arr[count].itemid << " " << arr[count].cat << " " << arr[count].itemc << " " << arr[count].all_to << endl;
			count++;
		}
		cout << "Item not available!" << endl;
		cout << "Add to request list?" << endl;
		cin >> user_ch;
		if (user_ch == 'y' || user_ch == 'Y') {
			if (add == 10)
				cout << "Request Box is full!" << endl;
			else {
				reqbox[add] = choice;
				requestbox(add);
			}
		}
		else
			cout << "Item not requested!" << endl;
	}

	fin.close();
	fout.close();

}

void delete_item() {

	string del;
	int DEL = 0, counter = 0;
	cout << "Enter ID of the item you want to delete: " << endl;
	cin >> del;
	for (int j = 0; j < i; ++j) {
		if (arr[j].itemid == del) {
			++counter;
		}
	}
	if (counter != 1) {
		cout << "No such data exists" << endl;
	}

	ifstream fin;
	fin.open("projectfile.txt");
	ofstream fout;
	fout.open("newfile.txt");
	fin >> arr[DEL].name;
	fin >> arr[DEL].itemid;
	fin >> arr[DEL].cat;
	fin >> arr[DEL].itemc;
	fin >> arr[DEL].all_to;

	while (!fin.eof()) {

		if (arr[DEL].itemid != del) {
			fout << arr[DEL].name << " " << arr[DEL].itemid << " " << arr[DEL].cat << " "
				<< arr[DEL].itemc << " " << arr[DEL].all_to << endl;
		}
		++DEL;
		fin >> arr[DEL].name;
		fin >> arr[DEL].itemid;
		fin >> arr[DEL].cat;
		fin >> arr[DEL].itemc;
		fin >> arr[DEL].all_to;

	}
	fout.close();
	fin.close();

	remove("projectfile.txt");
	rename("newfile.txt", "projectfile.txt");

	if (counter == 1) {
		cout << "Record deleted successfully!" << endl;
	}
}

void add_item() {

	ofstream fout;
	fout.open("projectfile.txt", ios::app);
	ifstream fin;
	fin.open("projectfile.txt", ios::app);

	cout << "Enter name of new item: ", cin >> arr[i].name;
	cout << "Enter Item ID: ", cin >> arr[i].itemid;
	cout << "Enter Category: ", cin >> arr[i].cat;
	cout << "Enter Item Count: ", cin >> arr[i].itemc;
	cout << "Allocated to: "; arr[i].all_to = "NONE";

	fout << arr[i].name << " " << arr[i].itemid << " " << arr[i].cat << " " << arr[i].itemc
		<< " " << arr[i].all_to << endl;
	++i;

	fin.close();
	fout.close();


}


void aboutus() {

	cout << setw(80) << "________________________________________________________________" << endl;
	cout << setw(80) << "  |                                                               |" << endl;
	cout << setw(80) << "|                         ABOUT US!                             |" << endl;
	cout << setw(80) << "|                                                               |" << endl;
	cout << setw(81) << "  |   Faculty College of Information and technology previously    | " << endl;
	cout << setw(80) << "|   known as PUCIT has a history of over 20 years.It comprises  |" << endl;
	cout << setw(80) << "|   of four distinct departments with over 56 faculty members.  |" << endl;
	cout << setw(80) << "|   The institution is responsible to provide necessary         |" << endl;
	cout << setw(80) << "|   resources to the faculty members like stationery items,     |" << endl;
	cout << setw(80) << "|              accessories, machines, etc.                      |" << endl;
	cout << setw(80) << "| ______________________________________________________________|" << endl;


}

void search_item() {

	string choice;
	char ch;
	bool flag = 1;
	int search = 0;
	cout << "Enter Name or Item ID: " << endl;
	cin >> choice;
	for (int l = 0; l < i; ++l) {
		if (choice == arr[l].name || choice == arr[l].itemid) {
			cout << "Name of Item: " << arr[l].name << endl;
			cout << "Item ID: " << arr[l].itemid << endl;
			cout << "Count of Item: " << arr[l].itemc << endl;
			cout << "Category of Item: " << arr[l].cat << endl;
			cout << "Item Allocated to: " << arr[l].all_to << endl;
			flag = 0;
		}
	}
	if (flag)
		cout << "No such item found" << endl;


}
void requestbox(int& add) {

	++add;
	cout << setw(50) << "-----------------------" << endl;
	cout << setw(28) << "|" << "     REQUEST BOX " << "    |" << endl;

	for (int m = 0; m < 10; ++m) {
		cout << setw(28) << "|" << reqbox[m] << setw(22 - reqbox[m].length()) << "|" << endl;
	}
	cout << setw(50) << "-----------------------" << endl;

}
void faculty_members() {

	//faccount++;
	if (faccount == 0)
		cout << "No faculty members have borrowed anything yet!" << endl;
	else {
		cout << setw(50) << "-----------------------" << endl;
		cout << setw(28) << "|" << "   FACULTY MEMBERS " << "  |" << endl;


		for (int m = 0; m < 15; m++) {
			cout << setw(28) << "|" << faclist[m] << setw(22 - faclist[m].length()) << "|" << endl;
		}
		cout << setw(50) << "-----------------------" << endl;

	}


}
void view_inventory() {

	string str;
	ofstream fout;
	fout.open("projectfile.txt", ios::app);
	ifstream fin;
	fin.open("projectfile.txt", ios::app);
	cout << "Name    Item ID    Category    ItemCount    Allocated to" << endl;
	while (!fin.eof()) {

		getline(fin, str);
		cout << str << endl;

	}
	fin.close();
	fout.close();

}
int main() {

	string search, order;
	int choice, c2, c3, c4;
	ofstream fout;
	fout.open("projectfile.txt", ios::app);
	ifstream fin;
	fin.open("projectfile.txt", ios::app);
	int x = 0;
	while (!fin.eof()) {
		fin >> arr[i].name;
		fin >> arr[i].itemid;
		fin >> arr[i].cat;
		fin >> arr[i].itemc;
		fin >> arr[i].all_to;
		++i;
	}
	fin.close();
	fout.close();

	do {
		cout << endl;
		cout << setw(10);
		cout << setw(80) << "        ________________________________________________" << endl;
		cout << setw(80) << "        |       PUCIT INVENTORY MANAGEMENT SYSTEM       |" << endl;
		cout << setw(80) << "        |                                               |" << endl;
		cout << setw(80) << "        |  Enter 1 to View...                           |" << endl; //about us
		cout << setw(80) << "        |  Enter 2 to Search Inventory Items            |" << endl;
		cout << setw(80) << "        |  Enter 3 to Edit Inventory Items              |" << endl;
		cout << setw(80) << "        |  Enter 4 to Return/Borrow item                |" << endl;
		cout << setw(80) << "        |  Enter 5 to Place Orders                      |" << endl;
		cout << setw(80) << "        |                                               |" << endl;
		cout << setw(80) << "        ------------------------------------------------" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "        ----------------------------------------" << endl;
			cout << "        |                                      |" << endl;
			cout << "        |  Enter 1 for Inventory Items         |" << endl;
			cout << "        |  Enter 2 for Faculty Members         |" << endl;
			cout << "        |  Enter 3 for Request/Order Box       |" << endl;
			cout << "        |  Enter 4 for About Us                |" << endl;
			cout << "        |                                      |" << endl;
			cout << "        ----------------------------------------" << endl;
			cin >> c2;
			switch (c2) {
			case 1:
				view_inventory();
				break;
			case 2:
				if (faccount == 15) {
					cout << "List is full! Can't assign anything yet" << endl;
				}
				faculty_members();

				break;
			case 3:
				requestbox(add);
				break;
			case 4:
				aboutus();
				break;
			default:
				cout << "No such option exists!" << endl;
			}
			break;
		case 2:
			search_item();
			break;
		case 3:
			cout << "        ----------------------------------------" << endl;
			cout << "        |                                      |" << endl;
			cout << "        |  Enter 1 to Update Inventory         |" << endl;
			cout << "        |  Enter 2 to Add Items                |" << endl;
			cout << "        |  Enter 3 to delete Items             |" << endl;
			cout << "        |                                      |" << endl;
			cout << "        ----------------------------------------" << endl;
			cin >> c3;
			switch (c3) {
			case 1:
				update_inventory();
				break;
			case 2:
				add_item();
				break;
			case 3:
				delete_item();
				break;
			default:
				cout << "No such option exists!" << endl;
			}
			break;
		case 4:
			cout << "        ----------------------------------------" << endl;
			cout << "        |                                      |" << endl;
			cout << "        |       Enter 1 to Borrow item         |" << endl;
			cout << "        |       Enter 2 to return item         |" << endl;
			cout << "        |                                      |" << endl;
			cout << "        ----------------------------------------" << endl;
			cin >> c4;
			switch (c4) {
			case 1:
				borrowitem();
				break;
			case 2:
				returnitem();
				break;
			default:
				cout << "No such option exists!" << endl;
			}
			break;
		case 5:

			if (add == 10) {
				cout << "Order Box is Full!";
			}
			else {
				cout << "Enter what you want to order:" << endl;
				cin >> order;
				reqbox[add] = order;
				requestbox(add);
			}
			break;
		default:
			cout << "No such option exists!" << endl;
		}


	} while (1);


	return 0;
}
