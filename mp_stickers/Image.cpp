#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <cmath>

    void Image::lighten() {
        
        lighten(0.1);
    }

    void Image::lighten(double amount) {
        
        unsigned const int height_ = height();
        unsigned const int width_ = width();
        for (unsigned int h = 0; h < height_; h++) {
            for (unsigned int w = 0; w < width_; w++) {
                cs225::HSLAPixel& CurPixel = getPixel(w, h);
                if (amount >= 0) {
                    CurPixel.l += amount;
                    CurPixel.l = CurPixel.l > 1 ? 1 : CurPixel.l;
                } else {
                    CurPixel.l += amount;
                    CurPixel.l = CurPixel.l < 0 ? 0 : CurPixel.l; 
                }
            }
        }        
    }

    void Image::darken() {

        lighten(-0.1);
    }

    void Image::darken(double amount) {

        lighten(-amount);
    }

    void Image::saturate() {

        saturate(0.1);
    }

    void Image::saturate(double amount) {

        unsigned const int height_ = height();
        unsigned const int width_ = width();
        for (unsigned int h = 0; h < height_; h++) {
            for (unsigned int w = 0; w < width_; w++) {
                cs225::HSLAPixel& CurPixel = getPixel(w, h);
                if (amount >= 0) {
                    CurPixel.s += amount;
                    CurPixel.s = CurPixel.s > 1 ? 1 : CurPixel.s;
                } else {
                    CurPixel.s += amount;
                    CurPixel.s = CurPixel.s < 0 ? 0 : CurPixel.s; 
                }
            }
        }   
    }

    void Image::desaturate() {

        saturate(-0.1);
    }

    void Image::desaturate(double amount) {
        
        saturate(-amount);
    }

    void Image::grayscale() {

        const int grey = -1;
        desaturate(grey);
    }

    void Image::rotateColor(double degrees) {

        int height_ = height();
        int width_ = width();
        const int hue_threshold_ = 360;
        for (int h = 0; h < height_; h++) {
            for (int w = 0; w < width_; w++) {
                cs225::HSLAPixel& CurPixel = getPixel(w, h);
                CurPixel.h += degrees;
                while (CurPixel.h < 0) {
                    //CurPixel.h += ceil(abs(CurPixel.h) / hue_threshold_) * hue_threshold_;
                    CurPixel.h += hue_threshold_;
                }
                const double decimal = CurPixel.h - (int)CurPixel.h;
                CurPixel.h = ((int) CurPixel.h) % hue_threshold_ + decimal;
            }
        }
    }
    void Image::illinify() {
        
        double orange = 11;
        double blue = 216;
        unsigned int height_ = height();
        unsigned int width_ = width();
        for (unsigned int h = 0; h < height_; h++) {
            for (unsigned int w = 0; w < width_; w++) {
                cs225::HSLAPixel& pixel = getPixel(w, h);
                double OrangeDist = abs(pixel.h - orange);
                double BlueDist = abs(pixel.h - blue);
                OrangeDist = OrangeDist >= 180 ? 360 - OrangeDist : OrangeDist;
                BlueDist = BlueDist >= 180 ? 360 - BlueDist : BlueDist;
            }
        }
    }

    void Image::scale(double factor) {
        
        double width_ = width() * factor;
        double height_ = height() * factor;
        double width_scale_ = width() / width_;
        double height_scale_ = height() / height_;
        //retain original aspect ratio
        double aspect_ratio_;
        if (width_scale_ < height_scale_) {
            aspect_ratio_ = width_scale_;
        } else {
            aspect_ratio_ = height_scale_;
        }
        
        //resize the image and append pixel
        Image original = *this;
        resize(width_, height_);
        for (unsigned int h = 0; h < height_; h++) {
            for (unsigned int w = 0; w < width_; w++) {
                cs225::HSLAPixel& CurPixel = getPixel(w, h);
                CurPixel = original.getPixel(w * width_scale_, h * height_scale_);
            }
        }
    }

    void Image::scale (unsigned w, unsigned h) {
       
        //get aspect ratio and call scale using factor 
        double width_scale_ = width() / w;
        double height_scale_ = height() / h;
        if (width_scale_ > height_scale_) {
            scale(width_scale_);
        } else {
            scale(height_scale_);
        }
    }