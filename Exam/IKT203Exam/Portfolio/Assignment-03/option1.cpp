#include "option1.h"

#include <limits>

int RunApp() {
    //Reading names from file for BST population
    bst = new TBST();
    /* Path to the names data file
    This is MY absolute path -- change to your local path for this to read properly
    something like "C:\Users\Username\FolderYouSavedTheSubmissionIn\Exam\IKT203Exam\DATA\random_names.txt"
    Double slash is needed for string to pass the correct file path */
    const std::string filename = "C:\\Users\\csand\\IKT203\\Exam\\IKT203Exam\\DATA\\random_names.txt";
    readNamesFromFile(filename, onNameRead);

    // BST traversal -- comment out the entire block
    // when done inspecting for more manageable terminal output
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
    // End of BST block

    // Start of AVL block
    // Again, comment out the block if terminal output is
    // too noisy
    pack("AVL");
    avl = new TAVL;


    TAVL::Populate(avl, 100, 1, 200);
    pack("Inorder");
    avl->PrintOrder(TAVL::Inorder);

    pack("Postorder");
    avl->PrintOrder(TAVL::Postorder);

    pack("Preorder");
    avl->PrintOrder(TAVL::Preorder);

    pack("Levelorder");
    avl->PrintOrder(TAVL::LevelOrder);
    // End of AVL block


    // Cleaning to free up memory.
    // Used only at end of runtime, but useful for when runtime needs
    // to be continuous
    pack ("Cleaning up");
    delete bst;
    delete avl;

    return 0;
}


