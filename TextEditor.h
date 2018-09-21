/*
*
* A document will be represented by a linked list.                              // document = linked list
* Each line in the document is a node in the linked list.                       //line = node
* Each line in the document is 80 characters.                                   //DOCUMENT CLASS >>
* Users can insert, delete or modify lines in the document.                     //insert, delete, modify fxns
* They can print the entire document.                                           //print doc fxn
*
*/


#ifndef TEXTEDITOR_HEADER_H
#define  TEXTEDITOR_HEADER_H


struct Line {   //a node

  Line(std::string text, Line *nxtLine);        //CONSTRUCTOR
  int lineNum;
  std::string data;  //line can only be 80 characters
  Line *next;
};


struct Document {     //THE LINKED LIST

  Line *head;         //pointer to starting line

   Document(Line *head);
  ~Document();
                      //member fxns
  void insertEnd(std::string text);
  void insert(int lineNm, std::string text);
  void deleteLn(int lineNm);
  void modify(int lineNm, std::string text);
  void printDoc();
  void searchDoc(std::string text);


};




#endif
