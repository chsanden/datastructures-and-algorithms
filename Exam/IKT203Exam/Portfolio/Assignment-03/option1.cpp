#include "option1.h"
#include <limits>

#include "SharedLib.h"

// Entry point for Category 3, Option 1.
// Demonstrates:
// 1) Building a BST of 200 employees from DATA/random_names.txt
// 2) Running all BST traversals
// 3) Searching and deleting by employee ID
// 4) Building and printing an AVL tree with random integer keys
int RunApp() {
    //Reading names from file for BST population
    bst = new TBST();

    // Read 200 employees from the names file and populate the BST.
    // IMPORTANT: Working directory must be the Portfolio/Assignment-03 folder
    // so that "DATA/random_names.txt" resolves correctly.
    const std::string filename = "DATA/random_names.txt";
    readNamesFromFile(filename, onNameRead);

    // --- BST traversals ---
    // These calls demonstrate all four traversal orders on the employee BST.
    // Comment out this block if the console output becomes too noisy.
    pack("Inorder traversal (sorted by ID)");
    bst->Inorder();

    pack("Level order traversal");
    bst->LevelOrder();

    pack("Preorder traversal");
    bst->Preorder();

    pack("Postorder traversal");
    bst->Postorder();

    // --- BST search demo ---
    // Ask the user for an ID, search in the BST, and print the matching employee (if any).
    pack("Search function");
    std::cout << "\nInput the ID you want to search for\n" << std::endl;
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (const TEmployee* result = bst->Search(choice))
        std::cout << "Match found:\n" << result->firstName << " " << result->lastName << std::endl;
    else
        std::cout << "ID not found" << std::endl;

    // --- BST delete demo ---
    // Ask the user for an ID, delete it from the BST if it exists,
    // then print the new inorder traversal to show the updated structure.
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

    // --- AVL demo ---
    // Build an AVL tree using random integers in [1, 200].
    // This tree only stores keys (no TEmployee data) and is used
    // to demonstrate balancing and traversals.
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


    // --- Cleanup ---
    // TBST destructor deletes all TEmployee objects it owns.
    // Here we delete the tree objects themselves to avoid leaks.
    pack ("Cleaning up");
    delete bst;
    delete avl;

    return 0;
}


