#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <limits.h>
#include <vector>
#include <sys/stat.h>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "filler.h"
#include "solidColorPicker.h"
#include "negativeColorPicker.h"
#include "blendColorPicker.h"
#include "edgeColorPicker.h"
#include "rainbowColorPicker.h"

using namespace std;
using namespace cs221util;

#define IMAGEDIR "images/"
#define SOLNIMGDIR "soln_images/"

#define FUNCTORTESTHEIGHT 150
#define FUNCTORTESTWIDTH 150
#define FUNCTORTESTFREQ 10
#define FUNCTORTESTX 40
#define FUNCTORTESTY 10
#define FUNCTORTESTRADIUS 45

#define SOLIDX 80
#define SOLIDY 80
#define SOLIDTOLERANCE 0.05
#define SOLIDTESTIMAGE "originals/Canada.png"
#define SOLIDFRAMEFREQ 100

#define NEGATIVEX 98 
#define NEGATIVEY 64
#define NEGATIVETOLERANCE 0.02
#define NEGATIVETESTIMAGE "originals/cloud.png"
#define NEGATIVEFRAMEFREQ 100

#define BLENDX 120
#define BLENDY 60
#define BLENDTOLERANCE 0.05
#define BLENDTESTIMAGE "originals/bento.png"
#define BLENDOTHERIMAGE "originals/ghost.png"
#define BLENDFRAMEFREQ 70

#define EDGEX 50
#define EDGEY 50
#define EDGETESTIMAGE "originals/mooncake.png"
#define EDGEFRAMEFREQ 250
#define EDGETOLERANCE 0.05
#define EDGEWIDTH 4

#define RAINFREQ 1.0/1000.0
#define RAINTOLERANCE 0.05
#define RAINX 75
#define RAINY 75
#define RAINTESTIMAGE "originals/leaf.png"
#define RAINFRAMEFREQ 70 

PNG testColorPicker(ColorPicker& picker)
{
    PNG img;
    img.resize(FUNCTORTESTWIDTH, FUNCTORTESTHEIGHT);
    RGBAPixel px;

    for (int x = 0; x < FUNCTORTESTWIDTH; x++){
        for (int y = 0; y < FUNCTORTESTHEIGHT; y++){
            RGBAPixel * p = img.getPixel(x,y);
            PixelPoint pp(x, y, *p);
            *p = picker(pp);
        }
    }

    return img;
}

TEST_CASE("colorPicker::basic solid","[weight=0][part=colorPicker]"){

  cout << "Entered colorPicker::basic solid..." << endl;

    RGBAPixel px(0, 255, 0, 1.0); // green
    SolidColorPicker solidPicker(px);

    PNG result = testColorPicker(solidPicker);
    result.writeToFile("images/solidColorPickerTest.png");
    PNG expected; expected.readFromFile("soln_images/solidColorPickerTest.png");
    REQUIRE(result == expected);
    
    cout << "Leaving colorPicker::basic solid..." << endl;
}

TEST_CASE("colorPicker::basic negative","[weight=1][part=colorPicker]"){

  cout << "Entered colorPicker::basic negative..." << endl;

    PNG imgtest;
    imgtest.readFromFile(NEGATIVETESTIMAGE);

    NegativeColorPicker negativePicker(imgtest);

    PNG result = testColorPicker(negativePicker);
    result.writeToFile("images/negativeColorPickerTest.png");
    PNG expected; expected.readFromFile("soln_images/negativeColorPickerTest.png");
    REQUIRE(result == expected);

    cout << "Leaving colorPicker::basic negative..." << endl;
}

TEST_CASE("colorPicker::basic blend","[weight=1][part=colorPicker]"){
    
  cout << "Entered colorPicker::basic blend..." << endl;

    PNG imgtest, imgother;
    imgtest.readFromFile(BLENDTESTIMAGE);
    imgother.readFromFile(BLENDOTHERIMAGE);

    BlendColorPicker blendPicker(imgtest, imgother);

    PNG result = testColorPicker(blendPicker);
    result.writeToFile("images/blendColorPickerTest.png");
    PNG expected; expected.readFromFile("soln_images/blendColorPickerTest.png");
    REQUIRE(result == expected);

    cout << "Leaving colorPicker::basic blend..." << endl;
}

TEST_CASE("colorPicker::basic edge", "[weight=1][part=colorPicker]") {
  
  cout << "Entered colorPicker::basic edge..." << endl;

  PNG imgtest;
  imgtest.readFromFile(EDGETESTIMAGE);
  RGBAPixel edgecolor(10, 10, 30, 1.0); // dark, with more blue
  PixelPoint p(EDGEX, EDGEY, *(imgtest.getPixel(EDGEX, EDGEY)));
  EdgeColorPicker edgePicker(imgtest, edgecolor, EDGEWIDTH, p, EDGETOLERANCE);

  PNG result = testColorPicker(edgePicker);
  result.writeToFile("images/edgeColorPickerTest.png");
  PNG expected; expected.readFromFile("soln_images/edgeColorPickerTest.png");
  REQUIRE(result == expected);

  cout << "Leaving colorPicker::basic edge..." << endl;
}

TEST_CASE("colorPicker::basic rainbow","[weight=0][part=colorPicker]"){
  
  cout << "Entered colorPicker::basic rainbow..." << endl;
  
  RainbowColorPicker rainPicker(1.0/1000.0);

  PNG result = testColorPicker(rainPicker);
  result.writeToFile("images/rainColorPickerTest.png");
  PNG expected; expected.readFromFile("soln_images/rainColorPickerTest.png");
  REQUIRE(result == expected);

  cout << "Leaving colorPicker::basic rainbow..." << endl;
}

TEST_CASE("fill::basic solid dfs","[weight=1][part=fill]"){
    
  cout << "Entered fill::basic solid dfs..." << endl;

    RGBAPixel px(85, 255, 0);
    SolidColorPicker solidPicker(px);

    filler::FillerConfig solidconfig;
    solidconfig.img.readFromFile(SOLIDTESTIMAGE);
    solidconfig.frameFreq = SOLIDFRAMEFREQ;
    solidconfig.tolerance = SOLIDTOLERANCE;
    solidconfig.seedpoint = PixelPoint(SOLIDX, SOLIDY, *solidconfig.img.getPixel(SOLIDX,SOLIDY));
    solidconfig.picker = &solidPicker;

    animation anim;
    anim = filler::FillDFS(solidconfig);
    PNG result = anim.write("images/dfssolid.gif"); 
    result.writeToFile("images/dfssolid.png");

    PNG expected; expected.readFromFile("soln_images/dfssolid.png");
    REQUIRE(result==expected);

    cout << "PIXEL AT (0, 0)" << solidconfig.img.getPixel(0, 0)->r << " " << solidconfig.img.getPixel(0, 0)->g << solidconfig.img.getPixel(0, 0)->b << endl;

    cout << "Leaving fill::basic solid dfs..." << endl;
}


TEST_CASE("fill::basic solid bfs","[weight=1][part=fill]"){
    
  cout << "Entered fill::basic solid bfs..." << endl;

    RGBAPixel px(85, 255, 0);
    SolidColorPicker solidPicker(px);

    filler::FillerConfig solidconfig;
    solidconfig.img.readFromFile(SOLIDTESTIMAGE);
    solidconfig.frameFreq = SOLIDFRAMEFREQ;
    solidconfig.tolerance = SOLIDTOLERANCE;
    solidconfig.seedpoint = PixelPoint(SOLIDX, SOLIDY, *solidconfig.img.getPixel(SOLIDX, SOLIDY));
    solidconfig.picker = &solidPicker;

    animation anim;
    anim = filler::FillBFS(solidconfig);
    PNG result = anim.write("images/bfssolid.gif");
    result.writeToFile("images/bfssolid.png");

    PNG expected; expected.readFromFile("soln_images/bfssolid.png");
    REQUIRE(result==expected);

    cout << "Leaving fill::basic solid bfs..." << endl;
}

TEST_CASE("fill::basic negative dfs", "[weight=1][part=fill]") {
    
  cout << "Entered fill::basic negative dfs..." << endl;

  PNG negativetest;
  negativetest.readFromFile(NEGATIVETESTIMAGE);
  NegativeColorPicker negativePicker(negativetest);

  filler::FillerConfig negativeconfig;
  negativeconfig.img = negativetest;
  negativeconfig.frameFreq = NEGATIVEFRAMEFREQ;
  negativeconfig.tolerance = NEGATIVETOLERANCE;
  negativeconfig.seedpoint = PixelPoint(NEGATIVEX, NEGATIVEY, *negativeconfig.img.getPixel(NEGATIVEX, NEGATIVEY));
  negativeconfig.picker = &negativePicker;

  animation anim;
  anim = filler::FillDFS(negativeconfig);
  PNG result = anim.write("images/dfsnegative.gif");
  result.writeToFile("images/dfsnegative.png");

  PNG expected; expected.readFromFile("soln_images/dfsnegative.png");
  REQUIRE(result == expected);

  cout << "Leaving fill::basic negative dfs..." << endl;
}

TEST_CASE("fill::basic negative bfs", "[weight=1][part=fill]") {
  
  cout << "Entered fill::basic negative bfs..." << endl;
  
  PNG negativetest;
  negativetest.readFromFile(NEGATIVETESTIMAGE);
  NegativeColorPicker negativePicker(negativetest);

  filler::FillerConfig negativeconfig;
  negativeconfig.img = negativetest;
  negativeconfig.frameFreq = NEGATIVEFRAMEFREQ;
  negativeconfig.tolerance = NEGATIVETOLERANCE;
  negativeconfig.seedpoint = PixelPoint(NEGATIVEX, NEGATIVEY, *negativeconfig.img.getPixel(NEGATIVEX, NEGATIVEY));
  negativeconfig.picker = &negativePicker;

  animation anim;
  anim = filler::FillBFS(negativeconfig);
  PNG result = anim.write("images/bfsnegative.gif");
  result.writeToFile("images/bfsnegative.png");

  PNG expected; expected.readFromFile("soln_images/bfsnegative.png");
  REQUIRE(result == expected);

  cout << "Leaving fill::basic negative bfs..." << endl;
}

TEST_CASE("fill::basic blend dfs","[weight=1][part=fill]"){
    
  cout << "Entered fill::basic blend dfs..." << endl;

  PNG blendtest;
  PNG blendother;
  blendtest.readFromFile(BLENDTESTIMAGE);
  blendother.readFromFile(BLENDOTHERIMAGE);
  BlendColorPicker blendPicker(blendtest, blendother);

  filler::FillerConfig blendconfig;
  blendconfig.img = blendtest;
  blendconfig.frameFreq = BLENDFRAMEFREQ;
  blendconfig.tolerance = BLENDTOLERANCE;
  blendconfig.seedpoint = PixelPoint(BLENDX, BLENDY, *blendconfig.img.getPixel(BLENDX, BLENDY));
  blendconfig.picker = &blendPicker;

  animation anim;
  anim = filler::FillDFS(blendconfig);
  PNG result = anim.write("images/dfsblend.gif");
  result.writeToFile("images/dfsblend.png");

  PNG expected; expected.readFromFile("soln_images/dfsblend.png");
  REQUIRE(result==expected);

  cout << "Leaving fill::basic blend dfs..." << endl;
}

TEST_CASE("fill::basic blend bfs","[weight=1][part=fill]"){
    
  cout << "Entered fill::basic blend bfs..." << endl;

  PNG blendtest;
  PNG blendother;
  blendtest.readFromFile(BLENDTESTIMAGE);
  blendother.readFromFile(BLENDOTHERIMAGE);
  BlendColorPicker blendPicker(blendtest, blendother);

  filler::FillerConfig blendconfig;
  blendconfig.img = blendtest;
  blendconfig.frameFreq = BLENDFRAMEFREQ;
  blendconfig.tolerance = BLENDTOLERANCE;
  blendconfig.seedpoint = PixelPoint(BLENDX, BLENDY, *blendconfig.img.getPixel(BLENDX, BLENDY));
  blendconfig.picker = &blendPicker;

  animation anim;
  anim = filler::FillBFS(blendconfig);
  PNG result = anim.write("images/bfsblend.gif");
  result.writeToFile("images/bfsblend.png");

  PNG expected; expected.readFromFile("soln_images/bfsblend.png");
  REQUIRE(result==expected);

  cout << "Leaving fill::basic blend bfs..." << endl;
}

TEST_CASE("fill::basic edge dfs","[weight=1][part=fill]"){
  
  cout << "Entered fill::basic edge dfs..." << endl;
  
  PNG imgtest;
  imgtest.readFromFile(EDGETESTIMAGE);
  RGBAPixel edgecolor(10, 10, 30, 1.0); // dark, with more blue
  PixelPoint p(EDGEX, EDGEY, *(imgtest.getPixel(EDGEX, EDGEY)));
  EdgeColorPicker edgePicker(imgtest, edgecolor, EDGEWIDTH, p, EDGETOLERANCE);

  filler::FillerConfig edgeconfig;
  edgeconfig.img = imgtest;
  edgeconfig.frameFreq = EDGEFRAMEFREQ;
  edgeconfig.tolerance = EDGETOLERANCE;
  edgeconfig.seedpoint = PixelPoint(EDGEX, EDGEY, *edgeconfig.img.getPixel(EDGEX, EDGEY));
  edgeconfig.picker = &edgePicker;

  animation anim;
  anim = filler::FillDFS(edgeconfig);
  PNG result = anim.write("images/dfsedge.gif");
  result.writeToFile("images/dfsedge.png");

  PNG expected; expected.readFromFile("soln_images/dfsedge.png");
  REQUIRE(result==expected);

  cout << "Leaving fill::basic edge dfs..." << endl;
}

TEST_CASE("fill::basic edge bfs","[weight=1][part=fill]"){
  
  cout << "Entered fill::basic edge bfs..." << endl;
  
  PNG imgtest;
  imgtest.readFromFile(EDGETESTIMAGE);
  RGBAPixel edgecolor(10, 10, 30, 1.0); // dark, with more blue
  PixelPoint p(EDGEX, EDGEY, *(imgtest.getPixel(EDGEX, EDGEY)));
  EdgeColorPicker edgePicker(imgtest, edgecolor, EDGEWIDTH, p, EDGETOLERANCE);

  filler::FillerConfig edgeconfig;
  edgeconfig.img = imgtest;
  edgeconfig.frameFreq = EDGEFRAMEFREQ;
  edgeconfig.tolerance = EDGETOLERANCE;
  edgeconfig.seedpoint = PixelPoint(EDGEX, EDGEY, *edgeconfig.img.getPixel(EDGEX, EDGEY));
  edgeconfig.picker = &edgePicker;

  animation anim;
  anim = filler::FillBFS(edgeconfig);
  PNG result = anim.write("images/bfsedge.gif");
  result.writeToFile("images/bfsedge.png");

  PNG expected; expected.readFromFile("soln_images/bfsedge.png");
  REQUIRE(result==expected);

  cout << "Leaving fill::basic edge bfs..." << endl;
}

TEST_CASE("fill::basic rainbow dfs","[weight=1][part=fill]"){

  cout << "Entered fill::basic rainbow dfs..." << endl;

  PNG imgtest;
  imgtest.readFromFile(RAINTESTIMAGE);
  RainbowColorPicker rainPicker(RAINFREQ);

  filler::FillerConfig rainbowconfig;
  rainbowconfig.img = imgtest;
  rainbowconfig.frameFreq = RAINFRAMEFREQ;
  rainbowconfig.tolerance = RAINTOLERANCE;
  rainbowconfig.seedpoint = PixelPoint(RAINX, RAINY, *rainbowconfig.img.getPixel(RAINX, RAINY));
  rainbowconfig.picker = &rainPicker;

  animation anim;
  anim = filler::FillDFS(rainbowconfig);
  PNG result = anim.write("images/dfsrain.gif");
  result.writeToFile("images/dfsrain.png");

  PNG expected; expected.readFromFile("soln_images/dfsrain.png");
  REQUIRE(result==expected);

  cout << "Leaving fill::basic rainbow dfs..." << endl;
}

TEST_CASE("fill::basic rainbow bfs","[weight=1][part=fill]"){

  cout << "Entered fill::basic rainbow bfs..." << endl;

  PNG imgtest;
  imgtest.readFromFile(RAINTESTIMAGE);
  RainbowColorPicker rainPicker(RAINFREQ);

  filler::FillerConfig rainbowconfig;
  rainbowconfig.img = imgtest;
  rainbowconfig.frameFreq = RAINFRAMEFREQ;
  rainbowconfig.tolerance = RAINTOLERANCE;
  rainbowconfig.seedpoint = PixelPoint(RAINX, RAINY, *rainbowconfig.img.getPixel(RAINX, RAINY));
  rainbowconfig.picker = &rainPicker;

  animation anim;
  anim = filler::FillBFS(rainbowconfig);
  PNG result = anim.write("images/bfsrain.gif");
  result.writeToFile("images/bfsrain.png");

  PNG expected; expected.readFromFile("soln_images/bfsrain.png");
  REQUIRE(result==expected);

  cout << "Leaving fill::basic rainbow bfs..." << endl;
}

