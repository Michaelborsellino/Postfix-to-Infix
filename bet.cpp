#include<iostream>
#include<stack>
#include<string>
#include<cctype>
#include<sstream>
#include<vector>

//default constructor
BET::BET()
   :rootnode{nullptr}
{
}

//parameterized constructor
BET::BET(const std::string postfix)
     :rootnode{nullptr}
{
  buildFromPostfix(postfix);
}

//copy constructor
BET::BET(const BET& x)
        :rootnode{nullptr}
{
  rootnode = clone(x.rootnode);
}

//Destructor
BET::~BET()
{
  makeEmpty(rootnode);
}

//equals operator overload
const BET& BET::operator=(const BET &rhs)
{
  rootnode = rhs.clone(rhs.rootnode);
  return *this;
}

//public member function that calls private member printInfix
void BET::printInfixExpression()
{
  printInfixExpression(rootnode);
 std::cout<<std::endl; 
}
//public member function that calls private member printPostfix
void BET::printPostfixExpression()
{
  printPostfixExpression(rootnode);
  std::cout<<std::endl;
}

//public member function that calls recursive size
size_t BET::size()
{
  return size(rootnode);
}

//public member function that calls recursive leaves
size_t BET::leaf_nodes()
{
  return leaf_nodes(rootnode);
}

//function that checks if tree is empty
bool BET::empty()
{
  return (rootnode == nullptr);
}

//outputs the infix expression of the tree
void BET::printInfixExpression(BinaryNode *n)
{
  //for case where there is only one node 
  if(isalnum(n->data[0]))
    std::cout<<n->data<<" ";
  else
  {
    //iterates through left side of the tree
    if(isalnum(n->left->data[0]))
      printInfixExpression(n->left);
    //checks for operator precidence and outputs parentheses as needed
    else if((!isalnum(n->left->data[0]))&& ((((n->left->data == "-")||(n->left->data == "+"))&&((n->data=="*")||(n->data=="/")||(n->data =="-")||(n->data=="+")))
                                              ||(((n->left->data == "*")||(n->left->data == "/"))&&((n->data =="*") ||(n->data =="/")) )))
	    {
      std::cout<<"( ";
      printInfixExpression(n->left);
      std::cout<<" ) ";
    }
    else
      printInfixExpression(n->left);
    //prints out operator node
    std::cout<<n->data<<" ";
    //iterates through right side of tree
    if(isalnum(n->right->data[0]))
      std::cout<<n->right->data<<" ";
    else
    {
      if(isalnum(n->right->data[0]))
        printInfixExpression(n->right);
      //checks for operator precidence and outputs parentheses as needed
      else if((!isalnum(n->right->data[0]))&& ((((n->right->data == "-")||(n->right->data == "+"))&&((n->data=="*")||(n->data=="/")||(n->data =="-")||(n->data=="+")))
                                              ||(((n->right->data == "*")||(n->right->data == "/"))&&((n->data =="*") ||(n->data =="/")) )))

      {
        std::cout<<"( ";
        printInfixExpression(n->right);
        std::cout<<" ) ";
      }
      else
        printInfixExpression(n->right);
    }
  }
   
}

//recursively deletes all nodes in tree
void BET::makeEmpty(BinaryNode *&t)
{
  if(t == nullptr)
    return;
  makeEmpty(t->left);
  makeEmpty(t->right);
  delete t;
}

//makes new branches of the tree
BET::BinaryNode* BET::clone(BinaryNode *t) const
{
  if(t == nullptr)
    return nullptr;
  else
    return new BinaryNode{t->data, clone(t->left), clone(t->right)};
}

//recursively prints out the postfix expression of the tree
void BET::printPostfixExpression(BinaryNode *n)
{
  if(n->left == nullptr)
    std::cout<<n->data<<" ";
  else
  {
    printPostfixExpression(n->left);
    printPostfixExpression(n->right);
    std::cout<<n->data<<" ";
  }  
}

//recursively prints the size of the tree Returns on nullptr
size_t BET::size(BinaryNode *t)

{
  if(t->left == nullptr)
    return 1;
  else
    return size(t->left) + size(t->right) + 1;
}

//recursively prints the amount of leaf nodes on the tree, returns on nullptr
size_t BET::leaf_nodes(BinaryNode *t)
{
  if(t->left == nullptr)
    return 1;
  else
    return leaf_nodes(t->left) + leaf_nodes(t->right);
}

//constructor initalizer
bool BET::buildFromPostfix(const std::string postfix)
{
  std::stack<BET::BinaryNode*> nodestack;
  std::istringstream inputstream(postfix);
  std::string word;
  std::vector<std::string> inputvector;
  int operators = 0, operands = 0;
 
  while(inputstream>>word)
  {
    //pushes expression into a vector for error checking
    inputvector.push_back(word);
    if(isalnum(word[0]))
    {
      ++operands;
    }
    else
    {
      ++operators;
    }
  }
  int finalop = operators + 1;
  //error checking. checks for incorrect number of operators vs operands and also if the postfix 
  //expression begins/ends with an operator or not returns false if either condition is met.
  if((operands != finalop)||((inputvector.size() > 1)&&((!isalnum(inputvector[0][0]))||(isalnum(inputvector[inputvector.size()-1][0])))))
  {
    std::cout<<"Error creating tree\n";
    return false;
  }
  //building the actual tree using a stack
  for(size_t i = 0; i < inputvector.size(); ++i)
  {
    BinaryNode * tempnode = new BinaryNode();
    tempnode->data = inputvector[i];
    if(isalnum(tempnode->data[0]))
    {
      nodestack.push(tempnode);
      
    }
    else 
    {
      tempnode->right = nodestack.top();
      nodestack.pop();
      tempnode->left = nodestack.top();
      nodestack.pop();
      nodestack.push(tempnode);
      
    }
    
  }
  //setting the rootnode value
  rootnode = nodestack.top();
  return true;
}
