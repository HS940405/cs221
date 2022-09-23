/**
 *  @file imgtree-private.h
 *  @description student-defined functions for binary tree class storing image data for CPSC 221 PA3
 *  @author CPSC 221
 *
 *  SUBMIT THIS FILE TO PRAIRIELEARN, EVEN IF YOU DO NOT ADD ANYTHING TO IT
 * 
 *  Usage: As this file is included entirely into imgtree.h by the #include statement on line __
 *  you only need to write the function signature,
 *  e.g.
 *  void MyOwnSpecialFunction(int fave_num, ImgTreeNode* nd);
 * 
 *  and add/complete your implementation in imgtree.cpp
 */

#ifndef _IMGTREE_PRIVATE_H_
#define _IMGTREE_PRIVATE_H_

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "stats.h"

#include <utility>

//using namespace std;
//using namespace cs221util;


    private:

        // helper function for imgtree::Clear() function
        void Clear(ImgTreeNode*& node);

        // helper for ImgTree::Copy
        ImgTreeNode* Copy(ImgTreeNode* node);

        // helper for ImgTree::Render
        void Render(const ImgTreeNode* node, PNG* renderImg) const;

        // helper function for imgtree::FlipHorizontal()
        void FlipHorizontal(ImgTreeNode* node, unsigned int width);

        void FlipVertical(ImgTreeNode* node, unsigned int height);

        unsigned int CountLeaves(const ImgTreeNode* node) const;

        //void Trim(ImgTreeNode* node);

        int checkTol(ImgTreeNode* node, double tol, RGBAPixel parentpix);

        void Prune(ImgTreeNode*& node, double pct, double tol);


#endif