/**
 * @file twodlinkedlist.cpp
 * @author your name(s)
 *
 * Defines a two-dimensional null-terminated doubly-linked list containing rectangular image pieces
 *  for CPSC 221 PA1
 *
 * COMPLETE THE FUNCTION BODIES IN THIS FILE AND SUBMIT TO PRAIRIELEARN
 */

#include "twodlinkedlist.h"

TwoDNode::TwoDNode() {
  // THIS IMPLEMENTATION HAS BEEN COMPLETED FOR YOU ALREADY
  north = nullptr;
  east = nullptr;
  south = nullptr;
  west = nullptr;
}

TwoDNode::TwoDNode(const Block& bdata) {
  // THIS IMPLEMENTATION HAS BEEN COMPLETED FOR YOU ALREADY
  data = bdata;
  north = nullptr;
  east = nullptr;
  south = nullptr;
  west = nullptr;
}

/**
 *  Deallocates any associated dynamic memory and sets private attributes appropriately
 *
 *  @post this list is empty
 */
void TwoDLinkedList::Clear() {
  // COMPLETE YOUR IMPLEMENTATION BELOW
  if (northwest == NULL) {  // if there is no more linked list
    delete northwest;
    return;
  }
  TwoDNode* p = northwest;
  TwoDNode* preserve = northwest;
  TwoDNode* temp = northwest;

  int x = GetBlockDimensionX();
  int y = GetBlockDimensionY();

  int xindex = 0;

  for (int i = 0; i < x * y; i++) {
    p = northwest;
    
    if (xindex == x-1) {
      northwest = preserve;
      delete p;
      //cout << temp << endl;
      //cout << &(temp->data) << endl;
      //cout << temp->data.pixels[0][0] << endl;
      xindex = 0;
    } else {
      if (xindex == 0) {
        preserve = preserve->south;
      }
      northwest = northwest->east;
      delete p;
      xindex++;
    }
  }

  // if (northwest->east != NULL) {
  //   northwest = northwest->east;
  //   delete p;
  //   Clear();
  // } else if (northwest->south != NULL) {
  //   northwest = northwest->south;
  //   delete p;
  //   Clear();
  // } else if (northwest->west != NULL) {
  //   northwest = northwest->west;
  //   delete p;
  //   Clear();
  // } else if (northwest->north != NULL) {
  //   northwest = northwest->north;
  //   delete p;
  //   Clear();
  // }

  // TwoDNode* east = northwest->east;    // might need to separate these into deleting east first, then south...
  // TwoDNode* south = northwest->south;
  // delete northwest;
  // TwoDLinkedList(east) eastll;
  // TwoDLinkedList(south) southll;
  // eastll->Clear();
  // southll->Clear();
  
}

/**
 *  Copies the data and structure of otherlist into this list
 *
 *  @post this list is a physically separate copy of otherlist
 */
void TwoDLinkedList::Copy(const TwoDLinkedList& otherlist) {
  // COMPLETE YOUR IMPLEMENTATION BELOW

  if (otherlist.northwest == NULL) {   // if otherlist is empty -> do nothing
    return;
  }
  
  int x = otherlist.GetBlockDimensionX();    // return x number of blocks
  int y = otherlist.GetBlockDimensionY();    // return y number of blocks

  TwoDNode* currNodeOtherList = otherlist.northwest;  // pointer to the current node in the otherlist
  TwoDNode* indexWestOtherList = otherlist.northwest;

  TwoDNode* prevnorth = NULL;   // pointers to nodes in the newList
  TwoDNode* prevwest = NULL;
  TwoDNode* indexwest = NULL;

  for (int dimx = 0; dimx <x; dimx++) {
    for (int dimy = 0; dimy < y; dimy++) {

      TwoDNode* node = new TwoDNode(currNodeOtherList->data);        // create new Node with block data from otherlist, same position

      if (dimx == 0 && dimy == 0) {
        northwest = node;
      }

      southeast = node;

      if (dimy == 0) {
        indexwest = node;
      }

      //cout << "Test3" << endl;
      if (dimx != 0) {
        node->west = prevwest;
        prevwest->east = node;
      }

      if (dimy != 0) {
        node->north = prevnorth;
        prevnorth->south = node;
      }

      if (dimy == (y - 1)) {
        currNodeOtherList = indexWestOtherList->east;
        indexWestOtherList = indexWestOtherList->east;
        prevnorth = NULL;
        prevwest = indexwest;
      } else {
        currNodeOtherList = currNodeOtherList->south;
        prevnorth = node;
        if (dimx != 0) {
          prevwest = prevwest->south;
        }
      }
    }
  }
 }

/**
 *  Default constructor creates an empty list
 */
TwoDLinkedList::TwoDLinkedList() {
  // COMPLETE YOUR IMPLEMENTATION BELOW
  northwest = nullptr;
  southeast = nullptr;
}

/**
 *  Parameterized constructor creates a list with blockdimx columns,
 *  blockdimy rows, using color data from img
 *
 *  @param img - input PNG
 *  @param blockdimx - horizontal dimension of the list (in Blocks, i.e. number of columns)
 *  @param blockdimy - vertical dimension of the list (in Blocks, i.e. number of rows)
 *
 *  @pre img has dimensions at least 1x1
 *  @pre 1 <= blockdimx <= PNG's horizontal dimension (in pixels)
 *  @pre 1 <= blockdimy <= PNG's vertical dimension (in pixels)
 */
TwoDLinkedList::TwoDLinkedList(PNG& img, unsigned int blockdimx, unsigned int blockdimy) {
  // THIS IMPLEMENTATION HAS BEEN COMPLETED FOR YOU ALREADY
  Build(img, blockdimx, blockdimy);
}

/**
 *  Copy constructor creates a new list as a copy of the data in otherlist
 */
TwoDLinkedList::TwoDLinkedList(const TwoDLinkedList& otherlist) {
  // THIS IMPLEMENTATION HAS BEEN COMPLETED FOR YOU ALREADY
  Copy(otherlist);
}

/**
 *  Overloaded assignment operator assigns structure and data of rhs into this list
 *
 *  @post this list is a physically separate copy of otherlist
 */
TwoDLinkedList& TwoDLinkedList::operator=(const TwoDLinkedList& rhs) {
  // THIS IMPLEMENTATION HAS BEEN COMPLETED FOR YOU ALREADY
  if (this != &rhs) { // this list and rhs are not the same physical list in memory (i.e. they are at different addresses)
    Clear(); // release any existing dynamic memory
    Copy(rhs); // copy data and structure from rhs
  }
  return *this;
}

/**
 *  Destructor deallocates associated dynamic memory
 */
TwoDLinkedList::~TwoDLinkedList() {
  // THIS IMPLEMENTATION HAS BEEN COMPLETED FOR YOU ALREADY
  Clear();
}

/**
 *  Builds the structure of this list from the provided parameters.
 *  The dimension of individual blocks will be an even division
 *  of the input PNG's dimensions by blockdimx or blockdimy.
 *  Assume that supplied PNG dimensions will be divisible by
 *  blockdimx and blockdimy.
 *
 *  @pre PNG horizontal dimension is divisible by blockdimx
 *  @pre PNG vertical dimension is divisible by blockdimy
 *
 *  Example: PNG dimensions 320x240
 *           blockdimx = 4
 *           blockdimy = 2
 *           The constructed list will have the following Block and node structure:
 *
 *                +-----------+     +-----------+     +-----------+     +-----------+
 *  northwest --> |           | --> |           | --> |           | --> |           |
 *                |  80 x 120 |     |  80 x 120 |     |  80 x 120 |     |  80 x 120 |
 *                |           | <-- |           | <-- |           | <-- |           |
 *                +-----------+     +-----------+     +-----------+     +-----------+
 *                   |     ^           |     ^           |     ^           |     ^
 *                   v     |           v     |           v     |           v     |
 *                +-----------+     +-----------+     +-----------+     +-----------+
 *                |           | --> |           | --> |           | --> |           |
 *                |  80 x 120 |     |  80 x 120 |     |  80 x 120 |     |  80 x 120 |
 *                |           | <-- |           | <-- |           | <-- |           | <-- southeast
 *                +-----------+     +-----------+     +-----------+     +-----------+
 */


void TwoDLinkedList::Build(PNG& img, unsigned int blockdimx, unsigned int blockdimy) {

  if (img.width() == 0 || img.height() == 0) {
    northwest = NULL;
    southeast = NULL;
    return;
  }

  int x = img.width() / blockdimx; //width
  int y = img.height() / blockdimy; //height

  TwoDNode* currwest = NULL;
  TwoDNode* indexwest = NULL; 
  TwoDNode* currnorth = NULL;

  int xindex = 1;
  int yindex = 1;

  int blocknums = blockdimx * blockdimy;

  //cout << blocknums << endl;

  for (int i = 0; i < blocknums; i++) {

  //  cout << xindex << "  ";
  //  cout << yindex << endl;

    Block block = Block();

   // cout << "Test1" << endl;

    block.Build(x, y, (yindex - 1) * y, (xindex - 1) * x, img);
    TwoDNode* node = new TwoDNode(block);

   // cout << node << endl;

    if (xindex == 1 && yindex == 1) {
      northwest = node;
    } else if (xindex == ((int)blockdimx) && yindex == ((int)blockdimy)) {
      southeast = node;
    }

    //cout << "Test2" << endl;

    node->north = currnorth;

    if (yindex == 1) {
      node->west = indexwest;

      if (xindex != 1) {
        indexwest->east = node;
        currwest = indexwest->south;
      }

     // cout << "Test3" << endl;

      indexwest = node;
      currnorth = node;

    } else if (yindex == ((int)blockdimy)) {

      //cout << "Test4" << endl;

      node->west = currwest;
  
      if (xindex != 1) {
        currwest->east = node;
      }

      //cout << "Test5" << endl;

      currnorth->south = node;
      currnorth = NULL;
        
      //cout << "Test 6" << endl;

    } else {

     // cout << "Test7" << endl;
      currnorth->south = node;
      node->west = currwest;

      if (xindex != 1) {
        currwest->east = node;
        currwest = currwest->south;
      }

      currnorth = node;

    }

   // cout << "Test8" << endl;

    if (yindex == ((int) blockdimy)) {
      yindex = 1;
      xindex++;
    } else {
      yindex++;
    }

    //cout << "Test9" << endl;

  }

  //cout << northwest << endl;
  //cout << southeast << endl;

  // for (int i = 0; i < blockdimx; i++) {
  //   for (int j = 0; j < blockdimy; j++) {
  //     Block* block = new Block();
  //     block->Build(x, y, j * y, i * x, img);

  //     TwoDNode* node = new TwoDNode(*block);

  //     if (i == 0 && j == 0) {
  //       northwest = node;
  //     } else if (i == (blockdimx - 1) && j == (blockdimy - 1)) {
  //       southeast = node;
  //     }
      
  //     node->north = currnorth;

  //     if (j == 0) {
  //       node->west = indexwest;
  //       if (i != 0) {
  //         indexwest->east = node;
  //         currwest = indexwest->south;
  //       }
  //       indexwest = node;
  //       currnorth = node;

  //     } else if (j == ((int) blockdimy - 1)) {
  //       node->west = currwest;
  //       if (i != 0) {
  //         currwest->east = node;
  //       }
  //       currnorth->south = node;
  //       currnorth = NULL;

  //     } else {
  //       currnorth->south = node;
  //       node->west = currwest;
  //       if (i != 0) {
  //         currwest->east = node;
  //         currwest = currwest->south;
  //       }
  //       currnorth = node;
  //     }
  //   }
  // }
}

/**
 *  Returns the horizontal dimension of this list (in blocks)
 */
unsigned int TwoDLinkedList::GetBlockDimensionX() const {
  // REPLACE THE LINE BELOW WITH YOUR IMPLEMENTATION
  if (northwest == NULL) return 0;

  TwoDNode* currNode = northwest;
  int n = 1;
  while (currNode->east) {   //while the current node's eastern node is not null
    n++;
    currNode = currNode->east;
  }
  return n;
}

/**
 *  Returns the vertical dimension of this list (in blocks)
 */
unsigned int TwoDLinkedList::GetBlockDimensionY() const {
  // REPLACE THE LINE BELOW WITH YOUR IMPLEMENTATION
  if (northwest == NULL) return 0;

  TwoDNode* currNode = northwest;
  int n = 1;
  while (currNode->south) {
    n++;
    currNode = currNode->south;
  }
  return n;
}

/**
 *  Places this lists's color data into a PNG of appropriate dimensions
 */
PNG TwoDLinkedList::Render() const {

  if (northwest == NULL) {
    PNG img = PNG(0,0);
    return img;
  }

  int x = GetBlockDimensionX();
  int y = GetBlockDimensionY();

  int datawidth = northwest->data.GetWidth();
  int dataheight = northwest->data.GetHeight(); 

  int imgwidth = x * datawidth;
  int imgheight = y * dataheight; 

  PNG img = PNG(imgwidth, imgheight);

  int xindex = 0;
  int yindex = 0;

  TwoDNode* p = northwest;
  TwoDNode* preservewest = northwest;

  for (int j = 0; j < y; j++) {
    xindex = 0;

    for (int i = 0; i < x; i++) {
      p->data.Render(yindex, xindex, img);
      xindex += datawidth;
      p = p->east;
    }
    p = preservewest->south;
    preservewest = preservewest->south;
    yindex += dataheight;
  }

  return img;
}

/**
 *  Every Block in this list has the color of all its pixels replaced with the Block's average color
 */
void TwoDLinkedList::Blockify() {

  if (northwest == NULL) return;

  TwoDNode* p = northwest;
  // TwoDNode* indexrow = NULL;

  // int numnodex = 1;

  // //int numnodex = GetBlockDimensionX();
  // TwoDNode* temp = northwest;
  // while (temp->south != NULL) {
  //   numnodex++;
  // }
  // //numnodex = width of the twodlinkedlist\

  // int xindex = 1;
  // while (p->south != NULL) {
  //   if (xindex == 1) {
  //     indexrow = p;
  //     p->data.MakeAverage();
  //     p = p->east;
  //     xindex++;
  //   } else if (xindex == numnodex) {
  //     p->data.MakeAverage();
  //     p = indexrow->south;
  //     xindex = 1;
  //   } else {
  //     p->data.MakeAverage();
  //     p = p->east;
  //   }
  // }

  // while (xindex != numnodex) {
  //   p->data.MakeAverage();
  //   p = p->east;
  //   xindex++;
  // }

  // p->data.MakeAverage();



  while (p->south != NULL) {

    if (p->east != NULL) {
      while (p->east != NULL) {
        p->data.MakeAverage();
        p = p->east;
      } 
    } 
    // else if (p->east == NULL) {
    //   p->data.MakeAverage();
    //   p = p->south;
    // }
    
    if (p->west != NULL) {
      while (p->west != NULL) {
        p->data.MakeAverage();
        p = p->west;
      }
    }
    p = p->south; //ADDED BY IRENE
  }

  if (p->east == NULL) {
    while (p->west != NULL) {
      p->data.MakeAverage();
      p = p->west;
    }

  } else {
    while (p->east != NULL) {
      p->data.MakeAverage();
      p = p->east;
    }
  }

  p->data.MakeAverage();
}

/**
 *  Applies Block::SwapChannels to produce a rotating cycle of color swaps to each Block in this list,
 *  in a row-order sequence.
 *  Example: For a list with 4 columns and 3 rows, the application will be as follows:
 *
 *  northwest ->  no change -> SC(0) ->   SC(1)   -> SC(2)
 *                    SC(3) -> SC(4) -> no change -> SC(0)
 *                    SC(1) -> SC(2) ->   SC(3)   -> SC(4) <- southeast
 */
void TwoDLinkedList::CheckerSwap() {

  if (northwest == NULL) return;

  TwoDNode* p = northwest;
  TwoDNode* nextrow = northwest;
  int swaptype = 5;

  int x = GetBlockDimensionX();
  int y = GetBlockDimensionY();

  int xindex = 0;

  for (int i = 0; i < x * y; i++) {
    p->data.SwapChannels(swaptype);
    if (swaptype == 5) {
      swaptype = 0;
    } else {
      swaptype++;
    }

    if (xindex == x - 1) {
      p = nextrow;
      xindex = 0;

    } else if (xindex == 0) {
      nextrow = nextrow->south;
      p = p->east;
      xindex++;

    } else {
      p = p->east;
      xindex++;

    }
  }
}

/**
 *  Reorganizes the list and node contents so that a rendered image will be flipped horizontally.
 *  This must be achieved by pointer manipulation. Do not deallocate any existing nodes, and
 *  do not allocate any new nodes.
 *
 *  Ensure that the integrity of north/south/east/west pointers of all nodes is maintained.
 *
 *  You may use up to O(n) time and space complexity, where n is the total number of nodes in the list.
 *
 *  Example: A, B, C, D etc. are physical nodes (each at a particular address)
 *  before:
 *   northwest -> A <-> B <-> C <-> D
 *                ^     ^     ^     ^
 *                v     v     v     v
 *                E <-> F <-> G <-> H
 *                ^     ^     ^     ^
 *                v     v     v     v
 *                I <-> J <-> K <-> L  <- southeast
 *
 *  after:
 *   northwest -> D <-> C <-> B <-> A
 *                ^     ^     ^     ^
 *                v     v     v     v
 *                H <-> G <-> F <-> E
 *                ^     ^     ^     ^
 *                v     v     v     v
 *                L <-> K <-> J <-> I  <- southeast
 */
void TwoDLinkedList::FlipHorizontal() {
   // use int xindex to make O(n) (while last node) -> xindex++ 해가면서 찾기
   // northwest/southeast는 따로 빼도 상관 없을듯! 어차피 O(n)에 영향 X
   // p로 따로 두고 northwest/southeast만 먼저 뺌
   // p, previous, preservenode 3개 node 필요!
   // when xindex == 0, p->east = NULL
   // when xindex == 4(width), p->west = NULL
   // else previous(west) 저장 + p->west = p->east + p->east = previous
   // p = p->west

  if (northwest == NULL) return;

  int width = GetBlockDimensionX();
  int height = GetBlockDimensionY();

  TwoDNode* previouswest = NULL;
  TwoDNode* curr = northwest;
  TwoDNode* currRow = northwest;

  for (int i = 0; i < width - 1; i++) {  // move northwest pointer to the far right
    northwest = northwest->east;
  }
  for (int i = 0; i < width - 1; i++) {  // move southeast pointer to the far left
    southeast = southeast->west;
  }

  while (currRow != NULL) {
    while (curr != NULL) {
      curr->data.FlipHorizontal();
      previouswest = curr->west;
      curr->west = curr->east;
      curr->east = previouswest;
      curr = curr->west;
    }
    currRow = currRow->south;
    curr = currRow;
  }
  
}

/**
 *  Reorganizes the list and node contents so that a rendered image will be flipped vertically.
 *  This must be achieved by pointer manipulation. Do not deallocate any existing nodes, and
 *  do not allocate any new nodes.
 *
 *  Ensure that the integrity of north/south/east/west pointers of all nodes is maintained.
 *
 *  You may use up to O(n) time and space complexity, where n is the total number of nodes in the list.
 *
 *  Example: A, B, C, D etc. are physical nodes (each at a particular address)
 *  before:
 *   northwest -> A <-> B <-> C <-> D
 *                ^     ^     ^     ^
 *                v     v     v     v
 *                E <-> F <-> G <-> H
 *                ^     ^     ^     ^
 *                v     v     v     v
 *                I <-> J <-> K <-> L  <- southeast
 *
 *  after:
 *   northwest -> I <-> J <-> K <-> L
 *                ^     ^     ^     ^
 *                v     v     v     v
 *                E <-> F <-> G <-> H
 *                ^     ^     ^     ^
 *                v     v     v     v
 *                A <-> B <-> C <-> D  <- southeast
 */
void TwoDLinkedList::FlipVertical() {

  if (northwest == NULL) return;

  int height = GetBlockDimensionY();

  TwoDNode* previousnorth = NULL;
  TwoDNode* curr = northwest;
  TwoDNode* currRow = northwest;

  for (int i = 0; i < height - 1; i++) {  // move northwest pointer to the far right
    northwest = northwest->south;
  }
  for (int i = 0; i < height - 1; i++) {  // move southeast pointer to the far left
    southeast = southeast->north;
  }

  while (currRow != NULL) {
    while (curr != NULL) {
      curr->data.FlipVertical();
      previousnorth = curr->north;
      curr->north = curr->south;
      curr->south = previousnorth;
      curr = curr->north;
    }
    currRow = currRow->east;
    curr = currRow;
  }
}

// ADD IMPLEMENTATIONS OF ANY OF YOUR OWN PRIVATE FUNCTIONS BELOW
