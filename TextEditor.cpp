#include <iostream>
#include "TextEditor.h"





int main()
{

  Document *Doc = new Document(NULL);
  std::string full, woFunc, function, text;
  int lineNumber;

while(function != "quit")
{

  getline(std::cin, full);
  std::cin.clear();
  function = full.substr(0, full.find(' '));


    if(function.compare("delete")==0) {                          //DELETE function access
      lineNumber = std::stoi(full.substr(full.find(' ')+1), nullptr);
      Doc->deleteLn(lineNumber);
    }
    else if(function.compare("edit")==0) {                       //MODIFY function access
      lineNumber = std::stoi(full.substr(full.find(' ')+1), nullptr);
      text = full.substr( full.find('\"')+1 );
      text = text.substr(0, text.length()-1 );
      std::cin.clear();
      Doc->modify(lineNumber,text);
    }
    else if(function.compare("search")==0) {                     //SEARCH function access
      text = full.substr( full.find('\"')+1 );
      text = text.substr(0, text.length()-1 );
      std::cin.clear();
      Doc->searchDoc(text);
    }
    else if(function.compare("insertEnd")==0){               //INSERT END function access
      text = full.substr( full.find('\"')+1 );
      text = text.substr(0, text.length()-1 );
      std::cin.clear();

      Doc->insertEnd(text);
    }
    else if(function.compare("insert")==0) {                     //INSERT function access
      lineNumber = std::stoi(full.substr(full.find(' ')+1), nullptr);
      text = full.substr( full.find('\"')+1 );
      text = text.substr(0, text.length()-1 );
      std::cin.clear();
      Doc->insert(lineNumber, text);
    }
    else if(function.compare("print")==0){                        //PRINT function access
      Doc->printDoc();
    }
    else if("quit" == function){                                          //QUIT
      return 0;
    }
    else{                                                        //INVALID INPUT
      std::cout<<"Invalid input!"<<std::endl;
    }

}//end of while loop
Doc->~Document();

};




/*
* ------------------------------LINE CONSTRUCTOR--------------------------------    //WORKS
* This constructor checks for 80 character limit of a line, initializes the
* lines data to the string text parameter, and allows for initialization  of the
* next pointer
* ----------------------------O(1) time complexity------------------------------
*/
Line::Line(std::string text, Line *nxtLine){
  if(text.length() > 80) {
    throw "Line is over 80 character limit!";
  }
  else
    this->next = nxtLine;
    this->data = text;
};


/*
* -----------------------------DOCUMENT CONSTRUCTOR-----------------------------    //WORKS
* This constructor sets the head of the Document(a linked list) to the pointer
* specified as the head parameter
* ----------------------------O(1) time complexity------------------------------
*/
Document::Document(Line *head){
  this->head = head;

};

/*
* -----------------------------DOCUMENT DESTRUCTOR------------------------------    //WORKS
*
* -----------------O(n) time complexity (goes to the last line)-----------------
*/
Document::~Document(){

  Line *curr = this->head->next;
  Line * prev = this->head;


  while (head!=NULL) {
    delete prev;
    delete curr;

    prev = curr;
    curr = prev->next;
  }
};



/*
* -------------------------------INSERT FUNCTION--------------------------------    //WORKS
* This method finds goes thru the document a specified number of times until
* lineNm is reached and makes a pointer to a new line object, and sets the
* previous nodes (lines) pointer tp the new line pointer object
* ---------------O(n) time complexity (when going to the last line)-------------
*/
void Document::insert(int lineNm, std::string text){
    Line *current = this->head;
    Line *prev = nullptr;
    int i = 1;

    while(current!=nullptr){

      if(i == lineNm-1 && current->next == nullptr){
        this->insertEnd(text);
        break;
      }
      else if(i == lineNm && current!=nullptr){
        Line *newOne = new Line(text, current);
        prev->next = newOne;
        break;
      }

      prev = current;
      current = current->next;
      i++;
    }
};


/*
* ----------------------------INSERT END FUNCTION-------------------------------        //WORKS
* This method goes thru the linked list and finds where the current node's next
* pointer is a nullptr (indicating its the last line of the doc) and makes a
* new line and sets the node's next pointer as the pointer to the new line
* --------------O(n) time complexity (when accessing the last line)-------------
*/
void Document::insertEnd(std::string text){

  if(text.compare("insertEnd")==0){
  }
  if(this->head == NULL){
    this->head = new Line(text, nullptr);
  }
  else{
    Line *current = this->head;
    while(current!=NULL) {
        if(current->next==nullptr){
            Line *end = new Line(text, nullptr);
            current->next = end;
            break;
          }
        else
            current = current->next;
    }
  }
};



/*
* -----------------------------DELETE LINE FUNCTION-----------------------------       //WORKS
* This method goes thru the linked list until the specified line number (via for
* loop) and sets the prev next pointer to the line that the current line's next
* pointer points to and then deletes the current node;
* ---------------O(n) time complexity (when deleting the last line)-------------
*/
void Document::deleteLn(int lineNm){

  Line *current = head;
  Line *prev = nullptr;

  for(int i = 0; i < lineNm; i++){
    if(i == lineNm-1 && current!=nullptr){
        if(current->next != nullptr || prev != nullptr){
          prev->next = current->next;
          delete current;
          break;
        }
      }
      else if (current==nullptr) {
        break;
      }
      else{
        prev = current;
        current = current->next;
      }

    }

};

/*
* -------------------------------MODIFY FUNCTION--------------------------------
* This method goes thru the linked list until the specified line number (via for
* loop) and sets the current lines data to the string specified by the text
* parameter
* -----------------O(n) time complexity (could go thru whole list)--------------
*/
void Document::modify(int lineNm, std::string text){
  Line *current = this->head;

  for(int i = 0; i < lineNm; i++){
    if(i == lineNm-1){
      current->data = text;
      break;
    }
    else{
      current = current->next;
    }

  }
};


/*
* -------------------------------PRINT FUNCTION---------------------------------
* This method goes thru the document and prints the data at each "line" (node)
* -----------------O(n) time complexity (goes thru whole list)------------------
*/
void Document::printDoc(){
  Line *current = this->head;

  for(int i = 1; current!=nullptr; i++){

    std::cout<<i<<" ";
    std::cout<<current->data<<std::endl;
    current = current->next;

  }
};


/*
* -------------------------------SEARCH FUNCTION--------------------------------
* This method goes thru the document and finds a substring specified by the text
* parameter, if found it prints the line num and line, otherwise prints
* "not found"
* ------------------O(n) time complexity (could go thru whole list)-------------
*/
void Document::searchDoc(std::string text){
  Line *current = this->head;
  int lineNm = 1;
  while(current!=NULL) {

    if(current->data.find(text) != -1){
      std::cout<<lineNm<<" "<<current->data<<std::endl;
      current = current->next;
      lineNm++;
    }
    else if(current->next == NULL && current->data.find(text) == -1){
      std::cout<<"not found"<<std::endl;
      break;
    }
    else{
        current = current->next;
        lineNm++;
    }

  }
};
