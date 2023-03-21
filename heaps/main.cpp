/*
Name: Andrew Banks
NetID: alb1424
Compiler:ONline GBD
Description:  a program that creeates a priorty queue the use users inputs
which then changes modes for scheduling or simulation to the user likely
*/
#include <iostream>
#include <fstream>
#include"Tokenizer.h"
#include <string>
#include <vector>
#include "heap.h"
#include"Process.h"
using namespace std;

int mode =0; //abitily to change the mode from scheduding mode or sitmulate mode
int steps; // the total numbmer of steps for the program while its running
int timer=0; // overall counter for the elasped time for the program

bool processText(istream& is, bool interactive = true)
{
    // implement support for
    // exit ... exit the program
    // load file ... loads a file containing supported commands
    string line;
    string command;
    string arg1, arg2;
    int darg1,darg2,darg3;
    Tokenizer tkn;
    Heap p;
    vector<int>priority;
    vector<int>time;
    vector<int>arrival;
    vector<string>tasks;

    //Enters control loop...
    while (true)
    {
        if (!interactive)
        {
            if (is.eof())
                return true;
        }
        else
        {
            cout <<"Commands"<<endl;
            cout <<"##############"<<endl;
            cout <<"exit - Exits the interactive shell"<<endl;
            cout <<"load file - Loads a file to exceute a list of commands"<<endl;
            cout <<"register<task><priority><length> <arrives> - registers the task with the given priority and length starting at time"<<endl;
            cout <<"remove<task> - removes the specified task from the scheduling vector"<<endl;
            cout <<"display -displays a list of the tasks"<<endl;
            cout <<"mode<flag> -  0 - enters scheduling mode, 1 - enters simulting mode "<<endl;
            cout<<"step - move the simulation forward one time unit and display the results"<<endl;
            cout<<"step<time> - move the simulation forward time units and display the results"<<endl;
            cout<<"run - run the simulation until the last task has completed"<<endl;
            cout<<"runtil <time> - run the simulation until the specified time unit has been reached."<<endl;
            cout<<"reset -resets the time to 0 and empties the priority queue."<<endl;
            cout <<"###############"<<endl;
        }
        //varname.field you wan tout of your class

        //gets line from input stream
        getline(is, line);
        tkn.setString(line);

        //first word in stream should always be a command
        tkn.readWord(command);

        //Below we start checking if the command is recognized

        if (command == "exit")
        {
            cout << "Exiting ...." << endl;
            return false;
        }

        if (command == "load")
        {
            // load expects a filename .. so read one more word
            if (!tkn.readWord(arg1))
            {
                cout << "Missing file name" << endl;
                continue; // skip back to the top of the read loop
            }

            //Attempts to read input file
            ifstream fin;
            bool status = true;
            fin.open(arg1);
            if (fin.is_open())
            {
                status = processText(fin, false);
            }
            else
            {
                cout << "Failed to open the file" << endl;
            }
            fin.close();
            if (!status)
                return false;
        }

        if (command == "register")
        {
            if(mode == 0)// when the program is in sheduling mode
            {
                if(tkn.readWord(arg1)) // task name
                {
                    if(tkn.readInteger(darg1)) // priority in an heap
                    {
                        if(darg1<=100 or darg1>=1)
                        {
                            if(tkn.readInteger(darg2)) // length which is measured in steps
                            {
                                if(darg2 >=1)
                                {
                                    if(tkn.readInteger(darg3)) //arrival time
                                    {
                                        if(darg3 >=0)
                                        {

                                            priority.push_back(darg1);
                                            tasks.push_back(arg1);// the name
                                            time.push_back(darg2); // the length
                                            arrival.push_back(darg3); // when the heap takes effect
                                            cout<<"Task "<<arg1<<" has been register"<<endl;
                                        }
                                        else
                                        {
                                            cout<<"Failed to register! arrival must be postive"<<endl;
                                        }
                                    }
                                }
                                else
                                {
                                    cout<<"Failed to register! length must be postive"<<endl;
                                }
                            }
                        }
                        else
                        {
                            cout<<"Failed to register! Priority must be within 1 - 100"<<endl;
                        }
                    }
                }
            }
            else//whenever it is not sheduling mode
            {
                cout<<"Your are in the wrong mode"<<endl;
            }

        }
        else if (command == "remove")
        {
            if(mode == 0) //to ensure the the program is in schedule mode
            {
                if(tkn.readWord(arg1))
                {
                    //remove tasks form the vector
                    for(int i =0; i < tasks.size();i++)
                    {
                        if(arg1 == tasks[i])
                        {
                            tasks.erase(tasks.begin()+i);
                            arrival.erase(arrival.begin()+i);
                            time.erase(time.begin()+i);
                            p.remove(i);
                        }
                    }
                }
            }
            else
            {
                cout<<"You must be in scheduling mode"<<endl;
            }
        }
        else if (command == "display")
        {
            if(mode ==0) //schedualing mode
            {
                cout<<"Task yet to be schedule"<<endl;
                for(unsigned int i=0;i<tasks.size();i++)
                {
                    cout<<tasks[i]<<"@ "<<priority[i]<<" for 0 out of "<<time[i]<<" arriving @ "<<arrival[i]<<endl;
                }
            }
            else //when the program is in simulation mode
            {
                if(p.isEmpty()==true)// if the heap is empty
                {
                    cout<<"Next step: "<<timer<<endl; // the actul time step that its on
                    cout<<"Current Task: None"<<endl;
                    cout<<"Task yet to be schedule"<<endl;
                    for(unsigned int i=0;i<tasks.size();i++)
                    {
                        cout<<tasks[i]<<"@ "<<priority[i]<<" for "<<steps<<" out of "<<time[i]<<" arriving @ "<<arrival[i]<<endl;
                    }
                }
                else // if the heap has any values within it
                {int i =0;
                    while (steps < timer)
                    {
                        if(steps < time[i]){
                        steps++;
                        }
                        else
                        {
                            i++;
                        }
                    }
                    cout<<"Next Step:"<<timer<<endl; // the total length of time
                    cout<<"Current Task: "<<tasks[i]<<"@ "<<priority[i]<<" for "<<steps<<" out of "<<time[i]<<" arriving @ "<<arrival[i]<<endl;
                    cout<<"Task yet to be schedule"<<endl;
                    for(unsigned int w=i;w<tasks.size();w++)// displays the remaining number in the list
                    {
                        cout<<tasks[w]<<"@ "<<priority[w]<<" for 0 out of "<<time[w]<<" arriving @ "<<arrival[w]<<endl;
                    }
                }
            }

        }
        else if (command == "mode")
        {
            if(tkn.readInteger(darg1))
            {
                if(darg1==0)
                {
                    mode = 0; // enter into schedule mode
                    cout<<"Entering scheduling mode ....removing all schedule task"<<endl;
                    for(int i =0; i < tasks.size();i++)
                    {
                        tasks.erase(tasks.begin()+i);
                        arrival.erase(arrival.begin()+i);
                        time.erase(time.begin()+i);
                        priority.erase(priority.begin()+i);
                        p.remove(i);
                    }
                    cout<<endl;
                }
                else if(darg1 == 1) //when you enter into simulating mode
                {
                    mode = 1; //enters into simulated mode 
                    cout<<"Entering simulting mode ...."<<endl;
                    cout<<endl;
                }
                else// whenever the user inputs any other number other than 1 or 0
                {
                    cout<<"Please enter 0 or 1 to pick a mode"<<endl;
                }
            }
        }
        else if(command=="step")
        {
            if(mode == 1)
            {
                if(tkn.readInteger(darg1)) // step number
                {
                    int i =0;
                    timer = timer +darg1;
                    //move the simulation forward  x time units and display the results
                    while (steps < timer)
                    {
                        if(steps < time[i]){
                            if(timer==arrival[i+1])
                            {
                                int n =i+1;
                                int w =priority[n];
                                //add the next item of all of the list to the queue
                                p.add(w,priority,time,arrival,tasks);
                                cout<<"Added "<<tasks[n]<<" @ "<<priority[n]<<" for 0 out of "<<time[n]<<" arriving @ "<<arrival[n]<<endl;
                            }
                        steps++;
                        }
                        else
                        {
                            i++;
                        }
                    }
                    cout<<"Time Step: "<<timer<<endl;
                    cout<<"Current Task: "<<tasks[i]<<": "<<steps<<" out of "<<time[i]<<" arriving @ "<<arrival[i]<<endl;
                    //p.display(i,time,arrival,tasks);
                }
                else // step by itself
                {
                    int i =0;
                    timer++; //timer +1
                    //move the simulation forward one time unit and display the results
                    while (steps < timer)//just to check to see where
                    {
                        if(steps<time[i]){
                            if(timer==arrival[i+1])// see if the next task arrival time matches with the current timer
                            {
                                int n =i+1;
                                int w =priority[n];
                                //add the next item of all of the list to the q
                                p.add(w,priority,time,arrival,tasks);
                                cout<<"Added "<<tasks[n]<<" @ "<<priority[n]<<" for 0 out of "<<time[n]<<" arriving @ "<<arrival[n]<<endl;
                            }
                        steps++;
                        }
                        else
                        {
                            i++;
                        }
                    }
                    cout<<"Time Step: "<<timer<<endl;
                    cout<<"Current Task: "<<tasks[i]<<": "<<steps<<" out of "<<time[i]<<" arriving @ "<<arrival[i]<<endl;
                    p.display(i,time,arrival,tasks);
                 }
            }
            else
            {
                cout<<"You need to be in simulation mode"<<endl;
            }
        }
        else if(command=="run")
        {
            if(mode == 1)
            {
                int i =0;
                    while(i<tasks.size()) // seeing how to add time to the steps
                    {
                        while(steps <= time[i]){
                            if(timer==arrival[i+1])
                            {
                                int n =i+1;
                                int w =priority[n];
                                //add the next item of all of the list to the q
                                p.add(w,priority,time,arrival,tasks);
                                cout<<"Added "<<tasks[n]<<" @ "<<priority[n]<<" for 0 out of "<<time[n]<<" arriving @ "<<arrival[n]<<endl;
                            }
                            cout<<"Time Step: " <<timer<<endl;
                            cout<<endl;
                            cout<<"Current Task "<<tasks[i]<<": "<<steps<<" out of "<<time[i]<<" arriving @ "<<arrival[i]<<endl;
                            steps++;
                            timer++;
                        }
                        cout<<"Task "<<tasks[i]<<" is finished"<<endl;
                        cout<<endl;
                        p.remove(i);
                        steps=1;
                        i++;
                    }

            }
            else
            {
                cout<<"You need to be in simulation mode"<<endl;
            }
        }

        else if(command=="runtil")
        {
            if(mode == 1) // when the program is in
            {
                // use a while loop until steps = an int
                if(tkn.readInteger(darg1))
                {
                    int i=0;
                    int lim=0; // varable to ensure that the limit is reached
                    while(i < tasks.size()){
                        if(timer==arrival[i+1])
                        {
                            int n =i+1;
                            int w =priority[n];
                            //add the next item of all of the list to the q
                            p.add(w,priority,time,arrival,tasks);
                            cout<<"Added "<<tasks[n]<<" @ "<<priority[n]<<" for 0 out of "<<time[n]<<" arriving @ "<<arrival[n]<<endl;
                        }
                        while(steps <= time[i]){
                            if(lim < darg1){
                            cout<<"Current Step:" <<timer<<endl;
                            cout<<tasks[i]<<": "<<steps<<" out of "<<time[i]<<" arriving @ "<<arrival[i]<<endl;
                            steps++;
                            timer++;
                            lim++;
                           }
                            else
                            {
                                lim=1;
                                break;
                            }
                        }
                        cout<<"Task "<<tasks[i]<<" is finished"<<endl;
                        cout<<endl;
                        p.remove(i);
                        steps=1;
                        i++;
                        }
                }

                            }

            else
            {
                cout<<"You need to be in simulation mode"<<endl;
            }
        }
        else if(command=="reset")
        {
            if(mode == 1)
            {
                steps = 0;
                timer=0;
               //clear the vectors and heap
                //remove tasks form the vector
            }
            else
            {
                cout<<"You need to be in simulation mode"<<endl;
            }
        }
        else
        {
            cout<<"Please enter in one of the suggestions"<<endl;
        }
    }


}





int main()
{

    processText(cin);
    return 0;
}
