/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"

class StickerSheet {

    public:
        StickerSheet(const Image &picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet &other);
        const StickerSheet & operator= (const StickerSheet &other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image* getSticker(unsigned index);
        Image render() const;

    private:
        void clear();
        void copy(const StickerSheet &other);

        //array of stickers
        Image** stickers;
        //base image
        Image* base;
        //maximumm stickers allowed
        unsigned max_;
        //array of x coordinate of stickers
        unsigned* x_coor_;
        //array of y coordinate of stickers
        unsigned* y_coor_;
        //number of stickers currently stored
        unsigned num_stickers_;
}; 
