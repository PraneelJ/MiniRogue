//
//  idol.hpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/13/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#ifndef idol_hpp
#define idol_hpp

class idol{
public:
    idol();
    // getter functions to access the idol's location on the grid
    int row() const {return srow;}
    int col() const {return scol;}
    // method to set the location of the idol
    void setpos(int r, int c) ;
    
private:
    // private variables to store the idol's location on the grid 
    int srow;
    int scol;
    
};


#endif /* idol_hpp */
