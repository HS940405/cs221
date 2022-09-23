/**
 *  @file twodlinkedlist.h
 *  @author CPSC 221
 * 
 *  Defines a two-dimensional null-terminated doubly-linked list containing rectangular image pieces
 *  for CPSC 221 PA1
 * 
 *  DO NOT MODIFY EXISTING DEFINITIONS
 *  YOU MAY ADD YOUR OWN PRIVATE MEMBER FUNCTIONS AT THE BOTTOM OF THIS FILE
 */

#ifndef _TWODLINKEDLIST_H_
#define _TWODLINKEDLIST_H_

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "block.h"

class TwoDNode {
  public:
    Block data;
    TwoDNode* north; // pointer to the northern neighbour, if one exists; NULL otherwise
    TwoDNode* east; // pointer to the eastern neighbour, if one exists; NULL otherwise
    TwoDNode* south; // pointer to the southern neighbour, if one exists; NULL otherwise
    TwoDNode* west; // pointer to the western neighbour, if one exists; NULL otherwise

    /**
     *  Default node constructor assigns appropriate values to the neighbour pointers
     */
    TwoDNode();

    /**
     *  Parameterized node constructor assigns data block and appropriate values to the neighbour pointers
     */
    TwoDNode(const Block& bdata);
};

class TwoDLinkedList {
  public:
    TwoDNode* northwest; // pointer to upper-left node in the 2D list
    TwoDNode* southeast; // pointer to lower-right node in the 2D list

    /**
     *  Deallocates any associated dynamic memory and sets private attributes appropriately
     * 
     *  @post this list is empty
     */
    void Clear();

    /**
     *  Copies the data and structure of otherlist into this list
     * 
     *  @post this list is a physically separate copy of otherlist
     */
    void Copy(const TwoDLinkedList& otherlist);

  public:
    /**
     *  Default constructor creates an empty list
     */
    TwoDLinkedList();

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
    TwoDLinkedList(PNG& img, unsigned int blockdimx, unsigned int blockdimy);

    /**
     *  Copy constructor creates a new list as a copy of the data in otherlist
     */
    TwoDLinkedList(const TwoDLinkedList& otherlist);

    /**
     *  Overloaded assignment operator assigns structure and data of rhs into this list
     * 
     *  @post this list is a physically separate copy of otherlist
     */
    TwoDLinkedList& operator=(const TwoDLinkedList& rhs);

    /**
     *  Destructor deallocates associated dynamic memory
     */
    ~TwoDLinkedList();

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
    void Build(PNG& img, unsigned int blockdimx, unsigned int blockdimy);

    /**
     *  Returns the horizontal dimension of this list (in blocks)
     */
    unsigned int GetBlockDimensionX() const;

    /**
     *  Returns the vertical dimension of this list (in blocks)
     */
    unsigned int GetBlockDimensionY() const;

    /**
     *  Places this lists's color data into a PNG of appropriate dimensions
     */
    PNG Render() const;

    /**
     *  Every Block in this list has the color of all its pixels replaced with the Block's average color
     */
    void Blockify();

    /**
     *  Applies Block::SwapChannels to produce a rotating cycle of color swaps to each Block in this list,
     *  in a row-order sequence.
     *  Example: For a list with 4 columns and 3 rows, the application will be as follows:
     * 
     *  northwest ->  no change -> SC(0) ->   SC(1)   -> SC(2)
     *                    SC(3) -> SC(4) -> no change -> SC(0)
     *                    SC(1) -> SC(2) ->   SC(3)   -> SC(4) <- southeast
     */
    void CheckerSwap();

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
    void FlipHorizontal();

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
    void FlipVertical();

    // The following two functions are used ONLY for us (the CPSC 221 staff) to test the structure of your TwoDLinkedList.
    // None of your other member functions should be calling these.
    // In normal practice, we should not expose private member attributes like this.
    TwoDNode* GetNorthwest() { return northwest; }
    TwoDNode* GetSoutheast() { return southeast; }

  private:
    // DECLARE YOUR OWN PRIVATE FUNCTIONS HERE IF NEEDED

};

#endif