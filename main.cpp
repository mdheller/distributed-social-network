#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "Menu.h"
#include "System.h"
using namespace std;

int main(){
	int flag;
	
	char ch;
	Menu men;
	System sys;

	if(!sys.grantAccess()){
		men.thankMsg();
		return 0;
	}

	string user;
	men.welcome();

	while(true){

		cout<<"\nPlease enter username : ";
		cin>>user;
		if(sys.newUser(user)==1){

			men.welcomeUser(user);
			break;
		}

	}

	while(true){


		sys.getGroups();
		string command = "chmod 777 "+sys.getPath();;
		//		system(command.c_str());

		cout<<men.getMenu();
		cout<<"\nEnter Option: ";
		cin>>ch;

		if( ch == 'b'){
			if(sys.broadcast()){
				men.broadcastedMsg(user);
			}

		}
		else if(ch == 'm'){

			string group = sys.multicast();
			if(group!="INVALID"){
				men.multicastedMsg(user,group);
			}


		}
		else if(ch == 'u'){

			string rec = sys.unicast();

			if(rec!="INVALID"){
				men.unicastedMsg(user,rec);
			}

		}
		else if(ch == 'w'){
			men.wallMessage(user);
			sys.showWall();

		}
		else if(ch == 'h'){
			men.homeMessage(user);
			sys.showHome();

		}
		else if(ch == 'g'){

			string groupname;
			cout<<"\nEnter New Group Name: ";
			cin>> groupname;
			flag = sys.newGroup(groupname);
			if(flag==1){
				men.createdGroup(groupname);
				flag = 0;
			}

		}
		else if(ch == 'j'){

			string groupname;
			cout<<"\nEnter Group name : ";
			cin>>groupname;
			flag = sys.joinGroup(groupname);
			if(flag==1){
				men.jointGroup(user,groupname);
				flag = 0;
			}
		}
		else if(ch=='q'){
			men.thankMsg();
			break;
		}
		else{
			cout<<"\nInvalid Option.";
		}

	}
	return 0;

}
