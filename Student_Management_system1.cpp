#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
class Student{
	int admno;
	char name[40];
	char gender;
	int day, month, year;
	int yearOfStudy;
	char department[30];
	char email[50];
	char address[30];
	public:
		void addData();
		void showData();
		int getAdmno(){
			return admno;
		}
}s;

void Student::addData(){
	cout<<"\n\nEnter student details......\n";
	cout<<"Enter admission number: "; cin>>admno;
	cin.ignore();
	cout<<"Enter full name: "; cin.getline(name, 40);
	cout<<"Enter gender (M/F): "; cin>>gender;
	cout<<"Enter date of birth: "; cin>>day>>month>>year;
	cout<<"Enter year of study: "; cin>>yearOfStudy;
	cin.ignore();
	cout<<"Enter department: "; cin.getline(department, 30);
	cout<<"Enter e-mail: "; cin>>email;
	cout<<"Enter address: "; cin>>address;
}

void Student::showData(){
	cout<<"\n\n.......Student Details......\n";
	cout<<"Admission number: "<<admno<<endl;
	cout<<"Name: "<<name<<endl;
	cout<<"Gender: "<<gender<<endl;
	cout<<"Date: "<<day<<"."<<month<<"."<<year<<endl;
	cout<<"Year of study: "<<yearOfStudy<<"."<<endl;
	cout<<"Department: "<<department<<endl;
	cout<<"E-mail: "<<email<<endl;
	cout<<"Address: "<<address<<endl;
	cout<<endl;
}

void addDataFile(){
	ofstream fin("students.txt", ios::in);
	s.addData();
	fin.write((char*)&s, sizeof(s));
	fin.close();
	cout<<"\n\nData Successfully Saved to File....\n";
}

void displayData(){
	ifstream fout("students.txt",ios::in);
    while(fout.read((char*)&s,sizeof(s))){
        s.showData();
    }
    fout.close();
    cout<<"\n\nData Reading from File Successfully Done....\n";
}

void searchData(){
	int n, flag=0;
	ifstream fout("students.txt", ios::in);
	cout<<"Enter admission number you want to search: ";
    cin>>n;
    while(fout.read((char*)&s, sizeof(s))){
    	if(n==s.getAdmno()){
    		cout<<"The Details of admission number "<<n<<" shown herewith:\n";
    		s.showData();
    		flag++;
		}
	}
	fout.close();
	if(flag==0){
		cout<<"The admission number "<<n<<" not found....\n\n";
	}
	cout<<"\n\nData reading from file successfully done....\n";
}

void deleteData(){
    int n, flag=0;
    ifstream fout("students.txt", ios::in);
    ofstream fin("newStudents.txt", ios::out|ios::app);
    ofstream tin("TrashStud.txt", ios::out|ios::app);
	cout<<"Enter admission number you want to move to trash: ";
    cin>>n;
    while(fout.read((char*)&s,sizeof(s))){
        if(n==s.getAdmno()){
            cout<<"The following admission number "<<n<<" has been moved to trash:\n";
            s.showData();
            tin.write((char*)&s,sizeof(s));
            flag++;
        }else{
            fin.write((char*)&s,sizeof(s));
        }
    }
    fin.close();
    tin.close();
    fout.close();
    if(flag==0) cout<<"The admission number "<<n<<" not found....\n\n";
    remove("students.txt");
    rename("newStudents","students.txt");
}

void getTrash(){
	ifstream fout("students.txt", ios::in);
	while(fout.read((char*)&s, sizeof(s))){
		s.showData();
	}
	fout.close();
	cout<<"\n\nData reading from trash file successfully done....\n";
}

void modifyData(){
	int n, flag=0, pos;
	fstream finout("students.txt", ios::in|ios::out);
	cout<<"Enter admission number you want to modify : ";
    cin>>n;
    while(finout.read((char*)&s, sizeof(s))){
    	pos = finout.tellg();
    	if(n==s.getAdmno()){
    		cout<<"The following admission number "<<n<<" will be modified with new data:\n";
    		s.showData();
    		cout<<"\n\nNow enter the new details....\n";
    		s.addData();
    		finout.seekg(pos-sizeof(s));
    		finout.write((char*)&s, sizeof(s));
    		flag++;
		}
	}
	finout.close();
	if(flag==0) cout<<"The admission number "<<n<<" not found....\n\n";
}

void project(){
    int ch;
    do{
        system("cls");
        cout<<"...............STUDENT MANAGEMENT SYSTEM..............\n";
        cout<<"======================================================\n";
        cout<<"0. Exit from Program\n";
        cout<<"1. Write Data to File\n";
        cout<<"2. Read Data From File\n";
        cout<<"3. Search Data From File\n";
        cout<<"4. Delete Data From File\n";
        cout<<"5. Get Deleted Records from Trash file\n";
        cout<<"6. Modify Data in File\n";
        cout<<"Enter your choice  : ";
        cin>>ch;
        system("cls");
        switch(ch){
            case 1: addDataFile(); break;
            case 2: displayData(); break;
            case 3: searchData(); break;
            case 4: deleteData(); break;
            case 5: getTrash(); break;
            case 6: modifyData(); break;
        }
        system("pause");
   }while(ch);
}

int main(){
    project();
    return 0;
}

































