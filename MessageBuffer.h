#ifndef _MESSAGEBUFFER_H
#define _MESSAGEBUFFER_H
#include <iostream>
#include <string>
#include <sstream>
#include "System.h"

class MessageBuffer{
	string timeStamp, totalMessage, from, to;	
	int timeCount;
	
	public:
	
	MessageBuffer(){
		timeCount = 0;
	}
	
	MessageBuffer(string ts){
		timeStamp = ts;
		stringstream ss(timeStamp);
		ss>>timeCount;
	
	}
	

	string messageInput(){
		
			string message;
			
			totalMessage = "";
			cout << "\nEnter the message: ";

			while (true)
			{
				getline(cin, message);
	
				if (message == "^!")
				{
					break;
				}
				else
					totalMessage = totalMessage + message + "\n";
			}
			return totalMessage;

	}
	
	void enterMessage(string ts, string f, string t, string msg){
		
			stringstream ss(ts);
		
			ss>>timeCount;
			
			from = f;
			to = t;
			totalMessage = msg;
	}
	
	void showMessage(){

			cout<<"\n"<<from<<" ("<<to<<")>";
			cout<<totalMessage;
	}
	int getTimeCount(){
		return timeCount;
	
	}
	string getFrom(){
		return from;
	}

	
};

#endif
