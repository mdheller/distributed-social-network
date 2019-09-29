#ifndef _MENU_H 
#define _MENU_H
#include <iostream>    
#include <string>  

using namespace std;

class Menu{
	private:
	
		string MenuMsg;

	public:
		Menu(){
		
			MenuMsg = "\n\n Send broadcast message (b)\n Send multicast group message (m)\n Send unicast personal message (u)\n Inbox (h)\n Outbox (w)\n Create new group (g)\n Join a group (j)\n Quit (q) \n";
		
		}

		void broadcastedMsg( string username){
			cout << "=========================================================================\n|";
			cout << "\t\t"<<username<<" has broadcasted a new message.\t\t\t|\n";
			cout << "=========================================================================\n";

		}
		void unicastedMsg( string username, string to){
			cout << "=========================================================================\n|";
			cout << "\t"<<username<<" has unicasted a new message to "<<to<<"\t\t\t|\n";
			cout << "=========================================================================\n";

		}
		void multicastedMsg( string username, string to){
			cout << "=========================================================================\n|";
			cout << "\t"<<username<<" has multicasted a new message to group "<<to<<".\t|\n";
			cout << "=========================================================================\n";

		}

		void welcome(){
			cout << "=========================================================================\n|";
				cout << "\t\tWelcome to the Distributed Social Network!\t\t|\n|\t\tDeveloped by - Prashant Shinde\t\t\t\t|\n";
				cout << "=========================================================================\n";
		}	

		void welcomeUser(string username){
			cout << "=========================================================================\n|";
				cout << "\t\tWelcome, "<<username<<"!\t\t\t\t\t\n";
				cout << "=========================================================================\n";
		}

		void jointGroup(string username,string groupname){
			cout << "=========================================================================\n|";
				cout <<"\t"<<username<<" has joined  "<<groupname<<" group!\t\t\t\t|\n";
				cout << "=========================================================================\n";
		}

		void createdGroup(string groupname){
			cout << "=========================================================================\n|";
				cout <<"\t\t\tNew Group "<<groupname<<" created!\t\t\t|\n";
				cout << "=========================================================================\n";
		}

		void wallMessage(string username){
			cout << "=========================================================================\n|";
				cout <<"\t\t\t"<<username<<"'S Outbox\t\t\t\t|\n";
				cout << "=========================================================================\n";
	
		}

		void homeMessage(string username){
			cout << "=========================================================================\n|";
				cout <<"\t\t\t"<<username<<"'S Inbox\t\t\t\t|\n";
				cout << "=========================================================================\n";
	
		}

		void thankMsg(){

			cout << "=========================================================================\n|";
				cout <<"\tThank you for using Distributed Social Network\t\t|\n";
				cout << "=========================================================================\n";
		}

	   string getMenu() 
	   {  
		  return MenuMsg;
	   }

};
#endif


