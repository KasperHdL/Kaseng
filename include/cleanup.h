//
// Created by kaholi on 9/13/16.
//

#ifndef SDL_LESSONS_CLEANUP_H
#define SDL_LESSONS_CLEANUP_H

#include <utility>
#include <SDL.h>


template<typename T, typename... Args>
void cleanup(T *t, Args&&... args){
    cleanup(t);
    cleanup(std::forward<Args>(args)...);

}
template<>
inline void cleanup<SDL_Window>(SDL_Window *win){
    if (!win){
        return;
    }
    SDL_DestroyWindow(win);
}
template<>
inline void cleanup<SDL_Renderer>(SDL_Renderer *ren){
    if (!ren){
        return;
    }
    SDL_DestroyRenderer(ren);
}
template<>
inline void cleanup<SDL_Texture>(SDL_Texture *tex){
    if (!tex){
        return;
    }
    SDL_DestroyTexture(tex);
}
template<>
inline void cleanup<SDL_Surface>(SDL_Surface *surf){
    if (!surf){
        return;
    }
    SDL_FreeSurface(surf);
}

#endif //SDL_LESSONS_CLEANUP_H
