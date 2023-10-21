// Name:Cali Mullen
// Course: DSA anaylsis and design

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
struct Course
{
    string CourseNumber; // unique identifier
    string CourseName;
    vector<string> Prerequisites;
};
struct Node
{
    Course course;
    Node* left;
    Node* right;

    // Default contructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Initialize with a Course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};
class BinaryTree
{
public:
    BinaryTree();
    void InsertNode(Course course);
    void AddNode(Node* node, Course course);
    void PrintCourseList();
    void PrintCourseInformation(string courseNumber, bool isPrerequisites);
private:
    Node* rootNode;
    void PrintList(Node* node);

};

BinaryTree::BinaryTree()
{
    rootNode = nullptr;
}
void BinaryTree::InsertNode(Course course)
{
    // If rootNode is empty
    if (rootNode == nullptr)
    {
        // Add node to the rootNode
        rootNode = new Node(course);
    }
    else
    {
        // Traverse the tree to add the next node
        AddNode(rootNode, course);
    }
}
void BinaryTree::AddNode(Node* node, Course course)
{
    // If node is larger then add to left
    if (node->course.CourseNumber > course.CourseNumber)
    {
        // If left node is empty
        if (node->left == nullptr)
        {
            // Add to the left node
            node->left = new Node(course);
        }
        else
        {
            // Traverse left 
            AddNode(node->left, course);
        }
    }
    else
    {
        // If right node is empty
        if (node->right == nullptr)
        {
            node->right = new Node(course);
        }
        else
        {
            // Traverse right 
            AddNode(node->right, course);
        }
    }
}
void BinaryTree::PrintCourseList()
{
    PrintList(rootNode);
}
void BinaryTree::PrintList(Node* node)
{
    if (node != nullptr)
    {
        //PrintList not left
        PrintList(node->left);
        //output CourseNumber, CourseName
        cout << node->course.CourseNumber << ", " << node->course.CourseName << endl;
        //PrintList right
        PrintList(node->right);
    }
}
void BinaryTree::PrintCourseInformation(string courseNumber, bool isPrerequisites)
{
    Node* currentNode = rootNode;

    // keep looping downwards until bottom reached or matching courseNumber found
    while (currentNode != nullptr)
    {
        // if match found, return current courseNumber
        if (currentNode->course.CourseNumber == courseNumber)
        {
            // Print the Course information
            cout << currentNode->course.CourseNumber << ", ";
            cout << currentNode->course.CourseName << endl;
            // Check for Prerequisites and check that course we are looking for is not a Prerequisites
            if (currentNode->course.Prerequisites.size() > 0 && isPrerequisites == false)
            {
                cout << "Prerequisites: " << endl;
                for (int i = 0; i < currentNode->course.Prerequisites.size(); i++)
                {
                    PrintCourseInformation(currentNode->course.Prerequisites.at(i), true);
                }
            }
            return;
        }
        // if Course Number is smaller than current node then traverse left
        if (currentNode->course.CourseNumber > courseNumber)
        {
            currentNode = currentNode->left;
        }
        // else larger so traverse right
        else
        {
            currentNode = currentNode->right;
        }
    }
    cout << "Could not find the course!" << endl;
}

BinaryTree LoadDataStructure(string fileName)
{
    // Create a binary tree object
    BinaryTree binaryTree;

    cout << "Loading file " << fileName << endl;
    // Store the course numbers that are in the document
    vector<string> courseNumbers;
    ifstream iFile(fileName);
    // Check the file is open
    if (iFile.is_open())
    {
        string line;
        while (iFile.good())
        {
            string line, spliLine;
            vector<string> words;
            // Get the next line
            getline(iFile, line);
            stringstream linestream(line);
            // Split the line at ','
            while (getline(linestream, spliLine, ','))
            {
                words.push_back(spliLine);
            }
            // Check for any errors in the file
            if (words.size() < 2)
            {
                cout << "Error in file!" << endl;
                return binaryTree;
            }
            // Add the course number to the vector
            courseNumbers.push_back(words.at(0));
        }
        // Close the file
        iFile.close();
    }
    else
    {
        cout << "File was unable to be opened." << endl;
        return binaryTree;
    }
    // Open the file again 
    iFile.open(fileName);
    if (iFile.is_open())
    {
        while (iFile.eof() != true)
        {
            string line;
            while (iFile.good())
            {
                Course course;
                string line, spliLine;
                vector<string> words;
                // Get the next line
                getline(iFile, line);
                stringstream linestream(line);
                // Split the line at ','
                while (getline(linestream, spliLine, ','))
                {
                    words.push_back(spliLine);
                }
                // Add the Course information
                course.CourseNumber = words.at(0);
                course.CourseName = words.at(1);
                // Add Prerequisites
                if (words.size() > 2)
                {
                    for (int i = 2; i < words.size(); i++)
                    {
                        for (int j = 0; j < courseNumbers.size(); j++)
                        {
                            // Check the Prerequisites exists in the course number
                            if (words.at(i) == courseNumbers.at(j))
                            {
                                course.Prerequisites.push_back(words.at(i));
                                break;
                            }
                        }
                    }
                }
                // Insert course to the binary tree
                binaryTree.InsertNode(course);
            }
        }
        // Close the file
        iFile.close();
    }
    else
    {
        cout << "File was unable to be opened." << endl;
    }
    return binaryTree;
}

int main(int argc, char* argv[])
{
    BinaryTree binaryTree;

    // Process command line arguments
    string filePath, courseNumber;
    switch (argc) 
    {
    case 2:
        filePath = argv[1];
        break;
    case 3:
        filePath = argv[1];
        break;
    default:
        filePath = "CourseList.csv";
    }

    cout << "Welcome to the course planner." << endl;
    int choice = 0;
    bool dataLoaded = false;

    // Loop the menu till user exists
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Data Structure." << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course." << endl;
        cout << "  9. Exit" << endl;
        cout << "What would you like to do?: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            binaryTree = LoadDataStructure(filePath);
            // Data has been loaded now is able to print
            dataLoaded = true;
            break;
        case 2:
            if (dataLoaded == true)
            {
                binaryTree.PrintCourseList();
            }
            else
            {
                cout << "Please load a file before displaying" << endl;
            }
            break;
        case 3:
            if (dataLoaded == true)
            {
                cout << "What course do you want to know about? ";
                cin >> courseNumber;
                binaryTree.PrintCourseInformation(courseNumber, false);
            }
            else
            {
                cout << "Please load a file before searching" << endl;
            }
            break;
        case 9:
            cout << "Thank you for using the course planner!." << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
        }
    }
    return 0;
}

