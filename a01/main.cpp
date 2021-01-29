//Name: Micah Arndt
//File Name:a01q01.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "BufferFrame.h"

//File input into the program
void read(std::string & characters)
{
    std::fstream f;
    f.open("test.txt");
    f >> characters;
    f.close();
    //return characters;
}

//File Output into the System
void write(std::string & characters)
{
    std::fstream f;
    f.open("test.txt");
    f << characters;
    f.close();
}

//Prints out the file contents
void test_write(std::string & c)
{
     for (int i = 0; i < c.size(); ++i)
    {
        std::cout << c[i];
        if((i + 1) % 4 == 0)
        {
            std::cout << std::endl;
        }
    }
}
//Print Frames in Buffer
void PrintFrames(BufferFrame  buffer[])
{
    for (int i = 0; i < 3; ++i)
        {
            std::cout << '[';
            
            if(buffer[i].page() > -1)
            {
                if (!(buffer[i].isClean()))
                {
                    std::cout << '*';
                }
                std::cout << buffer[i].page() << ": "
                          << buffer[i].id();
            }
            std::cout << ']';
        }
        std::cout << std::endl;
}
int main()
{
    std::string item;
    read(item);
    int option = -1;
    int page = -1;
    //This Program will have an array of size 3 that will serve as a buffer.
    //There will also be a class called BufferFrame that looks like the following:
    /*
      BufferFrame:
          -Keys:
               id_->the four letter combo
               page_->where the id is in the full file.
               isClean_->whether or not the frame has been modified
               pos_->Provides the frame id of the BufferFrame.
     */
    BufferFrame buffer[3];
    int currentBuffer = 0;
    while (option != 2)
    {
        std::cout << "[0] Fetch a page into memory" << std::endl;
        std::cout << "[1] Write Frame" << std::endl;
        std::cout << "[2] Shutdown" << std::endl;
        std::cout << "Frames: ";
        PrintFrames(buffer);
        std::cout << "option: ";
        std::cin >> option;
        switch (option)
        {
            case 0:
            {
                std::cout << "which page? ";
                std::cin >> page;
                bool cont = 0;
                for(int i = 0; i < 3; ++i)
                {
                    if (page == buffer[i].page())
                    {
                        cont  = 1;
                    std::cout << "page " << page
                              <<"already fetched ... frame id is "
                              << i << std::endl;
                    break;
                    }
                }
                if (cont)
                    continue;
                if (currentBuffer < 3)
                {
                    buffer[currentBuffer].fetch(item, page, currentBuffer);
                    ++currentBuffer;
                }
                else
                {
                    int frame = -1;
                    std::cout << "which frame to remove? ";
                    std::cin >> frame;
                    
                    //If the frame is Dirty, we write to the original.
                    if(!(buffer[frame].isClean()))
                    {
                        std::cout << "Frame " << frame
                                  <<" is dirty ... write to block "
                                  << buffer[frame].page() << std::endl;
                        buffer[frame].writeBuffer(item);
                        buffer[frame].fetch(item, page, frame);
                    }
                    //If the Frame is clean, we don't need to write
                    else
                    {
                        std::cout << "Frame " << frame
                                  <<" is not dirty ... no write" << std::endl;
                        buffer[frame].fetch(item, page, frame);
                    }
                }
                std::cout << std::endl;
                break;
            }
            
            //Write Frame
            case 1:
            {
                std::string inputs;
                std::cout << "which page? ";
                std::cin >> page;
                std::cout << "enter 4 characters: ";
                for (int i = 0; i < 4; ++i)
                {
                    std::cin >> inputs[i];
                }
                for (int i = 0; i < 3; ++i)
                {
                    if (buffer[i].page() == page)
                    {
                        buffer[i].overwrite(inputs);
                        break;
                    }
                }
                break;
            }
            
            //ShutDown
            case 2:
            {
                for (int i = 0; i < 3; ++i)
                {
                    if (!buffer[i].isClean())
                    {
                         std::cout << "Frame " << i
                                  <<" is dirty ... write to block "
                                  << buffer[i].page() << std::endl;
                        buffer[i].writeBuffer(item);
                    }
                }
                std::cout << "halt" << std::endl;
                break;
            }
        }
        
    }
    std::cout << item << std::endl;
    write(item);
    
    return 0;
}
