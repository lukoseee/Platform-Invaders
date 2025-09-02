#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "../Util/ImageInfo.hpp"
#include "../Util/AudioInfo.hpp"


/*
 ResourceManagerInterface provides an abstracted way of instantiating
 abstraction layer objects such as: ImageInfo, AudioInfo.
 
 This interface handles the construction of filepaths for game resources which
 can then be used by other elements of the abstraction layer.
 
 Users of the library are encouraged to use the ImageInfo and AudioInfo 'constructors'
 provdied here.
 */
class ResourceManagerInterface {
public:
    virtual ImageInfo* makeImage(std::string, int, int, bool) = 0;
    virtual AudioInfo* makeAudio(std::string) = 0;
    
    // reads the full contents of a file and returns it as a string
    std::string readFile(std::string file) {
        // construct an input stream for the text file
        std::ifstream inFile(getBuildPathForResource(file + ".txt"));
        
        // sanity check file was opened
        if (!inFile)
            return NULL;
        
        // iterate over the file and append lines to a string
        std::string builder, line;
        while(std::getline(inFile, line))
            builder += (line + '\n');
        
        // remove the last '\n'
        if(!builder.empty())
            builder.pop_back();
        
        // return contents
        return builder;
    }
    
    // opens a file and writes to it
    void writeFile(std::string file, std::string contents, bool appendMode) {
        std::string path = getBuildPathForResource(file + ".txt");
    
        // open file and configure if file should be overwritten or appended to
        std::ofstream outFile;
        appendMode ? outFile.open(path, std::ios::app) : outFile.open(path);
        
        // sanity check file was opened
        if (!outFile)
            return;
    
        // write contents
        outFile << contents;
    }
    
protected:
    virtual std::string getBuildPathForResource(std::string) = 0;
};
