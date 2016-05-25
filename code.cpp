#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
int find_author(string , int num);
class Commit{
public:
	string commitID;
	string commitDate;
	string commitInfo;
	string whichfiles_changed[200];
	int numberof_files = 0;
	void print_commit();

	//string comment;
};
void Commit::print_commit(){
	cout<<endl;
	cout <<"ID:\t\t  "<< commitID <<endl<<endl;
	cout<<"DATE:\t\t"<< commitDate << endl<<endl;
	cout<<"COMMIT INFO:\t " << commitInfo << endl<<endl;
		cout << "CHANGED FILES: " << endl<<endl;
	for (int i = 0; i<numberof_files; i++){
		cout << whichfiles_changed[i] <<"\t";
	}
	cout<<endl;
	cout<<endl;

}
class Author{
public:
	string name;
	Commit* commit_array[200];
	int number_of_commit = 0;
	void print_Author();
	bool find_file(string);
	void rearrange_AuthorCommits();

//	void find_commit(string);
};
Author *array[200];
Author *top_developers[200];
Commit *c_array[200];
string files[100]; /// bi tane set oluþturucaz bunun yerine 
int file=0;
set <string> setOfFiles;
string uniquefiles[100];
int numberof_actor = 0;
int total_commit = 0;
void Author::print_Author(){
	//cout<<"########################"<<endl;
	cout<<endl;	
	cout <<"AUTHOR: "<<name <<endl;	
	cout<<endl<<endl;
	cout<<"COMMIT LIST:"<<endl;
	for (int i = 0; i<number_of_commit; i++){
		
		commit_array[i]->print_commit();
	}
	//cout<<"########################"<<endl;	
}

void Author::rearrange_AuthorCommits(){
	for(int i=0; i<number_of_commit; i++){
		for(int j=0; j<total_commit; j++){
			if(c_array[j]->commitID==commit_array[i]->commitID){
				for(int k=0; k<commit_array[i]->numberof_files; k++){
					commit_array[i]->whichfiles_changed[k]=c_array[j]->whichfiles_changed[k];
		//			cout<<name<<"->"<<commit_array[i]->whichfiles_changed[k]<<endl;
				}
			}
		}
	}
}


void split(const string& s, char c,
	vector<string>& v) {
	string::size_type i = 0;
	string::size_type j = s.find(c);
	while (j != string::npos) {
		v.push_back(s.substr(i, j - i));
		i = ++j;
		j = s.find(c, j);
		if (j == string::npos)
			v.push_back(s.substr(i, s.length()));
	}
}
void identifyTopDevelopers(){
		ofstream output;
		output.open("kayit3.txt");
		float percent=total_commit*0.8;
		int total=0;
		int i=0;
		int index;			
		ifstream myfile("log-raw2.txt");
		string line,name;
		int commit_number;
			while(!myfile.eof()){
				vector<string> line_vector;
				getline(myfile,line);
  				split(line, ',', line_vector);
       			commit_number=atoi(line_vector[0].c_str());
       		 	index=find_author(line_vector[1], numberof_actor);
       		 	top_developers[i]=array[index];       		 
       		 	i++;
       		 	total=total+commit_number;
       		 if(total>=percent){
       		 	break;
				} 		
}
for(int j=0; j<i; j++){
	output<<top_developers[j]->name<<endl;
	top_developers[j]->print_Author();
}
}
int find_author(string author_name, int num){
	for (int i = 0; i<num; i++){
		if (author_name == array[i]->name){
			return i;
		}
	}
	return -1;
}


int find_commit(string commitID){
	for (int i = 0; i<total_commit; i++){
		if (commitID == c_array[i]->commitID){
			return i;
		}
	}
	return -1;
}
bool Author::find_file(string file_name){
	int index;
	for(int i=0; i<number_of_commit; i++){
		index=find_commit(commit_array[i]->commitID);
		for(int j=0; j<c_array[index]->numberof_files; j++){
			if(c_array[index]->whichfiles_changed[j]==file_name){
			return true;
			}
		}
	}
	return false;
}
void convert_filearray(string array1[], int numberof_files){
	ofstream output;
	output.open("kayit.txt");
	int i = 0;
	for (set<string>::iterator it = setOfFiles.begin(); it != setOfFiles.end(); ++it) {
		uniquefiles[i] = *it;
		output << i << "\t" << uniquefiles[i] << endl;
		i++;	
		file++;
		//cout<<file<<endl;
	}
	file=file-1;
}

void create_matrix(){
	ofstream output;
	output.open("kayit2.txt");
	int matrix[file][numberof_actor];
	for(int i=0 ;i<file; i++){ 
		for(int j=0 ;j<numberof_actor ; j++){
		//	output2<<array[j]->name<<endl;
		bool response=array[j]->find_file(uniquefiles[i]);
		if(response==true){
			matrix[i][j]=1;
		}
		else{
			matrix[i][j]=0;
		}
		}
	}
	for(int i=0 ;i<file; i++){ 
		for(int j=0 ;j<numberof_actor ; j++){
			output<<matrix[i][j]<<" ";
}
output<<endl;
}
}

void create_structure(){
	ifstream myfile("log-rawson.txt");
	int param = 0, i = 0, j = 0;
	int k = 0;
	int a = 1;
	int response;
	int control=0;
	string commitID, commitDate, commitInfo, aname;
	if (!myfile.is_open()){
		cout << "acilmadi" << endl;
	}
	string tmp;
	int counter = 0;
	while (!myfile.eof()) {
		counter++;
		if (counter == 102){
			break;
		}
		vector<string> v;
		getline(myfile, tmp);
		if (tmp[0] != 'M'){
			control=1;
			split(tmp, ',', v);
			Commit *commit = new Commit();
			commit->commitID = v[0];
			commit->commitDate = v[2];
			commit->commitInfo = v[3];
			aname = v[1];
			c_array[total_commit] = commit;
			//cout<<c_array[total_commit]->commitID<<endl;
				//cout<<c_array[total_commit]->commitID<<endl;
			total_commit++;
			//cout<<	commit->commitID<<" "<<aname<<" "<<commit->commitDate<<" "<<commit->commitInfo<<endl;
			if (counter == 1){
				array[0] = new Author();
				array[0]->name = aname;
				array[0]->commit_array[0] = commit;
				numberof_actor++;
				array[0]->number_of_commit++;
			}
			else{
				param = find_author(aname, numberof_actor);
				if (param == -1){
					array[numberof_actor] = new Author();
					array[numberof_actor]->name = aname;
					array[numberof_actor]->commit_array[array[numberof_actor]->number_of_commit] = commit;
					array[numberof_actor]->number_of_commit++;
					numberof_actor++;
					i++;
				}
				else{
					array[param]->commit_array[array[param]->number_of_commit] = commit;
					array[param]->number_of_commit++;
					i++;
				}
			}
		}
		else{
			split(tmp, '\t', v);
			if(control==1){
				control=0;
				k=0;//k indisini kontrol etmek için
			}
			response=find_author(aname, numberof_actor);		
			//array[response]->commit_array[array[response]->number_of_commit-1]->whichfiles_changed[k] = v[1];
			c_array[total_commit - 1]->whichfiles_changed[k] = v[1];	
			c_array[total_commit - 1]->numberof_files = c_array[total_commit - 1]->numberof_files + 1;
		  //  cout<<c_array[total_commit-1]->whichfiles_changed[k]<<endl;
		   // c_array[total_commit - 1]->print_commit();
			files[k] = v[1];
			setOfFiles.insert(v[1]);
			//cout<<files[k]<<endl;
			k++;
		}
	}
	convert_filearray(files, k);
	/*void create_matrix(){
	int **matrix;
	matrix= new int*[number];
	}*/

}
int main() {
	
	create_structure();
//    array[0]->find_commit("deb6a40");
/*cout<<array[0]->commit_array[0]->commitID<<endl;
    if(array[0]->commit_array[0]->commitID==c_array[0]->commitID){
    	cout<<"sukur kavusturana"<<endl;
	}*/
	//array[1]->print_Author();
//	cout<<" "<<response<<endl;
	//int i=find_commit("9c61b01");
	//cout<<i;
//	create_matrix();
	for(int i=0; i<numberof_actor; i++){
		array[i]->rearrange_AuthorCommits();
	
	}
	array[3]->print_Author();
//	create_matrix();
//	array[i]->print_Author();
//	cout<<endl;
/*	for(int i=0; i<numberof_actor; i++){
	
	array[i]->print_Author();
	cout<<endl;
	}
	}*/
//identifyTopDevelopers();
}
	//cout<<numberof_actor<<endl;
//cout<<file<<endl;
	//getchar();*/





