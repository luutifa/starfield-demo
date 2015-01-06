#ifndef INTRO_HPP
#define INTRO_HPP

#include "common.hpp"
#include "gfx_screen.hpp"
#include "gfx_postprocessor.hpp"

class PIntro{
    public:
        PIntro(CommonData* icommon);
        ~PIntro();
        void draw();
    private:
        GfxScreen* metaballs;
        GfxPostProcessor* rb;
};

#endif
