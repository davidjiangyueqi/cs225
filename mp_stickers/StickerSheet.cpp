#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h"

    //Initialize base pic and max stickers can hold
    StickerSheet::StickerSheet(const Image &picture, unsigned max) {

        stickers = new Image*[max];
        base = new Image(picture);
        max_ = max;
        min_layer = 0;
        x_coor_ = new unsigned[max_];
        y_coor_ = new unsigned[max_];
        for (unsigned i = 0; i < max; i++) {
            stickers[i] = nullptr;
            x_coor_[i] = 0;
            y_coor_[i] = 0;
        }
    }

    void StickerSheet::clear() {

        for (unsigned i = 0; i < max_; i++) {
            if (stickers[i] != nullptr) {
                delete stickers[i];
                stickers[i] = nullptr;
            }
        }
        
        delete base;
        base = nullptr;
        delete[] stickers;
        stickers = nullptr;
        delete[] x_coor_;
        x_coor_ = nullptr;
        delete[] y_coor_;
        y_coor_ = nullptr;
    }
    
    void StickerSheet::copy(const StickerSheet &other) {

        max_ = other.max_;
        base = new Image(*other.base);
        min_layer = other.min_layer;
        x_coor_ = new unsigned[max_];
        y_coor_ = new unsigned[max_];
        stickers = new Image*[max_];
        for (unsigned i = 0; i < max_; i++) {
            if (other.stickers[i] != nullptr) {
                stickers[i] = new Image(*other.stickers[i]);
                x_coor_[i] = other.x_coor_[i];
                y_coor_[i] = other.y_coor_[i];
            } else {
                stickers[i] = nullptr;
            }
        }
    }
    
    StickerSheet::~StickerSheet() {

        clear();
    }
    
    StickerSheet::StickerSheet(const StickerSheet &other) {

        copy(other);
    }
    
    const StickerSheet & StickerSheet::operator= (const StickerSheet &other) {

        clear();
        copy(other);
        return *this;
    }
    
    void StickerSheet::changeMaxStickers(unsigned max) {

        //copy the original arrays into temp array
        if (max == max_) {
            return;
        }

        Image** temp_stickers = new Image*[max_];
        unsigned* temp_x = new unsigned[max_];
        unsigned* temp_y = new unsigned[max_];
        for (unsigned i = 0; i < max_; i++) {
            temp_stickers[i] = stickers[i];
            temp_x[i] = x_coor_[i];
            temp_y[i] = y_coor_[i];
        }

        delete[] stickers;
        delete[] x_coor_;
        delete[] y_coor_;
        //create new data with new max
        stickers = new Image*[max];
        x_coor_ = new unsigned[max];
        y_coor_ = new unsigned[max];

        if (max_ < max) {
            for (unsigned i = 0; i < max_; i++) {
                stickers[i] = temp_stickers[i];
                x_coor_[i] = temp_x[i];
                y_coor_[i] = temp_y[i];
            }
            for (unsigned int i = max_; i < max; i++) {
                stickers[i] = nullptr;
            }
        } else {
            for (unsigned int i = 0; i < max; i++) {
                stickers[i] = temp_stickers[i];
                x_coor_[i] = temp_x[i];
                y_coor_[i] = temp_y[i]; 
            }
            for (unsigned int i = max; i < max_; i++) {
                delete temp_stickers[i];
                temp_stickers[i] = nullptr;
            }
        }
        max_ = max;
        delete[] temp_stickers;     temp_stickers = nullptr;
        delete[] temp_x;            temp_x = nullptr;
        delete[] temp_y;            temp_y = nullptr;
    }

    //MODIFIED MON    
    int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
        
        //add sticker if within range.
        if (min_layer < max_) {
            if (stickers[min_layer] == nullptr) {
                stickers[min_layer] = new Image(sticker);
                x_coor_[min_layer] = x;
                y_coor_[min_layer] = y;
            } else {
                std::cout << "The min_layer counter is wrong" << std::endl;
                std::cout << "Max is " << max_ << std::endl;
                std::cout << "min_layer" << min_layer << std::endl;
                std::cout << "DEBUG" << std::endl;
                std::cout << "DEBUG" << std::endl;
                std::cout << "DEBUG" << std::endl;
            }

            //update min_layer counter
            for (unsigned i = 0; i < max_; i++) {
                if (stickers[i] == nullptr) {
                    min_layer = i;
                    break;
                } else {
                    min_layer = max_;
                }
            }
        }
        return -1;
    }
    
    bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {

        if (index < max_) {
            if (stickers[index] != nullptr) {
                x_coor_[index] = x;
                y_coor_[index] = y;
                return true;
            }
        }
        return false;
    }
    
    void StickerSheet::removeSticker(unsigned index) {
        
        if (index >= max_ || index < 0 || stickers[index] == nullptr) return;
        //remove sticker at index
        delete stickers[index];
        stickers[index] = nullptr;

        //update min_layer counter
        for (unsigned i = 0; i < max_; i++) {
            if (stickers[i] == nullptr) {
                min_layer = i;
                break;
            }
        }
    }
    
    Image* StickerSheet::getSticker(unsigned index) {
    
        if (index >= max_ || stickers[index] == nullptr) return nullptr;
        return stickers[index];
    }
    
    Image StickerSheet::render() const {
        
        Image result(*base);
        unsigned ResultWidth = result.width();
        unsigned ResultHeight = result.height();
        //traverse thru stickers
        for (unsigned i = 0; i < max_; i++) {
            
            if (stickers[i] != nullptr) {
                Image* CurSticker = stickers[i];
                //get dimension and adjust result image size
                unsigned CurWidth = stickers[i]->width();
                unsigned CurHeight = stickers[i]->height();
                if (CurWidth + x_coor_[i] > ResultWidth) {
                    ResultWidth = CurWidth + x_coor_[i];
                } else if (CurHeight + y_coor_[i] > ResultHeight) {
                    ResultHeight = CurHeight + y_coor_[i];
                }
                result.resize(ResultWidth, ResultHeight);
                for (unsigned h = 0; h < CurHeight; h++) {
                    for (unsigned w = 0; w < CurWidth; w++) {
                        //sticker's position on the result image
                        cs225::HSLAPixel& ResultPixel = result.getPixel(w + x_coor_[i], h + y_coor_[i]);
                        cs225::HSLAPixel& StickerPixel = CurSticker->getPixel(w, h);
                        if (StickerPixel.a != 0) {
                            ResultPixel = StickerPixel;
                        }
                    }
                }
            }

            
        }
        return result;
    };