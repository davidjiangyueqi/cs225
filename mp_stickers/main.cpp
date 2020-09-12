#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image base;
  base.readFromFile("sunsetBase.png");
  Image cxLogo;
  cxLogo.readFromFile("cx1.png");
  Image anaLogo;
  anaLogo.readFromFile("analogo.png");
  Image lhLogo;
  lhLogo.readFromFile("lufthansalogo.png");

  //resize all stickers
  cxLogo.scale(900, 400);
  anaLogo.scale(600, 200);
  lhLogo.scale(600, 200);

  //append to stickersheet and render final output
  StickerSheet* ResultSheet = new StickerSheet(base, 3);
  ResultSheet->addSticker(cxLogo, 1800, 0);
  ResultSheet->addSticker(anaLogo, 500, 150);
  ResultSheet->addSticker(lhLogo, 1100, 300);
  Image result = ResultSheet->render();
  result.writeToFile("myImage.png");

  //reclaim memory
  delete ResultSheet;   ResultSheet = nullptr;
  return 0;
}
