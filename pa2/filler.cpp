/*
*  File:        filler.cpp
*  Description: Implementation of functions in the filler namespace.
*
*/

/*
*  Performs a flood fill using breadth first search.
*
*  PARAM:  config - FillerConfig struct to setup the fill
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
animation filler::FillBFS(FillerConfig& config) {
  // complete your implementation below
  // You should replace the following line with a
  // correct call to fill.

  return Fill<Queue>(config); //IT'S the only thing I should do in here!
  
  // while (!os.IsEmpty()) {
  //   PixelPoint curr = os.Peek();
  //   if (curr.x - 1 != config.img.width) {
  //     os.Push(PixelPoint(curr.x + 1, curr.y, config.img.getPixel(curr.x + 1, curr.y)));
  //   }
  //   if (curr.y - 1 != config.img.height) {
  //     os.Push(PixelPoint(curr.x, curr.y + 1, config.img.getPixel(curr.x, curr.y + 1)));
  //   }
  //   if (curr.y != 0) {
  //     os.Push(PixelPoint(curr.x, curr.y - 1, config.img.getPixel(curr.x, curr.y - 1)));
  //   }
  //   if (curr.x != 0) {
  //     os.Push(PixelPoint(curr.x - 1, curr.y, config.img.getPixel(curr.x - 1, curr.y)));
  //   }

  //   Fill(config);

  // }

  //return animation();
}

/*
*  Performs a flood fill using depth first search.
*
*  PARAM:  config - FillerConfig struct to setup the fill
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
animation filler::FillDFS(FillerConfig& config) {
  // complete your implementation below
  // You should replace the following line with a
  // correct call to fill.
  // animation anim;
  // OrderingStructure<PixelPoint> os;

  // Fill(config);

  // while (!os.IsEmpty()) {
  //   PixelPoint goDeep = os.Peek();
  //   if (goDeep.y != config.img.height) {
  //     os.Push(PixelPoint(goDeep.x, goDeep.y + 1, config.img.getPixel(goDeep.x, goDeep.y + 1)));
  //   } else if (goDeep.x != config.img.width) {
  //     os.Push(PixelPoint(goDeep.x + 1, seedpoint.y, config.img.getPixel(goDeep.x + 1, seedpoint.y)));
  //   }

  //   Fill(config);
  // }


  return Fill<Stack>(config);

  
}

/*
*  Run a flood fill on an image starting at the seed point
*
*  PARAM:  config - FillerConfig struct with data for flood fill of image
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
template <template <class T> class OrderingStructure> animation filler::Fill(FillerConfig& config)
{
  /*
  * You need to implement this function!
  *
  * This is the basic description of a flood-fill algorithm: Every fill
  * algorithm requires an ordering structure, which is passed to this
  * function via its template parameter. For a breadth-first-search
  * fill, that structure is a Queue, for a depth-first-search, that
  * structure is a Stack. To begin the algorithm, you simply place the
  * given point in the ordering structure, marking it processed
  * (the way you mark it is a design decision you'll make yourself).
  * We have a choice to either change the color, if appropriate, when we
  * add the point to the OS, or when we take it off. In our test cases,
  * we have assumed that you will change the color when a point is removed
  * from the structure.
  * Until the structure is empty, you do the following:
  *
  * 1.     Remove a point from the ordering structure, and then...
  *
  *        1.    add its unprocessed neighbors (up/down/left/right) whose color values are
  *              within (or equal to) tolerance distance from the seed point,
  *              to the ordering structure, and
  *              mark them as processed.
  *        2.    if it is an appropriate frame, send the current PNG to the
  *              animation (as described below).
  *
  * 2.     When implementing your breadth-first-search and
  *        depth-first-search fills, you will need to explore neighboring
  *        pixels (up/down/left/right) in some order.
  *
  *        While the order in which you examine neighbors does not matter
  *        for a proper fill, you must use the same order as we do for
  *        your animations to come out like ours! The order you should put
  *        neighboring pixels **ONTO** the queue or stack is as follows:
  *        1. northern neighbour (up)
  *        2. eastern neighbour (right)
  *        3. southern neighbour (down)
  *        4. western neighbour (left)
  * 
  *        If you process the neighbours in a different order, your fill may
  *        still work correctly, but your animations will be different
  *        from the grading scripts!
  *
  * 3.     For every k pixels filled, **starting at the kth pixel**, you
  *        must add a frame to the animation, where k = frameFreq.
  *
  *        For example, if frameFreq is 4, then after the 4th pixel has
  *        been filled you should add a frame to the animation, then again
  *        after the 8th pixel, etc.  You must only add frames for the
  *        number of pixels that have been filled, not the number that
  *        have been checked. So if frameFreq is set to 1, a pixel should
  *        be filled every frame.
  *
  * 4.     Finally, as you leave the function, send one last frame to the
  *        animation. This frame will be the final result of the fill, and
  *        it will be the one we test against.
  *
  */

  int framecount = 0; // increment after processing one pixel; used for producing animation frames (step 3 above)
  animation anim;
  OrderingStructure<PixelPoint> os;

  vector<vector<bool>> marked;

  for (int x = 0; x <= config.img.width(); x++) {
    vector<bool> ys;
    for (int y = 0; y <= config.img.height(); y++) {
      ys.push_back(false);
    }
    marked.push_back(ys);
  }

  os.Add(config.seedpoint); //add seedpoint (starting point) //os.Add(RGBAPixel*)
  marked[config.seedpoint.x][config.seedpoint.y] = true; //mark seedpoint

  while (!os.IsEmpty()) { //while os has PixelPoint
    PixelPoint curr = os.Remove(); //Pop
    //config.picker->operator()(curr); //coloring the current PixelPoint
    RGBAPixel* original = config.img.getPixel(curr.x, curr.y);
    *original = (*(config.picker))(curr);
    //colorImg(original, curr); //trying to change the color in referenceimg
    framecount++;
    
    if (framecount == config.frameFreq) { //check Frame
        anim.addFrame(config.img); 
        framecount = 0;
    }
  
   if (curr.y != 0) {
      RGBAPixel* northpix = config.img.getPixel(curr.x, curr.y - 1);
      PixelPoint north = PixelPoint(curr.x, curr.y - 1, *northpix);
      if (checkTolerance(north, config.tolerance, config.seedpoint.color) && !isMarked(marked, north)) {
        os.Add(north);
        marked[north.x][north.y] = true;
      }
    }
    if (curr.x != config.img.width()) {
      RGBAPixel* eastpix = config.img.getPixel(curr.x + 1, curr.y);
      PixelPoint east = PixelPoint(curr.x + 1, curr.y, *eastpix);
      if (checkTolerance(east, config.tolerance, config.seedpoint.color) && !isMarked(marked, east)) {
        os.Add(east);
        marked[east.x][east.y]=true;
      }
    }
    
    
    if (curr.y != config.img.height())  //if it's in boundary of img
    {
      RGBAPixel* southpix = config.img.getPixel(curr.x, curr.y + 1);
      PixelPoint south = PixelPoint(curr.x, curr.y + 1, *southpix);
      if (checkTolerance(south, config.tolerance, config.seedpoint.color) && !isMarked(marked, south)) {
        os.Add(south); //if south is tolerable(fillable) and not marked add north os to process
        marked[south.x][south.y] = true;
      }
    }
    if (curr.x != 0) {
      RGBAPixel* westpix = config.img.getPixel(curr.x - 1, curr.y);
      PixelPoint west = PixelPoint(curr.x - 1, curr.y, *westpix);
      if (checkTolerance(west, config.tolerance, config.seedpoint.color) && !isMarked(marked, west)) {
        os.Add(west);
        marked[west.x][west.y] = true;
      }
    }
  }

  anim.addFrame(config.img);
  
  

  // complete your implementation below
  // HINT: you will likely want to declare some kind of structure to track
  //       which pixels have already been visited
  

  return anim;
}

bool filler::isMarked(vector<vector<bool>> vec, PixelPoint point) {

  return vec[point.x][point.y];
}

bool filler::checkTolerance(PixelPoint point, double tol, RGBAPixel color) {
  return (point.color.dist(color) <= tol);
}

void filler::colorImg(RGBAPixel* pixel, PixelPoint point) {
  pixel->r = point.color.r;
  pixel->g = point.color.g;
  pixel->b = point.color.b;
}

vector<int> filler::toVector(PixelPoint point) {
  vector<int> position;
  position.push_back(point.x);
  position.push_back(point.y);
  return position;
}