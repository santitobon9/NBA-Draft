#include <cstring>
#include <cctype>
#include <iostream>
#include <fstream>
using namespace std;

struct prospect {
  char * name;
  char * position;
  char * school;
  int age;
  char * height;
  int rank; //rank based on all available prospects
  char * report;
  prospect * left;
  prospect * right;
  prospect ();
  ~prospect ();
};

struct team {
  char * teamName;
  prospect * drafted; //prospect that was drafted by this team
  team * next;
  team ();
  ~team ();
};

class draft {
  private:
    prospect * root; //root of the prospect BST
    int pick; //the current pick
    team * head; //the head of the team LLL
    team * onClock; //pointer that points the the team that is currently selecting

  public:
    //prospect * root;
    //team * head;
    int bstFunction (prospect * root, prospect * tempPro);
    int bstFunction2 (prospect * root, char * NAME);
    prospect * retrieveProspect (prospect *& root, char * name);
    int readTeamIn ();
    int readProspectIn ();
    int onTheClock ();
    int traverseTeam ();
    int draftOrder ();
    int insertProspect (prospect *& root, prospect * tempPro);
    int wrapDisplayAvailable ();
    int displayAvailable (prospect * root);
    int wrapDisplayProspect ();
    int displayProspect (prospect * root);
    int displayWrapperPrevious ();
    int displayPrevious (team * head, int i);
    int draftingProspect ();
    prospect * removeProspect (prospect *& root, char * name);
    int copyProspect (prospect * source, prospect *& dest);
    draft ();
    ~draft ();
};

