/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<3>> converted;
    map<Point<3>, TileImage*> ConvertedMap;
    for (auto& pt : theTiles) {
        LUVAPixel pixel = pt.getAverageColor();
        Point<3> point = convertToXYZ(pixel);
        converted.push_back(point);
        ConvertedMap[point] = &pt;
    }
    KDTree<3> AvgColorTree(converted);
    MosaicCanvas *ReturnCanvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    for (int y = 0; y < ReturnCanvas->getColumns(); y++) {
        for (int x = 0; x < ReturnCanvas->getRows(); x++) {
            Point<3> cur = convertToXYZ(theSource.getRegionColor(x, y));
            Point<3> match = AvgColorTree.findNearestNeighbor(cur);
            ReturnCanvas->setTile(x, y, ConvertedMap[match]);
        }
    }
    return ReturnCanvas;
}

