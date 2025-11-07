#include "option1.h"

#include <limits>

int RunApp() {
    bst = new TBST();
    /* Path to the names data file
    This is MY absolute path -- change to your local path for this to read properly
    something like "C:\Users\Username\FolderYouSavedTheSubmissionIn\Exam\IKT203Exam\DATA\random_names.txt"
    Double slash is needed for string to pass the correct file path */
    const std::string filename = "C:\\Users\\csand\\IKT203\\Exam\\IKT203Exam\\DATA\\random_names.txt";
    readNamesFromFile(filename, onNameRead);

    pack("Inorder traversal (sorted by ID)");
    bst->Inorder();

    pack("Level order traversal");
    bst->LevelOrder();

    pack("Preorder traversal");
    bst->Preorder();

    pack("Postorder traversal");
    bst->Postorder();

    pack("Search function");
    std::cout << "\nInput the ID you want to search for\n" << std::endl;
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (const TEmployee* result = bst->Search(choice))
        std::cout << "Match found:\n" << result->firstName << " " << result->lastName << std::endl;
    else
        std::cout << "ID not found" << std::endl;

    pack("Remove function");
    std::cout << "\nInput the ID you want to remove\n" << std::endl;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (const TEmployee* res = bst->Search(choice)) {
        bst->Delete(choice);
        std::cout << "ID removed\n" << std::endl;
    }
    else
        std::cout << "ID not found\n" << std::endl;
    bst->Inorder();
    pack ("Cleaning up");
    delete bst;

    return 0;
}


