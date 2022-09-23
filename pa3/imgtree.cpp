/**
 *  @file imgtree.cpp
 *  @description implementation of a binary tree class storing image data for CPSC 221 PA3
 *  @author CPSC 221
 *
 *  SUBMIT THIS FILE TO PRAIRIELEARN
 */

#include "imgtree.h"
// not necessary to include imgtree-private.h since it is already included in imgtree.h

    /**
     *  Default constructor creates an empty tree
     */
ImgTree::ImgTree() {
  // complete your implementation below
  root = NULL;
  imgwidth = 0;
  imgheight = 0;
}

/**
 *  Parameterized constructor creates a tree from an input image.
 *  Every leaf in the tree corresponds to a single pixel in the PNG.
 *  Every non-leaf node corresponds to a rectangle of pixels defined
 *  by upper, left, lower, and right image coordinates. A node will
 *  also store the average color over its defined rectangle. Note that
 *  this average MUST be freshly computed from the individual pixels in
 *  the image and NOT by computing a weighted average from the colors
 *  of its direct children, as this would lead to an accumulation of
 *  rounding errors due to the integer nature of RGB color channels.
 *
 *  A non-leaf node's children correspond to a partition of the node's
 *  rectangle into two smaller rectangles, either by a horizontal line
 *  creating an upper rectangle and a lower rectangle, or a vertical line
 *  creating a left rectangle and a right rectangle.
 *
 *  The split is determined as follows:
 *  1. If the current node's rectangle width is the same or larger than its height,
 *     then a vertical line will divide the rectangle into left and right rectangles.
 *     If the current node's rectangle width is smaller than its height,
 *     then a horizontal line will divide the rectangle into upper and lower rectangles.
 *  2. The coordinate of the dividing line is chosen such that combined sum squared
 *     deviations from the mean color in the left/upper and right/lower rectangles is minimal
 *     among all other potential dividing lines of the same orientation.
 *     e.g. for a region (0,0) to (3,2), the candidates are the vertical lines dividing the region into:
 *     - (0,0) to (0,2) and (1,0) to (3,2)
 *     - (0,0) to (1,2) and (2,0) to (3,2)
 *     - (0,0) to (2,2) and (3,2) to (3,2)
 *     The line which produces the minimal combined sum squared scores on the left
 *     and right will be used for the split.
 *  3. In the unlikely event that multiple candidates produce the same score, the one which
 *     most evenly splits the rectangular area will be chosen.
 *  4. In the even more unlikely even that two candidates produce the same score and produce
 *     the same minimal area difference, the one with the smaller coordinate will be chosen.
 */
ImgTree::ImgTree(const PNG& img) {
  // complete your implementation below

  // TODO: compute average RGBAPixel to put into ImgTeeNode constructor
  Stats stat = Stats(img);
  imgheight = img.height();
  imgwidth = img.width();

  cout << "imgheight: " << imgheight << endl;
  cout << "imgwidth: " << imgwidth << endl;

  RGBAPixel avgPixel = stat.GetAvg(0,0,imgheight - 1, imgwidth - 1); //REVISED
  
  root = BuildNode(stat, 0, 0,imgheight - 1, imgwidth - 1);
  
}



/**
 *  Copy constructor creates a new tree that is structurally the same as the input tree and
 *  contains the same image data.
 *  @param other - the ImgTree to be copied
 */
ImgTree::ImgTree(const ImgTree& other) {
  // This implementation has already been completed for you
  Copy(other);
}

/**
 *  Overloaded assignment operator allows statements such as mytree_a = some_other_tree;
 *  Releases any existing memory and reconstructs this tree as a copy of other.
 *  @param rhs - the right hand side of the assignment statement
 */
ImgTree& ImgTree::operator=(const ImgTree& rhs) {
  // This implementation has already been completed for you
  if (this != &rhs) { // this and rhs are physically different trees in memory
    Clear(); // release any existing heap memory for this tree
    Copy(rhs);  // rebuild this tree as a copy of rhs
  }
  return *this;
}

/**
 *  Destructor releases any heap memory associated with this tree.
 */
ImgTree::~ImgTree() {
  // This implementation has already been completed for you
  Clear();
}

/**
 *  Releases all heap memory associated with this tree, restoring it to an "empty tree" state.
 *  Will be useful to define a recursive helper function for this.
 */
void ImgTree::Clear() {
  // complete your implementation below
  Clear(root);                             // is this not working??
}

/**
 *  Copies the supplied parameter tree into this tree. Does not free any memory.
 *  Called by the copy constructor and operator=.
 *  Will be useful to define a recursive helper function for this.
 *  HINT: the helper should allocate a new node, and return a pointer to the allocated node.
 *        See the documention for BuildNode - this should work similarly.
 */
void ImgTree::Copy(const ImgTree& other) { //DO WE NEED const HERE?
  // complete your implementation below
  imgwidth = other.imgwidth;
  imgheight = other.imgheight;
  root = Copy(other.root);
}

/**
 *  Recursive helper function for initial construction of the tree. Constructs a single
 *  node according to supplied Stats and the requirements specified by the constructor
 *  documentation, and returns a pointer to the completed node.
 *  @param s - populated Stats object for computing this node's attributes
 *  @param upr - y-coordinate of the upper edge of the node's rectangular region
 *  @param lft - x-coordinate of the left side of the node's rectangular region
 *  @param lwr - y-coordinate of the lower edge of the node's rectangular region
 *  @param rt - x-coordinate of the right side of the node's rectangular region
 *  @return - pointer to a (completed) newly-allocated node for the specified parameters.
 */
ImgTreeNode* ImgTree::BuildNode(Stats& s, unsigned int upr, unsigned int lft, unsigned int lwr, unsigned int rt) {
  // complete your implementation below
  //return nullptr; // REPLACE THIS STUB

  ImgTreeNode* treeNode = new ImgTreeNode(upr,lft,lwr,rt, s.GetAvg(upr, lft, lwr, rt)); // this creates one node

  // if node is only ONE PIXEL - this is a a leaf without any children
  if (upr == lwr && lft == rt) {
    //cout << "made a node at: (" << lft << ", " << upr << ")" << endl;
    return treeNode;
  }

  SplitInfo info = SplitInfo();
  info.sumsqscore = 50000000000000; // random large number
  //info.coordinate = min(imgheight,imgwidth);    // does this need to be set up?

  // if width >= height - vertical split (A is left, B is right child)
  // if height < width - horizontal split (A is upper, B is lower child)

  if ((rt - lft + 1) >= (lwr - upr +1)) {  // make a vertical split
    for (int x = lft; x <= rt - 1; x++) {
      double leftDev = s.GetSumSqDev(upr,lft,lwr,x);
      double rightDev = s.GetSumSqDev(upr,x+1,lwr,rt);
      double devDifference = leftDev + rightDev;   /// CHANGED: from abs(leftDev - rightDev)

      if (devDifference < info.sumsqscore) {
        info.coordinate = x; /// A node becomes (upr,lft,lwr,x), B node (upr,x+1,lwr,rt)
        info.sumsqscore = devDifference;  // sumsqscore is lowest devDifference so far
      } else if (devDifference == info.sumsqscore) {  // if two coordinates have same devDifference, choose most even split
        if (fabs((info.coordinate - lft + 1) - (rt - info.coordinate)) < fabs((x - lft + 1) - (rt - x))) {  // info.coord (prev. x) closer to centre
          info.coordinate = x;
          info.sumsqscore = devDifference;
        } else if (fabs((info.coordinate - lft + 1) - (rt - info.coordinate)) > fabs((x - lft + 1) - (rt - x))) { // info.coord farther from centre, no change
          ;
        } else if (fabs((info.coordinate - lft + 1) - (rt - info.coordinate)) == fabs((x - lft + 1) - (rt - x))) { // devDiff same, split is same
          ;
        }
        // double middle = (rt - lft + 1 + lft) / 2;
        // if (abs(info.coordinate - middle) < abs(x - middle)) {
        //   ;
        // } else if (abs(info.coordinate - middle) > abs(x - middle)) {
        //   info.coordinate = x;
        //   info.sumsqscore = devDifference;
        // } else if (abs(info.coordinate - middle) == abs(x - middle)) { // if same devDifference & same split, choose smaller coordinate
        //   ;
        // }
      }
    }

    // make nodes A & B
    treeNode->A = BuildNode(s,upr,lft,lwr,info.coordinate);
    treeNode->B = BuildNode(s,upr,info.coordinate+1,lwr,rt);


  } else if ((lwr - upr + 1) > (rt - lft + 1)) {   // make a horizontal split


    for (int y = upr; y <= lwr - 1; y++) {
      double upperDev = s.GetSumSqDev(upr,lft,y,rt);
      double lowerDev = s.GetSumSqDev(y+1,lft,lwr,rt);
      double devDifference = upperDev + lowerDev; /// CHANGED: from abs(upperDev - lowerDev)
      if (devDifference < info.sumsqscore) {
        info.coordinate = y; // A node (upr,lft,y,rt), B node (y+1,lft,lwr,rt)
        info.sumsqscore = devDifference; // sumsqscore is lowest devDifference so far;
      }
      if (devDifference == info.sumsqscore) {  // if two coordinates have same devDifference, choose most even split
        // if ((lwr - info.coordinate - info.coordinate) > (lwr - y - y)) {  // info.coord (prev. x) closer to centre
        //   info.coordinate = y;
        //   info.sumsqscore = devDifference;
        // } else if ((lwr - info.coordinate - info.coordinate) < (lwr - y - y)) { // info.coord farther from centre, no change
        //   ;
        // } else if ((lwr - info.coordinate - info.coordinate) == (lwr - y - y)) { // devDiff same, split is same
        //   ;
        // }

        double middle = (lwr - upr + 1 + upr) / 2;
        if (fabs((info.coordinate - upr + 1) - (lwr - info.coordinate)) < fabs((y - upr + 1) - (lwr - y))) {
          ;
        } else if (fabs((info.coordinate - upr + 1) - (lwr - info.coordinate)) > fabs((y - upr + 1) - (lwr - y))) {
          info.coordinate = y;
          info.sumsqscore = devDifference;
        } else if (fabs((info.coordinate - upr + 1) - (lwr - info.coordinate)) == fabs((y - upr + 1) - (lwr - y))) { // if same devDifference & same split, choose smaller coordinate
          ;
        }
      }
    }

    // make children
    treeNode->A = BuildNode(s,upr,lft,info.coordinate,rt);
    treeNode->B = BuildNode(s,info.coordinate+1,lft,lwr,rt);

  }

  return treeNode;

}

/**
 *  Produces a PNG of appropriate dimensions and paints every leaf node's rectangle
 *  into the appropriate area of the PNG.
 *  May be called on pruned trees.
 *  @return fully-colored PNG, painted from the tree's leaf node data
 */
PNG ImgTree::Render() const { 

  // complete your implementation below
  //return PNG(); // REPLACE THIS STUB

  PNG renderedImg = PNG(imgwidth, imgheight);   // first set up empty PNG file //REVISED
  // if A&B are null (current node is a leaf)- paint PNG according to coordinates

  Render(root, &renderedImg); // 1. not change ImgTree 2. not change root (first parameter)

  return renderedImg;
}

/**
 *  Rearranges a tree's internal pointers and node content so that its image data
 *  appears flipped horizontally when rendered.
 *  Beware that the tree may or may not have been pruned!
 *  Will be useful to define a recursive helper function for this.
 */
void ImgTree::FlipHorizontal() {
  // complete your implementation below
  FlipHorizontal(root, imgwidth);     // see helper function implementation below
}

/**
 *  Rearranges a tree's internal pointers and node content so that its image data
 *  appears flipped vertically when rendered.
 *  Beware that the tree may or may not have been pruned!
 *  Will be useful to define a recursive helper function for this.
 */
void ImgTree::FlipVertical() {
  // complete your implementation below
  FlipVertical(root, imgheight);
}

/**
 *  Trims subtrees as high as possible in the tree.
 *  A subtree is pruned (all decendants deallocated and child links set to null)
 *  if at least pct (out of 100) of its leaves are within tol of the average
 *  color in the subtree's root.
 *  Assume that this will only be called on trees which have not previously been pruned.
 *  Will be useful to define AT LEAST one recursive helper function for this.
 *  @pre pct is a valid value between 0 and 100
 *  @param pct percentage (out of 100) of leaf node descendants must be within the tolerance threshold
 *             of color difference in order to be pruned
 *  @param tol threshold color difference to qualify for pruning
 */
void ImgTree::Prune(double pct, double tol) {
  // complete your implementation below

  Prune(root, pct, tol);
}

/**
 *  Counts the number of leaf nodes in the tree.
 *  Will be useful to define a recursive helper function for this.
 */
unsigned int ImgTree::CountLeaves() const {
  // complete your implementation below
  return CountLeaves(root);
}

/**
 *  ADD YOUR PRIVATE FUNCTION IMPLEMENTATIONS BELOW
 */

void ImgTree::Clear(ImgTreeNode*& node) {     // unsure if I implemented correctly with no leaks
  if (node == NULL) return;

  //ImgTreeNode* a = node->A;
  //ImgTreeNode* b = node->B;


  Clear(node->A);
  Clear(node->B);

  delete node;
  node = NULL;

}

ImgTreeNode* ImgTree::Copy(ImgTreeNode* node) { //***REVISED
  if (node == NULL) {
    return NULL;
  }

  ImgTreeNode* newNode = new ImgTreeNode(node->upper, node->left, node->lower, node->right, node->avg);

  newNode->A = Copy(node->A);
  newNode->B = Copy(node->B);

  return newNode;
}

void ImgTree::Render(const ImgTreeNode* node, PNG* renderImg) const {

  if (node == NULL) return; //ADDED

  for (int x = node->left; x <= node->right; x++) {
    for (int y = node->upper; y <= node->lower; y++) {
      RGBAPixel* pix = renderImg->getPixel(x, y);
      *pix = node->avg;
    }    
  }

  Render(node->A, renderImg);
  Render(node->B, renderImg);


/*   if (node->right != node->left && node->upper != node->lower) {  // if node is not true leaf (more than 1 pixel)
    if (node->A == nullptr && node->B == nullptr) {   // not true leaf, but has no children
      for (int x = node->left; x <= node->right; x++) {
        for (int y = node->upper; y <= node->lower; y++) {
          RGBAPixel* pix = renderImg->getPixel(x, y);
          *pix = node->avg;
        }
      }
    }
    
  } else if (node->right == node->left && node->upper == node->lower) {  // if node is true leaf (1 pixel) 
    unsigned int x = node->right;
    unsigned int y = node->upper;
    RGBAPixel* pix = renderImg->getPixel(x, y);
    *pix = node->avg;
  } */

}

void ImgTree::FlipHorizontal(ImgTreeNode* node, unsigned int width) {

  if (node == NULL) return; //ADDED

  unsigned int lft = node->left;
  node->left = width - node->right - 1;
  node->right = width - lft - 1;

  FlipHorizontal(node->A, width);
  FlipHorizontal(node->B, width);

/*   if (node == NULL) return; //ADDED

  for (int x = node->left; x <= node->right; x++) {
    for (int y = node->upper; y <= node->lower; y++) {
      node->right = width - node->right - 1;
      node->left = width - node->left - 1;
    }
  }

  FlipHorizontal(node->A, width);
  FlipHorizontal(node->B, width);  */

} 

void ImgTree::FlipVertical(ImgTreeNode* node, unsigned int height) {

  if (node == NULL) return;

  unsigned int up = node->upper;
  node->upper = height - node->lower - 1;
  node->lower = height - up - 1;

  FlipVertical(node->A, height);
  FlipVertical(node->B, height);

/*   if (node == NULL) return; //ADDED

  for (int x = node->left; x <= node->right; x++) {
    for (int y = node->upper; y <= node->lower; y++) {
      node->upper = height - node->upper - 1;
      node->lower = height - node->lower - 1;
    }
  }


  FlipVertical(node->A, height);
  FlipVertical(node->B, height);  */

}

unsigned int ImgTree::CountLeaves(const ImgTreeNode* node) const {

  unsigned int count = 0;

  if (node == NULL) {
    return count;
  }
  
  if (node->A != NULL) { 
    count += CountLeaves(node->A); 
  }
  if (node->B != NULL) { 
    count += CountLeaves(node->B); 
  }
  if (node->A == NULL && node->B == NULL) { 
    count++;
  }

  return count;
}


void ImgTree::Prune(ImgTreeNode*& node, double pct, double tol) {

  if (node == NULL || (node->A == NULL && node->B == NULL)) return;

  if (node->A != nullptr && node->B != nullptr) { // if the node has children

    RGBAPixel parentpix = node->avg;
    int numLeaves = CountLeaves(node);

    if (checkTol(node->A,tol,parentpix) + checkTol(node->B,tol,parentpix) >= (pct * numLeaves / 100)) {
      Clear(node->A);
      Clear(node->B);
    } else {
      Prune(node->A, pct, tol);
      Prune(node->B, pct, tol);
    }
  }
}

int ImgTree::checkTol(ImgTreeNode* node, double tol, RGBAPixel parentpix) {  // returns number of leaves within tol
  if (node == NULL) return (double) 0;

  if (node->A == NULL && node->B == NULL) {
    if (node->avg.dist(parentpix) <= tol) {
      return 1; 
    } else {
      return 0;
    }
  } else {
    return checkTol(node->A, tol, parentpix) + checkTol(node->B, tol, parentpix);
  }
  
}
