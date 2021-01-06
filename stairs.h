//
//  stairs.hpp
//  Project3x
//
//  Created by Neel Jhunjhunwala on 5/13/20.
//  Copyright © 2020 Neel Jhunjhunwala. All rights reserved.
//

#ifndef stairs_hpp
#define stairs_hpp

class stairs{
public:
    stairs();
    
    // getter methods to access the location of the stairs
    int row() const {return srow;}
    int col() const {return scol;}
    // setter function to assign teh scroll's location
    void setpos(int r, int c) ; 
    
private:
    // private variables to store the idol's location on the grid 
    int srow;
    int scol;
    
};

#endif /* stairs_hpp */
