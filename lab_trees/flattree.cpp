using namespace std;

template <typename T>
void FlatTree<T>::printLeftToRight() const {
    int size = data.size();

    for (int i = 1; i < size; i++) {
        cout << data[i];
    }

    // Do not remove this line - used for correct print output
    cout << endl;
}

template <typename T>
T& FlatTree<T>::getElement(const string& path) {
    int size = path.size();

    if (size == 0) {
        return data.front();
    }

    if (path.substr(0, 1) == "L") {
        data.erase(data[1]);
        path = path.substr(1, size - 1);
        getElement(path);
    } else if (path.substr(0, 1) == "R") {
        data.erase(data[1]);
        data.erase(data[1]);
        path = path.substr(1, size - 1);
        getElement(path);   
    }
   // return data.front(); // STUB, delete this line
}

template <typename T>
void FlatTree<T>::fromBinaryTree(const BinaryTree<T>& tree) {
    // Your code here

    if (tree != NULL) {
        data.push_back(tree->root->elem);
        fromBinaryTree(tree->root->left);
        fromBinaryTree(tree->root->right);
    }

}

template <typename T>
BinaryTree<T> FlatTree<T>::toBinaryTree() const {
    // Your code here

    BinaryTree<T> tree = BinaryTree<T>();

    toBinaryTree(tree);
}

template <typename T>
BinaryTree<T> FlatTree<T>::toBinaryTree(const Node* subRoot) const {

    if (!subRoot) return;

    subRoot->elem = data[1];
    data.erase(data.begin());
    toBinaryTree(subRoot->left);
    toBinaryTree(subRoot->right);

    return tree;
}

