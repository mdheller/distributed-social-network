#ifndef _SYSTEM_H
#define _SYSTEM_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include "MessageBuffer.h"

using namespace std;

class System{

	string fileServerPath, timeFilePath, fileName, uname, groups[10], time;
	int groupSize, homeSize, wallSize, currentTimeCount, timecount, access;
	MessageBuffer wall[100], home[100];
	
	public:
	
		System(){
			homeSize = 0;
			wallSize = 0;

			fileServerPath = "./Files";            //Change this address to the mounted directory
			
			fileServerPath+="/";
			timeFilePath = fileServerPath + "time.txt";
			
			fstream timefile;
			timefile.open(timeFilePath.c_str());
			if(timefile.is_open()){
				cout<<"\nConnected to File Server. \n";
				access=1;
			}
			else{
				cout<<"\nConnection Failed. \n";
				access = 0;
			}
		}

		string getPath(){
			return fileServerPath;
		}
		
		int grantAccess(){

			return access;
		}
		int newUser(string username){

			fileName = fileServerPath + username + ".txt";
			uname = username;
					
			fstream userfile;
			userfile.open(fileName.c_str());
			

			if(userfile.is_open()){
				

				userfile.close();
				
			}
			else{
				ofstream newfile(fileName.c_str());
				
				newfile.close();

				fileName = fileServerPath + username + "_groups.txt";
				ofstream usergroupsfile(fileName.c_str());

				usergroupsfile.close();

			}

			return 1;

		}

		int verifyRecipient(string checkname){

			
			fileName = fileServerPath + checkname + ".txt";
			fstream checkfile;
			
			checkfile.open(fileName.c_str());
			
			if(checkfile.is_open()){
			
				checkfile.close();

				return 1;
			
			}
			return 0;
			

		}

		string getTime(){

			fstream timefile;

			timefile.open(timeFilePath.c_str());
	
			if(!timefile.is_open()){
				cout<<"\nTime file not present";
				return "";
			}
	
			timefile>>time;
			timefile.close();
			return time;

		}
		
		void incrementTimeCount(){
		
			
			time = getTime();

			stringstream ss(time);
		
			ss>>timecount;
			timecount++;

		
			ofstream writeTimeStream;
			writeTimeStream.open(timeFilePath.c_str(), ofstream::out | ofstream::trunc);
			writeTimeStream<<timecount;
			writeTimeStream.close();
		
		}


		void getGroups(){

			size_t left, right;
			int msgIterator, i=0;
		
			fileName = fileServerPath + uname + "_groups.txt";
			fstream broadcastStream;
			broadcastStream.open(fileName.c_str());
			string alltext((istreambuf_iterator<char>(broadcastStream) ),(istreambuf_iterator<char>()));
			broadcastStream.close();

			msgIterator=0;
			while(msgIterator!=string::npos){

				left = alltext.find("<!", msgIterator);
				if(left==string::npos){
				
					break;
				
				}
				left += 2;
				right = alltext.find("!>", left);

				groups[i] = alltext.substr(left, right-left);
		
			

				i++;
				msgIterator = right;
				
				
			}
			
			groupSize = i;
	
		
		}
		
		int newGroup(string groupname){
		
			
			fileName = fileServerPath + "_" + groupname + ".txt";
		
			fstream userfile;
			userfile.open(fileName.c_str(),ios::in);


			if(userfile.is_open()){
				

				userfile.close();
				cout<<"\nGroup already exists. Please join the group";
				return 0;
				
			}
			else{

				ofstream newfile(fileName.c_str());

				newfile.close();
				return 1;
			}
		
		}
		int joinGroup(string groupname){
	
			groupname = "_" + groupname;
			
			for(int i =0;i<groupSize;i++){

				if(groups[i]==groupname){
					cout<<"\nYou are already part of the group.\n";
					return 0;
				}
			}

			if(verifyRecipient(groupname)){
			
				fileName = fileServerPath + uname + "_groups.txt";

				ifstream usergroupsfile;
				usergroupsfile.open(fileName.c_str());
		
				string text((istreambuf_iterator<char>(usergroupsfile) ),(istreambuf_iterator<char>()));
				usergroupsfile.close();
	
				groupname = "<!" + groupname + "!>\n";
				groupname = text + groupname ;
			
				
				ofstream writefile;
				writefile.open(fileName.c_str(), ofstream::out | ofstream::trunc);
				writefile<<groupname;
				writefile.close();
			
				
				getGroups();

				return 1;

			}
			else{
				cout<<"\nCould not find Group . ";
				return 0;
			}

		}
		
		string unicast(){

			string recname;
			cout<<"\nPlease enter recipient name: ";
			cin>>recname;
			
			if(verifyRecipient(recname)==1){
							
				MessageBuffer temp(getTime());
				string msg=temp.messageInput();
				string mbmsg = msg;
				
				
				ifstream recfile;
				recfile.open(fileName.c_str());
				
  				string text((istreambuf_iterator<char>(recfile) ),(istreambuf_iterator<char>()));
				recfile.close();
				
	
				incrementTimeCount();
	    
				msg = "{!" + getTime() + "!} <!" + uname + "!>"+ msg ;

				mbmsg = "{!" + getTime() + "!} <!" + uname + "!> [!" +recname+"!]"+ mbmsg ;
				
				msg = msg + text ;
			
    				
 				ofstream writefile;
				writefile.open(fileName.c_str(), ofstream::out | ofstream::trunc);
				writefile<<msg;
				writefile.close();
	
				fileName = fileServerPath + "_MessageBuffer.txt";
			
				recfile.open(fileName.c_str());
		
				string mbtext((istreambuf_iterator<char>(recfile) ),(istreambuf_iterator<char>()));
				recfile.close();
			
				mbmsg = mbmsg + mbtext ;

				writefile.open(fileName.c_str(), ofstream::out | ofstream::trunc);
				writefile<<mbmsg;
				writefile.close();
				return recname;

			}
			else{
				return "INVALID";
			}

		}
		
		string multicast(){

			
			string groupname;
			cout<<"\nPlease enter group name: ";
			cin>>groupname;
			groupname = "_" + groupname;
			
			if(verifyRecipient(groupname)==1){
			
				
				int found=0;
				for(int i=0;i<groupSize;i++){
				
					if(groupname==groups[i]){
					
						found = 1;
						break;
					
					}
				
				}
				
				if(found == 0){
					cout<<"\n Please join the group first.";
					return "INVALID";
				}
				
				MessageBuffer temp(getTime());
				string msg=temp.messageInput();
				string mbmsg = msg;
				
				
				ifstream groupfile;
				groupfile.open(fileName.c_str());
				
  				string text((istreambuf_iterator<char>(groupfile) ),(istreambuf_iterator<char>()));
				groupfile.close();
				
	
				incrementTimeCount();
				msg = "{!" + getTime() + "!} <!" + uname + "!>"+ msg ;
	
				mbmsg = "{!" + getTime() + "!} <!" + uname + "!> [!" +groupname+"!]" + mbmsg ;
				
				msg = msg + text ;
				
    			
 				ofstream writefile;
				writefile.open(fileName.c_str(), ofstream::out | ofstream::trunc);
				writefile<<msg;
				writefile.close();

				fileName = fileServerPath + "_MessageBuffer.txt";
				ifstream recfile;
				recfile.open(fileName.c_str());
		
				string mbtext((istreambuf_iterator<char>(recfile) ),(istreambuf_iterator<char>()));
				recfile.close();
				mbmsg = mbmsg + mbtext ;
				writefile.open(fileName.c_str(), ofstream::out | ofstream::trunc);
				writefile<<mbmsg;
				writefile.close();
	
				return groupname;
			}
			else{
				cout<<"\nRecipient not found";
				return "INVALID";
			}
		
		}
		
		int broadcast(){
			MessageBuffer temp(getTime());
			string msg=temp.messageInput();
			string mbmsg = msg;
				
			fileName = fileServerPath + "_All.txt";
			ifstream recfile;
			recfile.open(fileName.c_str());
		
			string text((istreambuf_iterator<char>(recfile) ),(istreambuf_iterator<char>()));
			recfile.close();
			

			incrementTimeCount();

			msg = "{!" + getTime() + "!} <!" + uname + "!>" + msg ;
			mbmsg = "{!" + getTime() + "!} <!" + uname + "!> [!#All!]" + mbmsg ;
			
			msg = msg +text;
			
			
			ofstream writefile;
			writefile.open(fileName.c_str(), ofstream::out | ofstream::trunc);
			writefile<<msg;
			writefile.close();

				
			fileName = fileServerPath + "_MessageBuffer.txt";
			
			
			
			recfile.open(fileName.c_str());
		
			string mbtext((istreambuf_iterator<char>(recfile) ),(istreambuf_iterator<char>()));
			recfile.close();
			
			mbmsg = mbmsg + mbtext ;

			writefile.open(fileName.c_str(), ofstream::out | ofstream::trunc);
			writefile<<mbmsg;
			writefile.close();
			return 1;

		}

		void sortHomeMessages(){
		
			int i, j;
			MessageBuffer temp;
			for (i = 0; i < homeSize-1; i++){  

			   for (j = 0; j < homeSize-i-1; j++){
				   if (home[j].getTimeCount() < home[j+1].getTimeCount()){
				   		
						temp = home[j];
						home[j] = home[j+1];
						home[j+1] = temp;
					}
					  
				}
			}
			
			currentTimeCount = home[0].getTimeCount();


	
		}
		
		void getHomeMessages(){

			string timestamp, from, msg;
			size_t left, right;
			int msgIterator, i=0;
		
			fileName = fileServerPath + "_All.txt";
			ifstream broadcastStream;
			broadcastStream.open(fileName.c_str());
			string alltext((istreambuf_iterator<char>(broadcastStream) ),(istreambuf_iterator<char>()));
			broadcastStream.close();

			msgIterator=0;
			while(msgIterator!=string::npos){

				left = alltext.find("{!", msgIterator);
				if(left==string::npos){
				
					break;
				
				}
				left += 2;
				right = alltext.find("!}", left);
				timestamp = alltext.substr(left, right-left);
			
				left = alltext.find("<!", msgIterator);
				left += 2;
				right = alltext.find("!>", left);
				from = alltext.substr(left, right-left);
			
				left = right + 2;
				right = alltext.find("{!",left);
				msg = alltext.substr(left, right-left);
			
			

				home[i].enterMessage(timestamp,from,"#All",msg);

				i++;
				msgIterator = right;
				
				
			}
			

			fileName = fileServerPath + uname + ".txt";
			ifstream unicastStream;
			unicastStream.open(fileName.c_str());
			string unitext((istreambuf_iterator<char>(unicastStream) ),(istreambuf_iterator<char>()));
			unicastStream.close();

			msgIterator=0;
			while(msgIterator!=string::npos){

				left = unitext.find("{!", msgIterator);
				
				if(left==string::npos){
				
					break;
				
				}
				left += 2;
				right = unitext.find("!}", left);
				timestamp = unitext.substr(left, right-left);
			
				left = unitext.find("<!", msgIterator);
				left += 2;
				right = unitext.find("!>", left);
				from = unitext.substr(left, right-left);
			
				left = right + 2;
				right = unitext.find("{!",left);
				msg = unitext.substr(left, right-left);

				home[i].enterMessage(timestamp,from,uname,msg);
	
				i++;
				msgIterator = right;
			}
			
			

			
			for(int g=0; g<groupSize; g++){
			
				fileName = fileServerPath + groups[g] + ".txt";
				ifstream groupfile;
				groupfile.open(fileName.c_str());
				string grouptext((istreambuf_iterator<char>(groupfile)),(istreambuf_iterator<char>()));
				groupfile.close();

			
				msgIterator=0;
				while(msgIterator!=string::npos){

					left = grouptext.find("{!", msgIterator);
					
					if(left==string::npos){
				
						break;
				
					}
					left += 2;
					right = grouptext.find("!}", left);
					timestamp = grouptext.substr(left, right-left);
			
					left = grouptext.find("<!", msgIterator);
					left += 2;
					right = grouptext.find("!>", left);
					from = grouptext.substr(left, right-left);
			
					left = right + 2;
					right = grouptext.find("{!",left);
					msg = grouptext.substr(left, right-left);
		

					home[i].enterMessage(timestamp,from,groups[g],msg);

				
					i++;
					msgIterator = right;
				}
			
			}

			homeSize = i;
		
		}
		
		void getWallMessages(){

			string timestamp, from, msg, to;
			size_t left, right;
			int msgIterator, i=0;
		
			fileName = fileServerPath + "_MessageBuffer.txt";
			ifstream mbfile;
			mbfile.open(fileName.c_str());
			if(!mbfile.is_open()){
				cout<<"\n_MessageBuffer.txt file not found.";
				return;
			}
			string alltext((istreambuf_iterator<char>(mbfile) ),(istreambuf_iterator<char>()));
			mbfile.close();
			


			msgIterator=0;
			while(msgIterator!=string::npos){

				left = alltext.find("{!", msgIterator);
				if(left==string::npos){
				
					break;
				
				}
				left += 2;
				right = alltext.find("!}", left);
				timestamp = alltext.substr(left, right-left);
			
				left = alltext.find("<!", msgIterator);
				left += 2;
				right = alltext.find("!>", left);
				from = alltext.substr(left, right-left);
				
				left = alltext.find("[!", msgIterator);
				left += 2;
				right = alltext.find("!]", left);
				to = alltext.substr(left, right-left);
			
				left = right + 2;
				right = alltext.find("{!",left);
				msg = alltext.substr(left, right-left);
			
			

				wall[i].enterMessage(timestamp,from,to,msg);
				
			

				i++;
				msgIterator = right;
				
				
			}
			wallSize = i;
		}

		void showHome(){
			int count =0 ;
			string choice;
		
			getHomeMessages();

			sortHomeMessages();
			
			for(int i = 0 ; i<homeSize; i++){
				if(count ==2){
					cout<<"\n\t\tMore Messages? (yes/no): ";
					cin>>choice;
					if(choice=="no"){
						break;
					}
				}
				
				home[i].showMessage();
				count++;
		
			}

		}
		
		void showWall(){
		
			int count;
			string choice;
			getWallMessages();
	
			
			for(int i = 0 ; i<wallSize; i++){


				if(count ==2){
					cout<<"\n\t\tMore Messages? (yes/no): ";
					cin>>choice;
					if(choice=="no"){
						break;
					}
				}
				if(wall[i].getFrom()==uname){

					wall[i].showMessage();
					count++;
				}

			
		
			}
			
			
		}

};

#endif
