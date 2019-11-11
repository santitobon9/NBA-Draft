#include "header.h" 
//Santiago Tobon

int main () {
    int quit = 0;
    int done = 0;
    int choice = 0;
    draft myDraft; 

    myDraft.readTeamIn ();
    myDraft.readProspectIn (); 
    cout << "Welcome to the 2018 NBA Draft!!!\n";
         
    while (quit == 0) {
        myDraft.onTheClock (); 
        while (done == 0) {
            cout << "///////////////////////////////////////////////////////\n"
                 << "Options: \n"
                 << "1. View All Available Prospects \n"
                 << "2. View Scouting report of Specific Prospect \n"
                 << "3. View Previous Selections \n"
                 << "4. View Draft Order \n"
                 << "5. Draft a Prospect!! \n"
                 << "6. Quit Draft \n";
            cin >> choice;
            cin.ignore (10, '\n');
            
            if (choice == 1) { //Views Available Prospects
                myDraft.wrapDisplayAvailable ();
            }
            else if (choice == 2) { //Views Specific Prospect
                myDraft.wrapDisplayProspect (); 
            }
            else if (choice == 3) { //Views Previous Selections
                if (myDraft.displayWrapperPrevious () == 0) {
                    cout << "No players have been selected yet.\n";
                }
            }
            else if (choice == 4) { //Views Draft Order
                myDraft.draftOrder();      
            }
            else if (choice == 5) { //Drafts a Prospect
                if (myDraft.draftingProspect() == 1) {
                    done = 1;
                }                 
            }
            else if (choice == 6) { //Quits
                done = 1;
                quit = 1;         
            }
            else {
                cout << "Invalid Input!!! Try again. \n"; 
            }
        }
        if (myDraft.traverseTeam() == 0) {
            quit = 1;
        }
        done = 0; 
    }
}
        
