#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<iomanip>

using namespace std;

struct student{

    //Define struct student with four member (name ,id , gender, gpa);
	char *name;
	int id;
	char gender;
	float gpa;
    
};

struct course{
	string name;
	int id;
	vector<string> lecture_list;
	vector<student *> student_list;
};

student * findstudent(vector<student> &allstudents,int key){ //There is something wrong in this line.
	for(unsigned int i = 0; i < allstudents.size(); i++){
		if(allstudents[i].id  == key) return &allstudents[i];
	}
	return 0;
}

void printreport(vector<course> allcourses){
	for(unsigned int i = 0;i < allcourses.size(); i++){
		cout << "-----------------------------------------------------------------------------\n";
		cout << left << setw(20);
		cout << "Course:" << allcourses[i].name << " ("<< allcourses[i].id << ")\n\n";
		cout << left << setw(20);
		cout << "Lecturers:";
		for(unsigned int j = 0; j < allcourses[i].lecture_list.size();j++){
			if(j != 0) cout << ", ";
			cout << allcourses[i].lecture_list[j];
		}
		cout << "\n\n";
		cout << left << setw(20);
		cout << "Students:";
		for(unsigned int j = 0; j < allcourses[i].student_list.size();j++){
			if(j != 0) cout << left << setw(20) << " ";
			cout << left << setw(20) << allcourses[i].student_list[j]->name;
			cout << left << setw(10) << allcourses[i].student_list[j]->id;
			cout << left << setw(3) << allcourses[i].student_list[j]->gender;
			cout << left << setw(5) << setprecision(2) << fixed << allcourses[i].student_list[j]->gpa << "\n";
		} 
		
	}
	cout << "-----------------------------------------------------------------------------\n";
}

int main(){
	int i=0,j=0;
	ifstream student_file("students.txt");
	ifstream course_file("courses.txt");
	vector<student> allstudents;
	vector<course> allcourses;
	
	string textline;
	char names[100][100];
	int k=0;
	
	while(getline(student_file,textline)){
		student s; 
		
		//Use sscanf() to split the values in textline and assign those values to the members of struct s;
		char check[] = "%[^,],%d,%c,%f";

		int ids;
		char genders;
		float gpas;
		sscanf(textline.c_str(),check,&names[k][0],&ids,&genders,&gpas);
		s = {&names[k][0],ids,genders,gpas};
		k++;

		allstudents.push_back(s); 		
	}
	
	int state = 1;
	while(getline(course_file,textline)){
		if(state == 1){
			course c;
			int loc = textline.find_first_of('(');
			c.name = textline.substr(0,loc-1);
			c.id = atof(textline.substr(loc+1,5).c_str());
			getline(course_file,textline);
			allcourses.push_back(c);
			state = 2;			
		}else if(state == 2){
			if(textline == "> Students"){
				state = 3;
			}else{
			
			    //Append (push_back) textline to lecture_list[] of the recently added course in allcourses[];
				do{
				if(textline == "> Students")
				{
					i++;
					state = 3;
					break;
				}
				allcourses[i].lecture_list.push_back(textline);
				}while(getline(course_file,textline));
			}			
		}else{
			if(textline == "---------------------------------------"){
				state = 1;
				j++;
			}else{
				student *p = findstudent(allstudents,atof(textline.c_str()));
				
				//Append (push_back) p to student_list of the recently added course in allcourses[];

				allcourses[j].student_list.push_back(p);
				
			}
		}
	}
	printreport(allcourses);
	
}
