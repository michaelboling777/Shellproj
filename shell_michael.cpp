// Michael Boling
// CSC 360
// Professor: Dr. Siming Liu

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>

using namespace std;

int main(void)
{
    vector<int> store;
    int add;
    int add2 = 0;
    int manipulate_var;
    int add3;

    int argc = 0;

    while (1)
    {

        pid_t pid;

        // prompt
        cout << "mb7593s$ ";

        string cmd;
        getline(cin, cmd);

        // ignore empty input
        if (cmd == "" || cmd.size() == 0)
        {
            continue;
        }

        // built-in: help

        if (cmd == "help")
        {

            cout << "\nMichael Boling\nCSC360 Operating Systems\nProject #2: My Shell - Writing Your Own Shell\nThis shell supports the following commands : help, exit, history\n\n";
        }

        // built-in: exit

        if (cmd == "exit")
        {
            cout << "Exit!\n(shell exits)\n";
            exit(0);
        }

        // built-in: history

        if ((cmd == "history") && (store.size() >= 5))
        {

            cout << "history\n";
            for (int i = (store.size() - 5); i < store.size(); i++)
            {

                cout << store[i] << endl;
            }
        }
        else if ((store.size() <= 4) && (cmd == "history"))
        {
            cout << "Not atleast 5 accounts of child process IDs needed to show the history\n";
        }

        // using fork:

        if ((cmd == "pwd") || (cmd == "ls") || (cmd == "date"))
        {
            pid = fork();
            if (pid == 0) // child begins
            {

                int x = getpid();

                if (cmd == "ls")
                {

                    execl("/bin/ls", "ls", NULL);
                }
                else if (cmd == "date")
                {
                    execl("/bin/date", "date", NULL);
                }
                else if (cmd == "pwd")
                {
                    execl("/bin/pwd", "pwd", NULL);
                }

                // child ends
            }
            else // parent begins
            {
                if (add2 == 0)
                {
                    manipulate_var = getpid();
                    add3 = getpid();
                }
                add = manipulate_var;

                waitpid(-1, &manipulate_var, 0);

                // parent ends
            }

            manipulate_var++;

            add2++;
            add++;
            add3 = (1 + add3);
            store.push_back(add3);
        }
        else if ((cmd == "history") || (cmd == "exit") || (cmd == "help"))
        {
            continue;
        }
        else
        {
            cout << "Error: Command could not be executed" << endl;
        }
    }
}
