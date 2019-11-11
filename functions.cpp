#include "header.h"

prospect::prospect () { //constructor for prospect
  name = NULL;
  position = NULL;
  school = NULL;
  age = 0;
  height = NULL;
  rank = 0;
  report = NULL;
  left = NULL;
  right = NULL;
};
prospect::~prospect () { //destructor for prospect
  if (name) {
    delete [] name;
    name = NULL;
  }
  if (position) {
    delete [] position;
    position = NULL;
  }
  if (school) {
    delete [] school;
    school = NULL;
  }
  if (height) {
    delete [] height;
    height = NULL;
  }
  if (report) {
    delete [] report;
    report = NULL;
  }
  if (left) {
    delete left;
    left = NULL;
  }
  if (right) {
    delete right;
    right = NULL;
  }
};

team::team () { //constructor for team
  teamName = NULL;
  drafted = NULL;
  next = NULL;
};
team::~team () { //destructor for team
  if (teamName) {
    delete [] teamName;
    teamName = NULL;
  }
  if (drafted) {
    delete drafted;
    drafted = NULL;
  }
  if (next) {
    delete next;
    next = NULL;
  }
};

draft::draft () { //constructor for draft
  root = NULL;
  pick = 1;
  head = NULL;
  onClock = head;
};
draft::~draft () { //destructor for draft
  if (root) {
    delete root;
    root = NULL;
  }
  if (head) {
    delete head;
    head = NULL;
  }
  if (onClock) {
    onClock = NULL;
  }
};

int draft::bstFunction (prospect * root, prospect * tempPro) { //This determines whether to go left or right for when adding a prospect to the tree
  return strcmp (root -> name, tempPro -> name);
}
int draft::bstFunction2 (prospect * root, char * NAME) { //This determines whether to go left or right for when searching for a prospect based on the name
  return strcmp (root -> name, NAME);
}

prospect * draft::retrieveProspect (prospect *& root, char * name) { //This retrieves a prospect from the tree
  if (!root) {
    return NULL;
  }
  else if ((bstFunction2 (root, name)) < 0) { //goes left
    retrieveProspect (root -> left, name);
  }
  else if ((bstFunction2 (root, name)) > 0) { //goes right
    retrieveProspect (root -> right, name);
  }
  else if ((bstFunction2 (root, name)) == 0) { //Found prospect
    return root;
  }
}

int draft::readTeamIn () { //this function reads in the teams from the teams.txt file
  team * current = head;
  ifstream file_in;
  file_in.open("teams.txt");
  if (file_in) {
    while (file_in && !file_in.eof()) {
      if (!head) {
        head = new team;
        head -> next = NULL;
        current = head;
      }
      else {
        team * tempTeam = new team;
        current -> next = tempTeam;
        current = current -> next;
        current -> next = NULL;
      }
      if (head) {
        char temp[500];
        file_in.get (temp, 100, '\n');
        file_in.ignore(100, '\n');
        current -> teamName = new char[strlen(temp)+1];
        strcpy (current -> teamName, temp);
      }
    }
  }
}

int draft::readProspectIn () { //this function reads in the prospects from the Prospects.txt file
  char temp[500];
  int rankTemp = 0;
  int ageTemp = 0;
  ifstream file_in;
  file_in.open("prospects.txt");
  if (file_in) {
    file_in.get (temp, 100, '|');
    file_in.ignore(100, '|');
    while (file_in && !file_in.eof()) {
      prospect * tempPro = new prospect;
      tempPro -> name = new char[strlen(temp)+1];
      strcpy (tempPro -> name, temp);

      file_in.get (temp, 100, '|');
      file_in.ignore(100, '|');
      tempPro -> position = new char[strlen(temp)+1];
      strcpy (tempPro -> position, temp);

      file_in.get (temp, 100, '|');
      file_in.ignore(100, '|');
      tempPro -> school = new char[strlen(temp)+1];
      strcpy (tempPro -> school, temp);

      file_in >> ageTemp;
      file_in.ignore(100, '|');
      tempPro -> age = ageTemp;

      file_in.get (temp, 100, '|');
      file_in.ignore(100, '|');
      tempPro -> height = new char[strlen(temp)+1];
      strcpy (tempPro -> height, temp);

      file_in >> rankTemp;
      file_in.ignore(100, '|');
      tempPro -> rank = rankTemp;

      file_in.get (temp, 500, '\n');
      file_in.ignore(500, '\n');
      tempPro -> report = new char[strlen(temp)+1];
      strcpy (tempPro -> report, temp);

      insertProspect (root, tempPro);
      file_in.get (temp, 100, '|');
      file_in.ignore(100, '|');
    }
  }
}

int draft::onTheClock () { //displays current team that is on the clock
  if (!onClock) {
    onClock = head;
  }
  cout << "The " << onClock -> teamName << " are on the clock\n";
  return 1;
}

int draft::traverseTeam () { //next team is on the clock
  if (!onClock) {
    return 0;
  }
  else if (!onClock -> next) {
    return 0;
  }
  else {
    onClock = onClock -> next;
    ++pick;
    return 1;
  }
}

int draft::draftOrder () { //displays the draft order
  int i = 1;
  team * curr = head;
  cout << "///////////////////////////////////////////////////////\n";
  while (curr->next) {
    cout << i << ". " << curr -> teamName << "\n";
    curr = curr -> next;
    ++i;
  }
  return 1;
}

int draft::insertProspect (prospect *& root, prospect * tempPro) { //inserts a prospect into the BST
  if (!root) {
    root = tempPro;
    root -> left = NULL;
    root -> right = NULL;
    return 1;
  }
  else {
    if ((bstFunction (root, tempPro)) < 0) {
      insertProspect (root -> left, tempPro); //traverse to the left
    }
    else {
      insertProspect (root -> right, tempPro); //traverse to the right
    }
  }
}

int draft::wrapDisplayAvailable () { //wrapper for display available
  cout << "///////////////////////////////////////////////////////\n";
  cout << "Available: \n";
  displayAvailable (root);
  //cout << "///////////////////////////////////////////////////////\n";
}

int draft::displayAvailable (prospect * root) { //displays all available prospects from the BST
  if (!root) {
    return 0;
  }

  displayAvailable (root -> left);
  cout << root -> name << "\n";
  displayAvailable (root -> right);
}

int draft::wrapDisplayProspect () { //wrapper for the display prosepect
  char * name = new char[100];
  cout << "Please input full name of Prospect\n";
  cin.get (name, 100, '\n');
  cin.ignore (100, '\n');
  prospect * retrieved = retrieveProspect (root, name); //retrieves the prospected to be displayed
  if (!retrieved) {
    cout << "Could not find this name!\n";
    return 0;
  }
  displayProspect (retrieved);
  return 1;
}

int draft::displayProspect (prospect * root) { //displays a single prospect
  if (!root) {
    return 0;
  }
  else {
    cout << "/////////////// " << root -> name << " ///////////////\n"
      << "Position: " << root -> position << "\n"
      << "School: " << root -> school << "\n"
      << "Age: " << root -> age << "\n"
      << "Height: " << root -> height << "\n"
      << "Rank: " << root -> rank << "\n"
      << "Report: " << root -> report << "\n";
  }
}

int draft::draftingProspect () { //user selects a prospect and displays the selection
  char * NAME = new char[100];
  cout << "Full name of prospect you would like to draft please!\n";
  cin.get (NAME, 100, '\n');
  cin.ignore (100, '\n');
  prospect * selection = removeProspect(root, NAME); //catches the prospect removed from the BST
  if (selection) {
    onClock -> drafted = selection; //adds selected prospect to the team that is currently on the clock
    cout << "///////////////////////////////////////////////////////\n";
    if (pick == 1) {
      cout << "With the " << pick << "st pick in the NBA draft!\n";
    }
    else if (pick == 2) {
      cout << "With the " << pick << "nd pick in the NBA draft!\n";
    }
    else if (pick == 3) {
      cout << "With the " << pick << "rd pick in the NBA draft!\n";
    }
    else {
      cout << "With the " << pick << "th pick in the NBA draft!\n";
    }
    cout << "The " << onClock -> teamName << " select " << selection -> name << ", " << selection -> position
      << " from " << selection -> school << "!!\n \n";

    return 1;
  }
  else {
    cout << "Player does not exist. Try again\n";
    return 0;
  }
}

prospect * draft::removeProspect (prospect *& root, char * name) { //removes a prospect from the BST and returns them
  if (!root) {
    return NULL;
  }
  else if ((bstFunction2 (root, name)) < 0) { //traverse left
    removeProspect (root -> left, name);
  }
  else if ((bstFunction2 (root, name)) > 0) { //traverse right
    removeProspect (root -> right, name);
  }
  else if ((bstFunction2 (root, name)) == 0) { //found prospect
    if (!root -> right && !root -> left) { //at a leaf
      prospect * temp = root;
      root = NULL;
      return temp;
    }
    else if (root -> left && !root -> right) { //has only a left subtree
      prospect * temp1 = root -> left;
      prospect * temp2 = root;
      root -> left = NULL;
      root = temp1;
      return temp2;
    }
    else if (root -> right && !root ->right -> left) { //has a right subtree and right doesn't have a left subtree
      prospect * temp1 = root -> right;
      prospect * temp2 = root;
      root -> right = NULL;
      temp1 -> left = root -> left;
      root -> left = NULL;
      root = temp1;
      return temp2;
    }
    else if (root -> right && root -> right -> left) { //has a right subtree and right has a left subtree
      prospect * current = root -> right -> left;
      prospect * previous = root -> right;
      while (current -> left != NULL) { //traverse to the inorder successor
        current = current -> left;
        previous = previous -> left;
      }
      previous -> left = current -> right;
      current -> right = NULL;
      current -> right = root -> right;
      root -> right = NULL;
      current -> left = root -> left;
      root -> left = NULL;
      prospect * temp = root;
      root = current;
      return temp;
    }
  }
}

int draft::copyProspect (prospect * source, prospect *& dest) { //copy function for prospects
  if (!source) {
    return 0;
  }
  else {
    strcpy (dest -> name, source -> name);
    strcpy (dest -> position, source -> position);
    strcpy (dest -> school, source -> school);
    dest -> age = source -> age;
    strcpy (dest -> height, source -> height);
    dest -> rank = source -> rank;
    strcpy (dest -> report, source -> report);
    return 1;
  }
}

int draft::displayWrapperPrevious () { //wrapper function for displayPrevious
  int i = 1;
  cout << "//////// Previously Selected ////////\n";
  return displayPrevious (head, i);
}

int draft::displayPrevious (team * head, int i) { //displays the previous draft selections
  if (!head||!head -> drafted) { //at end of list or a team that hasn't drafted yet
    return 0;
  }
  else {
    cout << i << ". " << head -> teamName << ": " << head -> drafted -> name << ", " << head -> drafted -> position << "\n";
    ++i;
    return 1 + displayPrevious (head -> next, i);
  }
}

