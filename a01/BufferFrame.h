#ifndef BUFFERFRAME_H
#define BUFFERFRAME_H
#include <string>

class BufferFrame
{
public:
    BufferFrame()
        :id_(""), page_(-1), pos_(-1)
    {
        isClean_ = 1;
    }
    std::string id() const
    {
        return id_;
    }
    
    int page() const
    {
        return page_;
    }

    int pos() const
    {
        return pos_;
    }
    
    bool isClean()
    {
        return isClean_;
    }


    void fetch(std::string & s, int page, int buffLoc)
    {
        page_ = page;
        pos_ = buffLoc;
        isClean_ = 1;
        for(int i = 0; i < 4; ++i)
        {
            id_[i] = s[(page_ * 4) + i];
            //std::cout << s[page_ + i];
        }
        //std::cout << std::endl << id_ << std::endl;
    }
    
    void writeBuffer(std::string & s)
    {
        for(int i = 0; i < 4; ++i)
        {
            s[(page_ * 4) + i] = id_[i];
        }
    }

    void overwrite(std::string & s)
    {
        isClean_ = 0;
        for (int i = 0; i < 4; ++i)
        {
            id_[i] = s[i];
        }
    }
private:
    char id_[5];
    int page_;
    bool isClean_;
    int pos_;
};

#endif
