// HW4ProgramCS3353.cpp
// Brendan Bovenschen
// CWID: A20323474

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

//Node class for each tree element
class Node
{
    public:
        //left, right and parent node
        //value held in node
        string val;
        Node* left;
        Node* right;
        Node* parent;

        //constructors
        Node(Node* newParent, string inVal)
        {
            parent = newParent;
            left = NULL;
            right = NULL;
            val = inVal;
        }

        Node(Node* newParent)
        {
            parent = newParent;
            left = NULL;
            right = NULL;

        }

        Node()
        {
            parent = NULL;
            left = NULL;
            right = NULL;
        }
};

//handle operator based on character
int operate(int a, int b, char opp)
{
    switch (opp)
    {
    case '+':
        return a + b;
        break;
    case '-':
        return a - b;
        break;
    case '*':
        return a * b;
        break;
    case '/':
        return a / b;
        break;
    default: //handle unknow character
        cout << "ERROR!\n";
        return -1;
        break;
    }
}

//determine if unsigned number from string
bool isNumber(const string& s)
{
    //Pre: const char array holding either int string or other

    //iterate through string
    for (char const& ch : s) 
    {
        if (std::isdigit(ch) == 0) //check if digit
            return false;
    }
    return true;

    //Post: true if every character is a digit, else false
}

//iterate through postfix
void recurPostfix(Node* node, string* str)
{
    //Pre: current node 'node' and compiling string 'str'

    if (!node) //end on empty node
        return;

    //postorder traversal
    recurPostfix(node->left, str);
    recurPostfix(node->right, str);
    *str = *str + node->val + " ";

    //Post: added node with value 'val' to string 'str'
}

//handle compiling string of postfix
string postfix(Node* node)
{
    string strOut = "";
    recurPostfix(node, &strOut);
    return strOut;
}

//evaluation of expresion through binary tree
int evaluateTree(Node* node)
{
    //Pre: head node 'node' of tree
    
    //Tree is null
    if (!node)
        return 0;

    //return integer value if integer
    if (!node->left && !node->right)
        return stoi(node->val);

    //integer values of left and right subtree's and operator character
    int lVal = evaluateTree(node->left);
    int rVal = evaluateTree(node->right);
    char opChar = node->val[0];
    
    //handle operations of two integers and and operator
    operate(lVal, rVal, opChar);

   //Post: total integer from evaluated expresion tree
}

//recursive evaluation of postfix expression
void evaluatePostfixRecur(vector<string>& vect)
{
    //Pre: vector 'vect' holding each element

    //iterate through all element
    for (int i = 0; i < vect.size(); i++)
    {
        if (vect[i].size() == 1 && !isNumber(vect[i])) //if operator
        {
            //calcualte two elements before with operator in position i,
            //replace i with calculated number
            vect[i] = to_string(operate(stoi(vect[i - 2]), stoi(vect[i - 1]), vect[i][0]));
            //remove 2 elements before operator
            vect.erase(vect.begin() + i - 2);
            vect.erase(vect.begin() + i - 2);
        }
    }
    //continue running if more than 1 element
    if (vect.size() > 1)
        evaluatePostfixRecur(vect);

    //Post: final element of total calculated value from postfix string
}

//handle evaluation of postfix string
int evaluatePostfix(string postfix)
{
    //create vector
    vector<string> vect;
    stringstream stream(postfix);
    string temp;
    while (stream >> temp)
    {
        vect.push_back(temp);
    }
    
    //use recurrence to evaluate
    evaluatePostfixRecur(vect);

    //first element of vect cast to int
    return stoi(vect[0]);
}

class Tree
{
    private:
        Node head;

    public:
        Tree(string strIn)
        {
            //Pre: string strIn containing string of expression

            //Handle empty string
            if (strIn == "")
            {
                cout << "\nEmpty expression!";
                return;
            }

            cout << "\nBinary Tree: ";

            //divide string into each part through string stream
            stringstream stream(strIn);
            head = Node();
            Node* currNode = &head;

            //iterate through each element
            string temp;
            while (stream >> temp)
            {
                cout << temp << " ";

                //'(': if left == null, create left node, else, create right
                if (temp == "(")
                {
                    if (!currNode->left)
                    {
                        currNode->left = new Node(currNode);
                        currNode = currNode->left;
                    }
                    else
                    {
                        currNode->right = new Node(currNode);
                        currNode = currNode->right;
                    }
                }

                // ')': move currNode its parent
                else if (temp == ")")
                    currNode = currNode->parent;

                //operator: currNode parent value = operator,
                //create right node from parent
                else if (temp == "+" || temp == "-" || temp == "*" || temp == "/")
                {
                    currNode = currNode->parent;
                    currNode->val = temp;
                    currNode->right = new Node(currNode);
                    currNode = currNode->right;
                }

                //number: write number to current node
                else if (isNumber(temp))
                    currNode->val = temp;

                //handle bad string
                else
                {
                    cout << "STOPPED\nBad element: " << temp;
                    return;
                }
            }

            //handle syntax error
            //check if final node cursor position is head (complete tree)
            if (currNode != &head)
            {
                cout << "\nSyntax error!";
                return;
            }

            //Post: Expression tree with head node 'head'

            //Print operations
            cout << "\nSuccessfully created tree!";
            string post = postfix(&head);
            cout << "\nPostfix: " << post;
            cout << "\nEvaluated from Tree: " << evaluateTree(&head);
            cout << "\nEvaluated from Postfix: " << evaluatePostfix(post) << "\n";
        }       
};

//Examples from assignment
void UIExamples()
{
    string ex1 = "100";
    string ex2 = "( 100 + 200 )";
    string ex3 = "( 100 * ( 200 - 300 ) )";
    string ex4 = "( ( 100 * ( 200 + 300 ) ) * ( ( 400 - 200 ) / ( 100 + 100 ) ) )";

    Tree tree1 = Tree(ex1);
    Tree tree2 = Tree(ex2);
    Tree tree3 = Tree(ex3);
    Tree tree4 = Tree(ex4);
}

//Handle input for expression
void UIEnterExpression()
{
    cout << "\nEnter expression with every element seperated by spaces, end with 'enter':" << endl;
    cin.ignore(); //nexline
    string s;
    getline(cin, s); // read input
    Tree tree = Tree(s);
}

int main()
{
    while (true)
    {
        //User Prompt
        cout << "\nType 0 for examples, 1 to enter expression, other to quit: ";
        int input;
        cin >> input;

        //Menu Options Handler
        switch (input)
        {
        case 0:
            UIExamples();
            break;
        case 1:
            UIEnterExpression();
            break;
        default:
            return 0;
        }
    }

    return 0;
    
}
