#include <costants.h>

float tileCentered_Pos(unsigned long i){
    return (image_size * int (i) + float(image_size-tiles_size)/2);
}

void debug(int i){
    std::cout<<"Debug "<<i<<std::endl;
}

char pos_to_letter(size_t pos){
        switch (pos) {
        case 0: return 'A'; break;
        case 1: return 'B'; break;
        case 2: return 'C'; break;
        case 3: return 'D'; break;
        case 4: return 'E'; break;
        case 5: return 'F'; break;
        case 6: return 'G'; break;
        case 7: return 'H'; break;
        case 8: return 'I'; break;
        case 9: return 'L'; break;
        case 10: return 'M'; break;
        case 11: return 'N'; break;
        case 12: return 'O'; break;
        case 13: return 'P'; break;
        case 14: return 'Q'; break;
        case 15: return 'R'; break;
        case 16: return 'S'; break;
        case 17: return 'T'; break;
        case 18: return 'U'; break;
        case 19: return 'V'; break;
        case 20: return 'Z'; break;
        default: return ' '; break;
        }
    }

