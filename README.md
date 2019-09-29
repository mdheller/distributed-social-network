# distributed_social_network


How to run:




---On Standalone Local PC---

In the System Class's Constructor, change the value for "fileServerPath" variable to path to "Files" folder which contains all the necessary centralized data. 
For Example, If you have the "Files" folder in your home directory, change the path to:

fileServerPath = "/home/{username}/Files"

*Do Not End with Forward Slash*

Make sure that the folder already has the vital files i.e.
_All.txt
_MessageBuffer.txt
Time.txt

Time.txt should contain "0" if the system is fresh.
Rest of the files can be present or later created during runtime automatically depending upon whether a user/group is created or not.

Compile main.cpp using g++ and run.





---On a Network---

On the file server i.e the dedicated PC to store and retrive files, install the nfs-kernel-service.
On the client PC i.e the PC which will be used to send receive messages, install nfs-common.
Complete procedure is given in detail in the video.

Paste the "Files" folder on the server.
Mount the same on client PC.

In the System Class's Constructor, change the value for "fileServerPath" variable to path to "Files" folder which contains all the necessary centralized data. 
For Example, If you have the "Files" folder in your home directory, change the path to:

fileServerPath = "/home/{username}/Files"

*Do Not End with Forward Slash*

Make sure that the folder already has the vital files i.e.
_All.txt
_MessageBuffer.txt
Time.txt

Time.txt should contain "0" if the system is fresh.
Rest of the files can be present or later created during runtime automatically depending upon whether a user/group is created or not.

Compile main.cpp using g++ and run.


