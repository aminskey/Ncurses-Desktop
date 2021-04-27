# Ncurses Desktop
Welcome to The Ncurses Desktop Project, also known as AcornDOS.    
To run this desktop you'll need to have the following packages:    

1. build-essentials
2. gcc
3. libncurses-dev
4. libcurl-nss-dev

The Makefile for this desktop project is in the CWorkspace repo.   
Initially this project was made in the CWorskpace repo, but then I moved it in it's own.    
Some programs in the CWorkspace repo rely on the libraries in this repo.    

## Well Enough of that let's set up our repos - Must be done!!
There is a program in the CWorkspace, that has a very nice GUI for installing this desktop.    
But first we have to build it, and the rest of the cworkspace.    
**Run make all**:    
    

	Username@Computer> pwd    
	/home/UsrName/cworkspace    
	Username@Computer> make all    
	...    
	.    
	.
	.
	.
	.
	.    


_After that put bin in your src path._    
**.bashrc or .bash_profile**:    

	Username@Computer> pwd    
	/home/Usrname    
	Username@Computer> nano .bashrc    

And Enter    

	export PATH=/home/Usrname/bin:$PATH    

After that source it    
    
	Username@Computer> source ~/.bashrc   

After that restart your terminal    

## Now Time to setup your System
**Run setup**:    

	Username@Computer> setup    

**Don't Worry!** _The setup command has consideration of the type of OS you're running    
Sad thing is that it only works for Mac and Linux_    
    
You'll have to answer a few questions.   
Here are the background and forground numbers:    

        COLOR_BLACK   0    
        COLOR_RED     1    
        COLOR_GREEN   2    
        COLOR_YELLOW  3    
        COLOR_BLUE    4    
        COLOR_MAGENTA 5    
        COLOR_CYAN    6    
        COLOR_WHITE   7    
When you're Done setting up your system.    

**After that build the system again**:    

	Username@Computer> pwd    
	/home/Username/cworkspace    
	Username@Computer> make setup BOXEmu desk   

### Now Your done congrats
**Just Run**

	Username@Computer> AcornDesk    
	or even    
	Username@Computer> AcornDos    
	
