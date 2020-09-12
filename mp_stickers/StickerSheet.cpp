#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h"

    //Initialize base pic and max stickers can hold
    StickerSheet::StickerSheet(const Image &picture, unsigned max) {

        stickers = new Image*[max];
        base = new Image(picture);
        max_ = max;
        num_stickers_ = 0;
        x_coor_ = new unsigned[max_];
        y_coor_ = new unsigned[max_];
        x_coor_[0] = 0;
        y_coor_[0] = 0;
    }

    void StickerSheet::clear() {

        for (unsigned i = 0; i < num_stickers_; i++) {
            delete stickers[i];
            stickers[i] = nullptr;
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
        num_stickers_ = other.num_stickers_;
        x_coor_ = new unsigned[max_];
        y_coor_ = new unsigned[max_];
        stickers = new Image*[max_];
        for (unsigned i = 0; i < num_stickers_; i++) {
            stickers[i] = new Image(*other.stickers[i]);
            x_coor_[i] = other.x_coor_[i];
            y_coor_[i] = other.y_coor_[i];
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
        unsigned original_num_ = num_stickers_;
        Image** temp_stickers = new Image*[num_stickers_];
        unsigned* temp_x = new unsigned[num_stickers_];
        unsigned* temp_y = new unsigned[num_stickers_];
        for (unsigned i = 0; i < num_stickers_; i++) {
            temp_stickers[i] = new Image(*stickers[i]);
            temp_x[i] = x_coor_[i];
            temp_y[i] = y_coor_[i];
        }

        //clean up original data
        //if (num_stickers_ > max_) {
            for (unsigned i = 0; i < num_stickers_; i++) {
                delete stickers[i];
                stickers[i] = nullptr;
            }
        //}
        delete[] stickers;
        delete[] x_coor_;
        delete[] y_coor_;
        //create new data with new max
        stickers = new Image*[max];
        x_coor_ = new unsigned[max];
        y_coor_ = new unsigned[max];

        //assign value according to max
        if (max > num_stickers_) {

            for (unsigned i = 0; i < num_stickers_; i++) {
                stickers[i] = new Image(*temp_stickers[i]);
                x_coor_[i] = temp_x[i];
                y_coor_[i] = temp_y[i];
            }
        //when max < num_stickers
        //forfeit stickers from max to num_stickers
        } else {
            
            for (unsigned i = 0; i < max; i++) {
                stickers[i] = new Image(*temp_stickers[i]);
                x_coor_[i] = temp_x[i];
                y_coor_[i] = temp_y[i];
            }
            num_stickers_ = max;
        }
        
        //update max
        max_ = max;
        // reclaim temp memory
        for (unsigned i = 0; i < original_num_; i++) {
            delete temp_stickers[i];
            temp_stickers[i] = nullptr;
        }
        delete[] temp_stickers;     temp_stickers = nullptr;
        delete[] temp_x;            temp_x = nullptr;
        delete[] temp_y;            temp_y = nullptr;
    }
    
    int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
        
        //add sticker if within range.
        if (num_stickers_ < max_) {
            stickers[num_stickers_] = new Image(sticker);
            x_coor_[num_stickers_] = x;
            y_coor_[num_stickers_] = y;
            num_stickers_++;
            return (int) num_stickers_ - 1;
        }
        return -1;
    }
    
    bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {

        if (index < num_stickers_) {
            x_coor_[index] = x;
            y_coor_[index] = y;
            return true;
        }
        return false;
    }
    
    void StickerSheet::removeSticker(unsigned index) {
        
        if (index >= num_stickers_) return;
        //left shift everyimage after index
        delete stickers[index];
        for (unsigned i = index; i < max_ - 1; i++) {
            stickers[i] = stickers[i + 1];
            x_coor_[i] = x_coor_[i + 1];
            y_coor_[i] = y_coor_[i + 1];
        }
        stickers[num_stickers_ - 1] = nullptr;
        x_coor_[num_stickers_ - 1] = 0;
        y_coor_[num_stickers_ - 1] = 0;
        num_stickers_--;
    }
    
    Image* StickerSheet::getSticker(unsigned index) {
    
        if (index >= num_stickers_) return nullptr;
        return stickers[index];
    }
    
    Image StickerSheet::render() const {
        
        Image result(*base);
        unsigned ResultWidth = result.width();
        unsigned ResultHeight = result.height();
        //traverse thru stickers
        for (unsigned i = 0; i < num_stickers_; i++) {

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
        return result;
    };